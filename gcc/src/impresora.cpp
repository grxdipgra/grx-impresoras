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
	//cout << "Constructor impresora" << endl;
	pair <string,string> aux;
	//cout << "Numero de claves: " << NUMCLAVES << endl;
	for (int i = 0; i < NUMCLAVES; ++i)
    {	
		aux.first = claves[i];
		aux.second = "NULL";
		datos.insert(aux);  	
	}
	//cout << "Fin constructor impresora" << endl;
}

/******************************************************************************/

impresora::~impresora()
{
	this->datos.clear();
}

/******************************************************************************/ 

const string impresora::get_atributo(const string& key)
{
        return datos.find(key)->second;
}

/******************************************************************************/ 

void impresora::set_atributo (const string& key, const string& valor)
{
        datos.find(key)->second = valor;
}

/******************************************************************************/ 

ostream& operator<<(ostream& os, impresora& impresora)
{
	os << "Nombre: " << impresora.get_atributo("Printer") << endl << "Info: " << impresora.get_atributo("Info") << endl << "DeviceUri: " << impresora.get_atributo("DeviceUri") << endl << "MakeModel: " << impresora.get_atributo("MakeModel") << endl <<  "PPD: " << impresora.get_atributo("PPD") << endl; 
    return os;  
}

/******************************************************************************/

/*Fin del archivo impresora.cpp*/

