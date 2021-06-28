NAME= philo
FILE= $(wildcard *.c) \
	  $(wildcard utils/*.c)
FLAGS= -Wall -Werror -Wextra
LIB= -lpthread

all:
	gcc $(FILE) $(LIB) $(FLAGS) -o $(NAME)