from __future__ import annotations

import importlib.util
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
INCLUDE_ROOT = ROOT / "include"
BUNDLE_ROOT = ROOT / "bundled"
VERIFY_ROOT = ROOT / "verify"
BUNDLE_SCRIPT = ROOT / "scripts" / "bundle_header.py"
SYNC_SCRIPT = ROOT / "scripts" / "sync_library_index.py"


def _load_bundler():
    spec = importlib.util.spec_from_file_location("bundle_header", BUNDLE_SCRIPT)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"failed to load: {BUNDLE_SCRIPT}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.bundle_header


def _load_library_index_syncer():
    spec = importlib.util.spec_from_file_location("sync_library_index", SYNC_SCRIPT)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"failed to load: {SYNC_SCRIPT}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.sync_library_index


def on_pre_build(config):
    sync_library_index = _load_library_index_syncer()
    sync_library_index(write=True)

    bundle_header = _load_bundler()
    for path in INCLUDE_ROOT.rglob("*.hpp"):
        rel = path.relative_to(INCLUDE_ROOT)
        out_path = BUNDLE_ROOT / rel
        bundle_header(path, out_path, include_dirs=[INCLUDE_ROOT])
    for path in VERIFY_ROOT.rglob("*.test.cpp"):
        rel = path.relative_to(ROOT)
        out_path = BUNDLE_ROOT / rel
        bundle_header(path, out_path, include_dirs=[INCLUDE_ROOT, VERIFY_ROOT, ROOT])
