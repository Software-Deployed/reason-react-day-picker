#!/usr/bin/env bash
set -euo pipefail

repo_root="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
cd "$repo_root"

if [[ ! -d node_modules/react || ! -d node_modules/react-dom || ! -d node_modules/react-day-picker ]]; then
  printf 'Install npm runtime deps first: npm install react react-dom react-day-picker\n' >&2
  exit 1
fi

scenarios=(
  range-same-day
  range-multi-day
  range-start-only
  range-end-only
)

if [[ $# -gt 0 ]]; then
  scenarios=("$@")
fi

tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT

dune build -j1 @example/js/melange example/native/RangeNativeRenderer.exe
dune exec ./example/native/test/RangeNativeTest.exe

for scenario in "${scenarios[@]}"; do
  node "_build/default/example/js/render/example/js/RangeJsRenderer.re.js" "$scenario" > "$tmpdir/js.txt"
  dune exec ./example/native/RangeNativeRenderer.exe -- "$scenario" > "$tmpdir/native.txt"
  if ! diff -u "$tmpdir/native.txt" "$tmpdir/js.txt"; then
    printf 'Range parity failed for scenario: %s\n' "$scenario" >&2
    exit 1
  fi
  printf 'ok %s\n' "$scenario"
done

printf 'All range parity scenarios matched.\n'
