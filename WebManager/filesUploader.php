<?php
///@file

error_reporting(E_ALL); // or E_STRICT
ini_set("display_errors",1);
ini_set("memory_limit","1024M");
set_time_limit(0);
ini_set('upload_max_filesize', '500M');
ini_set('post_max_size', '500M');
ini_set('max_input_time', 4000); // Play with the values
ini_set('max_execution_time', 4000); // Play with the values
//echo exec('whoami');
//
print_r($_FILES);
$new_song_name="ApplicazioneMobile.mp3";
move_uploaded_file($_FILES["file"]["tmp_name"], "/var/www/consoleWEB/uploadedFiles/".$new_song_name);
?>
