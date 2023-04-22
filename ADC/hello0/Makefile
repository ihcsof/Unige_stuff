N=hello0
M=string_master
CMP=gc_string_master
SCRPT=check_master.bash

all: $(N) $(M) 

test_master : $(M) $(CMP)
		./$(SCRPT) $(CMP) $(M) m
		./$(SCRPT) $(CMP) $(M) f
		./$(SCRPT) $(CMP) $(M) mp
		./$(SCRPT) $(CMP) $(M) fp

$(M): $(M).c
	gcc -o $(M) -DMY_SOURCE_FILE='"$(M)"' $(M).c

$(N): $(N).c
	gcc -o $(N) $(N).c

clean:
	/bin/rm -f a.out *.o $(M) $(N) diff_*.txt

tgz: clean
	cd .. ; tar cvzf $(N).tgz $(N)

