SYSTEMC=/c/systemc/systemc-2.3.2/
SYSTEMC-AMS=/c/systemc/systemc-ams-2.1/
LDFLAGS=-L$(SYSTEMC-AMS)/lib-mingw-w64 -lsystemc-ams -L$(SYSTEMC)/lib-mingw64 -lsystemc
BIN_DIR=./bin/
BUILD_DIR=./build/
SRC_DIR=./src/
CXXFLAGS=-Wno-deprecated -std=c++14 -I./src -I./src/include -I$(SYSTEMC-AMS)/include -I$(SYSTEMC)/include -fpermissive -O3
TARGET_EXEC=pll

SRCS = $(shell find $(SRC_DIR) -name "*.cpp" -exec basename {}  \;)
OBJS = $(SRCS:%=$(BUILD_DIR)%.o)

#$(info OBJS="$(OBJS)")

all: directories $(BIN_DIR)$(TARGET_EXEC)
directories: ${BIN_DIR} ${BUILD_DIR}
.PHONY: clean

$(BIN_DIR)$(TARGET_EXEC): $(OBJS)
	@echo "CXX" $(OBJS)
	@$(CXX) $(OBJS) $(LDFLAGS) -o $(BIN_DIR)$(TARGET_EXEC)

# c++ source
$(BUILD_DIR)%.cpp.o: $(SRC_DIR)%.cpp $(SRC_DIR)%.h
	@echo "CXX" $<
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)%.cpp.o: $(SRC_DIR)%.cpp
	@echo "CXX" $<
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

${BIN_DIR}:
	@mkdir -p ${BIN_DIR}

${BUILD_DIR}:
	@mkdir -p ${BUILD_DIR}

clean:
	@$(RM) -rf ${BIN_DIR} ${BUILD_DIR}
	@echo "All done"
