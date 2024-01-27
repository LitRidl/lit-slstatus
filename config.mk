# slstatus version
VERSION = 1.0

# customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

X11INC = /usr/X11/include
X11LIB = /usr/X11/lib

# flags
CPPFLAGS = -I$(X11INC) -D_DEFAULT_SOURCE -DVERSION=\"${VERSION}\"
CFLAGS   = -std=c99 -march=native -mtune=native -pipe -fno-plt -fexceptions -fstack-clash-protection -fcf-protection -flto=auto -pedantic -Wall -Wno-unused-function -Wno-deprecated-declarations -Os ${INCS} ${CPPFLAGS}
LDFLAGS  = -L$(X11LIB) -lpulse -s -Wl,-O2,--sort-common,--as-needed,-z,relro,-z,now
LDLIBS   = -lX11

# compiler and linker
CC = cc
