# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -O2

# Raylib flags (adjust paths if needed)
RAYLIB_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Target executable
TARGET = raylib_app

# Source files
SRCS = src/main.cpp

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(RAYLIB_FLAGS)

# Clean up build files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean