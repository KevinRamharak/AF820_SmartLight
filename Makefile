## Author: Kevin Ramharak

# Project settings
PROJECTNAME := AF820_SmartLight# project name here #

# Directory structure
SRCDIR := src
BUILDDIR := build
TARGET := bin/$(PROJECTNAME)

# Inlude paths
# this enables the use of '#include "Anything.h"' from anywhere in the project. Not sure if i should use it
#INCLUDE := $(shell find $(SRCDIR) -type d | sed -e 's/\(src.*\)/-I\1/')

# Compiler settings
CXX := g++
CXXFLAGS := -g -std=c++11 -Wall
SRCEXT := cpp

# Files
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPENDS := $(OBJECTS:%.o=%.d)

# default
$(TARGET) : $(OBJECTS)
	@mkdir -p bin/
	@echo " $(CXX) $^ -o $(TARGET)"; $(CXX) $^ -o $(TARGET)

-include $(DEPENDS)

# object files
$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	@echo " $(CXX) $(CXXFLAGS) -MMD -o $@ -c $<"; $(CXX) $(CXXFLAGS) -MMD -o $@ -c $<

# clean
clean :
	@echo -e " rm -rf $(BUILDDIR)/*\n rm -f $(TARGET)"; rm -rf $(BUILDDIR)/*; rm -f $(TARGET)

.PHONY: clean
