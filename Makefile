CC = g++
CC_FLAGS = -g

OUTPUT_DIR = exe
CPP_FILES := $(wildcard source/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

$(OUTPUT_DIR)/kodavimas: $(OBJ_FILES)
	$(CC) -o $@ $^
obj/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<
clean:
	\rm obj/*.o exe/kodavimas.exe