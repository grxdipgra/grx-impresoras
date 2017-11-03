CC = g++
CPPFLAGS = -Wall -std=c++0x -g -I$(INCLUDE) -I$(WIPINCLUDE)

LDFLAGS =  -L$(LIB)/ -lvisca 
LDWIRI = -L$(WIPILIB)/ -lwiringPi

LIB = ./lib
WIPILIB = /usr/local/lib
INCLUDE = ./include
WIPINCLUDE = /usr/local/include
BIN = ./bin
SRC = ./src
OBJ = ./obj

all: dev-artnet app_cliente app_server raspip

#Compilacion del archivo *.cpp necesario
$(OBJ)/%.o : $(SRC)/%.cpp $(INCLUDE)/%.h
	$(CC) -c $(CPPFLAGS) $< -o $@ 

#Compilacion del archivo *.c necesario
#$(OBJ)/%.o : $(SRC)/%.c $(INCLUDE)/%.h
#	$(CC) -c $(CPPFLAGS) $< -o $@ 

# Compilando server_tcp.cpp
$(OBJ)/server_tcp.o: $(SRC)/server_tcp.cpp $(INCLUDE)/server_tcp.h 
	$(CC) -c $(CPPFLAGS) $(LDWIRI) $(SRC)/server_tcp.cpp -o $(OBJ)/server_tcp.o

# Compilando app_server.cpp
$(OBJ)/app_server.o: $(SRC)/app_server.cpp $(INCLUDE)/server_tcp.h
	$(CC) -c $(CPPFLAGS) $(SRC)/app_server.cpp -o $(OBJ)/app_server.o

# Compilando cliente_tcp.cpp
$(OBJ)/cliente_tcp.o: $(SRC)/cliente_tcp.cpp $(INCLUDE)/cliente_tcp.h
	$(CC) -c $(CPPFLAGS) $(SRC)/cliente_tcp.cpp -o $(OBJ)/cliente_tcp.o

# Compilando app_cliente.cpp
$(OBJ)/app_cliente.o: $(SRC)/app_cliente.cpp $(INCLUDE)/cliente_tcp.h
	$(CC) -c $(CPPFLAGS) $(SRC)/app_cliente.cpp -o $(OBJ)/app_cliente.o

# Compilando server_artnet.cpp
$(OBJ)/server_artnet.o: $(SRC)/server_artnet.cpp $(INCLUDE)/server_artnet.h 
	$(CC) -c $(CPPFLAGS) $(LDWIRI) $(SRC)/server_artnet.cpp -o $(OBJ)/server_artnet.o
	
# Compilando dev-artnet.cpp
$(OBJ)/dev_artnet.o: $(SRC)/dev_artnet.cpp $(INCLUDE)/server_artnet.h 
	$(CC) -c $(CPPFLAGS) $(SRC)/dev_artnet.cpp -o $(OBJ)/dev_artnet.o

# Compilando frame.cpp
$(OBJ)/frame.o: $(SRC)/frame.cpp
	$(CC) -c $(CPPFLAGS) $(SRC)/frame.cpp -o $(OBJ)/frame.o

# Compilando util.cpp
$(OBJ)/util.o: $(SRC)/util.cpp
	$(CC) -c $(CPPFLAGS) $(SRC)/util.cpp -o $(OBJ)/util.o

# Compilando libvisca_hl.c
$(OBJ)/libvisca_hl.o: $(SRC)/libvisca_hl.c
	$(CC) -c $(CPPFLAGS) $(SRC)/libvisca_hl.c -o $(OBJ)/libvisca_hl.o

# Compilando raspip.cpp
$(OBJ)/raspip.o: $(SRC)/raspip.cpp
	$(CC) -c $(CPPFLAGS) $(SRC)/raspip.cpp -o $(OBJ)/raspip.o

# Compilando sha1.cpp
$(OBJ)/sha1.o: $(SRC)/sha1.cpp
	$(CC) -c $(CPPFLAGS) $(SRC)/sha1.cpp -o $(OBJ)/sha1.o

# Creacion del ejecutable bin/dev-artnet
dev-artnet: $(BIN)/dev-artnet
$(BIN)/dev-artnet: $(OBJ)/server_artnet.o $(OBJ)/dev_artnet.o $(OBJ)/frame.o $(OBJ)/util.o $(OBJ)/libvisca_hl.o $(OBJ)/sha1.o $(LIB)/libvisca.a
	$(CC) $(CPPFLAGS) -o $(BIN)/dev-artnet $(OBJ)/server_artnet.o  $(OBJ)/frame.o $(OBJ)/dev_artnet.o $(OBJ)/util.o  $(OBJ)/libvisca_hl.o $(OBJ)/sha1.o $(LDFLAGS) -lpthread -I/usr/local/include -L/usr/local/lib -lwiringPi

# Creacion del ejecutable bin/app_server
app_server: $(BIN)/app_server
$(BIN)/app_server: $(OBJ)/app_server.o $(OBJ)/server_tcp.o $(OBJ)/util.o
	$(CC) $(CPPFLAGS) -o $(BIN)/app_server $(OBJ)/server_tcp.o $(OBJ)/app_server.o $(OBJ)/util.o $(OBJ)/sha1.o -lpthread 

# Creacion del ejecutable bin/app_cliente
app_cliente: $(BIN)/app_cliente
$(BIN)/app_cliente: $(OBJ)/app_cliente.o $(OBJ)/cliente_tcp.o $(OBJ)/util.o
	$(CC) $(CPPFLAGS) -o $(BIN)/app_cliente $(OBJ)/app_cliente.o $(OBJ)/cliente_tcp.o $(OBJ)/util.o $(OBJ)/sha1.o

# Creacion del ejecutable bin/raspip
raspip: $(BIN)/raspip
$(BIN)/raspip: $(OBJ)/raspip.o $(OBJ)/raspip.o $(OBJ)/util.o
	$(CC) $(CPPFLAGS) -o $(BIN)/raspip $(OBJ)/raspip.o $(OBJ)/util.o $(OBJ)/sha1.o $(LDFLAGS) -lpthread -I/usr/local/include -L/usr/local/lib -lwiringPi

# Documentacion
doc:
	doxygen Doxyfile

# Borrar ficheros intermedios
clean :
	\rm -rf $(OBJ)/*.o \rm $(SRC)/*~ $(INCLUDE)/*~ Makefile~ 

# Reestablecer la estructura
mrproper : clean
	\rm -rf $(BIN)/* $(DOC)/html
