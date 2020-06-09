
include ../Makefile.common
SFML_FLAGS=-L${SFML_PATH} -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

FRAME_OBJS=frame/Frame.o frame/FrameState.o frame/SampleFrame.o

game: $(FRAME_OBJS)
	echo Hello world !
	$(CC) -c Main.cpp -o Main.o $(CFLAGS)
	$(CC) Main.o $(FRAME_OBJS) -o Main $(CFLAGS) $(SFML_FLAGS)

$(FRAME_OBJS): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm -rf *.o Main $(FRAME_OBJS)