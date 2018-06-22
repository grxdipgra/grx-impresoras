<?php
class Equipo
{
    protected $hostname;
    protected $mac;
    protected $fecha;

    public function set_atributo($nombre, $valor)
    {
      switch ($nombre)
      {
        case "hostname":
          this->hostname = $valor;
        break;
        case "mac":
          this->mac = $valor;
        break;
        case "fecha":
          this->fecha = $valor;
        break;
      }
    }

    public function get_atributo($nombre)
    {
      switch ($nombre)
      {
        case "hostname":
          return this->hostname;
        break;
        case "mac":
          return this->mac;
        break;
        case "fecha":
          return this->fecha;
        break;
      }
    }
}
?>
