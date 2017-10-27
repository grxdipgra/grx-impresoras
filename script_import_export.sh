#!/bin/bash 

## SCRIPT DE EXPORTACION E IMPORTACIÓN DE LOS DATOS DE USUARIO, SUS CONEXIONES DE RED Y LAS IMPRESORAS QUE HA TENIDO INSTALADAS ##

DATOS_CUPS="/etc/cups"
DIR_EXPORTACION="/tmp/grx-impresoras"

export DATOS_CUPS
export DIR_EXPORTACION

_EXPORT_IMPRESORAS () {

	if test -d $DATOS_CUPS; then
		if [[ -e $DATOS_CUPS/printers.conf ]]; then

			# Se manda la información que nos interesa a dos ficheros filtrando la informacion de printers.conf (nombres y conexiones) y luego se comprimen junto con la carpeta ppd
			cat $DATOS_CUPS/printers.conf | grep "<DefaultPrinter" | cut -d " " -f 2- >$DIR_EXPORTACION/nombreimpresoras.txt 
        	cat $DATOS_CUPS/printers.conf | grep "<Printer" | cut -d " " -f 2- >>$DIR_EXPORTACION/nombreimpresoras.txt

        	if [[ -e $DIR_EXPORTACION/nombreimpresoras.txt ]]; then
                cat $DIR_EXPORTACION/nombreimpresoras.txt | tr -d ">" >$DIR_EXPORTACION/NombreImpresoras.txt
                cat $DATOS_CUPS/printers.conf | grep "DeviceURI" | cut -d " " -f 2- >$DIR_EXPORTACION/ConexionImpresoras.txt
                cp -r $DATOS_CUPS/ppd $DIR_EXPORTACION
                tar -C $DIR_EXPORTACION -cf $DIR_EXPORTACION/ConfiguracionImpresoras.tar ppd NombreImpresoras.txt ConexionImpresoras.txt
				rm -R $DIR_EXPORTACION/ppd $DIR_EXPORTACION/NombreImpresoras.txt $DIR_EXPORTACION/ConexionImpresoras.txt $DIR_EXPORTACION/nombreimpresoras.txt
                
                echo "Exportacion de impresoras realizada exitosamente"
        	else
            	echo "Error al exportar los nombres de las impresoras. No se ha podido exportar el nombre las impresoras, revie los permisos de la carpeta cups y la tmp"

       		fi
       		
       	else
       		echo "No se encuentra el archivo printers.conf o no se tiene permiso para acceder al directorio cups"

		fi
	else
		echo "No se encuentra el directorio cups"
	fi

}


## FUNCION IMPORTAR IMPRESORAS

_IMPORT_IMPRESORAS () {

# Se le pasan 3 rutas de archivos, la de los nombres, la de las conexiones y la de los ppds

ruta_configuracion_impresoras=`zenity --file-selection --title="Selecciona el archivo de las impresoras"`

    if [[ -e $ruta_configuracion_impresoras ]]; then

        tar -xf $ruta_configuracion_impresoras

        nombres_impresoras=`zenity --file-selection --title="Archivo con los nombres de las impresoras"`

        if [[ -e $nombres_impresoras ]]; then

                nombre_conexiones=`zenity --file-selection --title="Archivo con las conexiones"`

                if [[ -e $nombre_conexiones ]]; then

                        # Sustituye o mueve a tmp para trabajar y se borren en el proximo reinicio

                        if [[ -e $DIR_PPD ]]; then

                                mv $nombres_impresoras /tmp
                                mv $nombre_conexiones /tmp
                                mv $DIR_PPD /tmp

# Contamos las lineas del documento de los nombres, tanto en el fichero de nombres como el de conexiones habrá el mismo numero, por eso no es necesario contar en los dos   

                                lineas=`wc -l /tmp/NombreImpresoras.txt | cut -d " " -f 1`

                                contador=1

# Bucle que saca la primera linea de los dos documentos y el archivo de los ppds con el mismo nombre que el que saca del 
                                            # archivo con los nombres de las impresoras, se pasan esos parametros a lpadmin y se instala la impresora

                                while test $contador -le $lineas

                                    do 
                                        nombre=`head -$contador /tmp/NombreImpresoras.txt | tail -1`
                                        conexion=`head -$contador /tmp/ConexionImpresoras.txt | tail -1`
                                        /usr/sbin/lpadmin -p $nombre -E -v $conexion -P /tmp/ppd/$nombre.ppd
                                        contador=`expr $contador + 1`

                                    done

                                    echo "La importacion de las impresoras se ha realizado exitosamente"

                        else
                            echo "No la carpeta ppd en ese directorio, asegurese de haber escritor correctamente la ruta y tener ahi la carpeta"
                        fi

                else
                    echo "No existe el archivo de conexiones en ese directorio, asegurese de haber escritor correctamente la ruta y tener ahi el archivo"
                fi

        else
            echo "No existe el archivo con los nombres en ese directorio, asegurese de haber escritor correctamente la ruta y tener ahi el archivo" 
        fi

    else
        echo "Ese archivo no existe o tiene un nombre diferente, asegurese de haber escritor correctamente la ruta y tener ahi el archivo"
    fi

}

export _EXPORT_IMPRESORAS
export _IMPORT_IMPRESORAS

mkdir $DIR_EXPORTACION
_EXPORT_IMPRESORAS

