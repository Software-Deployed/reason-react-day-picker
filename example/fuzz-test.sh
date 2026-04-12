#!/usr/bin/env bash
set -euo pipefail

repo_root="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
cd "$repo_root"

dune build example/fuzz/FuzzTestRunner.exe
dune exec example/fuzz/FuzzTestRunner.exe -- "$@"
