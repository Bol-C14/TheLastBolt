#!/bin/bash

set -e

PROJECT_NAME="TheLastBolt"
BUILD_DIR="build-win"
DIST_DIR="win-dist"
TOOLCHAIN_FILE="toolchain-mingw64.cmake"
MINGW_GCC_VERSION="9.3-win32"
DLL_BASE="/usr/lib/gcc/x86_64-w64-mingw32/${MINGW_GCC_VERSION}"
WINPTHREAD_DLL="/usr/x86_64-w64-mingw32/lib/libwinpthread-1.dll"

echo "🧹 清理旧构建..."
rm -rf "$BUILD_DIR" "$DIST_DIR"
mkdir -p "$BUILD_DIR" "$DIST_DIR"

echo "🔨 构建 Windows 可执行文件..."
cmake -B "$BUILD_DIR" -S . -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE" -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR" --config Release

echo "📥 拷贝生成的 .exe 文件..."
cp "$BUILD_DIR/$PROJECT_NAME.exe" "$DIST_DIR/" || {
    echo "❌ 无法找到 $PROJECT_NAME.exe"
    exit 1
}

echo "📦 拷贝必要 DLL 文件..."

function copy_dll() {
    local dll_path="$1"
    local target="$DIST_DIR/$(basename "$dll_path")"
    if [ -f "$dll_path" ]; then
        cp "$dll_path" "$target"
        echo "✅ 复制 $(basename "$dll_path")"
    else
        echo "⚠️ 未找到 $dll_path"
    fi
}

copy_dll "$DLL_BASE/libgcc_s_seh-1.dll"
copy_dll "$DLL_BASE/libstdc++-6.dll"
copy_dll "$WINPTHREAD_DLL"

echo "🎉 打包完成！最终内容位于 $DIST_DIR："
ls -l "$DIST_DIR"

# 可选：使用 Wine 测试
if command -v wine &> /dev/null; then
    echo "🧪 使用 Wine 测试运行："
    wine "$DIST_DIR/$PROJECT_NAME.exe" || echo "⚠️ Wine 执行失败（可忽略）"
fi
