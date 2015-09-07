<?php
header('Content-Type: application/javascript');
/*
 * PHP Sockets - How to create a sockets server/client
 */

//include the server.php script to start the server
//include_once('server.php');

$host    = "127.0.0.1";
$port    = $_GET['port'];
$app = $_GET['application'];
//$priority = $_GET['priority'];
$message = $app.$_GET['message'];

// create socket
$socket = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");
// connect to server
$result = socket_connect($socket, $host, $port) or die("Could not connect to server\n");
// send string to server
socket_write($socket, $message, strlen($message)) or die("Could not send data to server\n");
// get server response
$result = socket_read ($socket, 1024) or die("Could not read server response\n");
//$jsonp = $_GET['callback'];

if(array_key_exists('callback', $_GET)){

    header('Content-Type: text/javascript; charset=utf8');
    header('Access-Control-Allow-Origin: *');
    header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE');

    $callback = $_GET['callback'];
    echo $callback.'('.$result.');';
}else{
    // normal JSON string
    header('Content-Type: application/json; charset=utf8');

    echo $result;
}
//echo $result;
// close socket
socket_close($socket);
?>
