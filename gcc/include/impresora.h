/**
	* @file impresora.h
	* @brief Archivo de cabecera del TDA impresora
	* @author Alejandro Castilla Peula OSL Diputacion de Granada
	* @date Noviembre  2017
	* License: GNU Public License 
	*/
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

class impresora
{	

public:

/****************************** CONSTRUCTOR ***********************************/

/** 
  * @brief Constructor de la clase que se encarga de la inicializacion de las propiedades del objeto.
    @param @a printers_conf archivo de configuracion de impresoras del sistema
    @return Un objeto de tipo @c impresora el objeto devuelto es un objeto valido de la clase.
  * 
*/
	impresora(const char * printers_conf);

/****************************** DESTRUCTOR ***********************************/

/** 

  * @brief destructor de la clase.
  * 
*/
	~impresora();

	
/******************************************************************************/
/**
  * @brief seleciona el atributo @c nombre del objeto.
    @param @a nombre de clave del atributo a extraer.
	@return un objeto de tipo @c pair<string,string> con la clave y el valor asociado al atributo. 	
*/
	pair<string,string> get_atributo(string nombre);
	
/******************************************************************************/ 
/**

  * @brief establece el valor del atributo indicado
    @param @a atributo nombre de la clave 
	@param @a valor valor asignado al par de @c clave @a atributo
	@post se modifica el objeto con la nueva clave @c pair<@a atributo, @a valor> o bien se inserta si no existe. 	

*/
	void set_atributo (string atributo, string valor);
	
/******************************************************************************/

private:
	//datos de la impresora, nombre ppd, driver
	map <string, string> datos;
	//nombre descriptivo
	string descripcion;
	
};//Fin de la clase impresora


#endif

/*Fin del archivo impresora.h*/
