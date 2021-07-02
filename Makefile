
NAME=libphilo.a
PROG=philo
FILE= $(wildcard utils/*.c) \
	  $(wildcard utils/mem/*.c) \
	  $(wildcard srcs/*.c)
FLAGS= -Wall -Werror -Wextra -g
LIB= -lpthread
RM= rm -f

OBJ=$(FILE:.c=.o)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	gcc main.c $(OBJ) -L. -lphilo $(LIB) -o $(PROG)

%.o: %.c
	gcc -I. -o $@ -c $? $(FLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(PROG)

re: fclean all