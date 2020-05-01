#!/bin/user/make -f

CXX = g++

CXXFLAGS = 

CPPFLAGS = -Wall -g -I/scratch/perkins/include 

LDFLAGS = -L/scratch/perkins/lib

LDLIBS = -lcdk -lcurses

EXECFILE = executable

SOURCES := $(wildcard *.cc)
OBJS = $(SOURCES:.cc=.o)

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#*

$(EXECFILE): $(OBJS)
	$(CXX) -o $@  $(OBJS) $(LDFLAGS) $(LDLIBS)

backup: clean
	@mkdir -p ~/backups: chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename 'pwd'))
	@$(eval MKBKUPNAME := ~\backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@echo
	@echo Done!
