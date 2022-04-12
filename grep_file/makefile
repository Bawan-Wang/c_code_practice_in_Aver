OBJS = grep_main.o grep_thread.o grep_cmd_info_proc.o

main: ${OBJS}
	gcc -o grep.out -lpthread ${OBJS}
grep_main.o: grep_main.c grep_main.h grep_thread.h grep_cmd_info_proc.h 

grep_thread.o: grep_thread.c grep_thread.h

grep_cmd_info_proc.o: grep_cmd_info_proc.c grep_cmd_info_proc.h

clean:
	rm -f grep.out ${OBJS}
