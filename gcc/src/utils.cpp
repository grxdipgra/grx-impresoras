/**
  * @file utils.cpp
  * @brief Fichero con las definiciones de los metodos de utilidades.
  * Implementa la interfaz de utils.h
  * @author Alejandro Castilla Peula OSL Diputacion de Granada
  * @date Noviembre 2017
  * License: GNU Public License 
  */

/******************************************************************************/

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
