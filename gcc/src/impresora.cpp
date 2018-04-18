	/**
	* @file impresora.cpp
	* @brief Archivo principal del TDA impresora
	* @author Alejandro Castilla Peula OSL Diputacion de Granada
	* @date Noviembre 2017
	* License: GNU Public License
	*/

/*****************************************************************************/

#include "impresora.h"
#include <sstream> // double -> string

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

string impresora::get_tiempo()
{
	struct tm *timeinfo;
	const char* timestr = get_atributo("StateTime").c_str();
	time_t timenum = (time_t) strtol(timestr, NULL, 10);
	timeinfo = localtime (&timenum);
  return asctime(timeinfo);
}

/******************************************************************************/

string impresora::get_instalacion()
{
	struct tm *timeinfo;
	const char* timestr = get_atributo("ConfigTime").c_str();
	time_t timenum = (time_t) strtol(timestr, NULL, 10);
	timeinfo = localtime (&timenum);
  return asctime(timeinfo);
}

/******************************************************************************/

string impresora::get_tiempo_sin_uso()
{
	struct tm *timeinfo;
	//tm *p;
	long int ahora, time_impresora;
	time (&ahora);
	time_t diferencia;
	time_impresora = atoi( get_atributo("StateTime").c_str() );
	diferencia = ahora - time_impresora;
	//p = gmtime(&diferencia);
	//cout << p->tm_yday << " dias ";
	//cout << p->tm_hour << " horas ";
	//cout << p->tm_min << " minutos ";
	//cout << p->tm_sec << " segundos" << endl;
	timeinfo = localtime (&diferencia);
	ostringstream strs; //convertir int to string
	strs << ahora - time_impresora;
  string str = strs.str();
	return asctime(timeinfo);
}

/******************************************************************************/

void impresora::set_atributo (const string& key, const string& valor)
{
        datos.find(key)->second = valor;
}

 /******************************************************************************/

ostream& operator<<(ostream& os, impresora& impresora)
{
	//time(&timenum);
	os << "\033[1;32mNombre: \033[0m" << impresora.get_atributo("Printer") << endl;
  os << "\033[1;32mInfo: \033[0m";
  os << impresora.get_atributo("Info") << endl << "\033[1;32mDeviceUri: \033[0m";
  os << impresora.get_atributo("DeviceUri") << endl << "\033[1;32mMakeModel: \033[0m";
  os << impresora.get_atributo("MakeModel") << endl <<  "\033[1;32mPPD: \033[0m";
  os << impresora.get_atributo("PPD") << endl << "\033[1;32mUsada: \033[0m";
	os << impresora.get_tiempo() << endl << "\033[1;32mSin uso: \033[0m";
	os << impresora.get_tiempo_sin_uso() << endl << "\033[1;32mInstalacion: \033[0m";
	os << impresora.get_instalacion() << endl;
  return os;
}

/******************************************************************************/

/*Fin del archivo impresora.cpp*/
