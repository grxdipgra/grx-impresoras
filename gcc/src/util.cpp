/**
  * @file utils.cpp
  * @brief Fichero con las definiciones de los metodos de utilidades.
  * Implementa la interfaz de utils.h
  * @author Alejandro Castilla Peula OSL Diputacion de Granada
  * @date Noviembre 2017
  * License: GNU Public License 
  */

/******************************************************************************/

#include <util.h>

bool ExisteFichero(const char* nombre)
{
	ifstream fichero;
	bool problema;

	fichero.open(nombre);
	problema=fichero.fail();
	if(!problema) fichero.close();

	return ((problema)?false:true);
}

/******************************************************************************/

/******************* LOG *****************************/

//void log_handle(string log){
/*http://stackoverflow.com/questions/10952515/c-c-syslog-to-custom-file-not-var-log-syslog-but-var-log-mylog-ubuntu-12*/
//    openlog(NULL, 0, LOG_USER);
//    syslog(LOG_INFO, (char*)log.c_str());
//    setbuf(stdout,0);
//}
