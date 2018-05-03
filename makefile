IDIR =../include
CC=g++
CFLAGS=-lncurses -I$(IDIR)

ODIR=source
LDIR =../lib

LIBS=-lm 

_DEPS = being.h curses.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Armor.o Battle.o Being.o Companion.o Desert.o Enemy.o Functions.o Intro.o Item.o KeyBinding.o LichHideout.o Main.o Player.o Potion.o Saving.o Scroll.o Spell.o SpellTome.o StatusEffect.o Tyria.o Weapon.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

soc: $(OBJ)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 