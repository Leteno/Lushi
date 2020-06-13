
include ../Makefile.common
SFML_FLAGS=-L${SFML_PATH} -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

FRAME_OBJS=frame/Event.o frame/Frame.o frame/FrameState.o frame/SampleFrame.o

FSM_OBJS=fsm/FSM.o fsm/RoadMap.o

TEST_OBJS=frame/test/TestEvent.o fsm/test/TestFSM.o

TEST_EX_OBJS=../unit_test/UT.o

game: $(FRAME_OBJS) $(FSM_OBJS)
	echo Hello world !
	$(CC) -c Main.cpp -o Main.o $(CFLAGS)
	$(CC) Main.o $(FRAME_OBJS) $(FSM_OBJS) -o Main $(CFLAGS) $(SFML_FLAGS)

test: $(TEST_OBJS) $(TEST_EX_OBJS) $(FRAME_OBJS) $(FSM_OBJS)
	echo run test
	$(CC) -c Test.cpp -o Test.o $(CFLAGS)
	$(CC) Test.o $(TEST_EX_OBJS) $(TEST_OBJS) $(FRAME_OBJS) $(FSM_OBJS) -o Test $(CFLAGS) $(SFML_FLAGS)
	./Test

$(TEST_EX_OBJS):
	make -C ../unit_test/ test

$(FSM_OBJS) $(FRAME_OBJS) $(TEST_OBJS): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm -rf *.o Main $(FRAME_OBJS) $(FSM_OBJS) $(TEST_OBJS)