HW_2 : HW_2.o genomeprocessing.o queries_ar.o my_strings.o
	        g++ -o HW_2 HW_2.o genomeprocessing.o queries_ar.o my_strings.o

HW_2.o : HW_2.cpp
	        g++ -c HW_2.cpp -o HW_2.o

genomeprocessing.o: genomeprocessing.cpp
	        g++ -c genomeprocessing.cpp -o genomeprocessing.o

queries_ar.o : queries_ar.cpp
		g++ -c queries_ar.cpp -o queries_ar.o

my_strings.o : my_strings.cpp
	        g++ -c my_strings.cpp -o my_strings.o

clean:
	        rm HW_2 HW_2.o genomeprocessing.o queries_ar.o my_strings.o
