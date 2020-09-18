all: thread proc

thread: searchtest.c multitest_thread.c multitest.h
	gcc -DMYSTRING='"thread"' -o searchtest searchtest.c -lpthread

proc: searchtest.c multitest_proc.c multitest.h
	gcc -DMYSTRING='"proc"' -o searchtest searchtest.c -lpthread

clean:
	rm searchtest
