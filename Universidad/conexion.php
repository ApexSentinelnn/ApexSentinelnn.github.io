<?php
$conn = new mysqli("localhost", "root", "", "universidad");
if ($conn->connect_error) {
    die("Conexión fallida: " . $conn->connect_error);
}
?>