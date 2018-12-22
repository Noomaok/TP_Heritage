ECHO = @echo
RM = rm
RMFLAGS = -f
EXE = GES
INT = Trajet.h TrajetSimple.h TrajetCompose.h TableauTrajet.h Catalogue.h Menu.h
REAL = $(INT:.h=.cpp)
OBJ = $(REAL:.cpp=.o)
COMP = g++
CPPFLAGS =-ansi -pedantic -Wall -std=c++11 -g #-DMAP
EDL = g++
EDLFLAGS =
LIBS =
EFFACE = clean
MAKE = make

.SILENT : debug release

all :
	$(ECHO) "- all     : display this message"
	$(ECHO) "- debug   : build the debug version"
	$(ECHO) "- release : build the release version, without debug option"

debug :
	$(ECHO) "Edition des liens de <$(EXE)> version debug"
	$(MAKE) -s $(EXE)

run :
	$(ECHO) "Execution de <$(EXE)>"
	./$(EXE)

release :
	$(ECHO) "Edition des liens de <$(EXE)> version release"
	$(MAKE) -s $(EXE)

$(EXE) : $(OBJ)
	$(EDL) $(EDLFLAGS) -o $(EXE) $(OBJ) $(LIBS)

Catalogue.o : Catalogue.cpp Catalogue.h Trajet.h TableauTrajet.h

TableauTrajet.o : TableauTrajet.cpp TableauTrajet.h Trajet.h

Trajet.o : Trajet.cpp Trajet.h

TrajetSimple.o : TrajetSimple.cpp TrajetSimple.h Trajet.h

TrajetCompose.o : TrajetCompose.cpp TrajetCompose.h TrajetSimple.h Trajet.h TableauTrajet.h

Menu.o : Menu.cpp Trajet.h TrajetSimple.h TrajetCompose.h Catalogue.h

%.o : %.cpp
	$(ECHO) "Compilation de <$<>"
	$(COMP) $(CPPFLAGS) -c $<

$(EFFACE) :
	$(RM) $(RMFLAGS) $(OBJ) $(EXE) core
