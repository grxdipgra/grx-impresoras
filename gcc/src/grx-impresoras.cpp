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
#include <util.h>
#include <thread>
#include <signal.h>
#include <syslog.h>   // funciones del sistema de log
#include <stdlib.h>  // itoa() atol()
#include <sstream>	

int main(int argc, char *argv[])
{

    impresoras impresoras_equipo;

    /* Argumentos, si se han pasado */
    if (argc > 1)
       {
        for(i=1; i<argc; i++)
              {
                     // Opciones...
            if ((argv[i][0] == '-') || (argv[i][0] == '/'))
                     {
                            // Cambio a minusculas ... si se necesita
                          switch(tolower(argv[i][1]))
                           {
                     // si -p o /p
                    case 'p':
                        if (!strcmp(argv[i+1], "TCP"))
                            tipo_socket = SOCK_STREAM;
                        else if (!strcmp(argv[i+1], "UDP"))
                            tipo_socket = SOCK_DGRAM;
                        else
                            Uso(argv[0]);
                        i++;
                        break;
                        
                     // si -i o /i ... si existen varias
                    case 'i':
                        ip_address = argv[++i];
                        break;

                    // si -e o /e
                    case 'e':
                        puerto = atoi(argv[++i]);
                        break;

					// si -e o /e
                    case 'd':
                        direccion_dmx = atoi(argv[++i]);
                        break;

		    		case 'n':
                        canales = atoi(argv[++i]);
                        break;

					case 's':
                        subred = atoi(argv[++i]);
                        break;

 					case 'u':
                        universo = atoi(argv[++i]);
                        break;

					case 'c':
			puerto_serie = (argv[++i]);
			break;
                     // Por defecto...
                    default:
                        Uso(argv[0]);
                        break;
                }
            }
            else
                Uso(argv[0]);
        }
    }

//******** LOOP DE FUNCIONAMIENTO ***********************/

  while(program_run)
    {
        if(parametros[0] != server.get_pan() || parametros[1] != server.get_tilt()){
	        VISCA_set_pantilt_absolute_position(&interface, &camara, 18, 14, server.get_pan(), server.get_tilt());
            parametros[0] = server.get_pan();
            parametros[1] = server.get_tilt();
        }

        if(parametros[2] != server.get_zoom()){
	        VISCA_set_zoom_value(&interface, &camara, server.get_zoom());
            parametros[2] = server.get_zoom();
        }
	    
        if(parametros[3] != server.get_brillo()){
	        VISCA_set_bright_value(&interface, &camara, server.get_brillo());
            parametros[3] = server.get_brillo();
        }
                 
        if(parametros[4] != server.get_mirror()){       
            if (server.get_mirror() >= 0x80){
                VISCA_set_mirror(&interface, &camara, 0x02);//on=0x02 off=0x03
            }
            else VISCA_set_mirror(&interface, &camara, 0x03);
            parametros[4] = server.get_mirror();
        }

	    if (server.get_reset())
	        VISCA_set_pantilt_reset(&interface, &camara);

        server.set_ledVisca(false);
       
	}

	thread_recepcion = false;
	recibir.join();
	thread_led_artnet = false;
	led_artnet.join();
	thread_led_visca = false;
	led_visca.join();
	VISCA_close_interface(&interface);
	log_handle("Conexion serie cerrada");
	log_handle("Dispositivo artnet terminado");   
	return 0;
}

/* Fin archivo dev-artnet.cpp */
