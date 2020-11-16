run: main.gp mylib.so primes.bin
	cat main.gp |gp -q
	
mylib.so: mylib.c
	cc -fPIC -shared -o mylib.so mylib.c

clean:
	rm -f *~ *.so *.o

primes.bin: one-billion-primes.txt parse
	./parse < one-billion-primes.txt 2> primes.bin

parse: parse.c
	cc -o parse parse.c


.PHONY: run clean
