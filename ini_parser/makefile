OBJS = main.o string_linked.o string_processing.o
main: ${OBJS}
	gcc -o ini_parser.out ${OBJS}
main.o: main.c main.h string_linked.h string_processing.h

string_linked.o: string_linked.c main.h string_linked.h

string_processing.o: string_processing.c main.h string_linked.h string_processing.h

clean:
	rm -f ini_parser.out ${OBJS}
