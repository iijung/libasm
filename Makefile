# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 08:57:50 by minjungk          #+#    #+#              #
#    Updated: 2024/05/16 11:01:51 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:
.DEFAULT_GOAL	:= all

# **************************************************************************** #
# for nasm
# **************************************************************************** #

AS = ./nasm

$(AS):
	$(MAKE) all_nasm

%_nasm:
	$(MAKE) -f nasm.mk $*

# **************************************************************************** #
# fot object
# **************************************************************************** #

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
	ft_list_remove_if.s \

OBJS = $(SRCS:.s=.o)
DEPS = $(SRCS:.s=.d)
-include $(DEPS)

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

%.o: %.s $(AS)
	$(COMPILE.s) -o $@ $<

# **************************************************************************** #
# for libasm
# **************************************************************************** #

NAME = libasm.a

ARFLAGS = rcs

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $?

# **************************************************************************** #
# rules
# **************************************************************************** #
.PHONY: all bonus clean fclean re

all:
	$(MAKE) SRCS="$(SRCS_M)" $(NAME)

bonus:
	$(MAKE) SRCS="$(SRCS_M) $(SRCS_B)" $(NAME)

clean:
	$(RM) $(wildcard *.o)
	$(RM) $(wildcard *.d)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all
