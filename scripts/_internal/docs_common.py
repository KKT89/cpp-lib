from __future__ import annotations

from pathlib import Path


def read_meta(md_path: Path) -> dict[str, str]:
    """Read YAML-style frontmatter (simple key: value pairs) from a markdown file."""
    meta: dict[str, str] = {}
    lines = md_path.read_text(encoding="utf-8").splitlines()
    if not lines or lines[0].strip() != "---":
        return meta
    for line in lines[1:]:
        if line.strip() == "---":
            break
        if ":" not in line:
            continue
        key, _, value = line.partition(":")
        meta[key.strip()] = value.strip()
    return meta


def _strip_frontmatter(lines: list[str]) -> list[str]:
    if not lines or lines[0].strip() != "---":
        return lines
    for idx in range(1, len(lines)):
        if lines[idx].strip() == "---":
            return lines[idx + 1 :]
    return lines


def read_title(md_path: Path) -> str:
    """Read title from first # heading, falling back to stem-based title."""
    title = md_path.stem.replace("_", " ").title()
    lines = _strip_frontmatter(md_path.read_text(encoding="utf-8").splitlines())
    for line in lines:
        if line.startswith("# "):
            return line[2:].strip()
    return title


def write_if_changed(path: Path, text: str) -> None:
    if path.exists() and path.read_text(encoding="utf-8") == text:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
