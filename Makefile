# Makefile for SmartRhime IME

# 编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -fPIC
LDFLAGS = -shared -limm32

# 源文件和目标文件
SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = freepy.ime

# 默认目标
all: $(TARGET)

# 创建目标文件目录
$(OBJ_DIR):
    mkdir -p $(OBJ_DIR)

# 编译源文件为目标文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h | $(OBJ_DIR)
    $(CXX) $(CXXFLAGS) -c $< -o $@

# 链接目标文件生成共享库
$(TARGET): $(OBJS)
    $(CXX) $(LDFLAGS) $^ -o $@

# 清理生成的文件
clean:
    rm -rf $(OBJ_DIR) $(TARGET)

# 伪目标
.PHONY: all clean