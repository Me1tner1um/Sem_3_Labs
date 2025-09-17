CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lm

TARGET = check.out

SRCS = main.cpp list.cpp polynomial.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)