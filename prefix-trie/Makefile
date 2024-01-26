CXX = g++
CXXFLAGS = -std=c++11

SRCS = main.cpp prefix_trie.cpp my_strings.cpp genomeprocessing.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = HW5

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
