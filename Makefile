but : main
graphe.o : graphe.c
	gcc -c  graphe.c
main.o : main.c
	gcc -c  main.c
main : main.o graphe.o
	gcc -o main main.o graphe.o -lgraph -lm
	rm main.o graphe.o
clean :
	rm -f main 
