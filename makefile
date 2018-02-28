OBJECTS= main.o draw.o display.o matrix.o
CFLAGS= -Wall -g
LDFLAGS= -lm
CC= gcc

main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(LDFLAGS)

main.o: main.c display.h draw.h ml6.h matrix.h
	$(CC) -g -c main.c

draw.o: draw.c draw.h display.h ml6.h matrix.h
	$(CC) $(CFLAGS) -c draw.c

dsiplay.o: display.c display.h ml6.h matrix.h
	$(CC) $(CFLAGS) -c display.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

run: main
	./main
clean:
	rm *.o *~


debug: main
	valgrind --leak-check=yes --track-origins=yes ./main
