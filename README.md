# grx-impresoras
Configuración de impresoras equipos dipgra

lpstat -s -> lista las impresoras configuradas en el sistema.
/etc/cups -> directorio de configuración de todo lo relacionado con impresoras. Hay que parar el servidor cups para realizar tanto la importación como la exportación.

./gcc/pruebas/leerfichero -> Se encarga de leer la configuración del archivo /etc/cups/printers.conf y lo imprime formateado.

Se puede realizar descubrimientos de impresoras en red con el comando lpinfo. Mas concretamente si especificamos el tipo de descubrimiento con:
lpinfo --include-schemes dnssd -v
lpinfo -v realizará el descubrimiento por todos los protocolos disponibles.

... y realizar la instalación con al URI devuelta de la impresora en concreto.

lpadmin -p HPLaserJetP3015 -v socket://19.86.82.172 -P 
/usr/share/cups/model/HP/LaserJet_P3005-Postscript.ppd



BASES DE DATOS

Tablas de la base de datos

Impresoras
	ID impresora (clave)
	IP del Nodo
	Nombre de la impresora
	Conexión 
	PPD

Nodos 
	IP del Nodo (clave)
	Nombre del nodo
	ID impresora
	Ultima fecha de disponibilidad



