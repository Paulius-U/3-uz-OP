main: failas.o funkcijos.o
	g++ -o main Main.cpp failas.o funkcijos.o
failas:
	g++ -c failas.cpp failas.h
funkcijos:
	g++ -c funkcijos.cpp funkcijos.h
clean:
	rm *.o main
clean-all:
	rm *.o main *.txt
