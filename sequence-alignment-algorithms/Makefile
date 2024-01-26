CXX = g++
CXXFLAGS = -std=c++11 -pedantic -fopenmp

SRCS = main.cpp Queries_NW.cpp Queries_BL.cpp my_strings.cpp genomeprocessing.cpp
OBJS = $(SRCS:.cpp=.o)

HW_4: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o HW_4

clean:
	rm -f $(OBJS) HW_4