# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra -I Core/Inc

# Directories
SRCDIR := Core/Src
INCDIR := Core/Inc
BUILDDIR := Core/Build

# Source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
# Object files
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Name of the final executable
TARGET := myprogram

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/*.o $(TARGET)