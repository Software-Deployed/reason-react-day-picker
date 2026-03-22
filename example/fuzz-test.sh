#!/usr/bin/env bash
set -euo pipefail

repo_root="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
cd "$repo_root"

count=${1:-30}

echo "Running $count fuzz tests..."

dune build example/fuzz/FuzzTestRunner.exe
dune exec example/fuzz/FuzzTestRunner.exe
