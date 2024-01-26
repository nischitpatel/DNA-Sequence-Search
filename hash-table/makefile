main : main.o genomeprocessing.o queries_ht.o my_strings.o
	        g++ -o main main.o genomeprocessing.o queries_ht.o my_strings.o

main.o : main.cpp
	        g++ -c main.cpp -o main.o

genomeprocessing.o: ../helpers/genomeprocessing.cpp
	        g++ -c ../helpers/genomeprocessing.cpp -o genomeprocessing.o

queries_ht.o : queries_ht.cpp
		g++ -c queries_ht.cpp -o queries_ht.o

my_strings.o : ../helpers/my_strings.cpp
	        g++ -c ../helpers/my_strings.cpp -o my_strings.o

clean:
	        rm main main.o genomeprocessing.o queries_ht.o my_strings.o
