#!/usr/bin/env python3
from __future__ import annotations

import argparse
from pathlib import Path
import re
import sys


INCLUDE_RE = re.compile(r'^\s*#\s*include\s*"([^"]+)"\s*$')


def resolve_include(
    include: str,
    current_dir: Path,
    include_dirs: list[Path],
) -> Path | None:
    cand = (current_dir / include).resolve()
    if cand.exists():
        return cand
    for inc in include_dirs:
        cand = (inc / include).resolve()
        if cand.exists():
            return cand
    return None


def bundle_file(
    path: Path,
    project_root: Path,
    include_dirs: list[Path],
    visited: set[Path],
    out_lines: list[str],
) -> None:
    path = path.resolve()
    if path in visited:
        return
    visited.add(path)

    rel = path.relative_to(project_root).as_posix()
    out_lines.append(f"// ---- begin: {rel}")

    for line in path.read_text(encoding="utf-8").splitlines():
        if line.strip() == "#pragma once":
            continue
        m = INCLUDE_RE.match(line)
        if m:
            inc = m.group(1)
            inc_path = resolve_include(inc, path.parent, include_dirs)
            if inc_path is None:
                out_lines.append(line)
            else:
                bundle_file(inc_path, project_root, include_dirs, visited, out_lines)
            continue
        out_lines.append(line)

    out_lines.append(f"// ---- end: {rel}")


def bundle_header(input_path: Path, output_path: Path, include_dirs: list[Path] | None = None) -> None:
    script_dir = Path(__file__).resolve().parent
    project_root = script_dir.parent

    if include_dirs is None or not include_dirs:
        include_dirs = [(project_root / "include").resolve()]
    include_dirs = [d.resolve() for d in include_dirs]

    input_path = input_path.resolve()
    if not input_path.exists():
        raise FileNotFoundError(input_path)

    out_lines: list[str] = []
    out_lines.append("// bundled by scripts/bundle_header.py")
    out_lines.append("")
    bundle_file(input_path, project_root, include_dirs, set(), out_lines)
    out_text = "\n".join(out_lines).rstrip() + "\n"

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
    args = parser.parse_args()

    include_dirs = [d.resolve() for d in args.include_dir]
    try:
        bundle_header(args.input, args.output, include_dirs)
    except FileNotFoundError:
        print(f"input not found: {args.input}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
