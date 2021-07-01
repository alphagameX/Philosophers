NAME= philo
FILE= $(wildcard utils/*.c) \
	  $(wildcard utils/mem/*.c) \
	  $(wildcard *.c) 
FLAGS= -Wall -Werror -Wextra
LIB= -lpthread

all:
	gcc $(FILE) $(LIB) $(FLAGS) -o $(NAME)