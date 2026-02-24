from __future__ import annotations

import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
INCLUDE_ROOT = ROOT / "include"
BUNDLE_ROOT = ROOT / "bundled"
VERIFY_ROOT = ROOT / "verify"

_SCRIPTS_DIR = str(ROOT / "scripts")
if _SCRIPTS_DIR not in sys.path:
    sys.path.insert(0, _SCRIPTS_DIR)

from bundle_header import bundle_header  # noqa: E402
from sync_library_index import sync_library_index  # noqa: E402


def on_pre_build(config):
    sync_library_index(write=True)

    for path in INCLUDE_ROOT.rglob("*.hpp"):
        rel = path.relative_to(INCLUDE_ROOT)
        out_path = BUNDLE_ROOT / rel
        bundle_header(path, out_path, include_dirs=[INCLUDE_ROOT])
    for path in VERIFY_ROOT.rglob("*.cpp"):
        rel = path.relative_to(ROOT)
        out_path = BUNDLE_ROOT / rel
        bundle_header(path, out_path, include_dirs=[INCLUDE_ROOT, VERIFY_ROOT, ROOT])
