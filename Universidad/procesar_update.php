<?php
include 'conexion.php';

// Si viene de update.html buscando un usuario:
if (isset($_POST['usuario_buscar'])) {
    $usr = $_POST['usuario_buscar'];
    $res = $conn->query("SELECT * FROM usuarios WHERE usuario = '$usr'");
    if ($res->num_rows > 0) {
        $row = $res->fetch_assoc();
        echo '<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">';
        echo '<div class="container mt-5"><h3>Modificar Datos</h3>';
        echo '<form action="procesar_update.php" method="POST" class="row g-3">';
        echo '<input type="hidden" name="id" value="' . $row['id'] . '">'; // ID oculto
        echo '<div class="col-md-6"><label>Nombre</label><input type="text" name="nombre" class="form-control" value="' . $row['nombre'] . '"></div>';
        echo '<div class="col-md-6"><label>Apellido</label><input type="text" name="apellido" class="form-control" value="' . $row['apellido'] . '"></div>';
        echo '<div class="col-md-4"><label>Edad</label><input type="number" name="edad" class="form-control" value="' . $row['edad'] . '"></div>';
        echo '<div class="col-md-8"><label>Teléfono</label><input type="text" name="telefono" class="form-control" value="' . $row['telefono'] . '"></div>';
        echo '<div class="col-12 mt-3"><button type="submit" class="btn btn-success">Guardar Cambios</button> <a href="update.html" class="btn btn-secondary">Cancelar</a></div>';
        echo '</form></div>';
    } else {
        echo "<script>alert('Usuario no encontrado'); window.location='update.html';</script>";
    }
}

// Si viene del formulario de modificación (para guardar):
if (isset($_POST['id'])) {
    $id = $_POST['id'];
    $sql = "UPDATE usuarios SET nombre='$_POST[nombre]', apellido='$_POST[apellido]', edad='$_POST[edad]', telefono='$_POST[telefono]' WHERE id=$id";
    if ($conn->query($sql) === TRUE)
        echo "<script>alert('Actualizado correctamente'); window.location='principal.html';</script>";
}
?>