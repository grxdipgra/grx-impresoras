<?php
$uploadpath = "./files/";
$filedata = $_FILES['file']['tmp_name'];
echo "Directorio de subida = ".$uploadpath."\n";
echo "filedata = ".$filedata."\n";
$filename = $_POST['filename'];
echo "filename = ".$filename."\n";
copy($filedata,$uploadpath.$filename);
echo "exito\n"
?>
