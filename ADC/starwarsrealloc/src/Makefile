PLAY = malloc_play
TEST = test_vector
TEST2 = new_test_vector
VLIB = vector

SOURCES = Makefile COPYING README $(VLIB).c $(VLIB).h $(TEST).c $(TEST2).c $(PLAY).c
MAINDIR = starwarsrealloc

all: $(VLIB).o $(TEST) $(TEST2) $(PLAY)

$(PLAY) : $(PLAY).c
	gcc -o $(PLAY) $(PLAY).c

$(VLIB).o: $(VLIB).c $(VLIB).h
	gcc -c $(VLIB).c

$(TEST): $(TEST).o $(VLIB).o
	gcc -o $(TEST) $(TEST).o $(VLIB).o

$(TEST).o: $(TEST).c $(VLIB).h
	gcc -c $(TEST).c

$(TEST2): $(TEST2).o $(VLIB).o
	gcc -o $(TEST2) $(TEST2).o $(VLIB).o

$(TEST2).o: $(TEST2).c $(VLIB).h
	gcc -c $(TEST2).c

clean:
	/bin/rm -f a.out *.o $(TEST) $(TEST2) $(PLAY)

tgz: clean $(SOURCES)
	cd ../.. ; tar cvzf $(MAINDIR)/$(MAINDIR).tgz $(MAINDIR)/src

