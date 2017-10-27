#!/bin/bash 

## SCRIPT DE EXPORTACION E IMPORTACIÓN DE LOS DATOS DE USUARIO, SUS CONEXIONES DE RED Y LAS IMPRESORAS QUE HA TENIDO INSTALADAS ##

## Antonio Garcia Illescas 2ºA Administración de Sistemas Informaticos en Red


## EXPORTACIÓN DE DATOS DESDE UN DISCO DURO
exportar_datos () {


 if test -d $carpeta_exportar; then

    carpeta_exportar=`zenity --file-selection --directory --title="Carpeta Home del usuario del que se extaeran los datos"`
        # Carpetas a la que se copiaran los datos en los que estamos interesados
        mkdir /tmp/carpetas_datos_usuario 2> /tmp/error_carpeta_creacion_datos_defecto.txt && mkdir /tmp/carpetas_datos_usuario/Documentos 2>> /tmp/error_carpeta_creacion_datos_defecto.txt && mkdir /tmp/carpetas_datos_usuario/Escritorio 2>> /tmp/error_carpeta_creacion_datos_defecto.txt
        
        if test -d /tmp/carpetas_datos_usuario/Documentos -a -d /tmp/carpetas_datos_usuario/Escritorio; then

            # Copiamos los datos que nos interesan y los comprimimos
            cp -R $carpeta_exportar/Escritorio/* /tmp/carpetas_datos_usuario/Escritorio
            cp -R $carpeta_exportar/Documentos/* /tmp/carpetas_datos_usuario/Documentos
            tar -C /tmp -cf $ruta_archivo_datos/datosusuario.tar carpetas_datos_usuario/Documentos carpetas_datos_usuario/Escritorio 2> /tmp/error_carpeta_comprimir_datos_defecto.txt

            if [[ -e /home/$username/datosusuario.tar ]]; then
                dialog --title "Correcto" --msgbox "Exportacion de datos realizada exitosamente" 10 50

            else
                dialog --title "Error de compresion" --textbox /tmp/error_carpeta_comprimir_datos_defecto.txt 10 100
            fi
            
        else
            dialog --title "Error durante la creacion de las carpetas" --textbox /tmp/error_carpeta_creacion_datos_defecto.txt 10 100
        fi

    else

        dialog --title "La carpeta del usuario no existe" --msgbox "Asegurese de estar ejecutando el script con el usuario correcto" 10 50

    fi
}

## EXPORTAR CONEXIONES DE UN EQUIPO DESDE UN DISCO EXTERNO

exportar_conexiones () {

    carpeta_exportar_conexiones=`zenity --file-selection --directory --title="Selecciona la carpeta /etc/NetworkManager"`

        # Comprimimos la carpeta system-connections que tiene los datos de las conexiones
		tar -C $carpeta_exportar_conexiones --exclude=Buscar -cf $ruta_archivo_datos/datosusuariored.tar system-connections/ 2> /tmp/error_exportar_conexiones_defecto
        if [[ -e $ruta_archivo_datos/datosusuariored.tar ]]; then
            dialog --title "Correcto" --msgbox "Exportacion de conexiones realizada exitosamente" 10 50
        else
            dialog --title "Error durante la exportacion" --textbox /tmp/error_exportar_conexiones_defecto.txt 10 100
        fi

}

## EXPORTAR IMPRESORAS DE UN EQUIPO DESDE UN DISCO EXTERNO

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


## FUNCION IMPORTAR DATOS USUARIO
importar_datos_usuario  () {

ruta_archivo_datos_usuario=`zenity --file-selection --title="Selecciona el archivo con los datos del usuario"`
nombre_usuario=`zenity --file-selection --directory --title="Selecciona el Home del usuario receptor"`

# Se descomprimen los datos, se mueven a su sitio y se les cambia los permisos, el bucle while que hay no se utiliza en este script
if [[ -e $ruta_archivo_datos_usuario ]]; then
    tar -C /tmp -xf $ruta_archivo_datos_usuario
    if test -d /tmp/carpetas_datos_usuario/Escritorio -a -d /tmp/carpetas_datos_usuario/Documentos; then
        mv /tmp/carpetas_datos_usuario/Escritorio/* $nombre_usuario/Escritorio/
        mv /tmp/carpetas_datos_usuario/Documentos/* $nombre_usuario/Documentos/
        chmod -R 777 $nombre_usuario/*
        dialog --title "Correcto" --msgbox "Importacion por defecto realizada exitosamente" 10 50
    else
        contador=1
        while test -e /tmp/carpetas_datos_usuario/carpeta$contador.tar; do
                tar -C $nombre_usuario -xf /tmp/carpetas_datos_usuario/carpeta$contador.tar
                contador=`expr $contador + 1` 
        done
    chmod -R 777 $nombre_usuario/*
    dialog --title "Correcto" --msgbox "Importacion especifica realizada exitosamente" 10 50
    fi
else
    dialog --title "Archivo no encontrado" --msgbox "No exite el archivo en ese directorio, asegurese de haber escritor correctamente la ruta y tener ahi el archivo" 10 50

fi

}

## FUNCION IMPORTAR DATOS CONEXIONES

importar_conexiones_red () {

ruta_archivo_datos_usuario_red=`zenity --file-selection --title="Selecciona el archivo con las conexiones"`
carpeta_conexiones=`zenity --file-selection --directory --title="Selecciona la carpeta /etc/NetworkManager"`

# Descomprimimos las carpetas y copiamos las conexiones a system-conections, se cambian los permisos al 600 si no, no las reconocerá
if [[ -e $ruta_archivo_datos_usuario_red ]]; then
        tar -C /tmp -xf $ruta_archivo_datos_usuario_red 
        if test -e /tmp/system-connections; then
            cp /tmp/system-connections/* $carpeta_conexiones/system-connections/ | dialog --title "Correcto"  --msgbox "Importacion de redes realizada exitosamente" 10 50
            chmod -R 600 $carpeta_conexiones/system-connections/*
        else
            dialog --title "Incorrecto" --msgbox "La exportacion de las conexiones no se ha realizado completamente" 10 50
        fi
    else
        dialog --title "Archivo no encontrado" --msgbox "No exite el archivo en ese directorio, asegurese de haber escritor correctamente la ruta y tener ahi el archivo" 10 50
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
# MENÚ PRINCIPAL
menu_principal=`dialog --stdout --menu "---------MENU PRINCIPAL---------" 20 40 30 1 "Exportar Datos" 2 "Importar Datos" 3 "Salir"`

#MENU DE EXPORTACIÓN
if [[ $menu_principal -eq 1 ]]; then
    menu_exportacion=`dialog --stdout --menu "---------MENU EXPORTACION---------" 20 40 30 1 "Exportar Todo" 2 "Exportar Datos de Usuario" 3 "Exportar Conexiones de Usuario" 4 "Exportar Impresoras de Usuario" 5 "Salir"`

        if [[ $menu_exportacion -eq 1 ]]; then

            ruta_archivo_datos=`zenity --file-selection --directory --title="Carpeta donde almacenar el paquete"`
            exportar_datos
            exportar_conexiones
            exportar_impresoras

        fi
        if [[ $menu_exportacion -eq 2 ]]; then

            ruta_archivo_datos=`zenity --file-selection --directory --title="Carpeta donde almacenar el paquete"`
            exportar_datos
        fi
        if [[ $menu_exportacion -eq 3 ]]; then

            ruta_archivo_datos=`zenity --file-selection --directory --title="Carpeta donde almacenar el paquete"`
            exportar_conexiones
        fi
        if [[ $menu_exportacion -eq 4 ]]; then

            ruta_archivo_datos=`zenity --file-selection --directory --title="Carpeta donde almacenar el paquete"`
            exportar_impresoras
        fi
        if [[ $menu_exportacion -eq 5 ]]; then

            exit

        fi
fi

# MENÚ DE IMPORTACION
if [[ $menu_principal -eq 2 ]]; then
    menu_importacion=`dialog --stdout --menu "---------MENU IMPORTACION---------" 20 40 30 1 "Importar Todo" 2 "Importar Datos" 3 "Importar Conexiones" 4 "Importar Impresoras" 5 "Salir"`

        if [[ $menu_importacion -eq 1 ]]; then
            importar_datos_usuario
            importar_conexiones_red
            importar_impresoras

        fi
        if [[ $menu_importacion -eq 2 ]]; then

            importar_datos_usuario
        fi
        if [[ $menu_importacion -eq 3 ]]; then

            importar_conexiones_red
        fi
        if [[ $menu_importacion -eq 4 ]]; then

            importar_impresoras
        fi
        if [[ $menu_importacion -eq 5 ]]; then

            exit

        fi
fi

if [[ $menu_principal -eq 3 ]]; then
    exit
fi
