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

//======================================================================

bool UploadXML()
{
	CURL *curl;
  CURLcode res;
  char *file = (char*)ARCHIVO_XML;
  char *url = (char*)URL_BD_IMPRESORAS;

  struct curl_httppost *formpost = NULL;
  struct curl_httppost *lastptr = NULL;
  struct curl_slist *headerlist = NULL;
  static const char buf[] = "Expect:";

	bool exito;

  curl_global_init(CURL_GLOBAL_ALL);

  /* Fill in the file upload field */
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "file",
               CURLFORM_FILE, file,
               CURLFORM_END);

  /* Fill in the filename field */
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "filename",
               CURLFORM_COPYCONTENTS, file,
               CURLFORM_END);


  /* Fill in the submit field too, even if this is rarely needed */
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "submit",
               CURLFORM_COPYCONTENTS, "send",
               CURLFORM_END);

  curl = curl_easy_init();
  /* initialize custom header list (stating that Expect: 100-continue is not
     wanted */
  headerlist = curl_slist_append(headerlist, buf);
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    /* what URL that receives this POST */
    curl_easy_setopt(curl, CURLOPT_URL, url);
    //if((argc == 2) && (!strcmp(argv[1], "noexpectheader")))
      /* only disable 100-continue header if explicitly requested */
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
			exito = false;
		}
		else exito = true;
    /* always cleanup */
    curl_easy_cleanup(curl);
    /* then cleanup the formpost chain */
    curl_formfree(formpost);
    /* free slist */
    curl_slist_free_all(headerlist);
  }
	return exito;
}

bool DownloadXML()
{
	size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	    size_t written = fwrite(ptr, size, nmemb, stream);
	    return written;
	}
	    CURL *curl;
	    FILE *fp;
	    CURLcode res;
	    char *url = "http://10.7.15.69/curl/files/impresoras.xml";
	    char outfilename[FILENAME_MAX] = "./salida.xml";
	    curl = curl_easy_init();
	    if (curl) {
	        fp = fopen(outfilename,"wb");
	        curl_easy_setopt(curl, CURLOPT_URL, url);
	        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	        res = curl_easy_perform(curl);
	        /* always cleanup */
	        curl_easy_cleanup(curl);
	        fclose(fp);
	    }
	    return 0;
	}
}

/******************* LOG *****************************/

//void log_handle(string log){
/*http://stackoverflow.com/questions/10952515/c-c-syslog-to-custom-file-not-var-log-syslog-but-var-log-mylog-ubuntu-12*/
//    openlog(NULL, 0, LOG_USER);
//    syslog(LOG_INFO, (char*)log.c_str());
//    setbuf(stdout,0);
//}
