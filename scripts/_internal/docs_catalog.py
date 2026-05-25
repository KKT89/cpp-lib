from __future__ import annotations

import posixpath
from collections import defaultdict
from pathlib import Path, PurePosixPath

from .docs_common import read_meta, read_title, write_if_changed
from .project_paths import DOCSRC_LIBRARY, DOCSRC_NOTE, INCLUDE_ROOT

type DocEntry = tuple[str, str]
type GroupedDocEntries = list[tuple[str, list[DocEntry]]]
type SubLibEntry = tuple[str, str, str]  # (title, doc_path, sub_hpp)


def _doc_path_from_header(lib_header: str) -> str:
    return f"library/{PurePosixPath(lib_header).with_suffix('.md').as_posix()}"


def _relative_doc_link(from_doc_path: str, to_doc_path: str) -> str:
    return posixpath.relpath(to_doc_path, start=posixpath.dirname(from_doc_path))


def build_library_sections(
    lib_header: str,
    current_doc_path: str,
    verifies: list[tuple[str, str]],
    sub_libraries: list[SubLibEntry] | None = None,
) -> str:
    """Build managed sections for a top-level library page."""
    lines: list[str] = []

    if sub_libraries:
        lines.extend(["## Sub Libraries", ""])
        for title, doc_path, _ in sub_libraries:
            lines.append(f"- [{title}]({_relative_doc_link(current_doc_path, doc_path)})")
        lines.append("")

    if verifies:
        lines.extend(["## Verify", ""])
        for title, doc_path in verifies:
            lines.append(f"- [{title}](../../verify/{doc_path})")
        lines.append("")

    lines.extend(
        [
            "## Code",
            "",
            f"Source: `{lib_header}`",
            "",
            "```cpp",
            f'--8<-- "include/{lib_header}"',
            "```",
            "",
            "## Bundled",
            "",
            "```cpp",
            f'--8<-- "bundled/{lib_header}"',
            "```",
        ]
    )
    return "\n".join(lines)


def build_sub_library_sections(
    lib_header: str,
    current_doc_path: str,
    parent_hpp: str,
    parent_title: str,
) -> str:
    """Build managed sections for a sub-library page."""
    parent_doc_path = _doc_path_from_header(parent_hpp)
    lines = [
        "## Parent Library",
        "",
        f"- [{parent_title}]({_relative_doc_link(current_doc_path, parent_doc_path)})",
        "",
        "## Code",
        "",
        f"Source: `{lib_header}`",
        "",
        "```cpp",
        f'--8<-- "include/{lib_header}"',
        "```",
        "",
        "## Bundled",
        "",
        "```cpp",
        f'--8<-- "bundled/{lib_header}"',
        "```",
    ]
    return "\n".join(lines)


def strip_managed_library_sections(markdown: str, lib_header: str) -> str:
    """Strip managed Code/Bundled sections from a library page."""
    body = markdown.rstrip()
    for bundled_heading in ("## Bundled", "## Bundled (Copy & Paste)"):
        managed_tail = _managed_library_tail(lib_header, bundled_heading, with_source=True)
        if body.endswith(managed_tail):
            return body[: -len(managed_tail)].rstrip()

        legacy_tail = _managed_library_tail(lib_header, bundled_heading, with_source=False)
        if body.endswith(legacy_tail):
            return body[: -len(legacy_tail)].rstrip()
    return body


def _managed_library_tail(lib_header: str, bundled_heading: str, with_source: bool) -> str:
    code_lines = ["## Code", ""]
    if with_source:
        code_lines.extend([f"Source: `{lib_header}`", ""])
    code_lines.extend(
        [
            "```cpp",
            f'--8<-- "include/{lib_header}"',
            "```",
            "",
            bundled_heading,
            "",
            "```cpp",
            f'--8<-- "bundled/{lib_header}"',
            "```",
        ]
    )
    return "\n".join(code_lines)


def scan_library_docs() -> tuple[
    GroupedDocEntries,
    dict[str, str],
    dict[str, list[SubLibEntry]],
    dict[str, str],
]:
    """Scan docsrc/library/ for .md files.

    Returns:
        groups: top-level library entries grouped by category (sub-libraries excluded)
        titles: hpp path -> title (all libraries including sub-libraries)
        sub_map: parent_hpp -> list of sub-library entries
        parent_of: sub_hpp -> parent_hpp
    """
    groups: dict[str, list[DocEntry]] = defaultdict(list)
    titles: dict[str, str] = {}
    sub_map: dict[str, list[SubLibEntry]] = defaultdict(list)
    parent_of: dict[str, str] = {}

    for md_path in sorted(DOCSRC_LIBRARY.rglob("*.md")):
        if md_path.name == "index.md":
            continue
        rel = md_path.relative_to(DOCSRC_LIBRARY)
        if len(rel.parts) != 2:
            continue

        category_name = rel.parts[0].replace("_", " ").title()
        title = read_title(md_path)
        doc_path = f"library/{rel.as_posix()}"
        hpp_key = rel.with_suffix(".hpp").as_posix()
        titles[hpp_key] = title

        meta = read_meta(md_path)
        parent_hpp = meta.get("parent")
        if parent_hpp and (INCLUDE_ROOT / parent_hpp).exists():
            parent_of[hpp_key] = parent_hpp
            sub_map[parent_hpp].append((title, doc_path, hpp_key))
        else:
            groups[category_name].append((title, doc_path))

    for entries in groups.values():
        entries.sort(key=lambda entry: entry[0].casefold())
    for entries in sub_map.values():
        entries.sort(key=lambda entry: entry[0].casefold())

    return sorted(groups.items()), titles, dict(sub_map), parent_of


def build_library_nav(groups: GroupedDocEntries) -> list:
    nav: list = [{"Library Top": "library/index.md"}]
    for category_name, entries in groups:
        nav.append({category_name: [{title: doc_path} for title, doc_path in entries]})
    return nav


def generate_library_index(
    groups: GroupedDocEntries,
    generator_name: str = "scripts/mkdocs_hooks.py",
) -> None:
    lines = [
        "# Library Top",
        "",
        "ライブラリ実装の一覧ページです。",
        "",
        f"<!-- This file is auto-generated by {generator_name} -->",
        "",
    ]
    for category_name, entries in groups:
        lines.append(f"## {category_name}")
        lines.append("")
        for title, doc_path in entries:
            lines.append(f"- [{title}]({doc_path.removeprefix('library/')})")
        lines.append("")

    write_if_changed(DOCSRC_LIBRARY / "index.md", "\n".join(lines).rstrip() + "\n")


def scan_note_docs() -> list[DocEntry]:
    entries: list[DocEntry] = []
    for md_path in sorted(DOCSRC_NOTE.glob("*.md")):
        if md_path.name == "index.md":
            continue
        entries.append((read_title(md_path), f"note/{md_path.name}"))
    return entries


def build_note_nav(entries: list[DocEntry]) -> list:
    nav: list = [{"Note Top": "note/index.md"}]
    for title, doc_path in entries:
        nav.append({title: doc_path})
    return nav


def generate_note_index(
    entries: list[DocEntry],
    generator_name: str = "scripts/mkdocs_hooks.py",
) -> None:
    lines = [
        "# Note",
        "",
        "いろいろメモ　旧scrapboxに書いてた内容を引っ越し予定",
        "",
        f"<!-- This file is auto-generated by {generator_name} -->",
        "",
    ]
    for title, doc_path in entries:
        lines.append(f"- [{title}]({doc_path.removeprefix('note/')})")
    lines.append("")

    write_if_changed(DOCSRC_NOTE / "index.md", "\n".join(lines).rstrip() + "\n")
