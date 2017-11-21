all : pipes.c
	gcc pipes.c -o piper
run : all
	./piper
