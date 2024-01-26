HW_3 : HW_3.o genomeprocessing.o queries_ht.o my_strings.o
	        g++ -o HW_3 HW_3.o genomeprocessing.o queries_ht.o my_strings.o

HW_3.o : main.cpp
	        g++ -c main.cpp -o HW_3.o

genomeprocessing.o: genomeprocessing.cpp
	        g++ -c genomeprocessing.cpp -o genomeprocessing.o

queries_ht.o : queries_ht.cpp
		g++ -c queries_ht.cpp -o queries_ht.o

my_strings.o : my_strings.cpp
	        g++ -c my_strings.cpp -o my_strings.o

clean:
	        rm HW_3 HW_3.o genomeprocessing.o queries_ht.o my_strings.o
