/*****************************************************************************/ 
/**
	* @file impresora.h
	* @brief Archivo de cabecera del TDA impresora
	* @author Alejandro Castilla Peula
	* @date Noviembre - 2017
	*/
/*****************************************************************************/

/*****************************************************************************/

#ifndef IMPRESORA_H
#define IMPRESORA_H
#define ARCHIVO_CONFIGURACION /etc/cups/printer.conf
#define DIRECTORIO_SALIDA /tmp/grx-impresoras

/*****************************************************************************/
#include <iostream>	//cout
#include <stdio.h>	//printf
#include <stdlib.h>
#include <time.h>
#include <string.h>	//strlen
#include <string>	//string
#include <cstring>
#include <sys/types.h>  //socket, bind
#include <sys/socket.h>	//socket, bind
#include <sys/time.h>
#include <errno.h>
#include <fstream>
#include <pair>
#include <map>

using namespace std;

/*
	Clase IMPRESORAS
*/

class impresoras
{	

public:

/****************************** CONSTRUCTOR ***********************************/

/** 
  * @brief Constructor de la clase que se encarga de la inicializacion de las propiedades del objeto.
    @param @c familia dominio de comunicaciones, puede ser @c AF_INET o @c PF_INET.
    @param @c tipo tipo de socket, puede ser @c SOCK_STREAM (TCP) o @c SOCK_DGRAM (UDP).
    @return Un objeto de tipo @c tcp_client devuelto es un objeto valido de la clase, preparado para 
		escuchar en una @c IP:puerto.
  * 
*/
	impresora();

/****************************** DESTRUCTOR ***********************************/

/** 

  * @brief destructor de la clase que se encarga de cerrar el socket.
  * 
*/
	~impresora();

	
/******************************************************************************/
/**
  * @brief asociacion del socket a la interface de red y puerto determinados.
    @param @c address de tipo @c string con la direccion ip a asociar en formato decimal.
	@param @c port de tipo @c int con el numero de puerto en el que escuchar.
	@pre el descriptor de socket a asociar debe existir en el objeto @c server_tcp.
	@return @c true si se establecido la escucha y @c false en caso contrario. 	
*/
	pair<string,string> get_atributo(string nombre);
	
/******************************************************************************/ 
/**

  * @brief Establece una conexión con el equipo cliente.
    @param @a cliente de tipo @c sockaddr_in que recibe los datos de conexión del cliente.
	@param @a msgsock de tipo @c int que recibe el id del socket a conectar.
	@return @c true si la conexion se ha establecido y @c false en caso contrario. 	

*/
	void set_atributo (pair<string,string> atributo);

/******************************************************************************/	
/**
  * @brief Envia datos al equipo conectado al socket.
    @param @a datos de tipo @c string con los datos a enviar.
	@param @a num_bytes referencia de tipo @c entero donde se devuelve el numero de bytes enviados.
	@param @a cliente de tipo @c sockaddr_in que recibe los datos de conexión del cliente.
	@param @a msgsock de tipo @c int que recibe el id del socket a conectar.
	@pre Para enviar los datos debe existir una conexion activa con el cliente.
	@return @c true si los datos se han enviado y @c false en caso contrario. 	
*/
//	bool enviar(string datos, int & num_bytes, int &msgsock, struct sockaddr_in &cliente);
	
/******************************************************************************/	
/**
  * @brief Recibe datos del equipo conectado.
    @param @a size de tipo @c int con el tamanio del buffer de recepcion.
	@param @a cliente de tipo @c sockaddr_in que recibe los datos de conexión del cliente.
	@param @a msgsock de tipo @c int que recibe el id del socket a conectar.
	@pre Para recibir los datos debe existir una conexion activa con el equipo destino.
	@return Un @c string con los datos recibidos. 	
*/
//	string recibir(int size, int & num_bytes, int msgsock, struct sockaddr_in cliente);
	
/******************************************************************************/

private:
	//datos de la impresora, nombre ppd, driver
	map <string, string> datos;
	//nombre descriptivo
	string descripcion;
	
};//Fin de la clase impresora


#endif

/*Fin del archivo impresoras.h*/
