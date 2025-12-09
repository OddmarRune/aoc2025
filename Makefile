CXX      := g++
CXXFLAGS := -O2 -std=c++17
INC      := -I./include
LIBS     :=
RPATH    :=
SRC_DIR  := src
BIN_DIR  := bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
BIN_FILES := $(patsubst $(SRC_DIR)/%.cpp,%,$(SRC_FILES))

all: $(BIN_FILES)

clean:
	rm -f $(BIN_DIR)/*

%: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) $< -o $(BIN_DIR)/$@ $(LIBS) $(RPATH)


