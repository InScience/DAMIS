# DAMIS algorithms - standalone Linux build (replaces the NetBeans generated Makefile).
#
#   make                 build ./Algorithms
#   make -j"$(nproc)"    parallel build
#   make clean           remove build output
#   make install PREFIX=/opt/damis   install to $(PREFIX)/bin/Algorithms
#
# Requires an MPI C++ compiler wrapper (OpenMPI or MPICH), e.g. Ubuntu/Debian:
#   apt-get install build-essential openmpi-bin libopenmpi-dev

# make's built-in default CXX is g++; use the MPI wrapper unless CXX was set explicitly.
ifeq ($(origin CXX),default)
CXX := mpic++
endif
CXXSTD   ?= -std=c++17
CXXFLAGS ?= -O2 -Wall -Wno-sign-compare -Wno-unused-variable -Wno-unused-but-set-variable
CPPFLAGS += -I. -IcmdLineParser -Ialglib
LDFLAGS  ?=
LDLIBS   ?=

TARGET   := Algorithms
BUILDDIR := build
PREFIX   ?= /usr/local

# DECISIONTREE.cpp is an unused, unfinished stub (main.cpp uses DECTREE).
SOURCES := $(filter-out DECISIONTREE.cpp,$(wildcard *.cpp)) \
           $(wildcard cmdLineParser/*.cpp) \
           $(wildcard alglib/*.cpp)
OBJECTS := $(SOURCES:%.cpp=$(BUILDDIR)/%.o)
DEPS    := $(OBJECTS:.o=.d)

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXSTD) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

install: $(TARGET)
	install -D -m 0755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

-include $(DEPS)
