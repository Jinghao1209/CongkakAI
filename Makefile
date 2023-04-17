CC := g++
CFLAGS := -Wall -Wextra -std=c++11
LIBS := -lm
INCLUDES := -Iinclude/

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

main.out: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDES) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) main.out
