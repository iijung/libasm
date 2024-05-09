# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 08:57:50 by minjungk          #+#    #+#              #
#    Updated: 2024/05/07 11:04:32 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:
.DEFAULT_GOAL	:= all

# **************************************************************************** #
# for nasm
# **************************************************************************** #

AS = ./nasm
ASFLAGS	= -w+error=all

ifeq ($(shell uname), Darwin)
ASFLAGS	+= -f macho64
else
ASFLAGS	+= -f elf64
ASFLAGS	+= -D __LINUX__
endif

ifdef DEBUG
ASFLAGS	+= -g
endif

$(AS):
	$(MAKE) all_nasm

%_nasm:
	$(MAKE) -f nasm.mk $*

# **************************************************************************** #
# for libasm
# **************************************************************************** #

NAME = libasm.a

ARFLAGS = rcs

SRCS_M = \
	ft_strlen.s \
	ft_strcpy.s \
	ft_strcmp.s \
	ft_write.s \
	ft_read.s \
	ft_strdup.s \

SRCS_B = \
	ft_atoi_base.s \
	ft_list_push_front.s \
	ft_list_size.s \
	ft_list_sort.s \
	ft_list_remove_if \

SRCS = \
	$(SRCS_M) \
	ft_atoi_base.s \
	ft_list_push_front.s \
	ft_list_size.s \
	ft_list_sort.s \
	# TODO: SRCS_M + SRCS_B

OBJS = $(SRCS:.s=.o)
DEPS = $(SRCS:.s=.d)
-include $(DEPS)

%.o: %.s $(AS)
	$(COMPILE.s) -o $@ $<

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# **************************************************************************** #
# rules
# **************************************************************************** #
.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: $(NAME)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all
