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
#define ARCHIVO_CONFIGURACION "/etc/cups/printers.conf"
#define NUMCLAVES 7
#define DIRECTORIO_SALIDA /tmp/grx-impresoras
#define CLAVES ( Printer,  Info,  DeviceUri,  MakeModel, PPD, StateTime, ConfigTime )

/*****************************************************************************/
#include <iostream>	//cout
#include <stdio.h>	//printf
#include <stdlib.h>
#include <ctime> //manejo de fechas
#include <time.h> // time(), localtime(), manejo de fechas
#include <string.h>	//strlen
#include <string>	//string
#include <cstring>
#include <sys/types.h>  //socket, bind
#include <sys/socket.h>	//socket, bind
#include <sys/time.h>
#include <errno.h>
#include <fstream>
#include <utility>
#include <map>

using namespace std;

/*
	Clase IMPRESORAS
*/

const static string claves[] = { "Printer", "Info", "DeviceUri", "MakeModel",
                                "PPD", "StateTime", "ConfigTime" };

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
    impresora();


/****************************** DESTRUCTOR ***********************************/

/**

  * @brief destructor de la clase.
  *
*/
	~impresora();


/******************************************************************************/
/**
  * @brief seleciona el atributo @c nombre del objeto.
    @param @a key de clave del atributo a extraer.
    @return un objeto de tipo @c pair<string,string> con la clave y el valor asociado al atributo.
*/
	const string get_atributo(const string& key);

/******************************************************************************/

string get_tiempo();
string get_tiempo_sin_uso();
string get_instalacion();

/**

  * @brief establece el valor del atributo indicado
    @param @a atributo nombre de la clave
    @param @a valor valor asignado al par de @c clave @a atributo
    @post se modifica el objeto con la nueva clave @c pair<@a atributo, @a valor> o bien se inserta si no existe.

*/
    void set_atributo (const string& key,const string& valor);

/******************************************************************************/

 /**
   * @brief sobrecarga operador <<.
   * @param @c os objeto ostream de salida
   * @param @c impresora el objeto que se quiere imprimir
 */
    friend ostream& operator<<(ostream& os, impresora& impresora);

/******************************************************************************/

private:
	//datos de la impresora, nombre ppd, driver
	map <string, string> datos;
    //nombre descriptivo -> campo Printer de printers.conf
	//string descripcion;
    //const static string claves[5] = { "Printer", "Info", "DeviceUri", "MakeModel", "PPD", StateTime };
        /**
          Valores de las claves a crear.
          Printer : nombre de la impresora que es el nombre del ppd
                    se puede modificar si en la gui se le cambia
                    el nombre, por lo cual se deb cambiar al campo Info
                    con los espacios cambiados por "_"
          Info : nombre del fabricante de la impresora
          DeviceUri :información del tipo de conexión
          MakeModel : Descripcion del driver usado (PCL, postscript, etc)
          PPD : nombre del PPD (se cambia si ha sido modificado). Debe crearse
                una copia para no romper el sistema.
          */

};//Fin de la clase impresora


#endif

/*Fin del archivo impresora.h*/
