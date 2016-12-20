all:
	g++ -c HevCnt.cpp -I/usr/local/include/zmp 
	g++ -o run.x main.cpp HevCnt.o ../degima/DriveLog.o \
		-I. -I../degima/ -I/usr/local/include/zmp -L/usr/local/lib/zmp/ -lhevcontrol -lcanif 


r: run

run: 
	./run.x 1>/dev/null

