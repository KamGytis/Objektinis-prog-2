CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET   = studentai
 
SRCS = main.cpp zmogus.cpp studentas.cpp vector_ops.cpp list_ops.cpp deque_ops.cpp \
       generator.cpp testavimas.cpp testavimas_klases.cpp utils.cpp
 
OBJS = $(SRCS:.cpp=.o)
 
.PHONY: all clean O1 O2 O3
 
all: $(TARGET)
 
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
 
O1:
	$(CXX) $(CXXFLAGS) -O1 -o $(TARGET)_O1 $(SRCS)
 
O2:
	$(CXX) $(CXXFLAGS) -O2 -o $(TARGET)_O2 $(SRCS)
 
O3:
	$(CXX) $(CXXFLAGS) -O3 -o $(TARGET)_O3 $(SRCS)
 
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET)_O1 $(TARGET)_O2 $(TARGET)_O3
 