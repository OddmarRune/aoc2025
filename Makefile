CXX      := g++
CXXFLAGS := -O2 -std=c++17
LIBS     :=
RPATH    :=
SRC_DIR  := src
BIN_DIR  := bin
INC_DIR  := include
INC      := -I./$(INC_DIR)

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
BIN_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(SRC_FILES))

.PHONY: all clean

all: $(BIN_FILES)

$(BIN_DIR):
	mkdir -p $@

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp $(INC_DIR)/helpers.h | $(BIN_DIR) 
	$(CXX) $(CXXFLAGS) $(INC) $< -o $@ $(LIBS) $(RPATH)

clean:
	rm -rf $(BIN_DIR)

