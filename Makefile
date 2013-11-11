#VPATH = source
#OBJS = main.o kunas.o kodas.o matrica.o kanalas.o dekodavimas.o pagalbines_funkcijos.o
CC = g++
CC_FLAGS = -g
#SRC = main.cpp kunas.cpp kodas.cpp matrica.cpp kanalas.cpp dekodavimas.cpp pagalbines_funkcijos.cpp
OUTPUT_DIR = exe
CPP_FILES := $(wildcard source/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

$(OUTPUT_DIR)/kodavimas: $(OBJ_FILES)
	$(CC) -o $@ $^
#$(CC) $(OBJS) -o kodavimas
obj/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<
#main.o: $(VPATH)/main.cpp
#	$(CC) -g -c $(VPATH)/main.cpp
#kunas.o: $(VPATH)/kunas.cpp kunas.h
#	$(CC) -g -c $(VPATH)/kunas.cpp
#kodas.o: $(VPATH)/kodas.cpp kodas.h
#	$(CC) -g -c $(VPATH)/kodas.cpp
#matrica.o: $(VPATH)/matrica.cpp matrica.h kunas.h
#	$(CC) -g -c $(VPATH)/matrica.cpp
#kanalas.o: kanalas.h $(VPATH)/kanalas.cpp
#	$(CC) -g -c $(VPATH)/kanalas.cpp
#dekodavimas.o: dekodavimas.h $(VPATH)/dekodavimas.cpp
#	$(CC) -g -c $(VPATH)/dekodavimas.cpp
#pagalbines_funkcijos.o: pagalbines_funkcijos.h $(VPATH)/pagalbines_funkcijos.cpp
#	$(CC) -g -c $(VPATH)/pagalbines_funkcijos.cpp
clean:
	\rm obj/*.o exe/kodavimas.exe