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

const string impresora::get_atributo(const string& key)const
{

        map<char,int>::iterator it;
        it = datos.find(key);
        return it.second;
}

/******************************************************************************/ 

void impresora::set_atributo (const string& key,const string& valor)
{
        map<char,int>::iterator it;
        it = datos.find(nombre);
        it.second = valor;
}

/******************************************************************************/ 

ostream& operator<<(ostream& os, const impresora& impresora)
{
	os << "Nombre: " << impresora.get_atributo("Printer") << endl << "Info: " << impresora.get_atributo("Info") << endl << "DeviceUri: " << impresora.get_atributo("DeviceUri") << endl << "MakeModel: " << impresora.get_atributo("MakeModel") << endl <<  "PPD: " << impresora.get_atributo("PPD") << endl; 
    return os;  
}

/******************************************************************************/

/*Fin del archivo impresora.cpp*/

