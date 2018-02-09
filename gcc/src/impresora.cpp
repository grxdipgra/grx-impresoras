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
 
impresora::impresora()
{
    map<string, string> aux;
	this->descripcion = descripcion;
	this->datos = new map <string, string>;
        aux.second = "NULL";
        for (int i = 0; i < sizeof(this->claves); ++i)
        {
            aux.first = claves[i];
            datos.insert(aux);
        }
}

/******************************************************************************/

impresora::~impresora()
{
	this->datos.clear();
}

/******************************************************************************/ 

const pair<string,string> impresora::get_atributo(const string& nombre)const
{

        map<char,int>::iterator it;
        it = datos.find(nombre);
        return *it;
}
/******************************************************************************/ 

void impresora::set_atributo (const string& key,const string& valor)
{
        map<char,int>::iterator it;
        it = datos.find(nombre);
        it.second = valor;
}

/******************************************************************************/

/*Fin del archivo impresora.cpp*/

