# ───────────────────────────────────────────────────────
# 项目根目录下的 Makefile —— 可一键编译 / 清理 / 重建
# ───────────────────────────────────────────────────────

# 编译器与选项
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS   :=                # 链接器选项（如 -Llib）
LDLIBS    :=                # 链接库（如 -ljson -lwhatever）

# 目录
SRC_DIR   := src
OBJ_DIR   := build
BIN_DIR   := bin

# 目标可执行文件名称
TARGET    := $(BIN_DIR)/StrongAtEnd

# 自动收集所有 src/*.cpp
SOURCES   := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS   := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# ───────────────────────────────────────────────────────
# 默认目标：编译并生成可执行文件
.PHONY: all
all: $(TARGET)

# 链接可执行文件
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "==> Build complete: $@"

# 编译源文件到对象文件
# 支持多级目录，只要在 SRC_DIR 下的 .cpp 都能编译
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled: $<"

# ───────────────────────────────────────────────────────
# 清理目标：删除所有编译产物
.PHONY: clean
clean:
	@echo "Cleaning build and bin directories..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete."

# 重建目标：先 clean 再 all
.PHONY: rebuild
rebuild: clean all

# ───────────────────────────────────────────────────────
# 可选：运行（假设 TARGET 支持命令行参数）
.PHONY: run
run: all
	@echo "Running $(TARGET)..."
	@$(TARGET)

# ───────────────────────────────────────────────────────
# 额外：显示变量值，便于调试 Makefile
.PHONY: info
info:
	@echo "CXX       = $(CXX)"
	@echo "CXXFLAGS  = $(CXXFLAGS)"
	@echo "LDFLAGS   = $(LDFLAGS)"
	@echo "LDLIBS    = $(LDLIBS)"
	@echo "SRC_DIR   = $(SRC_DIR)"
	@echo "OBJ_DIR   = $(OBJ_DIR)"
	@echo "BIN_DIR   = $(BIN_DIR)"
	@echo "SOURCES   = $(SOURCES)"
	@echo "OBJECTS   = $(OBJECTS)"
	@echo "TARGET    = $(TARGET)"

# ───────────────────────────────────────────────────────
# 说明：
# 1. 如需添加新的源文件目录，只需将 SRC_DIR 修改为包含多级路径，
#    或在 SOURCES 中追加 wildcard($(OTHER_DIR)/*.cpp)。
# 2. 若需要链接第三方库，设置 LDFLAGS 和 LDLIBS 即可。
# 3. 运行 `make` 即可编译，`make clean` 清理，`make rebuild` 重建，`make run` 编译并运行。
