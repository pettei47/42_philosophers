# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teppei <teppei@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 12:46:40 by teppei            #+#    #+#              #
#    Updated: 2022/01/16 13:26:13 by teppei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
SRCDIR		=	src
SRCS		:=	philosophers.c \
				ph_error.c \
				ph_check_args.c \
				ph_free_god.c \
				
OBJDIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJDIR)/%.o)
HEAD		=	./incs
INCS		=	-I./incs
LIBS		=	-lpthread

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME): $(OBJS) $(MOBJS)
	$(CC) -o $@ $^ $(LINK) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS) $(MOBJS) */*.gch
	rm -rf *.dSYM
fclean: clean
	rm -f $(NAME)

re: fclean all
cl: all clean

run: all
	./$(NAME)

.PHONY: all clean fclean re run
