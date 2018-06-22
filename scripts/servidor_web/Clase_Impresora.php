<?php
class Impresora
{
    protected $PPD;
    protected $Info;
    protected $DeviceUri;
    protected $MakeModel;
    protected $StateTime;
    protected $ConfigTime;

    public function set_atributo($nombre, $valor)
    {
      switch ($nombre)
      {
        case "PPD":
          this->PPD = $valor;
        break;
        case "Info":
          this->Info = $valor;
        break;
        case "DeviceUri":
          this->DeviceUri = $valor;
        break;
        case "MakeModel":
          this->MakeModel = $valor;
        break;
        case "StateTime":
          this->StateTime = $valor;
        break;
        case "ConfigTime":
          this->ConfigTime = $valor;
        break;
      }
    }

    public function get_atributo($nombre)
    {
      switch ($nombre)
      {
        case "PPD":
          return this->PPD;
        break;
        case "Info":
          return this->Info;
        break;
        case "DeviceUri":
          return this->DeviceUri;
        break;
        case "MakeModel":
          return this->MakeModel;
        break;
        case "StateTime":
          return this->StateTime;
        break;
        case "ConfigTime":
          return this->ConfigTime;
        break;
      }
    }
}
?>
