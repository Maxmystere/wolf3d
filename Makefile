# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/06/10 14:16:09 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include libft/include.mk
include wolf.mk

NAME			:=		wolf3d

CC				:=		gcc

CFLAGS			:=		-Wall -Wextra -Werror

LIB				:=		-L libft/ -lft							\
						-L ~/.brew/lib -lSDL2					\
						-lSDL2_ttf								\
						-lSDL2_image							\

INCLUDE			=		-I ./include							\
						-I ./libft								\
						-I ~/.brew/include/SDL2					\

COMPILE_LIB		:=		make -C libft/

OBJDIR			:=		objs

SRCDIR			:=		srcs

FOLDER			:=		objs

NB_SRCS			:=		$(shell ls srcs/ | wc -l)

NB_OBJS			=		$(shell ls objs/ | wc -l | sed -e 's/[^0-9]//g')

MAX_FILL		:=		$$(( $(NB_SRCS)))

FILL_BAR		=		$$(( $(NB_OBJS) * $(MAX_FILL) / $(NB_SRCS)))

INV_FILL_BAR	=		$$(( $(MAX_FILL) - $(FILL_BAR)))

OBJS    		:=		$(patsubst %.c,$(OBJDIR)/%.o,$(SRCS_WOLF))

SRCS_WOLF  		:=		$(patsubst %.c,srcs/%.c,$(SRCS_WOLF))

SRCS_LIBFT		:=		$(patsubst %.c,libft/%.c,$(SRCS_LIBFT))

all				:		$(NAME)

$(FOLDER)		:
	@mkdir -p $(FOLDER)

$(OBJDIR)/%.o	:		$(SRCDIR)/%.c $(SRCS_LIBFT) include/wolf3d.h libft/libft.h
	@printf '\rCompilation $(NAME)\n'
	@printf '[\e[94m%*s' $(FILL_BAR) | tr ' ' '#'
	@printf '%*s\e[0m] \e[94m $<\e[0m' $(INV_FILL_BAR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf '\033[M\033[A'

$(NAME)			:	$(FOLDER) $(OBJS)
	@make -C libft/
	@$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -o $(NAME) $(OBJS)
	@sips -i ressources/icon/icon.ico
	@derez -only icns ressources/icon/icon.ico > tmpicns.rsrc
	@rez -append tmpicns.rsrc -o $(NAME)
	@setfile -a C $(NAME)
	@rm tmpicns.rsrc
	@printf "\e[M\e[A\n\e[94m[--------$(NAME)--------]\n\e[0m"

clean:
	@make clean -C ./libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

