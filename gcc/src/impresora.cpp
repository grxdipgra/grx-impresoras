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
	os << "\033[1;32mNombre: \033[0m" << impresora.get_atributo("Printer") << endl;
  os << "\033[1;32mInfo: \033[0m";
  os << impresora.get_atributo("Info") << endl << "\033[1;32mDeviceUri: \033[0m";
  os << impresora.get_atributo("DeviceUri") << endl << "\033[1;32mMakeModel: \033[0m";
  os << impresora.get_atributo("MakeModel") << endl <<  "\033[1;32mPPD: \033[0m";
  os << impresora.get_atributo("PPD") << endl;
  return os;
}

/******************************************************************************/

/*Fin del archivo impresora.cpp*/
