<?php
include 'conexion.php';
$nombre = $_POST['nombre_buscar'];
$resultado = $conn->query("SELECT * FROM usuarios WHERE nombre LIKE '%$nombre%'");
echo '<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet"><div class="container mt-4"><h3>Resultados:</h3><table class="table table-bordered mt-3"><tr><th>ID</th><th>Nombre</th><th>Apellido</th><th>Usuario</th><th>Email</th></tr>';
while ($fila = $resultado->fetch_assoc()) {
    echo "<tr><td>{$fila['id']}</td><td>{$fila['nombre']}</td><td>{$fila['apellido']}</td><td>{$fila['usuario']}</td><td>{$fila['email']}</td></tr>";
}
echo '</table><a href="consulta.html" class="btn btn-secondary">Regresar</a></div>';
?>