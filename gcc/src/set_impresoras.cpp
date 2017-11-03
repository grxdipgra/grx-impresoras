/*****************************************************************************/ 
/**
	* @file server_tcp.cpp
	* @brief Archivo principal del TDA server_tcp
	* @author Alejandro Castilla Peula
	* @date Enero-2013
	*/
/*****************************************************************************/

#include "server_tcp.h"

/******************************************************************************/ 
 
server_tcp::server_tcp(int familia, int tipo_socket)
{
	this->tipo_socket = (__socket_type) tipo_socket;
	// Crea el socket
	sock = socket(familia , tipo_socket , 0);
	server.sin_family = familia;
	if (!sock){
        	cout <<" Servidor: socket() fallido con error" << stderr << endl;
	}
	else	
		cout<<"Socket creado\n";
}

/******************************************************************************/

server_tcp::~server_tcp()
{
	close(sock);
}

/******************************************************************************/ 

bool server_tcp::asociar(string address , int puerto)
{
    server.sin_addr.s_addr = (address.empty() ? INADDR_ANY:inet_addr(address.c_str()));
    /* El Puerto DEBE estar en Network Byte Order */
    server.sin_port = htons(puerto);
				
	//LISTEN bind() asocia una combinacion de direccion local y puerto con el socket recien creado.
    if (bind(sock, (struct sockaddr*) &server, sizeof(server)) < 0 )
       {
	   cout << "Servidor: bind() fallido con error " << stderr << endl;
       return false;
    }
    else
       cout <<"Servidor: bind() OK. Servidor asociado a la direccion " << address << " y al puerto " << puerto << endl;

     //Todo lo hecho es aplicable tanto a TCP como a UDP. 
     //sin embargo hay algunos pasos que no funcionan cuando el servidor
     // usa UDP. No se puede listen() en un socket UDP.
    if (tipo_socket != SOCK_DGRAM)
       {
        if (listen(sock,5) < 0)
              {
			cout << "Servidor: listen() fallido con error " << stderr << endl;
            return false;
        }
       else
            cout << "Servidor: listen() OK." << endl;
    }
	
    cout << "Servidor: Escuchando y esperando conexiones en el puerto: " << puerto << endl;
	return true;
}

/******************************************************************************/ 

bool server_tcp::conectar(struct sockaddr_in &cliente, int & msgsock )
{
		socklen_t cliente_len = sizeof(cliente);
        // accept() no funciona con UDP, ya que no se hace listen()
        if (sock != SOCK_DGRAM)
        {
            msgsock = accept(sock, (struct sockaddr *) &cliente,&cliente_len);
            if (!msgsock)
           {
				cout << "Servidor: accept() error " << stderr << endl;
                return false;
            }
           else
				cout << "Servidor: accept() OK." << endl;
				cout << "Servidor: conexion aceptada desde "<< inet_ntoa(cliente.sin_addr) << ":" << htons(cliente.sin_port) << endl;
        }
        else
            msgsock = sock;
			return true;
}

/******************************************************************************/

bool server_tcp::enviar(string datos,  int & num_bytes, int &msgsock, struct sockaddr_in &cliente)
{
	if (tipo_socket != SOCK_DGRAM)
        num_bytes = send(msgsock, datos.c_str(), datos.size(), 0);
	else
    num_bytes = sendto(msgsock, datos.c_str(), datos.size(), 0, (struct sockaddr *)&cliente, sizeof(cliente));
	
	if (!num_bytes)
    {
		cout << "Servidor: send() fallido: error %d\n" << stderr << endl;
		return false;
    }
    else
		cout << "Servidor: send() OK." << endl;
        
	if (tipo_socket != SOCK_DGRAM)
    {
		cout << "Servidor: Esperando nuevas conexiones cliente desde el mismo u otro equipo..." << endl;
		close(msgsock);
    }
	else 
		cout << "Servidor: UDP server en bucle para mas peticiones\n" << endl;
    return true;
}


/******************************************************************************/

string server_tcp::recibir(int size, int & num_bytes, int msgsock, struct sockaddr_in cliente)
{
	 // En caso de SOCK_STREAM, el servidor puede hacer recv() y send() en
        // el socket establecido y despues cerrarlo.
        // Sin embargo, para SOCK_DGRAM (UDP), el servidor debe hacer recvfrom() y sendto() en un bucle.
	char buffer[size];
    string datos;
	
	if (tipo_socket != SOCK_DGRAM)
		num_bytes = recv(msgsock, buffer, sizeof(buffer), 0);
	else
       {
		num_bytes = recvfrom(msgsock,buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, (socklen_t*)sizeof(cliente));
		cout << "Servidor: Recibido datagram desde " << inet_ntoa(cliente.sin_addr) << endl;
        }
	if (!num_bytes)
        {
		cout << "Servidor: recv() fallido: error " << stderr << endl;
		close(msgsock);
        }
	else
		cout << "Servidor: recv() OK." << endl;
	if (num_bytes == 0)
        {
		cout << "Servidor: Cliente a cerrado la conexion." << endl;
		close(msgsock);
        }
    datos = buffer;
    datos = datos.substr(0,num_bytes);
	return datos;
}

/*Fin del archivo server_tcp.cpp*/

