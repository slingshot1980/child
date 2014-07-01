# GNU compiler

CXX = g++
#
# -O is necessary for -Wuninitialized to be on
# -Weffc++ -fmessage-length=0 gives useful but noisy warnings
WARNINGFLAGS = -pedantic -Wall -W \
	-Wwrite-strings \
	-Wpointer-arith -Wcast-qual -Wcast-align

# recent versions of Linux use new style casts in their headers
WARNINGFLAGS += -Wold-style-cast

# -march=i686: generates code for pentiumpro and later
# -march=pentium3: generates code for pentium III and later
#ARCH := -march=pentium3
ARCH := 
# optimise
#PROFILE = -pg
CFLAGS = $(WARNINGFLAGS) -fpic $(PROFILE) -O2 $(ARCH) -c
LDFLAGS = $(WARNINGFLAGS) -shared $(PROFILE) -O2 $(ARCH)
# no optimisation, build is faster
#CFLAGS = $(WARNINGFLAGS) -g $(ARCH) -c
#LDFLAGS = $(WARNINGFLAGS) -g $(ARCH)
LIBS = 

LDFLAGS += -o $@

OBJEXT = o
EXEEXT =
LIBEXT = .so
