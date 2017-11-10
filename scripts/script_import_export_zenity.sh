exportar_impresoras () {

	carpeta_exportar_impresoras=`zenity --file-selection --directory --title="Selecciona la carpeta /etc/cups"`

	if test -d $carpeta_exportar_impresoras; then
		if [[ -e $carpeta_exportar_impresoras/printers.conf ]]; then

			# Se manda la información que nos interesa a dos ficheros filtrando la informacion de printers.conf (nombres y conexiones) y luego se comprimen junto con la carpeta ppd
			cat $carpeta_exportar_impresoras/printers.conf | grep "<DefaultPrinter" | cut -d " " -f 2- >/tmp/nombreimpresoras.txt 
        	cat $carpeta_exportar_impresoras/printers.conf | grep "<Printer" | cut -d " " -f 2- >>/tmp/nombreimpresoras.txt

        	if [[ -e /tmp/nombreimpresoras.txt ]]; then
                cat /tmp/nombreimpresoras.txt | tr -d ">" >/tmp/NombreImpresoras.txt
                cat $carpeta_exportar_impresoras/printers.conf | grep "DeviceURI" | cut -d " " -f 2- >/tmp/ConexionImpresoras.txt
                cp -r $carpeta_exportar_impresoras/ppd /tmp/
                tar -C /tmp -cf $ruta_archivo_datos/ConfiguracionImpresoras.tar ppd NombreImpresoras.txt ConexionImpresoras.txt
                
                dialog --title "Correcto" --msgbox "Exportacion de impresoras realizada exitosamente" 10 50
        	else
            dialog --title "Error al exportar los nombres de las impresoras" --msgbox "No se ha podido exportar el nombre las impresoras, revie los permisos de la carpeta cups y la tmp" 10 50

       		fi
       		
       	else
       		dialog --title "Archivo no encontrado" --msgbox "No se encuentra el archivo printers.conf o no se tiene permiso para acceder al directorio cups" 10 50

		fi
	else
		dialog --title "Directorio no encontrado" --msgbox "No se encuentra el directorio cups" 10 50
	fi

}


## FUNCION IMPORTAR IMPRESORAS

importar_impresoras () {

# Se le pasan 3 rutas de archivos, la de los nombres, la de las conexiones y la de los ppds

ruta_configuracion_impresoras=`zenity --file-selection --title="Selecciona el archivo de las impresoras"`

    if [[ -e $ruta_configuracion_impresoras ]]; then

        tar -xf $ruta_configuracion_impresoras

        nombres_impresoras=`zenity --file-selection --title="Archivo con los nombres de las impresoras"`

        if [[ -e $nombres_impresoras ]]; then

                nombre_conexiones=`zenity --file-selection --title="Archivo con las conexiones"`

                if [[ -e $nombre_conexiones ]]; then

                        carpeta_ppd=`zenity --file-selection --directory --title="Selecciona con la carpeta ppd"`
                        # Sustituye o mueve a tmp para trabajar y se borren en el proximo reinicio

                        if [[ -e $carpeta_ppd ]]; then

                                mv $nombres_impresoras /tmp
                                mv $nombre_conexiones /tmp
                                mv $carpeta_ppd /tmp

                                # Contamos las lineas del documento de los nombres, tanto en el fichero de nombres como el de conexiones habrá el mismo
                                    # numero, por eso no es necesario contar en los dos   
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

                                    dialog --title "Importacion Exitosa" --msgbox "La importacion de las impresoras se ha realizado exitosamente" 10 50

                        else
                            dialog --title "Carpeta ppd no encontrada" --msgbox "No la carpeta ppd en ese directorio, asegurese de haber escritor correctamente la ruta y tener ahi la carpeta" 10 50
                        fi

                else
                    dialog --title "Archivo conexiones no encontrado" --msgbox "No existe el archivo de conexiones en ese directorio, asegurese de haber escritor correctamente la ruta y tener ahi el archivo" 10 50
                fi

        else
            dialog --title "Archivo con nombres no encontrado" --msgbox "No existe el archivo con los nombres en ese directorio, asegurese de haber escritor correctamente la ruta y tener ahi el archivo" 10 50
        fi

    else
        dialog --title "Archivo no encontrado" --msgbox "Ese archivo no existe o tiene un nombre diferente, asegurese de haber escritor correctamente la ruta y tener ahi el archivo" 10 50
    fi

}
