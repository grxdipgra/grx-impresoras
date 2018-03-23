/**
  * @file utils.cpp
  * @brief Fichero con las definiciones de los metodos de utilidades.
  * Implementa la interfaz de utils.h
  * @author Alejandro Castilla Peula OSL Diputacion de Granada
  * @date Noviembre 2017
  * License: GNU Public License
  */

/******************************************************************************/

#include <util.h>

bool ExisteFichero(const char* nombre)
{
	ifstream fichero;
	bool problema;

	fichero.open(nombre);
	problema=fichero.fail();
	if(!problema) fichero.close();
	if(!fichero.good())
  	cerr << "Error: " << strerror(errno) << endl;
	return ((problema)?false:true);
}

/******************FUNCIONES PARA EL MANEJO DE XML ****************************/

string getFile( string filename )
{
   string buffer;
   char c;

   ifstream in( filename );   if ( !in ) { cout << filename << " not found";   exit( 1 ); }
   while ( in.get( c ) ) buffer += c;
   in.close();

   return buffer;
}


//======================================================================


vector<string> getData( const string &text, string tag )
{
   vector<string> collection;
   size_t pos, start;
   while ( true )
   {
      start = text.find( "<" + tag, pos );
      if ( start == string::npos ) return collection;
      start = text.find( ">" , start );
      start++;
      pos = text.find( "</" + tag, start );

      if ( pos >= string::npos ) return collection;
      collection.push_back( text.substr( start, pos - start ) );
   }
}


//======================================================================


void stripTags( string &text )
{
   size_t start = 0, pos;

   while ( start < text.size() )
   {
      start = text.find( "<", start );    if ( start == string::npos ) break;
      pos   = text.find( ">", start );    if ( pos   == string::npos ) break;
      text.erase( start, pos - start + 1 );
   }
}

/******************* LOG *****************************/

//void log_handle(string log){
/*http://stackoverflow.com/questions/10952515/c-c-syslog-to-custom-file-not-var-log-syslog-but-var-log-mylog-ubuntu-12*/
//    openlog(NULL, 0, LOG_USER);
//    syslog(LOG_INFO, (char*)log.c_str());
//    setbuf(stdout,0);
//}
