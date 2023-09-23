build:
	rm -f ./a.out
	g++ -std=c++17 -g -Wall main.cpp buildings.cpp building.cpp dist.cpp footway.cpp footways.cpp graph.o node.cpp nodes.cpp osm.cpp tinyxml2.cpp -Wno-unused-variable -Wno-unused-function

run:
	./a.out

valgrind:
	valgrind --tool=memcheck --leak-check=full ./a.out

clean:
	rm -f ./a.out