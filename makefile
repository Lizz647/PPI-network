TARGET=main.o create_net.o find_path.o binary_search.o
PPI : ${TARGET}
	gcc -o $@ $^

main.o:PPI.h
create_net.o:PPI.h
find_path.o:PPI.h
binary_search.o:PPI.h

.PHONY:clean
clean:
	rm PPI ${TARGET}

