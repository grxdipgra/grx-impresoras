<?php

require_once "./modelo.php";

if (file_exists('files/impresoras.xml')) {
    $xml = simplexml_load_file('files/impresoras.xml');
    //print_r($xml);
    echo "hostname: " . $xml->Sistema[0]->hostname . "</br>";
    echo "mac: " . $xml->Sistema[0]->mac. "</br>";
} else {
    exit('Error abriendo impresoras.xml.');
}

$db = new BaseDatos();

if($db->conectar()){
    /*$columnas = array('ip','nombre');
    $datos = array('ip' => "10.56%");
    $db->buscar("nodo", $columnas , $datos);*/
    /*$columnas = array('hostname','mac');
    $datos = array('hostname' => "esnaia", 'mac' => "7C:05:07:23:12:04");
    $db->insertar("equipo", $columnas, $datos);
    /*$columnas = array('InfoImpresora','DeviceUri','ppd');
    $datos = array('InfoImpresora' => "Samsung-X4300", 'DeviceUri' => "socket://10.7.15.230:9100",
                    'ppd' => "Samsung-X4300.ppd");
    $db->insertar("impresora", $columnas, $datos);
    $columnas = array('id_equipo','id_impresora');
    $datos = array('id_equipo' => "3", 'id_impresora' => "4");
    $db->insertar("equipo_impresora", $columnas, $datos);*/
    /*$datos = array('hostname' => "esnaia");
    $columnas = array("hostname","mac");
    $nuevos = array("paco","00:00:00:00:00:ff");
    $id = array('clave' => "id",'dato' => "4");
    $db->modificar("equipo", $columnas, $datos, $nuevos, $id);
    $columnas = array('id');
    $datos = array('id' => '5');
    $db->borrar("equipo", $columnas, $datos);*/
    $db->desconectar();
}
?>
