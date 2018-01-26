SYSTEMC=/c/systemc/systemc-2.3.2/
SYSTEMC-AMS=/c/systemc/systemc-ams-2.1/
LDFLAGS=-L$(SYSTEMC-AMS)/lib-mingw-w64 -lsystemc-ams -L$(SYSTEMC)/lib-mingw64 -lsystemc

CXXFLAGS=-Wno-deprecated -std=c++14 -I$(SYSTEMC-AMS)/include -I$(SYSTEMC)/include -fpermissive -O3
TARGET_EXEC=pll

SRCS = $(shell find . -name "*.cpp")
OBJS = $(SRCS:%=%.o)

all: $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET_EXEC)

# c++ source
%.cpp.o: %.cpp %.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%.cpp.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	
.PHONY: clean

clean:
	$(RM) -r *.o $(TARGET_EXEC)
