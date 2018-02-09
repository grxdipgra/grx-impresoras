# Script php para la adquisición de ficheros y datos:
#./NuevaImpresora.php
<?php
// Esta parte sube el archivo
$directorio = realpath('./') . '/';
move_uploaded_file($_FILES['fichero']['tmp_name'], $directorio . $_FILES['fichero']['name'] );

// Esta parte imprime la información adicional pasada por el Curl.
print_r ($_POST);
?>
