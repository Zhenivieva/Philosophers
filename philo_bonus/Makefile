# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/02 18:08:00 by mmaryjan          #+#    #+#              #
#    Updated: 2021/02/25 21:27:29 by mmaryjan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

DIR_OBJ = ./

SRCS	=   src/main.c \
            src/thread_functions.c \
            src/dop_functions.c \
			src/dop_functions2.c \
			src/dop_functions3.c \

DIR_HEADERS	= ./includes/

OBJS	= $(SRCS:.c=.o)

RM		= rm -f

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -g

.c.o:
			$(CC) $(CFLAGS) -c -I $(DIR_HEADERS) $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -I $(DIR_HEADERS) $(OBJS) -o $(NAME)

#$(CC) $(CFLAGS) -I $(DIR_HEADERS) $(OBJS) -o $(NAME) -ltermcap

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
