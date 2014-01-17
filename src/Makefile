# Makefile
#
# Copyright (c) 2013   Regents of the University of California
#
include $(CAPATH_MK_DEFS)

PATH_LDFLAGS += -L./lnx
PATH_CFLAGS += -pg -Wall

EXEC = $(OBJDIR)/rtms_parser

all: 	$(OBJDIR) $(PATH_OBJS) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	\rm -f $(OBJDIR)/*.[oa] $(EXEC)
