#!/usr/bin/env python3
from __future__ import annotations

import argparse
from pathlib import Path
import re
import sys


INCLUDE_RE = re.compile(r'^\s*#\s*include\s*"([^"]+)"\s*$')
SYSTEM_INCLUDE_RE = re.compile(r"^\s*#\s*include\s*<[^>]+>\s*$")


def resolve_include(
    include: str,
    current_dir: Path,
    include_dirs: list[Path],
) -> Path | None:
    candidates = (
        (d / include).resolve()
        for d in [current_dir, *include_dirs]
    )
    return next((c for c in candidates if c.exists()), None)


def bundle_file(
    path: Path,
    project_root: Path,
    include_dirs: list[Path],
    visited: set[Path],
    out_lines: list[str],
    keep_system_includes: bool = False,
    is_entry: bool = False,
) -> None:
    path = path.resolve()
    if path in visited:
        return
    visited.add(path)

    try:
        rel = path.relative_to(project_root).as_posix()
    except ValueError:
        rel = path.name
    out_lines.append(f"// ---- begin: {rel}")

    for line in path.read_text(encoding="utf-8").splitlines():
        if line.strip() == "#pragma once":
            continue
        # Keep includes written in the entry file (for example bits/stdc++.h),
        # but omit redundant system includes from expanded local headers by default.
        if SYSTEM_INCLUDE_RE.match(line) and not (is_entry or keep_system_includes):
            if out_lines and out_lines[-1] == "":
                out_lines.pop()
            continue
        m = INCLUDE_RE.match(line)
        if m:
            inc = m.group(1)
            inc_path = resolve_include(inc, path.parent, include_dirs)
            if inc_path is None:
                out_lines.append(line)
            else:
                bundle_file(
                    inc_path,
                    project_root,
                    include_dirs,
                    visited,
                    out_lines,
                    keep_system_includes,
                )
            continue
        out_lines.append(line)

    out_lines.append(f"// ---- end: {rel}")


def _bundle_to_string(
    input_path: Path,
    include_dirs: list[Path] | None = None,
    project_root: Path | None = None,
    keep_system_includes: bool = False,
) -> str:
    """Bundle input_path and return the result as a string."""
    script_dir = Path(__file__).resolve().parent
    if project_root is None:
        project_root = script_dir.parent

    if not include_dirs:
        include_dirs = [(project_root / "include").resolve()]
    include_dirs = [d.resolve() for d in include_dirs]

    input_path = input_path.resolve()
    if not input_path.exists():
        raise FileNotFoundError(input_path)

    out_lines: list[str] = []
    out_lines.append("// bundled by scripts/bundle_header.py")
    out_lines.append("")
    bundle_file(
        input_path,
        project_root,
        include_dirs,
        set(),
        out_lines,
        keep_system_includes,
        is_entry=True,
    )
    return "\n".join(out_lines).rstrip() + "\n"


# Public alias
bundle_header_to_string = _bundle_to_string


def bundle_header(
    input_path: Path,
    output_path: Path,
    include_dirs: list[Path] | None = None,
    project_root: Path | None = None,
    keep_system_includes: bool = False,
) -> None:
    out_text = _bundle_to_string(
        input_path,
        include_dirs,
        project_root,
        keep_system_includes,
    )

    output_path.parent.mkdir(parents=True, exist_ok=True)
    # Avoid touching timestamps when generated content is unchanged.
    if output_path.exists():
        current = output_path.read_text(encoding="utf-8")
        if current == out_text:
            return
    output_path.write_text(out_text, encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(description="Bundle C++ header by inlining local includes.")
    parser.add_argument("input", type=Path, help="entry header path")
    parser.add_argument("output", type=Path, help="output bundled header path")
    parser.add_argument(
        "--include-dir",
        action="append",
        type=Path,
        default=[],
        help="additional include directories (repeatable)",
    )
    parser.add_argument(
        "--keep-system-includes",
        action="store_true",
        help="keep system includes from expanded local headers",
    )
    args = parser.parse_args()

    include_dirs = [d.resolve() for d in args.include_dir]
    try:
        bundle_header(
            args.input,
            args.output,
            include_dirs,
            keep_system_includes=args.keep_system_includes,
        )
    except FileNotFoundError:
        print(f"input not found: {args.input}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
