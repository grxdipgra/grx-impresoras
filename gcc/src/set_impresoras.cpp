/*****************************************************************************/
/**
	* @file set_impresoras.cpp
	* @brief Archivo principal de la clase set_impresora
	* @author Alejandro Castilla Peula
	* @date Noviembre-2017
	*/
/*****************************************************************************/

#include "set_impresoras.h"

using namespace std;

/******************* FUNCIONES PUBLICAS **************************************/

set_impresoras::set_impresoras()
{
	impresora aux;
	ifstream printers_conf;
  string nombre = ARCHIVO_CONFIGURACION;
  string comienzo_impresora = "<Printer";
	string comienzo_impresora_default = "<DefaultPrinter";
	string fin_impresora = "</Printer>";
	string fin_impresora_default = "<DefaultPrinter";
	string printer, info, conexion, driver, uso, instalacion;
	string comienzo_info = "Info";
	string comienzo_conexion = "DeviceURI";
	string comienzo_driver = "MakeModel";
	string ppd = ".ppd";
	string ultimo_uso = "StateTime";
	string time_instalacion = "ConfigTime";
	string linea;
  sys_info();
  ip_nodo();
	//cout << "Archivo de configuración es: " << nombre << endl ;
  printers_conf.open ( nombre.c_str() , ios::in);
	if(printers_conf.good()){
    	if (printers_conf.is_open()) {
        	while (! printers_conf.eof() ) {
            	getline (printers_conf,linea);
							if(linea.find(comienzo_impresora_default) != string::npos){
								printer = linea.substr(16,linea.length()-17);
								//cout << "Impresora CUPS: " << printer << endl;
								//cout << "PPD: " << printer << ppd << endl;
								while (linea.find(fin_impresora_default) == string::npos){
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
									if(linea.find(ultimo_uso) != string::npos){
										uso = linea.substr(10,linea.length()-10);
										//cout << "Driver: " << driver << endl;
									}
									if(linea.find(time_instalacion) != string::npos){
										instalacion = linea.substr(10,linea.length()-10);
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
								aux.set_atributo("StateTime",uso);
								aux.set_atributo("ConfigTime",instalacion);
								impresoras.push_back(aux);
							}
							else if(linea.find(comienzo_impresora) != string::npos){
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
									if(linea.find(ultimo_uso) != string::npos){
										uso = linea.substr(10,linea.length()-10);
										//cout << "Driver: " << driver << endl;
									}
									if(linea.find(time_instalacion) != string::npos){
										instalacion = linea.substr(10,linea.length()-10);
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
								aux.set_atributo("StateTime",uso);
								aux.set_atributo("ConfigTime",instalacion);
								impresoras.push_back(aux);
							}
        	}
        	printers_conf.close();
    	}
			CrearXml();
	}
	else {
		cerr << "\033[1;31mError: \033[0m";
		cerr << "Fallo al abrir el fichero de configuración. ";
		cerr  << strerror(errno) << "." << endl;
	}
}

/******************************************************************************/

set_impresoras::~set_impresoras()
{
	this->impresoras.clear();
}

/******************************************************************************/

/*impresora set_impresoras::get_impresora(string nombre)
{
	map<string,string>::iterator it;
	it = impresoras.find(nombre);
	return
}*/

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
	os << "\033[1;36mInfo del sistema: \033[0m" << endl << endl;
	os << "\033[1;32mSistema: \033[0m" << impresoras.info_equipo.sysname << endl;
	os << "\033[1;32mHostname: \033[0m" << impresoras.hostname << endl;
	os << "\033[1;32mKernel: \033[0m" << impresoras.info_equipo.release << endl;
	os << "\033[1;32mBase: \033[0m" << impresoras.info_equipo.version << endl;
	os << "\033[1;32mArch: \033[0m" << impresoras.info_equipo.machine << endl;
	os << "\033[1;32mNombre dominio: \033[0m" << impresoras.info_equipo.domainname << endl;
	os << "\033[1;32mIP: \033[0m" << impresoras.nodo << endl;
	os << "\033[1;32mMAC: \033[0m" << impresoras.mac << endl << endl;
	os << "\033[1;36mNúmero de impresoras: \033[0m" << impresoras.size() << endl << endl;

	for (int i = 0 ; i< (int)impresoras.size() ; ++i)
	{
		os << impresoras[i] << endl;
	}
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
		hostname = info_equipo.nodename;
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
						if (!((ifa->ifa_flags & IFF_LOOPBACK) == IFF_LOOPBACK) &&
								 ((ifa->ifa_flags & IFF_UP)) == IFF_UP &&
								 (ifa->ifa_flags & IFF_RUNNING) != 0 &&
								 (get_mac(ifa->ifa_name) != "00:00:00:00:00:00")){
							mac = get_mac(ifa->ifa_name);
							nodo = addressBuffer;
							//cout << "Interface:" << ifa->ifa_name << endl;
							//cout << "IP: " << addressBuffer << endl;
            	//cout << "Flags:" << ifa->ifa_flags << endl;
            	//cout << "Is up:" << (ifa->ifa_flags & IFF_UP) << endl;
            	//cout << "Esta activa:" << (ifa->ifa_flags & IFF_RUNNING) << endl;

						}
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
  //cout << "MAC_string: " << mac << endl;
  return mac;
}

/******************************************************************************/

void set_impresoras::CrearXml(){
	ofstream xmlfile(ARCHIVO_XML , ios::out | ios::trunc);
	//xmlfile.open(ARCHIVO_XML);
	if (xmlfile.good()){
		xmlfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
		xmlfile << "<Sistema>" << endl;
		xmlfile << "<hostname>" << hostname <<"</hostname>" << endl;
		xmlfile << "<ip>" << nodo << "</ip>" << endl;
		xmlfile << "<mac>" << mac << "</mac>" << endl;
		xmlfile << "</Sistema>" << endl;
		for (int i = 0 ; i< (int)impresoras.size() ; ++i)
		{
			xmlfile << "<Impresora>" << endl;
			xmlfile << "<Printer>";
			xmlfile << impresoras[i].get_atributo("Printer");
			xmlfile << "</Printer>" << endl;
			xmlfile << "<Info>";
			xmlfile << impresoras[i].get_atributo("Info");
			xmlfile << "</Info>" << endl;
			xmlfile << "<DeviceUri>";
			xmlfile << impresoras[i].get_atributo("DeviceUri");
			xmlfile << "</DeviceUri>" << endl;
			xmlfile << "<MakeModel>";
			xmlfile << impresoras[i].get_atributo("MakeModel");
			xmlfile << "</MakeModel>" << endl;
			xmlfile << "<PPD>";
			xmlfile << impresoras[i].get_atributo("PPD");
			xmlfile << "</PPD>" << endl;
			xmlfile << "<StateTime>";
			xmlfile << impresoras[i].get_atributo("StateTime");
			xmlfile << "</StateTime>" << endl;
			xmlfile << "<ConfigTime>";
			xmlfile << impresoras[i].get_atributo("ConfigTime");
			xmlfile << "</ConfigTime>" << endl;
			xmlfile << "</Impresora>" << endl;
		}
		xmlfile.close();
	}
	else {
		cerr << "\033[1;31mError: \033[0m";
		cerr << "Fallo al abrir el fichero de configuración. ";
		cerr  << strerror(errno) << "." << endl;
	}
}

/******************************************************************************/

/*Fin del archivo set_impresoras.cpp*/
