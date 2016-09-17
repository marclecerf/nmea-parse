SRC := parser.cc
OBJ := $(SRC:.cc=.o)
EXE := $(SRC:.cc=)

LFLAGS += -lcommon

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LFLAGS) $(OBJ) -o $(EXE)

clean:
	rm -f $(EXE) $(OBJ)
