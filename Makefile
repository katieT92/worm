mySoln.x:  main.o getChar.o screen.o worm.o
	g++ -ggdb -o mySoln.x main.o getChar.o screen.o worm.o -lcurses -ltermcap

main.o: main.cpp getChar.hpp screen.hpp worm.hpp
	g++ -c -ggdb main.cpp -o main.o

getChar.o: getChar.cpp getChar.hpp
	gcc -c -ggdb getChar.cpp -o getChar.o

screen.o: screen.cpp screen.hpp
	g++ -c -ggdb screen.cpp -o screen.o

worm.o: worm.cpp worm.hpp
	g++ -c -ggdb worm.cpp -o worm.o

clean:
	/bin/rm -f mySoln.x main.o getChar.o screen.o worm.o *~
