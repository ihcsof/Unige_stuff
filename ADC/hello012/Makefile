N=hello012
M=string_master
CMP=gc_string_master
SCRPT=check_master.bash
E0=hello0
E1=hello1
KEN = ken_source
KT = ken_tool
KI = ken_init
KS = ken_self
KO = ken_output

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

$(KT): $(KT).c
	gcc -o $(KT) $(KT).c

$(KI).c: $(KT) $(KEN).c
	./$(KT) < $(KEN).c > $(KI).c
	cat $(KEN).c >> $(KI).c

$(KI): $(KI).c
	gcc -o $(KI) $(KI).c

$(KS).c: $(KI)
	./$(KI) > $(KS).c

$(KS): $(KS).c
	gcc -o $(KS) $(KS).c

$(KO).diff: $(KS).c
	/bin/rm -f $(KS) $(KO) $(KO).diff
	gcc -o $(KS) $(KS).c
	./$(KS) > $(KO)
	diff $(KS).c $(KO) > $(KO).diff

ken_check: $(KO).diff
	./checkdiff.bash $(KO).diff; /bin/rm -f $(KO) $(KO).diff

clean:
	/bin/rm -f a.out *.o $(M) $(E0) $(E1) diff_*.txt $(KI)* $(KO)* $(KS) $(KT)

tgz: clean
	cd .. ; tar cvzf $(N).tgz $(N)


