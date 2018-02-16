CC = g++
CPPFLAGS = -Wall -std=c++0x -g -I$(INCLUDE)
INCLUDE = ./include
BIN = ./bin
SRC = ./src
OBJ = ./obj

all: grx-impresoras

#Compilacion del archivo *.cpp necesario
$(OBJ)/%.o : $(SRC)/%.cpp $(INCLUDE)/%.h
	$(CC) -c $(CPPFLAGS) $< -o $@ 

# Compilando server_artnet.cpp
#$(OBJ)/server_artnet.o: $(SRC)/server_artnet.cpp $(INCLUDE)/server_artnet.h 
#	$(CC) -c $(CPPFLAGS) $(LDWIRI) $(SRC)/server_artnet.cpp -o $(OBJ)/server_artnet.o
	
# Compilando grx-impresoras.cpp
$(OBJ)/grx-impresoras.o: $(SRC)/grx-impresoras.cpp 
	$(CC) -c $(CPPFLAGS) $(SRC)/grx-impresoras.cpp -o $(OBJ)/grx-impresoras.o

# Creacion del ejecutable bin/grx-impresoras
grx-impresoras: $(BIN)/grx-impresoras
$(BIN)/grx-impresoras: $(OBJ)/impresora.o $(OBJ)/set_impresoras.o
	$(CC) $(CPPFLAGS) -o $(BIN)/grx-impresoras $(OBJ)/impresora.o  $(OBJ)/set_impresoras.o 

# Documentacion
doc:
	doxygen Doxyfile

# Borrar ficheros intermedios
clean :
	\rm -rf $(OBJ)/*.o \rm $(SRC)/*~ $(INCLUDE)/*~ Makefile~ 

# Reestablecer la estructura
mrproper : clean
	\rm -rf $(BIN)/* $(DOC)/html
