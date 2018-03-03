# Makefile for PLL simulator
# Usage:
# source config
# make

ifndef SYSTEMC_DIR
  $(error SYSTEMC_DIR is undefined. Edit your config file and type "source config")
endif
ifndef SYSTEMC_AMS_DIR
  $(error SYSTEMC_AMS_DIR is undefined. Edit your config file and type "source config")
endif

SYSTEMC_LIB_PATH = $(shell find $(SYSTEMC_DIR) -name "lib*" -type d)
SYSTEMC_AMS_LIB_PATH = $(shell find $(SYSTEMC_AMS_DIR) -name "lib*" -type d)
LDFLAGS=-L$(SYSTEMC_AMS_LIB_PATH) -lsystemc-ams -L$(SYSTEMC_LIB_PATH) -lsystemc
BIN_DIR=./bin/
BUILD_DIR=./build/
SRC_DIR=./src/
CXXFLAGS=-Wno-deprecated -std=c++14 -I./src -I./src/include -I$(SYSTEMC_AMS_DIR)/include -I$(SYSTEMC_DIR)/include -fpermissive -O3
TARGET_EXEC=pll

SRCS = $(shell find $(SRC_DIR) -name "*.cpp" -exec basename {}  \;)
OBJS = $(SRCS:%=$(BUILD_DIR)%.o)

all: dynamic

dynamic: directories $(OBJS)
	@echo "CXX" $(OBJS)
	@$(CXX) $(OBJS) $(LDFLAGS) -o $(BIN_DIR)$(TARGET_EXEC)
	
static: directories $(OBJS)
	@echo "CXX" $(OBJS)
	@$(CXX) $(OBJS) -o $(BIN_DIR)$(TARGET_EXEC) $(SYSTEMC_AMS_LIB_PATH)/libsystemc-ams.a $(SYSTEMC_LIB_PATH)/libsystemc.a

directories: ${BIN_DIR} ${BUILD_DIR}

${BIN_DIR}:
	@mkdir -p ${BIN_DIR}

${BUILD_DIR}:
	@mkdir -p ${BUILD_DIR}

# c++ source
$(BUILD_DIR)%.cpp.o: $(SRC_DIR)%.cpp $(SRC_DIR)%.h
	@echo "CXX" $<
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)%.cpp.o: $(SRC_DIR)%.cpp
	@echo "CXX" $<
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@$(RM) -rf $(BIN_DIR)$(TARGET_EXEC) ${BUILD_DIR}
	@echo "All done"
