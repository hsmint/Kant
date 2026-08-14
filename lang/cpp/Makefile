CC=g++
CFLAGS=-Wall -Wextra -std=c++17
NAME=calculator
SRC=calculator.cpp
OBJ=calculator.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)
