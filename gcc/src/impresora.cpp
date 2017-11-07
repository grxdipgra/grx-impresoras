/**
	* @file impresora.cpp
	* @brief Archivo principal del TDA impresora
	* @author Alejandro Castilla Peula OSL Diputacion de Granada
	* @date Noviembre 2017
	* License: GNU Public License 
	*/
/*****************************************************************************/

#include "impresora.h"

/******************************************************************************/ 
 
impresora::impresora(string descripcion)
{
	this->descripcion = descripcion;
	this->datos = new map <string, string>;
}

/******************************************************************************/

impresora::~impresora()
{
	this->datos.clear();
}

/******************************************************************************/ 

pair<string,string> impresora::get_atributo(string& nombre)
{
}
/******************************************************************************/ 

void impresora::set_atributo (pair<string,string>& atributo)
{
}

/******************************************************************************/

/*Fin del archivo impresora.cpp*/

