va_s: va_serial.c
	gcc -o va_s va_serial.c -lm

run: va_s
	./va_s

size:
	du -bsh *

clean:
	rm -f *.o va_s