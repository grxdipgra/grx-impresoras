/*****************************************************************************/ 
/**
	* @file set_impresoras.cpp
	* @brief Archivo principal de la clase set_impresora
	* @author Alejandro Castilla Peula
	* @date Noviembre-2017
	*/
/*****************************************************************************/

#include "set_impresoras.h"
#include "impresora.h"

/******************************************************************************/ 
 
set_impresoras::set_impresoras()
{
	this->impresoras = new vector<impresora>;
}

/******************************************************************************/

set_impresoras::~set_impresoras()
{
	this->impresoras.clear();
}

/******************************************************************************/ 

impresora set_impresoras::get_impresora(int indice);
{
    
	return impresoras[indice];
}

/******************************************************************************/ 

void set_impresoras::set_impresora(impresora printer);
{
    
	impresoras.insert(printer);
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

/*Fin del archivo set_impresoras.cpp*/

