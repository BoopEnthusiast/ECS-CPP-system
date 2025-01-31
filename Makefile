CXX = g++
CXXFLAGS = -std=c++17 -O2 -g

LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -Iinclude

BIN_DIR = ./bin
TARGET = main
SOURCES = main.cpp glad.c opengl.cpp vulkan.cpp renderer.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TARGET) $(SOURCES) $(LDFLAGS)

.PHONY: test clean

test: $(TARGET)
	$(BIN_DIR)/$(TARGET)

clean:
	rm -f $(BIN_DIR)/$(TARGET)