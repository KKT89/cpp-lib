#!/usr/bin/env python3
"""Bundle main.cpp with cpp-lib headers into a single submission file."""
from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

from bundle_header import bundle_header

LIB_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_INCLUDE_DIR = LIB_ROOT / "include"


def copy_to_clipboard(text: str) -> bool:
    """Try to copy text to clipboard. Returns True on success."""
    commands = [
        (["clip.exe"], "utf-16le"),                        # WSL2 / Windows
        (["xclip", "-selection", "clipboard"], "utf-8"),   # Linux X11
        (["xsel", "--clipboard", "--input"], "utf-8"),     # Linux X11
        (["wl-copy"], "utf-8"),                            # Wayland
        (["pbcopy"], "utf-8"),                             # macOS
    ]
    for cmd, encoding in commands:
        try:
            subprocess.run(
                cmd,
                input=text.encode(encoding),
                check=True,
                capture_output=True,
            )
            return True
        except (FileNotFoundError, subprocess.CalledProcessError):
            continue
    return False


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Bundle main.cpp with cpp-lib headers for submission."
    )
    parser.add_argument(
        "input",
        nargs="?",
        type=Path,
        default=Path("main.cpp"),
        help="entry .cpp file (default: main.cpp)",
    )
    parser.add_argument(
        "-o", "--output",
        type=Path,
        default=Path("submit.cpp"),
        help="output bundled file (default: submit.cpp)",
    )
    parser.add_argument(
        "--no-clipboard",
        action="store_true",
        help="skip copying result to clipboard",
    )
    parser.add_argument(
        "--include-dir",
        action="append",
        type=Path,
        default=[],
        help="additional include directories (repeatable)",
    )
    args = parser.parse_args()

    include_dirs: list[Path] = [DEFAULT_INCLUDE_DIR, *args.include_dir]

    try:
        bundle_header(args.input, args.output, include_dirs=include_dirs)
    except FileNotFoundError as e:
        print(f"input not found: {e}", file=sys.stderr)
        return 1

    print(f"Bundled: {args.input} -> {args.output}")

    if not args.no_clipboard:
        text = args.output.read_text(encoding="utf-8")
        if copy_to_clipboard(text):
            print("Copied to clipboard.")
        else:
            print("(clipboard unavailable)", file=sys.stderr)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
