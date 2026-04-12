#!/usr/bin/env bash
set -euo pipefail

repo_root="$(git rev-parse --show-toplevel)"

if [[ -d "$repo_root/_build/default/node_modules" ]]; then
  mv "$repo_root/_build/default/node_modules" "$repo_root/_build/default/node_modules.bak"
  trap 'mv "$repo_root/_build/default/node_modules.bak" "$repo_root/_build/default/node_modules"' EXIT
fi

echo "Bundling DayPickerExample for browser..."
"$repo_root/node_modules/esbuild/bin/esbuild" \
  "$repo_root/_build/default/example/test-browser/dist/example/test-browser/DayPickerExample.mjs" \
  --bundle \
  --outfile="$repo_root/example/test-browser/day-picker-example.bundle.mjs" \
  --format=esm \
  --platform=browser

echo "Running Playwright browser tests..."
node "$repo_root/_build/default/example/test-browser/dist/example/test-browser/DayPickerBrowserTest.mjs"

echo "Browser tests complete."
