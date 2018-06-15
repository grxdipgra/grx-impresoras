<?php

require_once "./modelo.php";

$db = new BaseDatos();

if($db->conectar()){
    $columnas = array('ip','nombre');
    $datos = array('ip' => "10.56%");
    $db->buscar("nodo", $columnas , $datos);
    $columnas = array('hostname','mac');
    $datos = array('hostname' => "esnaia", 'mac' => "7C:05:07:23:12:04");
    $db->insertar("equipo", $columnas, $datos);
    /*$columnas = array('InfoImpresora','DeviceUri','ppd');
    $datos = array('InfoImpresora' => "Samsung-X4300", 'DeviceUri' => "socket://10.7.15.230:9100",
                    'ppd' => "Samsung-X4300.ppd");
    $db->insertar("impresora", $columnas, $datos);
    $columnas = array('id_equipo','id_impresora');
    $datos = array('id_equipo' => "3", 'id_impresora' => "4");
    $db->insertar("equipo_impresora", $columnas, $datos);*/
    $columnas = array('id');
    $datos = array('id' => "5");
    $db->borrar("equipo", $columnas, $datos);
    $db->desconectar();
}
?>
