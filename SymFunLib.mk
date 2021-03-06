#
# This makefile builds the SCC::SynFun support library. 
#
SHELL=/bin/sh

# Parameters for library construction script 

CXX     := g++
LIB_DIR = ./lib
SRC_DIR = .

# Create library directory if it doesn't exist 

create_lib_dir := \
$(shell if [ ! -e $(LIB_DIR) ]; then mkdir $(LIB_DIR); fi) 

# specify make parameters

ifndef VERBOSE
QUIET     :=@
MAKEFLAGS += --no-print-directory
MAKEFLAGS := $(sort $(MAKEFLAGS))
endif

ifeq ($(MAKECMDGOALS),release)
CFLAGS      :=-O2  -fno-gcse -fno-optimize-sibling-calls -Wno-write-strings
CXXFLAGS    :=-O2  -fno-gcse -fno-optimize-sibling-calls -Wno-write-strings -std=c++11
CDEFINES    += 
CXXDEFINES  += 
endif

ifeq ($(MAKECMDGOALS),debug)
CFLAGS      =-g -Wall -fno-inline
CDEFINES    =-D_DEBUG
CXXFLAGS    =-g -Wall -fno-inline -std=c++11
CXXDEFINES  +=-D_DEBUG 
endif

RELEASE_DIR  = ./_releaseSymFun
DEBUG_DIR    = ./_debugSymFun

DEBUG_LIBRARY    = $(LIB_DIR)/libSymFun_debug.a
RELEASE_LIBRARY  = $(LIB_DIR)/libSymFun.a 

include ./CommonLibMake.mk
