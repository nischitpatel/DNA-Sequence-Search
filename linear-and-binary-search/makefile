main : main.o genomeprocessing.o queries_ar.o my_strings.o
	        g++ -o main main.o genomeprocessing.o queries_ar.o my_strings.o

main.o : main.cpp
	        g++ -c main.cpp -o main.o

genomeprocessing.o: genomeprocessing.cpp
	        g++ -c genomeprocessing.cpp -o genomeprocessing.o

queries_ar.o : queries_ar.cpp
		g++ -c queries_ar.cpp -o queries_ar.o

my_strings.o : my_strings.cpp
	        g++ -c my_strings.cpp -o my_strings.o

clean:
	        rm main main.o genomeprocessing.o queries_ar.o my_strings.o
