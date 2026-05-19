#!/usr/bin/env python3
"""Manage verify source registration and staleness for cpp-lib."""
from __future__ import annotations

import argparse
import shutil
import sys
from pathlib import Path

from _internal.project_paths import ROOT, VERIFY_ROOT
from _internal.verify_data import (
    compute_hash,
    current_timestamp,
    derive_title,
    discover_verify_files,
    load_status,
    parse_judge_dir,
    save_status,
    slugify_title,
    to_status_key,
)


def _resolve_verify_args(paths: list[Path]) -> list[Path]:
    return [path.resolve() for path in paths]


def cmd_check(args: argparse.Namespace) -> int:
    status = load_status()
    files = _resolve_verify_args(list(args.verify)) if args.verify else discover_verify_files()

    ok = stale = unverified = 0
    for path in files:
        key = to_status_key(path)
        current_hash = compute_hash(path)
        entry = status.get(key)

        if entry is None:
            print(f"  {key}  UNVERIFIED")
            unverified += 1
        elif entry["bundled_hash"] != current_hash:
            date = entry.get("verified_at", "?")
            print(f"  {key}  STALE  (last verified: {date})")
            stale += 1
        else:
            print(f"  {key}  OK")
            ok += 1

    print(f"\n  {ok} ok, {stale} stale, {unverified} unverified")
    return 0 if (stale == 0 and unverified == 0) else 1


def cmd_add(args: argparse.Namespace) -> int:
    src = Path(args.cpp).resolve()
    if not src.exists():
        print(f"file not found: {src}", file=sys.stderr)
        return 1

    try:
        judge_dir = parse_judge_dir(args.url)
    except ValueError as exc:
        print(str(exc), file=sys.stderr)
        return 1

    filename = slugify_title(args.title)
    dest = VERIFY_ROOT / judge_dir / f"{filename}.cpp"

    dest.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(src, dest)
    print(f"  copied: {src.name} -> {dest.relative_to(ROOT)}")

    status = load_status()
    key = to_status_key(dest)
    now = current_timestamp()

    entry = status.get(key, {})
    entry["bundled_hash"] = compute_hash(dest)
    entry["verified_at"] = now
    entry["judge_url"] = args.url
    entry["title"] = args.title
    status[key] = entry

    save_status(status)
    print(f"  registered: {key}")
    return 0


def cmd_mark(args: argparse.Namespace) -> int:
    status = load_status()
    files = discover_verify_files() if args.all else _resolve_verify_args(list(args.verify_files))

    if not files:
        print("No verify files specified. Use --all or pass file paths.", file=sys.stderr)
        return 1

    judge_url = getattr(args, "judge_url", None)
    now = current_timestamp()
    marked = 0
    for path in files:
        key = to_status_key(path)
        current_hash = compute_hash(path)
        entry = status.get(key, {})

        # Skip already-OK entries
        if entry.get("bundled_hash") == current_hash:
            print(f"  skip (OK): {key}")
            continue

        entry["bundled_hash"] = current_hash
        entry["verified_at"] = now
        if judge_url:
            entry["judge_url"] = judge_url
        entry.setdefault("title", derive_title(path))
        status[key] = entry
        print(f"  marked: {key}")
        marked += 1

    if marked:
        save_status(status)
    print(f"\n  {marked} marked, {len(files) - marked} skipped")
    return 0


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="Manage verify status")
    sub = parser.add_subparsers(dest="command", required=True)

    p_check = sub.add_parser("check", help="check staleness of verify codes")
    p_check.add_argument("verify", nargs="*", type=Path, help="specific verify files (default: all)")

    p_add = sub.add_parser("add", help="add a new verify code")
    p_add.add_argument("cpp", type=Path, help="source .cpp file")
    p_add.add_argument("--url", required=True, help="judge problem URL")
    p_add.add_argument("--title", required=True, help="display title")

    p_mark = sub.add_parser("mark", help="mark verify code as verified")
    p_mark.add_argument("verify_files", nargs="*", type=Path, help="verify files to mark")
    p_mark.add_argument("--all", action="store_true", help="mark all verify files")
    p_mark.add_argument("--judge-url", type=str, help="URL of the judge problem")
    return parser


def main() -> int:
    args = build_parser().parse_args()

    if args.command == "check":
        return cmd_check(args)
    elif args.command == "add":
        return cmd_add(args)
    elif args.command == "mark":
        return cmd_mark(args)
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
