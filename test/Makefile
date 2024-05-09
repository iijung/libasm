# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 20:27:58 by minjungk          #+#    #+#              #
#    Updated: 2024/05/10 04:50:25 by minjungk         ###   ########.fr        #
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
	ft_atoi_base \
	ft_list_push_front \
	ft_list_size \
	ft_list_sort \
	ft_list_remove_if \

all: $(BINS_M)

bonus: $(BINS_M) $(BINS_B)

clean:
	$(RM) $(BINS_M) $(BINS_B)

fclean: clean

re: fclean
	$(MAKE) all
