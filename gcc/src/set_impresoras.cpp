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
#include <iostream>
#include <fstream>

using namespace std;

/******************* FUNCIONES PUBLICAS **************************************/
 
set_impresoras::set_impresoras(string config = ARCHIVO_CONFIGURACION)
{
	impresora aux;
	ifstream printers_conf;
    string nombre = ARCHIVO_CONFIGURACION;
    string comienzo_impresora = "<Printer";
	string fin_impresora = "</Printer>";
	string printer, info, conexion, driver;
	string comienzo_info = "Info";
	string comienzo_conexion = "DeviceURI";
	string comienzo_driver = "MakeModel";
	string ppd = ".ppd";
	string linea;
 
    printers_conf.open ( nombre.c_str() , ios::in);
    if (printers_conf.is_open()) {
        while (! printers_conf.eof() ) {
            getline (printers_conf,linea);
			if(linea.find(comienzo_impresora) != string::npos){
					printer = linea.substr(9,linea.length()-10);				
					cout << "Impresora CUPS: " << printer << endl;				
					cout << "PPD: " << printer << ppd << endl; 
					while (linea.find(fin_impresora) == string::npos){
						getline (printers_conf,linea);
						if(linea.find(comienzo_info) != string::npos){
							info = linea.substr(5,linea.length()-5);
							cout << "Info: " << info << endl;
						}
						if(linea.find(comienzo_conexion) != string::npos){
							conexion = linea.substr(10,linea.length()-10);
							cout << "Conexión: " << conexion << endl;
						}
						if(linea.find(comienzo_driver) != string::npos){
							driver = linea.substr(10,linea.length()-10);
							cout << "Driver: " << driver << endl;
						}
					}
			cout << "******************" << endl;
			}
		aux.set_atributo("Printer", printer);
		ppd = printer + ppd;
		aux.set_atributo("PPD", ppd);
		aux.set_atributo("Info", info);	
		aux.set_atributo("DeviceUri",conexion);
		aux.set_atributo("MakeModel",driver);
		impresoras.push_back(aux);
        }
        printers_conf.close();
    }
    else cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;  
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
	impresoras.push_back(printer);
}

/******************************************************************************/

const unsigned char set_impresoras::size()
{
	return impresoras.size();
}

/******************************************************************************/

const impresora& set_impresoras::operator[](int indice)const
{
	int i;
    assert(i >= 0 && i < (int)impresoras.size());
    return impresoras[i];
 }

/******************************************************************************/

ostream& operator<<(ostream& os, set_impresoras& impresoras)
{
	for (int i = 0 ; i< (int)impresoras.size() ; ++i)
	{
		os << impresoras.get_impresora(i) << endl; 
	} 
    return os;  
}

/******************* FUNCIONES PRIVADAS **************************************/

utsname* sys_info()
{
    utsname* info;
    if ( uname(info) != 0)
    {
        cout << "fallo: " << std::strerror(errno) << '\n';
        //log_handle("Error leyendo la configuración del sistema");
    }
    return info;
}

/******************************************************************************/

/*Fin del archivo set_impresoras.cpp*/
