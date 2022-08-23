test: main.o printGeneration.o Thread_checkCells.o Thread_worker.o initFiles.o closeFiles.o
	gcc header.c main.o printGeneration.o Thread_checkCells.o Thread_worker.o initFiles.o closeFiles.o -lpthread -o test

main.o: main.c header.h 
	gcc -c main.c

printGeneration.o: printGeneration.c
	gcc -c printGeneration.c

Thread_checkCells.o: Thread_checkCells.c
	gcc -c Thread_checkCells.c

Thread_worker.o: Thread_worker.c
	gcc -c Thread_worker.c

initFiles.o: initFiles.c
	gcc -c initFiles.c

closeFiles.o: closeFiles.c
	gcc -c closeFiles.c

clean:
	rm *.o test
