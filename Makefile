OBJS = main.o kunas.o kodas.o matrica.o kanalas.o
CC = g++

kodavimas: $(OBJS)
	$(CC) $(OBJS) -o kodavimas
main.o: main.cpp kunas.h kodas.h matrica.h
	$(CC) -g -c main.cpp
kunas.o: kunas.cpp kunas.h
	$(CC) -g -c kunas.cpp
kodas.o: kodas.cpp kodas.h
	$(CC) -g -c kodas.cpp
matrica.o: matrica.cpp matrica.h kunas.h
	$(CC) -g -c matrica.cpp
kanalas.o: kanalas.h kanalas.cpp
	$(CC) -g -c kanalas.cpp
clean:
	\rm *.o *~ kodavimas