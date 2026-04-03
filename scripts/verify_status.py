#!/usr/bin/env python3
"""Verify staleness detection for cpp-lib."""
from __future__ import annotations

import argparse
import hashlib
import json
import sys
from datetime import datetime, timezone
from pathlib import Path

import re

from bundle_header import bundle_header_to_string

ROOT = Path(__file__).resolve().parents[1]
INCLUDE_ROOT = ROOT / "include"
VERIFY_ROOT = ROOT / "verify"
STATUS_PATH = VERIFY_ROOT / "status.json"

_INCLUDE_RE = re.compile(r'^\s*#\s*include\s*"([^"]+)"\s*$')

JUDGES_PATH = VERIFY_ROOT / "judges.json"


def compute_hash(verify_path: Path) -> str:
    include_dirs = [INCLUDE_ROOT.resolve(), VERIFY_ROOT.resolve(), ROOT.resolve()]
    text = bundle_header_to_string(verify_path, include_dirs, ROOT)
    return "sha256:" + hashlib.sha256(text.encode("utf-8")).hexdigest()


def load_status() -> dict:
    if STATUS_PATH.exists():
        return json.loads(STATUS_PATH.read_text(encoding="utf-8"))
    return {}


def save_status(status: dict) -> None:
    STATUS_PATH.write_text(
        json.dumps(status, indent=2, ensure_ascii=False) + "\n",
        encoding="utf-8",
    )


def discover_verify_files() -> list[Path]:
    return sorted(VERIFY_ROOT.rglob("*.cpp"))


def detect_libraries(verify_path: Path) -> list[str]:
    """Parse verify .cpp to find library headers it includes."""
    libs: list[str] = []
    for line in verify_path.read_text(encoding="utf-8").splitlines():
        m = _INCLUDE_RE.match(line)
        if m and (INCLUDE_ROOT / m.group(1)).exists():
            libs.append(m.group(1))
    return libs


def derive_title(verify_path: Path) -> str:
    """Derive display title from verify file path."""
    # verify/library_checker/lowest_common_ancestor.cpp → "Lowest Common Ancestor"
    return verify_path.stem.replace("_", " ").title()


def cmd_check(args: argparse.Namespace) -> int:
    status = load_status()
    files = [Path(p) for p in args.verify] if args.verify else discover_verify_files()

    ok = stale = unverified = 0
    for path in files:
        key = str(path.relative_to(ROOT))
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


def load_judge_patterns() -> list[tuple[re.Pattern, str]]:
    """Load judge URL patterns from verify/judges.json."""
    if not JUDGES_PATH.exists():
        return []
    judges = json.loads(JUDGES_PATH.read_text(encoding="utf-8"))
    return [
        (re.compile(cfg["url_pattern"]), judge_dir)
        for judge_dir, cfg in judges.items()
    ]


def parse_judge_dir(url: str) -> str:
    """Parse judge URL → judge_dir."""
    for pattern, judge_dir in load_judge_patterns():
        if pattern.match(url):
            return judge_dir
    raise ValueError(f"Unknown judge URL: {url}")


def cmd_add(args: argparse.Namespace) -> int:
    src = Path(args.cpp).resolve()
    if not src.exists():
        print(f"file not found: {src}", file=sys.stderr)
        return 1

    judge_dir = parse_judge_dir(args.url)
    filename = re.sub(r'[^a-z0-9]+', '_', args.title.lower()).strip('_')
    dest = VERIFY_ROOT / judge_dir / f"{filename}.cpp"

    dest.parent.mkdir(parents=True, exist_ok=True)
    import shutil
    shutil.copy2(src, dest)
    print(f"  copied: {src.name} -> {dest.relative_to(ROOT)}")

    status = load_status()
    key = str(dest.relative_to(ROOT))
    current_hash = compute_hash(dest)
    now = datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds")

    entry = status.get(key, {})
    entry["bundled_hash"] = current_hash
    entry["verified_at"] = now
    entry["judge_url"] = args.url
    entry["title"] = args.title
    status[key] = entry

    save_status(status)
    print(f"  registered: {key}")
    return 0


def cmd_mark(args: argparse.Namespace) -> int:
    status = load_status()
    files = discover_verify_files() if args.all else [Path(p) for p in args.verify_files]

    if not files:
        print("No verify files specified. Use --all or pass file paths.", file=sys.stderr)
        return 1

    judge_url = getattr(args, "judge_url", None)
    now = datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds")
    marked = 0
    for path in files:
        key = str(path.relative_to(ROOT))
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


def main() -> int:
    parser = argparse.ArgumentParser(description="Verify staleness detection")
    sub = parser.add_subparsers(dest="command", required=True)

    p_check = sub.add_parser("check", help="Check staleness of verify codes")
    p_check.add_argument("verify", nargs="*", type=Path, help="specific verify files (default: all)")

    p_add = sub.add_parser("add", help="Add a new verify code")
    p_add.add_argument("cpp", type=Path, help="source .cpp file")
    p_add.add_argument("--url", required=True, help="judge problem URL")
    p_add.add_argument("--title", required=True, help="display title")

    p_mark = sub.add_parser("mark", help="Mark verify code as verified")
    p_mark.add_argument("verify_files", nargs="*", type=Path, help="verify files to mark")
    p_mark.add_argument("--all", action="store_true", help="mark all verify files")
    p_mark.add_argument("--judge-url", type=str, help="URL of the judge problem")

    args = parser.parse_args()

    if args.command == "check":
        return cmd_check(args)
    elif args.command == "add":
        return cmd_add(args)
    elif args.command == "mark":
        return cmd_mark(args)
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
