/*****************************************************************************/ 
/**
	* @file set_impresoras.cpp
	* @brief Archivo principal de la clase set_impresora
	* @author Alejandro Castilla Peula
	* @date Noviembre-2017
	*/
/*****************************************************************************/

#include "set_impresoras.h"
#include "impresora.h"

/******************* FUNCIONES PUBLICAS **************************************/
 
set_impresoras::set_impresoras()
{
	this->impresoras = new vector<impresora>;
}

/******************************************************************************/

set_impresoras::~set_impresoras()
{
	this->impresoras.clear();
}

/******************************************************************************/ 

impresora set_impresoras::get_impresora(int indice)
{
	return impresoras[indice];
}

/******************************************************************************/ 

void set_impresoras::set_impresora(impresora printer)
{   
	impresoras.insert(printer);
}

/******************************************************************************/

const impresora& set_impresoras::operator[](int indice)const
{
        assert(i>=0 && i<Size(this->impresoras));
        return impresoras[i];
 }

/******************* FUNCIONES PRIVADAS **************************************/

utsname* sys_info()
{
    utsname* info;
    if ( uname(info) != 0)
    {
        cout << "fallo: " << std::strerror(errno) << '\n';
        log_handle("Error leyendo la configuración del sistema");
        return "NULL";
    }
    else return info;
}

/******************************************************************************/

/*Fin del archivo set_impresoras.cpp*/
