# ----------------------------
# Program Options
# ----------------------------

NAME         ?= TRELLO
ICON         ?= icon.png
DESCRIPTION  ?= ""
COMPRESSED   ?= YES
ARCHIVED     ?= NO
FONTPACKNAME ?= TREFONT
FONTPOS      ?= fonts

# ----------------------------

CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk

$(BINDIR)/$(FONTPACKNAME).bin: $(SRCDIR)/$(FONTPOS)/drsans-07-normal.fnt
	convfont -o fontpack -N "Dr. Sans" -P "Calculator 1252" \
	-D "A font designed for maximum readability [SCRATCH]" \
	-V "7/21/2020" \
	-f $(SRCDIR)/$(FONTPOS)/drsans-07-normal.fnt -l 8  -x 3 -c 1 -a 1 -b 1 -w normal -s 0 \
	$(BINDIR)/$(FONTPACKNAME).bin

$(BINDIR)/$(FONTPACKNAME).8xv: $(BINDIR)/$(FONTPACKNAME).bin
	convbin --iformat bin --input $(BINDIR)/$(FONTPACKNAME).bin --oformat 8xv --output $(BINDIR)/$(FONTPACKNAME).8xv --archive --name $(FONTPACKNAME)

all: $(BINDIR)/$(FONTPACKNAME).8xv

