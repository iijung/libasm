# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile.nasm                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 10:24:45 by minjungk          #+#    #+#              #
#    Updated: 2024/04/11 14:12:28 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:
.DEFAULT_GOALS	:= all

NASM			= nasm
NASM_VERSION	= 2.16.02
NASM_PACKAGE	= $(NASM)-$(NASM_VERSION)
NASM_PREFIX		= $(CURDIR)
NASM_BINDIR		= $(NASM_PREFIX)
NASM_MANDIR		= $(NASM_PREFIX)

all: $(NASM)

clean:
	$(RM) $(NASM_PACKAGE).tar.gz
	$(RM) -r $(NASM_PACKAGE)

fclean: clean
	rm -rf \
		$(NASM_BINDIR)/nasm \
		$(NASM_BINDIR)/ndisasm \
		$(NASM_MANDIR)/man1 \
	
$(NASM): | $(NASM_PACKAGE)
	cd $(NASM_PACKAGE); \
	./configure \
		--prefix=$(NASM_PREFIX) \
		--bindir=$(NASM_BINDIR) \
		--mandir=$(NASM_MANDIR) \
		; \
	$(MAKE) -j install

$(NASM_PACKAGE): $(NASM_PACKAGE).tar.gz
	tar xzf $@.tar.gz

$(NASM_PACKAGE).tar.gz:
	curl -O https://www.nasm.us/pub/nasm/releasebuilds/$(NASM_VERSION)/$@
