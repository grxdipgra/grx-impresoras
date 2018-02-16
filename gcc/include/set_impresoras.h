/*****************************************************************************/ 
/**
	* @file set_impresoras.h
	* @brief Archivo de cabecera del TDA set_impresoras
	* @author Alejandro Castilla Peula
	* @date Noviembre - 2017
	*/
/*****************************************************************************/

#ifndef SET_IMPRESORAS_H
#define SET_IMPRESORAS_H
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
#include <sys/time.h>
#include <sys/utsname.h> //version S.O., hostname, Hardware, etc.
#include <errno.h>
#include <fstream>
#include <utility>
#include <vector>
#include "impresora.h"
#include "utils.h"

using namespace std;

/*
	Clase SET_IMPRESORAS
*/

class set_impresoras
{	

public:

/****************************** CONSTRUCTOR ***********************************/

/** 
  * @brief Constructor de la clase que se encarga de la inicializacion de las propiedades del objeto.
    @return Un objeto de tipo @c set_impresora devuelto es un objeto valido de la clase.
*/
	set_impresoras(string printers_conf);

/****************************** DESTRUCTOR ***********************************/

/** 

  * @brief destructor de la clase que se encarga de liberar el map<string, string>
*/
	~set_impresoras();
	
/******************************************************************************/
/**
  * @brief Extrae un objeto impresora del conjunto de impresoras
    @param @a indice de tipo @c int de la impresora a extraer.
    @return un objeto de tipo @c impresora.
*/
	inline impresora get_impresora(int indice);
	
/******************************************************************************/ 
/**
  * @brief Inserta una impresora en el objeto impresoras.
    @param @a printer de tipo @c impresora a insertar en el conjunto.
*/
        inline void set_impresora(impresora printer);


/******************************************************************************/ 
/**
  * @brief obtiene el numero de impresoras del sistema.
    @return el numero de impresoras.
*/
		inline const unsigned char set_impresoras::size();

/******************************************************************************/
 /**
   * @brief sobrecarga operador de acceso constante.
   * @param índice dentro del @c impresoras de la impresora a la que se accede.
   * @pre el objeto al que se accede no se va a modificar
 */
        const impresora& operator[](int indice)const;
	
/******************************************************************************/

 /**
   * @brief sobrecarga operador <<.
   * @param @c os objeto ostream de salida
   * @param @c impresoras el objeto que se quiere imprimir
 */
        friend ostream& operator<<(ostream& os, const set_impresoras& impresoras);
	
/******************************************************************************/

private:

/********************** FUNCIONES PRIVADAS ************************************/

        utsname* sys_info();

/******************************************************************************/

    //string hostname; //nombre dns del equipo
    //string version_so; //version de sistema operativo
    utsname* info_equipo;
	string nodo; //dirección ip del nodo
	vector<impresora> impresoras; //impresoras del equipo
	
};//Fin de la clase set_impresoras

#endif

/*Fin del archivo set_impresoras.h*/
