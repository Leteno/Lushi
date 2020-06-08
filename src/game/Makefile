
include ../Makefile.common
SFML_FLAGS=-L${SFML_PATH} -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

game:
	echo Hello world !
	$(CC) -c Main.cpp -o Main.o $(CFLAGS)
	$(CC) Main.o -o Main $(CFLAGS) $(SFML_FLAGS)

clean:
	-rm -rf *.o Main