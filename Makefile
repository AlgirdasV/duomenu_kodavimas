OBJS = main.o kunas.o kodas.o matrica.o kanalas.o dekodavimas.o
CC = g++

kodavimas: $(OBJS)
	$(CC) $(OBJS) -o kodavimas
main.o: main.cpp
	$(CC) -g -c main.cpp
kunas.o: kunas.cpp kunas.h
	$(CC) -g -c kunas.cpp
kodas.o: kodas.cpp kodas.h
	$(CC) -g -c kodas.cpp
matrica.o: matrica.cpp matrica.h kunas.h
	$(CC) -g -c matrica.cpp
kanalas.o: kanalas.h kanalas.cpp
	$(CC) -g -c kanalas.cpp
dekodavimas.o: dekodavimas.h dekodavimas.cpp
	$(CC) -g -c dekodavimas.cpp
clean:
	\rm *.o *~ kodavimas