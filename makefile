# ----------------------------------------------------------------------------
# Makefile
# 
# release: 0.1 (28-Ago-2010) create makefile
# 
# purpose: searches recursively in current directory for c/cpp files (using find),
#          compile each source file and link them in a executable.
#
# Credits: https://lembra.wordpress.com/2011/09/04/recursive-makefile/
# ----------------------------------------------------------------------------
 
APP     = sound-effects
CC      = g++ -std=c++11
RM      = rm
SRCDIR  = src
SRCEXT  = cpp
OBJDIR  = build
 
SRCS    := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS := $(shell find . -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
OBJS    := $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS))
 
DEBUG   = -ggdb -O0
INCLUDE = -Iinclude -I /usr/include
LIBS 	= -lportaudio
CFLAGS  = -Wall -lm -c $(DEBUG) $(INCLUDE)
OFLAGS  = -lm -msse2 -ffast-math -ftree-vectorize $(LIBS)
LDFLAGS = -L/usr/lib/python3.4/config-3.4m-x86_64-linux-gnu -L/usr/lib -lpthread -ldl  -lutil -lm  -lpython3.4m -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions
 
all:    $(APP)
 
$(APP): buildrepo $(OBJS)
		@echo "$(CC) $(OFLAGS) $(OBJS) -o $@"
		@$(CC) $(OBJS) $(OFLAGS) $(LDFLAGS) -o $(OBJDIR)/$@
 
$(OBJDIR)/%.o: %.$(SRCEXT)
		@echo "$(CC) $(CFLAGS) $< -o $@";
		@$(CC) $(CFLAGS) $< -o $@
 
clean:
		$(RM) -r -f $(OBJDIR) docs
 
buildrepo:
		$(call make-repo)

documentation: doxyfile docs
	doxygen
	cd docs/latex && make > /dev/null
	ln -s `pwd`/docs/latex/refman.pdf docs/documentation.pdf

docs:
	mkdir -p $@
 
define make-repo
		for dir in $(SRCDIRS); \
		do \
				mkdir -p $(OBJDIR)/$$dir; \
		done
endef