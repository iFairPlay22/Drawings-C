all : monprogramme

monprogramme : test_proj.o proj.o
	gcc proj.o test_proj.o -o monprogramme

proj.o : proj.c proj.h
	gcc proj.c -c -o proj.o

test_proj.o : test_proj.c
	gcc test_proj.c -c -o test_proj.o

clean :
	rm -f *.o monprogramme
