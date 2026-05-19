from __future__ import annotations

from pathlib import Path


def read_title(md_path: Path) -> str:
    """Read title from first # heading, falling back to stem-based title."""
    title = md_path.stem.replace("_", " ").title()
    for line in md_path.read_text(encoding="utf-8").splitlines():
        if line.startswith("# "):
            return line[2:].strip()
    return title


def write_if_changed(path: Path, text: str) -> None:
    if path.exists() and path.read_text(encoding="utf-8") == text:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
