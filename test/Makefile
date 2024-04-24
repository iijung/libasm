# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 20:27:58 by minjungk          #+#    #+#              #
#    Updated: 2024/04/24 22:43:05 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:
.DEFAULT_GOAL	:= all

# **************************************************************************** #
# for libasm
# **************************************************************************** #

LIBS = ../libasm.a

CPPFLAGS = $(foreach dir, $(dir $(LIBS)), -I$(dir))
LDFLAGS = $(foreach dir, $(dir $(LIBS)), -L$(dir))
LDLIBS  = $(foreach lib, $(notdir $(LIBS)), -l$(patsubst lib%.a,%,$(lib)))

$(LIBS):
	$(MAKE) -C $(dir $(LIBS))

%: %.c $(LIBS)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

# **************************************************************************** #
# rules
# **************************************************************************** #
.PHONY: all bonus clean fclean re

BINS_M = \

BINS_B = \

all:
	$(foreach bin, $(BINS_M), $(MAKE) $(bin))

bonus:
	$(foreach bin, $(BINS_M), $(MAKE) $(bin))
	$(foreach bin, $(BINS_B), $(MAKE) $(bin))

clean:
	$(RM) $(BINS_M) $(BINS_B)

fclean: clean

re: fclean
	$(MAKE) all
