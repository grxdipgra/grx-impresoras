<?php

require_once "./modelo.php";

$db = new BaseDatos();

if($db->conectar()){
    $columnas = array('ip','nombre');
    $datos = array('ip' => "10.56%");
    $db->buscar("nodo", $columnas, $datos);
    $columnas = array('hostname','mac');
    $datos = array('hostname' => "esnaia", 'mac' => "7C:05:07:23:12:04");
    $db->insertar("equipo", $columnas, $datos);
    $db->desconectar();
}
?>
