run:
	rm -rf output
	mkdir output
	gcc -Wall -Wextra -g3 main.c interfaces.c adjacency_list.c adjacency_matrix.c queue.c priority_queue.c -o output/main.exe
	./output/main.exe
