CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lm

TARGET_0 = main_0.out
TARGET_1 = main_1.out

SRCS_0 = main0.cpp list.cpp polynomial.cpp
SRCS_1 = main1.cpp list.cpp polynomial.cpp

OBJS_0 = $(SRCS_0:.cpp=.o)
OBJS_1 = $(SRCS_1:.cpp=.o)

all: $(TARGET_0) $(TARGET_1)

$(TARGET_0): $(OBJS_0)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET_1): $(OBJS_1)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_0) $(OBJS_1) $(TARGET_0) $(TARGET_1)