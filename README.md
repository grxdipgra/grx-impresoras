# grx-impresoras
Configuración de impresoras equipos dipgra

lpstat -s -> lista las impresoras configuradas en el sistema.
/etc/cups -> directorio de configuración de todo lo relacionado con impresoras. Hay que parar el servidor cups para realizar tanto la importación como la exportación.

./gcc/pruebas/leerfichero -> Se encarga de leer la configuración del archivo /etc/cups/printers.conf y lo imprime formateado.

Se puede realizar descubrimientos de impresoras en red con el comando lpinfo. Mas concretamente si especificamos el tipo de descubrimiento con:
lpinfo --include-schemes dnssd -v
lpinfo -v realizará el descubrimiento por todos los protocolos disponibles.

... y realizar la instalación con al URI devuelta de la impresora en concreto.

lpadmin -p HPLaserJetP3015 -v socket://19.86.82.172 -P  /usr/share/cups/model/HP/LaserJet_P3005-Postscript.ppd



Modelo E-R grx-impresoras

	Los Equipos pueden conectarse a varios Nodos pero en un momento dado sólamente estan conectados a un Nodo.
	Las Impresoras pueden estar configuradas en distintos Equipos.
	Puede existir el mismo tipo de Impresora en diferentes Nodos.
	Las impresoras que no se ha actualizado en “x” tiempo puede que ya no estén disponibles.


Entidades y atributos:

	Impresora: InfoImpresora (nombre original), DeviceUri, PPD, StateTime(int)
	Equipo: Hostname, Mac
	Nodo: IP, Nombre

Relaciones:

	Disponible: Impresora disponible en un Nodo
		Impresora – Nodo	n:1	InfoImpresora, DeviceUri, IP, StateTime(int)
	Conexión: Equipos que se conectan a un nodo
		Equipo – Nodo	n:1	Hostname,  IP
	Configurada: Impresora configurada en un Equipo
		Equipo – Impresora	n:n 	Hostname, DeviceUri, InfoImpresora,


Modelo de intercambio de datos con xml:

	<Impresoras>
		<Sistema>
			<hostname>"NombreEquipo"</hostname>
			<ip>"DireccionIp"</ip>
			<mac>"DireccionMac"
		</Sistema>
		<Impresora>
			<Printer>"NombreCups"</Printer>
			<Info>"Modelo"</Info>
			<DeviceUri>"Conexión"</DeviceUri>
			<MakeModel>"NombreDriver"</MakeModel>
			<PPD>"NombrePpd"</PPD>
			<StateTime>"TimestampUltimoUso"</StateTime>
		</Impresora>
	<Impresoras>

Logica de negocio con el server.

Cliente -> solicita impresoras del nodo.
Cliente -> si posee alguna/s nueva/s la/s envia para su registro/actualización.
Server -> recibe y registra la/s nueva/s impresora/s
Cliente -> si le falta/n alguna/s la/s solicita para su instalación.
Cliente -> instala la impresora/s solicitada/s.
