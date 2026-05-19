from __future__ import annotations

import sys
from dataclasses import dataclass, field
from pathlib import Path

SCRIPTS_DIR = Path(__file__).resolve().parent
if str(SCRIPTS_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPTS_DIR))

from bundle_header import bundle_header  # noqa: E402
from _internal.docs_catalog import (  # noqa: E402
    GroupedDocEntries,
    build_library_nav,
    build_library_sections,
    build_note_nav,
    generate_library_index,
    generate_note_index,
    scan_library_docs,
    scan_note_docs,
    strip_managed_library_sections,
)
from _internal.project_paths import BUNDLE_ROOT, INCLUDE_ROOT, ROOT, VERIFY_ROOT  # noqa: E402
from _internal.verify_data import load_status, stale_status_entries, unverified_files  # noqa: E402
from _internal.verify_docs import (  # noqa: E402
    build_verify_map,
    build_verify_nav,
    generate_verify_index,
    generate_verify_pages,
)


@dataclass
class HookState:
    library_groups: GroupedDocEntries = field(default_factory=list)
    library_titles: dict[str, str] = field(default_factory=dict)
    note_entries: list[tuple[str, str]] = field(default_factory=list)
    verify_map: dict[str, list[tuple[str, str]]] = field(default_factory=dict)

STATE = HookState()


def _replace_nav_section(config, section_name: str, section_nav: list) -> None:
    for item in config["nav"]:
        if isinstance(item, dict) and section_name in item:
            item[section_name] = section_nav
            return


def _refresh_doc_state() -> None:
    STATE.library_groups, STATE.library_titles = scan_library_docs()
    STATE.note_entries = scan_note_docs()


def _refresh_nav(config, status: dict) -> None:
    _replace_nav_section(config, "Library", build_library_nav(STATE.library_groups))
    _replace_nav_section(config, "Note", build_note_nav(STATE.note_entries))
    if status:
        _replace_nav_section(config, "Verify", build_verify_nav(status))


def _bundle_generated_sources() -> None:
    for path in INCLUDE_ROOT.rglob("*.hpp"):
        bundle_header(path, BUNDLE_ROOT / path.relative_to(INCLUDE_ROOT), include_dirs=[INCLUDE_ROOT])
    for path in VERIFY_ROOT.rglob("*.cpp"):
        bundle_header(
            path,
            BUNDLE_ROOT / path.relative_to(ROOT),
            include_dirs=[INCLUDE_ROOT, VERIFY_ROOT, ROOT],
        )


def _report_verify_status(status: dict) -> None:
    stale = stale_status_entries(status)
    unverified = unverified_files(status)

    if not stale and not unverified:
        return

    if stale:
        print("[verify] stale verify detected:", file=sys.stderr)
        for key, verified_at in stale:
            suffix = f" (last verified: {verified_at})" if verified_at else ""
            print(f"[verify]   - {key}{suffix}", file=sys.stderr)

    if unverified:
        print("[verify] unverified verify detected:", file=sys.stderr)
        for key in unverified:
            print(f"[verify]   - {key}", file=sys.stderr)


def on_config(config):
    _refresh_doc_state()
    _refresh_nav(config, load_status())
    return config


def on_pre_build(config):
    _refresh_doc_state()
    status = load_status()
    _refresh_nav(config, status)
    _report_verify_status(status)

    generate_library_index(STATE.library_groups)
    generate_note_index(STATE.note_entries)
    _bundle_generated_sources()
    generate_verify_pages(status, STATE.library_titles)
    generate_verify_index(status)
    STATE.verify_map = build_verify_map(status)


def on_page_markdown(markdown, page, config, files):
    src_path = page.file.src_path
    if not src_path.startswith("library/"):
        return markdown

    lib_header = src_path.removeprefix("library/").replace(".md", ".hpp")
    if not (INCLUDE_ROOT / lib_header).exists():
        return markdown

    body = strip_managed_library_sections(markdown, lib_header)
    sections = build_library_sections(lib_header, STATE.verify_map.get(lib_header, []))
    return body.rstrip() + "\n\n" + sections + "\n"
