CXX = g++
CXXFLAGS = -std=c++11

SRCS = main.cpp prefix_trie.cpp ../helpers/my_strings.cpp ../helpers/genomeprocessing.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
