CC = g++
CPPFLAGS = -Wall -std=c++0x -g -I$(INCLUDE) -I$(INCLUDE_STD)
INCLUDE = ./include
INCLUDE_STD = /usr/lib/include
INCLUDE_CURL = -lcurl
BIN = ./bin
SRC = ./src
OBJ = ./obj

all: impresoras

#Compilacion del archivo *.cpp necesario
$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@ $(INCLUDE_CURL)

# Compilando server_artnet.cpp
#$(OBJ)/server_artnet.o: $(SRC)/server_artnet.cpp $(INCLUDE)/server_artnet.h
#	$(CC) -c $(CPPFLAGS) $(LDWIRI) $(SRC)/server_artnet.cpp -o $(OBJ)/server_artnet.o

#Compilando grx-impresoras.cpp
#$(OBJ)/grx-impresoras.o: $(SRC)/grx-impresoras.cpp
#	$(CC) -c $(CPPFLAGS) $(SRC)/grx-impresoras.cpp -o $(OBJ)/grx-impresoras.o

# Creacion del ejecutable bin/grx-impresoras
impresoras: $(BIN)/impresoras
$(BIN)/impresoras: $(OBJ)/impresora.o $(OBJ)/set_impresoras.o $(OBJ)/grx-impresoras.o $(OBJ)/simplexml.o $(OBJ)/util.o
	$(CC) $(CPPFLAGS) -o $(BIN)/impresoras $(OBJ)/grx-impresoras.o $(OBJ)/impresora.o  $(OBJ)/set_impresoras.o $(OBJ)/simplexml.o $(OBJ)/util.o -lcurl

# Documentacion
doc:
	doxygen Doxyfile

# Borrar ficheros intermedios
clean :
	\rm -rf $(OBJ)/*.o \rm $(SRC)/*~ $(INCLUDE)/*~ Makefile~

# Reestablecer la estructura
mrproper : clean
	\rm -rf $(BIN)/* $(DOC)/html
