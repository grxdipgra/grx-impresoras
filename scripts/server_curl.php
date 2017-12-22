<?php
$uploadpath = "./files/";
$filedata = $_FILES['file']['tmp_name'];
echo "filedata = ".$filedata;
$filename = $_POST['filename'];
copy($filedata,$uploadpath.$filename);
echo "exito"
?>

