<?php
include 'conexion.php';
$sql = "INSERT INTO usuarios (nombre, apellido, edad, email, fecha_registro, usuario, contrasena, telefono) 
        VALUES ('$_POST[nombre]', '$_POST[apellido]', '$_POST[edad]', '$_POST[email]', '$_POST[fecha_registro]', '$_POST[usuario]', '$_POST[contrasena]', '$_POST[telefono]')";

if ($conn->query($sql) === TRUE)
    echo "<script>alert('Usuario registrado con éxito'); window.location='principal.html';</script>";
else
    echo "Error: " . $conn->error;
$conn->close();
?>