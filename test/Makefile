# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 20:27:58 by minjungk          #+#    #+#              #
#    Updated: 2024/04/30 10:24:09 by minjungk         ###   ########.fr        #
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

ifdef DEBUG
CFLAGS += -g
endif

$(LIBS):
	$(MAKE) -C $(dir $(LIBS))

%: %.c $(LIBS)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

# **************************************************************************** #
# rules
# **************************************************************************** #
.PHONY: all bonus clean fclean re

BINS_M = \
	ft_strlen \
	ft_strcpy \
	ft_strcmp \
	ft_strdup \
	ft_write \
	ft_read \

BINS_B = \

all: $(BINS_M)

bonus: $(BINS_M) $(BINS_B)

clean:
	$(RM) $(BINS_M) $(BINS_B)

fclean: clean

re: fclean
	$(MAKE) all
