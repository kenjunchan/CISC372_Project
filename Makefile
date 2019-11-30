va_s: va_serial.c
	gcc -o va_s va_serial.c -lm

va_p: va_parallel.c
	export OMP_NUM_THREADS=16
	gcc -fopenmp -o va_p va_parallel.c -lm

run_s: va_s
	./va_s

run_p: va_p
	./va_p

size:
	du -bsh *

clean:
	rm -f *.o va_s
	rm -f *.o va_p

superclean:
	rm -f *.txt