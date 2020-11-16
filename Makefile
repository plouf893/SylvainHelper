run: main.gp mylib.so
	cat main.gp |gp -q
	
mylib.so: mylib.c
	cc -fPIC -shared -o mylib.so mylib.c

clean:
	rm -f *~ *.so *.o

.PHONY: run clean
