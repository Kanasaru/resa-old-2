# colored terinal output
define colorecho
	@tput setaf $1
	@echo $2
	@tput sgr0
endef

# output file name
PROG   = resa
# compiler and linker
CC     = clang
LINKER = clang
# directories
INCDIR = src
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# flags
CFLAGS = -I$(INCDIR)
LFLAGS = -lSDL2-2.0.0 -lSDL2_image-2.0.0 -lSDL2_ttf-2.0.0 -lSDL2_mixer-2.0.0

# source file paths
SOURCES := $(wildcard $(SRCDIR)/*.c) \
           $(wildcard $(SRCDIR)/utl/*.c) \
           $(wildcard $(SRCDIR)/mpos/*.c) \
           $(wildcard $(SRCDIR)/world/*.c) \
           $(wildcard $(SRCDIR)/world/fauna/*.c) \
           $(wildcard $(SRCDIR)/world/flora/*.c) \
           $(wildcard $(SRCDIR)/world/objects/*.c)
# object files
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

# linking
$(BINDIR)/$(PROG): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	$(call colorecho,6,"Linking complete!")
# compiling
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c | createdir
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call colorecho,6,"Compiled "$<" successfully!")

# create object file paths
createdir:
	$(call colorecho,4,"Create directories...")
	mkdir -p $(BINDIR)
	mkdir -p obj/utl
	mkdir -p obj/mpos
	mkdir -p obj/world
	mkdir -p obj/world/fauna
	mkdir -p obj/world/flora
	mkdir -p obj/world/objects

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	$(call colorecho,4,"Cleanup complete!")

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(PROG)
	@$(rm) $(wildcard $(BINDIR)/*.*)
	$(call colorecho,4,"Executable and game data removed!")
