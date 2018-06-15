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

    public function set_consulta($tipo, $tabla, $columnas, $datos)
    {
      echo "N&uacute;mero de columnas: " . count($columnas) . "</br>";
      echo "N&uacute;mero de datos: " . count($datos) . "</br>";
      $consulta = "";
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
      switch ($tipo)
      {
        case "buscar":
          end($datos); //mueve el cursor al ultimo elemento del array
          $last_key = key($datos); //obtiene el ultimo elemento del array
          foreach($datos as $clavedato=>$valordato)
          {
            if ($clavedato != $last_key)
            {
              $valores = $valores." ".$clavedato." LIKE '".$valordato."' AND";
            }
            else $valores = $valores." ".$clavedato." LIKE '".$valordato."'";
          }
          $consulta = "SELECT ".$claves." from ".$tabla." WHERE ".$valores;
        break;
        case "insertar":
          foreach($datos as $clavedato=>$valordato)
          {
            if ($valores == "")
            {
              $valores = $valores." '".$valordato."'";
            }
            else $valores = $valores.", '".$valordato."'";
          }
          $consulta = "INSERT INTO ". $tabla . "(".$claves.") VALUES (".$valores.")";
        break;
        case "borrar":
          foreach($datos as $clavedato=>$valordato)
          {
            if ($valores == "")
            {
              $valores = $valores." '".$valordato."'";
            }
            else $valores = $valores.", '".$valordato."'";
          }
          $consulta = "DELETE FROM ". $tabla . " WHERE ".$claves."=".$valores;
        break;
        case "modificar":
        break;
      }
      echo $claves;
      echo "<br>";
      echo $valores;
      echo "<br>";
      return $consulta;
    }

    public function buscar($tabla, $columnas, $datos)
    {
      $consulta = $this->set_consulta("buscar", $tabla, $columnas, $datos);
      $query = mysql_query($consulta, $this->conexion);
      echo "Consulta: ".$consulta." </br>";
      echo "Filas: ". mysql_num_rows($query);
      echo "<br>";
      if (!$query)
      {
        die("query failed: " . mysql_error());
      }
      else {
            echo "El resultado de la consulta a la tabla $tabla es ";
            for($x = 0; $x < mysql_num_rows($query); $x++)
            {
              for($i = 0; $i < count($columnas); $i++)
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
        $consulta = $this->set_consulta("insertar", $tabla, $columnas, $datos);
        echo "Consulta: ".$consulta." ";
        $query = mysql_query($consulta, $this->conexion);
        if (!$query) die("query failed: " . mysql_error());
      }
    }

    public function modificar($tabla, $columnas, $datos, $ids)
    {

      //UPDATE tabla SET columna="2003-06-01" WHERE ID=dato;
      //UPDATE tabla SET campo = ‘valor’, campo2 = ‘valor2’ WHERE condición;

      //Primero consultar que no existe;
    }

    public function borrar($tabla, $columnas, $datos)
    {
      if ($this->buscar($tabla, $columnas, $datos) != 0) //si encuentra el registro
      {
      $consulta = $this->set_consulta("borrar", $tabla, $columnas, $datos);
      echo "Consulta: ".$consulta." ";
      $query = mysql_query($consulta, $this->conexion);
      if (!$query) die("query failed: " . mysql_error());
    }
  }
}

?>
