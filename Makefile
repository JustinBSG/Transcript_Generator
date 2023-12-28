# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra

# Directories
CORE_DIR := Core
BUILD_DIR := $(CORE_DIR)/Build
INC_DIR := $(CORE_DIR)/Inc
SRC_DIR := $(CORE_DIR)/Src

# Source files
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES))

# Executable
TARGET := $(BUILD_DIR)/Transcript_generator.exe

# Default rule
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)