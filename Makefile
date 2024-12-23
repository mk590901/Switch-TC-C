# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Ilogger

# Source files
SRCS = core.c Switch_resetHelper.c main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable
TARGET = switch

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
