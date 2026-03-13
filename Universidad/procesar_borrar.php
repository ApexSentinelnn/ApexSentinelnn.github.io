<?php
include 'conexion.php';

if (isset($_POST['usuario_borrar'])) {
    $usr = $_POST['usuario_borrar'];
    $res = $conn->query("SELECT * FROM usuarios WHERE usuario = '$usr'");
    if ($res->num_rows > 0) {
        $row = $res->fetch_assoc();
        echo '<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">';
        echo '<div class="container mt-5"><div class="alert alert-danger"><strong>Atención:</strong> ¿Estás seguro que deseas eliminar este registro?</div>';
        echo '<form action="procesar_borrar.php" method="POST" class="row g-3">';
        echo '<input type="hidden" name="id_eliminar" value="' . $row['id'] . '">';
        // Campos readonly
        echo '<div class="col-md-6"><label>Nombre</label><input type="text" class="form-control" value="' . $row['nombre'] . '" readonly></div>';
        echo '<div class="col-md-6"><label>Usuario</label><input type="text" class="form-control" value="' . $row['usuario'] . '" readonly></div>';
        echo '<div class="col-12 mt-3"><button type="submit" class="btn btn-danger">Confirmar Eliminación</button> <a href="borrar.html" class="btn btn-secondary">Cancelar</a></div>';
        echo '</form></div>';
    } else {
        echo "<script>alert('Usuario no encontrado'); window.location='borrar.html';</script>";
    }
}

if (isset($_POST['id_eliminar'])) {
    $id = $_POST['id_eliminar'];
    $conn->query("DELETE FROM usuarios WHERE id=$id");
    echo "<script>alert('Usuario eliminado'); window.location='principal.html';</script>";
}
?>