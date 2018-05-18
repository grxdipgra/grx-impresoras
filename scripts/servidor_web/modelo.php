<?php

require_once "./config.php";

class BaseDatos
{
    protected $conexion;
    protected $db;

    public function conectar()
    {
        $this->conexion = mysql_connect(HOST, USER, PASS);
        if ($this->conexion == 0) DIE("Lo sentimos, no se ha podido conectar con MySQL: " . mysql_error());
        $this->db = mysql_select_db(DBNAME, $this->conexion);
        if ($this->db == 0) DIE("Lo sentimos, no se ha podido conectar con la base datos: " . DBNAME);
        return true;

    }

    public function desconectar()
    {
        if ($this->conexion) {
            mysql_close($this->conexion);
        }

    }

    public function pruebadb()
    {
        $tabla = "nodo";
        $query = mysql_query("SELECT `nombre` from $tabla WHERE `id` LIKE 67", $this->conexion);
        if ($query == 0) echo "Sentencia incorrecta llamado a tabla: $tabla.";
        else {
            $resultado = mysql_result($query, 0, 0);
            echo "El resultado de la consulta a la tabla $tabla es $resultado";
            mysql_free_result($query);
        }
    }

    public function buscar($tabla, $columnas, $datos)
    {
      $claves = "";
      $valores = "";
      foreach($columnas as $clave)
      {
        if ($claves == "")
        {
          $claves = $claves." ".$clave;
        }
        else $claves = $claves.",".$clave;
      }
      foreach($datos as $clavedato=>$valordato)
      {
        if ($valordato <> end($datos))
        {
          $valores = $valores." ".$clavedato." LIKE '".$valordato."' AND";
        }
        else $valores = $valores." ".$clavedato." LIKE '".$valordato."'";
      }
      echo $claves;
      echo "<br>";
      echo $valores;
      echo "<br>";
      $consulta = "SELECT ".$claves." from ".$tabla." WHERE ".$valores;
      $query = mysql_query($consulta, $this->conexion);
      echo "Consulta: ".$consulta." ";
      echo "Filas: ". mysql_num_rows($query);
      echo "<br>";
      if (!$query)
      {
        die("query failed: " . mysql_error());
      }
      else {
            echo "El resultado de la consulta a la tabla $tabla es ";
            for($x = 0; $x <= mysql_num_rows($query); $x++)
            {
              for($i = 0; $i <= count($columnas); $i++)
              {
                $resultado = mysql_result($query, $x, $i);
                echo $resultado." ";
              }
              echo "</br>";
            }
            $num_col = mysql_num_rows($query);
            mysql_free_result($query);
        }
        echo "Num columnas: ". $num_col."</br>";
        return $num_col;
    }

    public function insertar($tabla, $columnas, $datos)
    {
      //Primero consultar que no existe;
      if ($this->buscar($tabla, $columnas, $datos) == 0)
      {
        $claves = "";
        $valores = "";
        foreach($columnas as $clave)
        {
          if ($claves == "")
          {
            $claves = $claves." ".$clave;
          }
          else $claves = $claves.",".$clave;
        }
        foreach($datos as $clavedato=>$valordato)
        {
          if ($valores == "")
          {
            $valores = $valores." '".$valordato."'";
          }
          else $valores = $valores.", '".$valordato."'";
        }
        $consulta = "INSERT INTO ". $tabla . "(".$claves.") VALUES (".$valores.")";
        echo "Consulta: ".$consulta." ";
        $query = mysql_query($consulta, $this->conexion);
        if (!$query) die("query failed: " . mysql_error());
      }
    }

    public function modificar($tabla, $columnas, $datos)
    {

    }
    
    public function borrar($tabla, $columnas, $datos)
    {

    }
}

?>
