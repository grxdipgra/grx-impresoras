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

#define MAX_THREADS 20

/*Variables globales, necesarias para el manejo de señales*/
bool program_run = true;
bool thread_recepcion = true;
bool thread_led_visca = true;
bool thread_led_artnet = true;

/******************* LOG *****************************/

void log_handle(string log){
/*http://stackoverflow.com/questions/10952515/c-c-syslog-to-custom-file-not-var-log-syslog-but-var-log-mylog-ubuntu-12*/
	openlog(NULL, 0, LOG_USER);
    syslog(LOG_INFO, (char*)log.c_str());   
    setbuf(stdout,0);
}

/************** HEBRAS ****************************/

void recepcion_dmx(server_artnet& server){
	while(thread_recepcion){
		if (server.recibir() == 1){ //paquete Art-Dmx
		    //cout << "Estado hebra recepcion: " << hex << server.estado()  << endl;
		    server.get_frame();
		    //cout << "Error de interpretacion" << endl;
        }
	}
	log_handle("Saliendo del hilo recepcion");
	//pthread_exit(NULL);
	return;
}

void hardware_artnet(server_artnet& server){
	while(thread_led_artnet){
		server.LedArtnet();
	}
	log_handle("Saliendo del hilo led_artnet");
	//pthread_exit(NULL);
	return;
}

void hardware_visca(server_artnet& server){
	while(thread_led_visca){
		server.LedVisca();
	}
	log_handle("Saliendo del hilo led_visca");
	//pthread_exit(NULL);
	return;
}


/***************** MANEJADOR SEÑALES ******************/

void INThandler(int sig) {
	signal (SIGUSR1,SIG_IGN) ;
	program_run=false;
	log_handle("Parando servicio server_artnet...");
}

/*************** LEER CONFIGURACION ******************/

string LeerConfiguracion(const char* nombre)
{
    string dato;
    if(!ExisteFichero(nombre)){
        log_handle("Error: no pudo abrirse el archivo: " + (string)nombre);
		exit(-1);
	}
    ifstream fi(nombre);
    getline(fi,dato);//lee el identificador de tipo
    fi.close();
    return dato;
}

/************* MAIN *********************/	

int main(int argc, char *argv[])
{

	impresoras impresoras_equipo; 
    unsigned short puerto= DEFAULT_PORT;
    int i;
	uint8_t direccion_dmx = atoi((LeerConfiguracion(ARCHIVO_ADDR)).c_str()); 
    uint8_t canales = DEFAULT_CANALES;
	uint8_t subred = atoi((LeerConfiguracion(ARCHIVO_SUBRED)).c_str()); 
    uint8_t universo = atoi((LeerConfiguracion(ARCHIVO_UNIVERSO)).c_str()); 
    int tipo_socket =  DEFAULT_PROTO;
	char *puerto_serie = (char*)"/dev/ttyAMA0";
	string log;
    uint8_t parametros[5];

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

	server_artnet server(AF_INET,tipo_socket,direccion_dmx,universo,subred,canales);

    log_handle("Direccion DMX-512 : " + static_cast<ostringstream*>( &(ostringstream() << (int)direccion_dmx) )->str());
    log_handle("Universo Art-Net: " + static_cast<ostringstream*>( &(ostringstream() << (int)universo) )->str());
    log_handle("Subred Art-Net: " + static_cast<ostringstream*>( &(ostringstream() << (int)subred) )->str());

    if (puerto == 0)
    {
        Uso(argv[0]);
		return 0;
    }

	log_handle("Direccion del socket: " + (string)ip_address + ":" + static_cast<ostringstream*>( &(ostringstream() << puerto) )->str());

	if (!server.asociar(ip_address,puerto)){
		log_handle("No se ha podido poner a la escucha el socket en " + (string)ip_address + ":" + static_cast<ostringstream*>( &(ostringstream() << puerto) )->str());
		log_handle("Abortando el programa... ");
		exit (-1);
	}


// Lanzamos los hilos que controlan la recepción de artnet y los leds	

	thread recibir(recepcion_dmx,std::ref(server));
	thread led_artnet(hardware_artnet,std::ref(server));
	thread led_visca(hardware_visca,std::ref(server));

// Se abre la conexión serie

	log_handle("Abriendo conexion serie...");
	VISCA_open_interface(&interface, &camara, puerto_serie);

// Se inicia el sistema de señales 

	signal(SIGUSR1, &INThandler);  //captura la señal SIGUSR1 para el dispositivo y lo cierra.

//Se establece el modo de exposición a Brillo (Gain+Iris)

    VISCA_set_exp_comp_reset(&interface, &camara);
    VISCA_set_bright_reset(&interface, &camara);
    VISCA_set_auto_exp_mode(&interface, &camara, 0x0D);

//inicializamos parametros

    for (int i = 0; i<5; ++i)
        parametros[i] = 0x0;

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
