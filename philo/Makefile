# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teppei <teppei@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 12:46:40 by teppei            #+#    #+#              #
#    Updated: 2022/01/03 19:22:27 by teppei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
SRCDIR		=	src
SRCS		:=	# your src files both mandatory and bonus
MSRCDIR		=	msrc
SRCS_MAND	:=	# your src files only for mandatory
OBJDIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJDIR)/%.o)
MOBJDIR		=	mobj
MOBJS		=	$(SRCS_MAND:%.c=$(MOBJDIR)/%.o)
HEAD		=	./incs
INCS		=	-I./incs
LINK		=	-L./libft -L./gnl
LIBS		=	-lft -lgnl
L_FT		=	libft/libft.a
L_GNL		=	gnl/libgnl.a

BSRCDIR		=	bsrc
BSRCS		:=	# your src files only for bonus
BOBJDIR		=	bobj
BOBJS		=	$(BSRCS:%.c=%.o)
BONUS_NAME	=	$(NAME)_bonus

all: $(OBJDIR) $(MOBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME): $(OBJS) $(MOBJS) $(L_FT) $(L_GNL)
	$(CC) -o $@ $^ $(LINK) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(MOBJDIR)/%.o: $(MSRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(L_FT):
	@make -C libft

$(L_GNL):
	@make -C gnl

clean:
	rm -f $(OBJS) $(MOBJS) */*.gch
	rm -rf *.dSYM
fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	make fclean -C gnl

re: fclean all
cl: all clean

run: all
	./$(NAME)

.PHONY: all clean fclean re run

# if you challenge bonus
bonus: $(BOBJDIR) $(BONUS_NAME)

$(BOBJDIR)
	mkdir $(BSRCDIR)

$(BONUS_NAME): $(BOBJS) $(OBJS)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BOBJS): $(BSRCS:%.c) $(HEAD)

$(BOBJDIR)/%.o: $(BSRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

bclean: clean
	rm -f $(BOBJS) */*.gch

bfclean: bclean fclean
	rm $(BONUS_NAME)

.PHONY: bonus bclean bfclean
