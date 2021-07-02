
FILE= $(wildcard utils/*.c) \
	  $(wildcard utils/mem/*.c) \
	  $(wildcard srcs/*.c)
FLAGS= -Wall -Werror -Wextra -g
LIB= -lpthread

OBJ=$(FILE:.c=.o)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc -I. -o $@ -c $? $(FLAGS)

all: $(NAME)


