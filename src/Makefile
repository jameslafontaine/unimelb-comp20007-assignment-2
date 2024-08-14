# Build targets
# lm - link math library library. required if you use math.h functions (commonly
# linked by default on mac).
task2: task2.o utils.o graph.o pq.o list.o
	gcc -Wall -o task2 -g task2.o utils.o graph.o pq.o list.o -lm

task3: task3.o utils.o graph.o pq.o list.o
	gcc -Wall -o task3 -g task3.o utils.o graph.o pq.o list.o -lm

task4: task4.o utils.o graph.o pq.o list.o
	gcc -Wall -o task4 -g task4.o utils.o graph.o pq.o list.o -lm

task7: task7.o utils.o graph.o pq.o list.o
	gcc -Wall -o task7 -g task7.o utils.o graph.o pq.o list.o -lm

task2.o: task2.c graph.h utils.h
	gcc -c task2.c -Wall -g

task3.o: task3.c graph.h utils.h
	gcc -c task3.c -Wall -g

task4.o: task4.c graph.h utils.h
	gcc -c task4.c -Wall -g

task7.o: task7.c graph.h utils.h
	gcc -c task7.c -Wall -g

utils.o: utils.c utils.h graph.h
	gcc -c utils.c -Wall -g

graph.o: graph.c graph.h pq.h utils.h
	gcc -c graph.c -Wall -g

pq.o: pq.c pq.h
	gcc -c pq.c -Wall -g

list.o: list.c list.h
	gcc -c list.c -Wall -g
