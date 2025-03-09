import os
import tkinter as tk
from tkinter import filedialog, messagebox, simpledialog
from cryptography.fernet import Fernet
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.backends import default_backend
import base64

# Generar una clave derivada de la contraseña
def derivar_clave(contraseña, salt):
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=100000,
        backend=default_backend()
    )
    return base64.urlsafe_b64encode(kdf.derive(contraseña.encode()))

# Encriptar un archivo
def encriptar_archivo(ruta_archivo, clave):
    fernet = Fernet(clave)
    with open(ruta_archivo, "rb") as file:
        datos = file.read()
    datos_encriptados = fernet.encrypt(datos)
    with open(ruta_archivo + ".enc", "wb") as file:
        file.write(datos_encriptados)
    return ruta_archivo + ".enc"

# Desencriptar un archivo
def desencriptar_archivo(ruta_archivo, clave):
    fernet = Fernet(clave)
    with open(ruta_archivo, "rb") as file:
        datos_encriptados = file.read()
    datos = fernet.decrypt(datos_encriptados)
    with open(ruta_archivo[:-4], "wb") as file:  # Elimina la extensión .enc
        file.write(datos)
    return ruta_archivo[:-4]

# Interfaz gráfica
class EncriptadorApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Encriptador Seguro")
        self.root.geometry("500x300")

        # Botón para seleccionar archivo
        self.btn_seleccionar = tk.Button(root, text="Seleccionar Archivo", command=self.seleccionar_archivo)
        self.btn_seleccionar.pack(pady=20)

        # Botón para encriptar
        self.btn_encriptar = tk.Button(root, text="Encriptar", command=self.encriptar, state=tk.DISABLED)
        self.btn_encriptar.pack(pady=10)

        # Botón para desencriptar
        self.btn_desencriptar = tk.Button(root, text="Desencriptar", command=self.desencriptar, state=tk.DISABLED)
        self.btn_desencriptar.pack(pady=10)

        # Variable para almacenar la ruta del archivo
        self.ruta_archivo = None

    # Seleccionar archivo
    def seleccionar_archivo(self):
        self.ruta_archivo = filedialog.askopenfilename(title="Selecciona un archivo")
        if self.ruta_archivo:
            self.btn_encriptar.config(state=tk.NORMAL)
            self.btn_desencriptar.config(state=tk.NORMAL)

    # Encriptar archivo
    def encriptar(self):
        if not self.ruta_archivo:
            return

        # Solicitar contraseña
        contraseña = simpledialog.askstring("Contraseña", "Introduce una contraseña segura:", show="*")
        if not contraseña:
            return

        # Solicitar segunda contraseña (factor de autenticación)
        segunda_contraseña = simpledialog.askstring("Segunda Contraseña", "Introduce la segunda contraseña:", show="*")
        if not segunda_contraseña:
            return

        # Verificar segunda contraseña
        if segunda_contraseña != "mi_segunda_contraseña":  # Cambia esto por tu segunda contraseña
            messagebox.showerror("Error", "Segunda contraseña incorrecta.")
            return

        # Derivar clave y encriptar
        salt = os.urandom(16)  # Generar un salt aleatorio
        clave = derivar_clave(contraseña, salt)
        ruta_encriptado = encriptar_archivo(self.ruta_archivo, clave)

        # Mostrar resultado
        messagebox.showinfo("Éxito", f"Archivo encriptado guardado como:\n{ruta_encriptado}")

    # Desencriptar archivo
    def desencriptar(self):
        if not self.ruta_archivo:
            return

        # Solicitar contraseña
        contraseña = simpledialog.askstring("Contraseña", "Introduce la contraseña:", show="*")
        if not contraseña:
            return

        # Solicitar segunda contraseña (factor de autenticación)
        segunda_contraseña = simpledialog.askstring("Segunda Contraseña", "Introduce la segunda contraseña:", show="*")
        if not segunda_contraseña:
            return

        # Verificar segunda contraseña
        if segunda_contraseña != "mi_segunda_contraseña":  # Cambia esto por tu segunda contraseña
            messagebox.showerror("Error", "Segunda contraseña incorrecta.")
            return

        # Derivar clave y desencriptar
        salt = os.urandom(16)  # Usar el mismo salt que durante la encriptación
        clave = derivar_clave(contraseña, salt)
        try:
            ruta_desencriptado = desencriptar_archivo(self.ruta_archivo, clave)
            messagebox.showinfo("Éxito", f"Archivo desencriptado guardado como:\n{ruta_desencriptado}")
        except Exception as e:
            messagebox.showerror("Error", f"Error al desencriptar: {e}")

# Ejecutar la aplicación
if __name__ == "__main__":
    root = tk.Tk()
    app = EncriptadorApp(root)
    root.mainloop()