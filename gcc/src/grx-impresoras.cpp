/*****************************************************************************/
/**
* @file grx-impresoras.cpp
* @brief Archivo principal del programa grx-impresoras. Para la ejecución del programa se
        crea un servicio llamado grx-impresoras que llama al ejecutable grx-impresoras hubicado en /usr/bin.
        Se recolectan los datos de impresoras del equipo que se envian median CURL al scrip hubicado en
        http://incidencias.dipgra.es/impresoras.php que se encarga de su procesado, insertando los nuevos dispositivos
        (si existen) encontrados, para posteriormente, descargar he instalar los nuevos dispositivos, de la lista actualizada
        (si procede). del servicio se realiza mediante los comandos habituales de manejo de servicios.
* @author Alejandro Castilla Peula OSL Diputacion de Granada
* @ver 0.1 - Incorpora la posibilidad de lanzar procesos concurrentes con std::thread.
* @date Noviembre - 2017
*
* This code is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
*/
/*****************************************************************************/

#include <set_impresoras.h>
#include <thread>
#include <signal.h>
#include <syslog.h>   // funciones del sistema de log
#include <stdlib.h>  // itoa() atol()
#include <sstream>

int main(int argc, char **argv)
{
    set_impresoras impresoras_equipo;
	//impresora aux;
	//for (int i=0 ; i < (int)impresoras_equipo.size() ; i++){
		cout << impresoras_equipo;
		cout << "*******************" << endl ;
	//}
    cout << "Número de impresoras:" <<  impresoras_equipo.size() << endl;
	return 0;
}

/* Fin archivo grx-impresoras.cpp */
