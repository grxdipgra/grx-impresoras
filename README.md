# grx-impresoras
Configuración de impresoras equipos dipgra

lpstat -s -> lista las impresoras configuradas en el sistema.
/etc/cups -> directorio de configuración de todo lo relacionado con impresoras. Hay que parar el servidor cups para realizar tanto la importación como la exportación.

./gcc/pruebas/leerfichero -> Se encarga de leer la configuración del archivo /etc/cups/printers.conf y lo imprime formateado.

Se puede realizar descubrimientos de impresoras en red con el comando lpinfo. Mas concretamente si especificamos el tipo de descubrimiento con:
lpinfo --include-schemes dnssd -v
lpinfo -v realizará el descubrimiento por todos los protocolos disponibles.

... y realizar la instalación con al URI devuelta de la impresora en concreto.
