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

set_impresoras::set_impresoras()
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
  sys_info();
  ip_nodo();

	cout << "Archivo de configuración es: " << nombre << endl ;
 	if (ExisteFichero(nombre.c_str()))
	{
    	printers_conf.open ( nombre.c_str() , ios::in);
    	if (printers_conf.is_open()) {
        	while (! printers_conf.eof() ) {
            	getline (printers_conf,linea);
				if(linea.find(comienzo_impresora) != string::npos){
					printer = linea.substr(9,linea.length()-10);
					//cout << "Impresora CUPS: " << printer << endl;
					//cout << "PPD: " << printer << ppd << endl;
					while (linea.find(fin_impresora) == string::npos){
						getline (printers_conf,linea);
						if(linea.find(comienzo_info) != string::npos){
							info = linea.substr(5,linea.length()-5);
							//cout << "Info: " << info << endl;
						}
						if(linea.find(comienzo_conexion) != string::npos){
							conexion = linea.substr(10,linea.length()-10);
							//cout << "Conexión: " << conexion << endl;
						}
						if(linea.find(comienzo_driver) != string::npos){
							driver = linea.substr(10,linea.length()-10);
							//cout << "Driver: " << driver << endl;
						}
					}
				//cout << "******************" << endl;
				aux.set_atributo("Printer", printer);
				ppd = ".ppd";
				ppd = printer + ppd;
				aux.set_atributo("PPD", ppd);
				aux.set_atributo("Info", info);
				aux.set_atributo("DeviceUri",conexion);
				aux.set_atributo("MakeModel",driver);
				impresoras.push_back(aux);
				}
        	}
        	printers_conf.close();
    	}
    	else cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;
	}
	else cout << "El fichero de configuración no existe" << endl;
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

size_t set_impresoras::size()
{
	return impresoras.size();
}

/******************************************************************************/

impresora& set_impresoras::operator[](int indice)
{
    assert(indice >= 0 && indice < (int)impresoras.size());
    return impresoras[indice];
 }

/******************************************************************************/

ostream& operator<<(ostream& os, set_impresoras& impresoras)
{
	for (int i = 0 ; i< (int)impresoras.size() ; ++i)
	{
		os << impresoras[i] << endl;
	}
  os << "Sistema: " << impresoras.info_equipo.sysname;
  os << " " << impresoras.info_equipo.nodename << endl;
  os << "Kernel: " << impresoras.info_equipo.release << endl;
  os << "Base: " << impresoras.info_equipo.version << endl;
  os << "Arch: " << impresoras.info_equipo.machine << endl;
  os << "Nodo: " << impresoras.info_equipo.domainname << endl;
  return os;
}

/******************* FUNCIONES PRIVADAS **************************************/

void set_impresoras::sys_info()
{
    if ( uname(&info_equipo) != 0)
    {
        cout << "fallo: " << std::strerror(errno) << '\n';
        //log_handle("Error leyendo la configuración del sistema");
    }
}

/******************************************************************************/

void set_impresoras::ip_nodo ()
{
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
            cout << "Flags:" << ifa->ifa_flags << endl;
            cout << "Is up:" << (ifa->ifa_flags & IFF_UP) << endl;
            if ((ifa->ifa_flags & IFF_LOOPBACK) == IFF_LOOPBACK)
            cout << "Es Loopback" << endl;
            cout << "Esta activa:" << (ifa->ifa_flags & IFF_RUNNING) << endl;
            get_mac(ifa->ifa_name);
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
}

/******************************************************************************/

string set_impresoras::get_mac (string interface)
{
  int s;
	struct ifreq buffer;
	s = socket(PF_INET, SOCK_DGRAM, 0);
  char* aux;
  string mac="";
	memset(&buffer, 0x00, sizeof(buffer));
	strcpy(buffer.ifr_name, interface.c_str());
	ioctl(s, SIOCGIFHWADDR, &buffer);
	close(s);
	for( s = 0; s < 6; s++ )
	{
    asprintf(&aux, "%.2X ", (unsigned char)buffer.ifr_hwaddr.sa_data[s]);
    mac.append(1,aux[0]);
    mac.append(1,aux[1]);
    mac.append(":");
	}
  mac.resize(mac.size()-1);
  cout << "MAC_string: " << mac << endl;
  return mac;
}

/******************************************************************************/

/*Fin del archivo set_impresoras.cpp*/
