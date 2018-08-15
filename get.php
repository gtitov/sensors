<?php
$log = fopen("log.csv", 'a');
$datestamp = date("Y.m.d H:i:s");
$value = $_GET["val"];
fwrite($log, $datestamp.",".$value.PHP_EOL) or die("Permission to csv denied!");
fclose($log);
?>
