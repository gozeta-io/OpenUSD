#!/bin/bash

SCRIPT_ROOT="$(dirname "$(realpath "$0")")"

cd "$SCRIPT_ROOT" || exit 1

BUILD_TARGET="build"
while getopts ":t:" opt; do
  case $opt in
    t) BUILD_TARGET="$OPTARG"
    ;;
    \?) echo "Invalid option -$OPTARG" >&2
    ;;
  esac
done

if [ "$BUILD_TARGET" == "emscripten" ]; then
  python3 ./build_scripts/build_usd.py --emscripten -vv \
      --build-variant release \
      --build ./build-wasm/USD-Build \
      --src ./build-wasm/USD-Deps \
      build-wasm/USD-Dist
else
  python3 ./build_scripts/build_usd.py --no-materialx -vv \
      --build-variant debug \
      --build ./build-linux/USD-Build \
      --src ./build-linux/USD-Deps \
      build-linux/USD-Dist
fi
