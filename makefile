OBJECTS= main.o draw.o display.o matrix.o
CFLAGS= -Wall
LDFLAGS= -lm
CC= gcc

D-OBJECTS= debug-main.o debug-draw.o debug-display.o debug-matrix.o
D-CFLAGS= -Wall -g


run: main
	./main

main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(LDFLAGS)

main.o: main.c display.h draw.h ml6.h matrix.h
	$(CC) -c main.c

draw.o: draw.c draw.h display.h ml6.h matrix.h
	$(CC) $(CFLAGS) -c draw.c

display.o: display.c display.h ml6.h matrix.h
	$(CC) $(CFLAGS) -c display.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

clean:
	rm *.o *~


debug: debug-main
	valgrind --leak-check=yes --track-origins=yes ./debug-main

debug-main: $(D-OBJECTS)
	$(CC) -g -o debug-main $(D-OBJECTS) $(LDFLAGS)

debug-main.o: main.c display.h draw.h ml6.h matrix.h
	$(CC) -g -c -o debug-main.o main.c

debug-draw.o: draw.c draw.h display.h ml6.h matrix.h
	$(CC) $(D-CFLAGS) -c -o debug-draw.o draw.c

debug-display.o: display.c display.h ml6.h matrix.h
	$(CC) $(D-CFLAGS) -c -o debug-display.o display.c

debug-matrix.o: matrix.c matrix.h
	$(CC) $(D-CFLAGS) -c -o debug-matrix.o matrix.c
