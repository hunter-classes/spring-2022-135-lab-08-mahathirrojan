main: main.o imageio.o functions.o
	g++ -o main main.o imageio.o functions.o

sample: sample.o imageio.o
	g++ -o sample sample.o imageio.o

sample.o: sample.cpp imageio.h

imageio.o: imageio.cpp imageio.h

main.o: main.cpp imageio.h functions.h

functions.o: functions.cpp functions.h imageio.h


clean:
	rm -f sample.o imageio.o

remove-pictures: 
	rm -f taskA-* taskB-* taskC-* taskD-* taskE-* taskF-*
