/**
  * @file utils.h
  * @brief Fichero cabecera con utilidades
  * @author Alejandro Castilla Peula OSL Diputacion de Granada
  * @date Novienbre 2017
  * License: GNU Public License
  */

/******************************************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

/******************************************************************************/
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h> // strerror()
#include <cstring>
#include <vector>

using namespace std;

/******************************************************************************/

/**
  * @brief comprueba la existencia del fichero.
  * @param nombre indica el archivo de disco que consultar.
  * @retval true si el archivo existe y puede ser abierto.
  * @retval false en caso contrario.
  */

bool ExisteFichero(const char* nombre);

/******************************************************************************/

string getFile( string filename );                         // Reads whole file into a string buffer
vector<string> getData( const string &text, string tag );  // Gets collection of items between given tags
void stripTags( string &text );                            // Strips any tags

#endif
