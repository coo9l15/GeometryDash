CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/opt/homebrew/include -Isrc/public
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = src
PUBLIC_DIR = $(SRC_DIR)/public
PRIVATE_DIR = $(SRC_DIR)/private
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.cpp $(PRIVATE_DIR)/player_class.cpp $(PRIVATE_DIR)/surface.cpp
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/player_class.o $(OBJ_DIR)/surface.o
TARGET = GeometryDash

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PRIVATE_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

all: $(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run