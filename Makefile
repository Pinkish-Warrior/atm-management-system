objects = src/main.o src/system.o src/auth.o

atm : $(objects)
	cc -o atm $(objects)

src/main.o : src/main.c src/header.h
	cc -c -I src src/main.c -o src/main.o

src/system.o : src/system.c src/header.h
	cc -c -I src src/system.c -o src/system.o

src/auth.o : src/auth.c src/header.h
	cc -c -I src src/auth.c -o src/auth.o

clean :
	rm -f $(objects) atm