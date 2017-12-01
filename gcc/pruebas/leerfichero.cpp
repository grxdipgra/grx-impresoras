#include <iostream>
#include <fstream>
 
using namespace std;

 
int main () {
    ifstream printers_conf;
    string nombre = "/etc/cups/printers.conf";
    string comienzo_impresora = "<Printer";
	string fin_impresora = "</Printer>";
	string printer, info, conexion, driver;
	string comienzo_info = "Info";
	string comienzo_conexion = "DeviceURI";
	string comienzo_driver = "MakeModel";
	string ppd = ".ppd";
	string linea;

    //cout << "Dime el nombre del fichero: ";
    //getline(cin,nombre);

 
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
        }
        printers_conf.close();
    }
    else cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;  

 
    return 0;
}
