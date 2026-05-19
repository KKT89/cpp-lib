from __future__ import annotations

import hashlib
import json
import re
from datetime import datetime, timezone
from pathlib import Path

from bundle_header import bundle_header_to_string
from .project_paths import INCLUDE_ROOT, JUDGES_PATH, ROOT, STATUS_PATH, VERIFY_ROOT

_INCLUDE_RE = re.compile(r'^\s*#\s*include\s*"([^"]+)"\s*$')


def current_timestamp() -> str:
    return datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds")


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
    libs: list[str] = []
    for line in verify_path.read_text(encoding="utf-8").splitlines():
        match = _INCLUDE_RE.match(line)
        if match and (INCLUDE_ROOT / match.group(1)).exists():
            libs.append(match.group(1))
    return libs


def derive_title(verify_path: Path) -> str:
    return verify_path.stem.replace("_", " ").title()


def load_judge_patterns() -> list[tuple[re.Pattern, str]]:
    if not JUDGES_PATH.exists():
        return []
    judges = json.loads(JUDGES_PATH.read_text(encoding="utf-8"))
    return [(re.compile(cfg["url_pattern"]), judge_dir) for judge_dir, cfg in judges.items()]


def parse_judge_dir(url: str) -> str:
    for pattern, judge_dir in load_judge_patterns():
        if pattern.match(url):
            return judge_dir
    raise ValueError(f"Unknown judge URL: {url}")


def slugify_title(title: str) -> str:
    return re.sub(r"[^a-z0-9]+", "_", title.lower()).strip("_")


def to_status_key(path: Path) -> str:
    return str(path.relative_to(ROOT))


def stale_status_entries(status: dict) -> list[tuple[str, str]]:
    entries: list[tuple[str, str]] = []
    for path in discover_verify_files():
        key = to_status_key(path)
        entry = status.get(key)
        if entry is None:
            continue
        if entry.get("bundled_hash") != compute_hash(path):
            entries.append((key, entry.get("verified_at", "")[:10]))
    return entries


def unverified_files(status: dict) -> list[str]:
    files: list[str] = []
    for path in discover_verify_files():
        key = to_status_key(path)
        if key not in status:
            files.append(key)
    return files
