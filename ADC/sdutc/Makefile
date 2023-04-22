DIR = sdutc
TRGT = write_log

all : $(TRGT)

$(TRGT): write_log.c
	gcc -o $(TRGT) write_log.c

clean : 
	/bin/rm -f *.o a.out core $(TRGT)

tgz : clean
	cd .. ; tar cvzf $(DIR).tgz $(DIR)/COPYING $(DIR)/README \
		$(DIR)/Makefile $(DIR)/*.c $(DIR)/gc_write_log* $(DIR)/captains_log*

