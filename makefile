TARGET=create_net.o find_path.o binary_search.o optimization.o main.o

PPI : ${TARGET}
	gcc -o $@ $^
 
create_net.o:PPI.h
find_path.o:PPI.h
binary_search.o:PPI.h
optimization.o:PPI.h
main.o:PPI.h

.PHONY:clean
clean:
	rm PPI ${TARGET}

