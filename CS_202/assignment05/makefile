PondSimulator: organism.o animal.o plant.o herbivore.o randNum.o main.o
	g++ organism.o animal.o plant.o herbivore.o randNum.o main.o -Wall -pedantic -o PondSimulator

organism: organism.cpp
	g++ -c organism.cpp

animal: animal.cpp
	g++ -c animal.cpp

plant: plant.cpp
	g++ -c plant.cpp

herbivore: herbivore.cpp
	g++ -c herbivore.cpp

randNum: randNum.cpp
	g++ -c randNum.cpp

main: main.cpp
	g++ -c main.cpp

clean:
	rm *.o
	rm PondSimulator