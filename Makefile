# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 14:15:16 by jleem             #+#    #+#              #
#    Updated: 2021/02/11 18:58:59 by jleem            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= g++
CPPFLAGS		= -Wall -Wextra -I$(INCDIR) -lpthread
# CPPFLAGS		= -Wall -Wextra -Werror -I$(INCDIR)
# CFLAGS		= -Wall -Wextra -Werror -O2 -I$(INCDIR)

SRCDIR		= srcs/
INCDIR		= includes/

SRCS		= $(wildcard $(SRCDIR)*.cpp)
OBJS		= $(SRCS:.cpp=.o)

NAME		= raytracing_in_one_weekend

all			: $(NAME)

$(NAME)		: $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@ -lpthread

clean		:
	rm -f $(OBJS)

fclean		: clean
	rm -f $(NAME)

re			: fclean all

test		: all
	./$(NAME) > test.ppm
	./../ppm-viewer/ppm-viewer test.ppm

.PHONY		: all clean fclean test
