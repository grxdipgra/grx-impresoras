/**
  * @file utils.h
  * @brief Fichero cabecera con utilidades 
  * @author Alejandro Castilla Peula OSL Diputacion de Granada
  * @date Novienbre 2017
  * License: GNU Public License 
  */

/******************************************************************************/

#ifndef _UTILS_H_
#define _UTILS_H_

/******************************************************************************/

#include <fstream>

/******************************************************************************/

/**
  * @brief comprueba la existencia del fichero.
  * @param nombre indica el archivo de disco que consultar.
  * @retval true si el archivo existe y puede ser abierto.
  * @retval false en caso contrario.
  */
bool ExisteFichero(const char* nombre);

/******************************************************************************/
