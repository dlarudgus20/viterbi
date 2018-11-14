TARGET = viterbi

CXX_SOURCE = $(wildcard src/*.cpp)
CXX_HEADER = $(wildcard src/*.h)

$(TARGET): $(CXX_SOURCE) $(CXX_HEADER)
	g++ -std=c++11 -O3 -flto -D_GNU_SOURCE -o $(TARGET) $(CXX_SOURCE)
