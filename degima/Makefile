all:
	g++ -c DriveLog.cpp
	g++ -c main.cpp
	g++ main.o DriveLog.o -o run.x
	ar r libdegima.a DriveLog.o

clean:
	rm -rf *~ .*~ *.o run.x

#g++ main.cpp  -o run.x

