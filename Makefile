NAME= philo
FILE= $(wildcard utils/*.c) \
	  $(wildcard utils/mem/*.c) \
	  $(wildcard *.c) 
FLAGS= -Wall -Werror -Wextra -g
LIB= -lpthread

all:
	gcc $(FILE) $(LIB) $(FLAGS) -o $(NAME)