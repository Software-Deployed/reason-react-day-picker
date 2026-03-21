#!/usr/bin/env bash
set -euo pipefail

repo_root="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
cd "$repo_root"

if [[ ! -d node_modules/react || ! -d node_modules/react-dom || ! -d node_modules/react-day-picker ]]; then
  printf 'Install npm runtime deps first: npm install react react-dom react-day-picker\n' >&2
  exit 1
fi

scenarios=(
  default
  outside-hidden
  multi-months
  reverse-months
  nav-after
  disable-navigation
  hide-navigation
  fixed-weeks
  animate
  caption-dropdown
  caption-dropdown-months
  caption-dropdown-years
  reverse-years
  paged-navigation
)

if [[ $# -gt 0 ]]; then
  scenarios=("$@")
fi

tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT

dune build -j1 @example/js/melange example/native/NativeRenderer.exe

for scenario in "${scenarios[@]}"; do
  node "_build/default/example/js/render/example/js/JsRenderer.re.js" "$scenario" > "$tmpdir/js.txt"
  dune exec ./example/native/NativeRenderer.exe -- "$scenario" > "$tmpdir/native.txt"
  if ! diff -u "$tmpdir/native.txt" "$tmpdir/js.txt"; then
    printf 'Parity failed for scenario: %s\n' "$scenario" >&2
    exit 1
  fi
  printf 'ok %s\n' "$scenario"
done

printf 'All parity scenarios matched.\n'
