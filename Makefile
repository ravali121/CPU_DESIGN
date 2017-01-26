IDIR =../includes
CC=gcc
CFLAGS=-I$(IDIR) -std=c99


TARGET = CPU

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = alu.h memory_controller.h constants.h register_dictionary.h register_file.h instruction_compiler.h instruction_parser.h label_handler.h util.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o alu.o memory_controller.o register_dictionary.o register_file.o instruction_compiler.o instruction_parser.o label_handler.o util.o
OBJ = $(patsubst %,%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	 $(CC) -g -Wall -o $@ $^ $(CFLAGS) $(LIBS)
	
all: $(TARGET)
	
debug: $(TARGET)

.PHONY: clean

clean:
	rm -f *.o $(TARGET) *.*~ *~
