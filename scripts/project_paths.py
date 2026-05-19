from __future__ import annotations

from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SCRIPTS_ROOT = ROOT / "scripts"
INCLUDE_ROOT = ROOT / "include"
BUNDLE_ROOT = ROOT / "bundled"
VERIFY_ROOT = ROOT / "verify"
DOCSRC = ROOT / "docsrc"
DOCSRC_LIBRARY = DOCSRC / "library"
DOCSRC_NOTE = DOCSRC / "note"
STATUS_PATH = VERIFY_ROOT / "status.json"
JUDGES_PATH = VERIFY_ROOT / "judges.json"
