OBJS = main.o bmp_file_process.o img_process.o
main: ${OBJS}
	gcc -o resizer.out ${OBJS}
main.o: main.c main.h bmp_file_process.h img_process.h
bmp_file_process.o: bmp_file_process.c main.h bmp_file_process.h
img_process.o: img_process.c img_process.h main.h bmp_file_process.h

clean:
	rm -f main ${OBJS}
