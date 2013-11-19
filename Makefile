#############################################################################
#
# Makefile for librf24-bcm on Raspberry Pi
#
# License: GPL (General Public License)
# Author:  Charles-Henri Hallard 
# Date:    2013/03/13 
#
# Description:
# ------------
# use make all and mak install to install the library 
# You can change the install directory by editing the LIBDIR line
#
PREFIX=/usr/local

# Library parameters
# where to put the lib
LIBDIR=$(PREFIX)/lib
# lib name 
LIB=librf24-network
# shared library name
LIBNAME=$(LIB).so.1.0

CPPFLAGS=-I$(PREFIX)/include -I.

# The recommended compiler flags for the Raspberry Pi
CXXFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

all: $(LIB)

# Make the library
$(LIB): RF24Network.o Sync.o 
	g++ -shared -Wl,-soname,$@.so.1 ${CCFLAGS} -o ${LIBNAME} $^
	
clean:
	rm -rf *.o ${LIB}.*

# Install the library to LIBPATH
install: 
	if ( test ! -d $(PREFIX)/lib ) ; then mkdir -p $(PREFIX)/lib ; fi
	install -m 0755 ${LIBNAME} ${LIBDIR}
	ln -sf ${LIBDIR}/${LIBNAME} ${LIBDIR}/${LIB}.so.1
	ln -sf ${LIBDIR}/${LIBNAME} ${LIBDIR}/${LIB}.so
	ldconfig
	install RF24Network.h RF24Network_config.h $(PREFIX)/include
