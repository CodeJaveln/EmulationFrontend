TARGET := emufront.out

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:src/%.cpp=build/%.o)

CXX := g++
CXXFLAGS := -Wall -Werror -Iinclude -std=c++23 -MMD -MP
LDFLAGS := -Llibraries -lraylib

$(TARGET): $(OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@ 

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

run:
	./$(TARGET)

clean:
	rm -rf build $(TARGET)
