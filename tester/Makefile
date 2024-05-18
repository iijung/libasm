# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 15:01:01 by minjungk          #+#    #+#              #
#    Updated: 2024/05/18 18:49:16 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:
.DEFAULT_GOAL	:= all

# **************************************************************************** #
# for libasm
# **************************************************************************** #

LIBS = ../libasm.a

CPPFLAGS	+= $(foreach dir, $(dir $(LIBS)), -I$(dir))
CPPFLAGS	+= $(foreach dir, $(dir $(LIBS)), -I$(dir))
LDFLAGS 	+= $(foreach dir, $(dir $(LIBS)), -L$(dir))
LDLIBS  	+= $(foreach lib, $(notdir $(LIBS)), -l$(patsubst lib%.a,%,$(lib)))

$(LIBS):
	$(MAKE) -C $(@D)

# **************************************************************************** #
# fot object
# **************************************************************************** #

NAME = main

SRCS = \
	test_util.c \
	test_strlen.c \
	test_strcpy.c \
	test_strcmp.c \
	test_strdup.c \
	test_write.c \
	test_read.c \
	test_atoi_base.c \
	test_list.c \
	main.c \

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
-include $(DEPS)

CFLAGS		+= -Wall -Wextra -Werror -pedantic
CPPFLAGS	+= -MMD -MP

ifdef DEBUG
CFLAGS		+= -g
endif

$(NAME): $(OBJS)
	$(MAKE) $(LIBS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

# **************************************************************************** #
# rules
# **************************************************************************** #
.PHONY: all clean fclean re

all:
	@for lib in $(LIBS); do $(MAKE) -C `dirname $$lib` bonus; done
	$(MAKE) $(NAME)

clean:
	$(RM) $(wildcard *.o)
	$(RM) $(wildcard *.d)

fclean: clean
	$(RM) $(NAME)
	$(RM) trace.out

re: fclean
	$(MAKE) all
