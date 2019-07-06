
LIBS = -lglut -lGL -lGLU

p2.out: main.o polyhedron.o fileHandling.o lineAlgorithms.o boundingBox.o transformations3D.o
	g++ -g -o p2.out main.o polyhedron.o fileHandling.o lineAlgorithms.o boundingBox.o transformations3D.o $(LIBS)

main.o: main.cpp PixelBuffer.h polyhedron.h fileHandling.h boundingBox.h transformations3D.h
	g++ -g $(LIBS) -c main.cpp

polyhedron.o: polyhedron.cpp polyhedron.h lineAlgorithms.h
	g++ -g $(LIBS) -c polyhedron.cpp

fileHandling.o: fileHandling.cpp fileHandling.h
	g++ -g $(LIBS) -c fileHandling.cpp

lineAlgorithms.o: lineAlgorithms.cpp lineAlgorithms.h
	g++ -g $(LIBS) -c lineAlgorithms.cpp

boundingBox.o: boundingBox.cpp boundingBox.h
	g++ -g $(LIBS) -c boundingBox.cpp

transformations3D.o: transformations3D.cpp transformations3D.h
	g++ -g $(LIBS) -c transformations3D.cpp

clean:
	rm -f main.o polyhedron.o fileHandling.o lineAlgorithms.o boundingBox.o transformations3D.o
