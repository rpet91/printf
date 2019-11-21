# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/13 09:40:33 by rpet          #+#    #+#                  #
#    Updated: 2019/11/21 16:01:34 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = ft_printf.c ft_check_flag.c ft_empty_flag.c ft_check_conv.c ft_conv_c.c
OBJS = $(SRCS:.c=.o) 
LIBDIR = libft
FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	cd $(LIBDIR) && make
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	gcc -c $? -o $@ -I. -I$(LIBDIR) $(FLAGS)

clean:
	cd $(LIBDIR) && make clean
	rm -f $(OBJS)

fclean: clean
	cd $(LIBDIR) && make fclean
	rm -f $(NAME)

re: fclean all


		\/  DIET MOET WEG \/


test: $(NAME)
	gcc main.c -L. -lftprintf -Ilibft -Llibft -lft
