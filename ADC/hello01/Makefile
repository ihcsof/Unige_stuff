N=hello01
M=string_master
CMP=gc_string_master
SCRPT=check_master.bash
E0=hello0
E1=hello1

all: $(E0) $(E1) $(M)

$(E0): $(E0).c
	gcc -o $(E0) $(E0).c

$(E1): $(E1).c
	gcc -o $(E1) $(E1).c

$(M): $(M).c
	gcc -o $(M) -DMY_SOURCE_FILE='"$(M)"' $(M).c

test_master : $(M) $(CMP)
		./$(SCRPT) $(CMP) $(M) m
		./$(SCRPT) $(CMP) $(M) f
		./$(SCRPT) $(CMP) $(M) mp
		./$(SCRPT) $(CMP) $(M) fp

check_$(E1): $(E1).c $(E0)
	./check1.bash $(E1) $(E0)

clean:
	/bin/rm -f a.out *.o $(M) $(E0) $(E1) diff_*.txt

tgz: clean
	cd .. ; tar cvzf $(N).tgz $(N)


