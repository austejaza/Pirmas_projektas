CXX = g++
CXXFLAGS = -std=c++17 -O3

TARGET = programa

OBJS = main.cpp funkcijos.cpp studentas.cpp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.txt