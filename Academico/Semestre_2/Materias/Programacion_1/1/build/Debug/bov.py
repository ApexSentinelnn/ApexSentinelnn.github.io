import os
import base64
import zipfile
from cryptography.fernet import Fernet
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.backends import default_backend
import tkinter as tk
from tkinter import ttk, filedialog, messagebox, simpledialog
from tkinter.scrolledtext import ScrolledText
from PIL import Image, ImageTk
import shutil
import io


class BovedaDigital:
    def __init__(self, master):
        self.master = master
        master.title("Bóveda Digital Segura")
        master.geometry("1200x800")
        master.configure(bg="#2E3440")  # Fondo oscuro

        # --- Estilo y Tema ---
        self.style = ttk.Style()
        self.style.theme_use('clam')  # Tema moderno

        # Configuración de estilos personalizados
        self.style.configure("TButton", padding=10, relief="flat", background="#4C566A", foreground="white", font=('Arial', 10, 'bold'))
        self.style.configure("TLabel", background="#2E3440", foreground="white", font=('Arial', 12))
        self.style.configure("TFrame", background="#3B4252")
        self.style.configure("TNotebook", background="#3B4252")
        self.style.configure("TNotebook.Tab", padding=10, background="#4C566A", foreground="white", font=('Arial', 12))
        self.style.configure("EstadoAbierta.TLabel", font=('Arial', 10, 'bold'), foreground="#A3BE8C")  # Verde claro
        self.style.configure("EstadoCerrada.TLabel", font=('Arial', 10, 'italic'), foreground="#BF616A")  # Rojo claro

        # --- Variables ---
        self.ruta_boveda = ""
        self.clave_maestra = ""
        self.boveda_abierta = False
        self.ruta_boveda_abierta = None

        # --- Interfaz Principal ---
        self.notebook = ttk.Notebook(master)
        self.notebook.pack(expand=True, fill="both", padx=10, pady=10)

        self.crear_tab_boveda()
        self.crear_tab_archivos()

    def crear_tab_boveda(self):
        # --- Tab: Gestión de Bóveda ---
        tab_boveda = ttk.Frame(self.notebook)
        self.notebook.add(tab_boveda, text="Bóveda")

        # --- Sección: Crear/Abrir Bóveda ---
        frame_boveda = ttk.LabelFrame(tab_boveda, text="Bóveda")
        frame_boveda.pack(padx=10, pady=10, fill="x")

        ttk.Label(frame_boveda, text="Ruta para la Bóveda:").grid(row=0, column=0, padx=5, pady=5, sticky="w")
        self.entry_ruta_boveda = ttk.Entry(frame_boveda, width=50)
        self.entry_ruta_boveda.grid(row=0, column=1, padx=5, pady=5, sticky="ew")

        ttk.Button(frame_boveda, text="Seleccionar", command=self.seleccionar_ruta_boveda).grid(row=0, column=2, padx=5, pady=5)
        ttk.Button(frame_boveda, text="Crear Bóveda", command=self.crear_boveda).grid(row=1, column=0, columnspan=3, padx=5, pady=5)

        # --- Lista de Bóvedas Existentes ---
        frame_lista = ttk.LabelFrame(tab_boveda, text="Bóvedas Existentes")
        frame_lista.pack(padx=10, pady=10, fill="both", expand=True)

        self.lista_bovedas = tk.Listbox(frame_lista, width=60, height=10, bg="#4C566A", fg="white", font=('Arial', 10))
        self.lista_bovedas.pack(padx=5, pady=5, fill="both", expand=True)
        self.lista_bovedas.bind("<Double-1>", self.abrir_boveda_seleccionada)

        ttk.Button(frame_lista, text="Actualizar Lista", command=self.actualizar_lista_bovedas).pack(pady=5)

        # --- Sección: Estado de la Bóveda ---
        frame_estado = ttk.LabelFrame(tab_boveda, text="Estado")
        frame_estado.pack(padx=10, pady=10, fill="x")

        self.label_estado = ttk.Label(frame_estado, text="Bóveda Cerrada", style="EstadoCerrada.TLabel")
        self.label_estado.pack(padx=5, pady=5)

    def crear_tab_archivos(self):
        # --- Tab: Encriptación de Archivos Individuales ---
        tab_archivos = ttk.Frame(self.notebook)
        self.notebook.add(tab_archivos, text="Archivos")

        frame_archivos = ttk.LabelFrame(tab_archivos, text="Encriptar/Desencriptar Archivo")
        frame_archivos.pack(padx=10, pady=10, fill="x")

        ttk.Label(frame_archivos, text="Archivo:").grid(row=0, column=0, padx=5, pady=5, sticky="w")
        self.entry_archivo = ttk.Entry(frame_archivos, width=50)
        self.entry_archivo.grid(row=0, column=1, padx=5, pady=5, sticky="ew")
        ttk.Button(frame_archivos, text="Seleccionar", command=self.seleccionar_archivo).grid(row=0, column=2, padx=5, pady=5)

        ttk.Label(frame_archivos, text="Clave:").grid(row=1, column=0, padx=5, pady=5, sticky="w")
        self.entry_clave_archivo = ttk.Entry(frame_archivos, width=30, show="*")
        self.entry_clave_archivo.grid(row=1, column=1, padx=5, pady=5, sticky="ew")

        ttk.Button(frame_archivos, text="Encriptar Archivo", command=self.encriptar_archivo_individual).grid(row=2, column=0, columnspan=3, padx=5, pady=5)
        ttk.Button(frame_archivos, text="Desencriptar Archivo", command=self.desencriptar_archivo_individual).grid(row=3, column=0, columnspan=3, padx=5, pady=5)

    # --- Funciones Bóveda ---
    def seleccionar_ruta_boveda(self):
        ruta = filedialog.askdirectory()
        self.entry_ruta_boveda.insert(0, ruta)
        self.ruta_boveda = ruta
        self.actualizar_lista_bovedas()

    def crear_boveda(self):
        self.ruta_boveda = self.entry_ruta_boveda.get()
        if not self.ruta_boveda:
            messagebox.showerror("Error", "Por favor, selecciona una ruta para la bóveda.")
            return

        nombre_boveda = simpledialog.askstring("Crear Bóveda", "Nombre de la Bóveda:")
        if not nombre_boveda:
            return

        clave = self.pedir_clave("Crear Contraseña para la Bóveda")
        if not clave:
            return

        ruta_boveda_completa = os.path.join(self.ruta_boveda, nombre_boveda + ".locked")

        try:
            os.makedirs(ruta_boveda_completa, exist_ok=False)
            self.guardar_clave_maestra(clave, ruta_boveda_completa)
            messagebox.showinfo("Éxito", "Bóveda creada con éxito.")
            self.actualizar_lista_bovedas()
        except FileExistsError:
            messagebox.showerror("Error", "Ya existe una bóveda con ese nombre.")
        except Exception as e:
            messagebox.showerror("Error", f"No se pudo crear la bóveda: {e}")

    def actualizar_lista_bovedas(self):
        self.lista_bovedas.delete(0, tk.END)
        if self.ruta_boveda and os.path.isdir(self.ruta_boveda):
            for item in os.listdir(self.ruta_boveda):
                if item.endswith(".locked"):
                    self.lista_bovedas.insert(tk.END, item.replace(".locked", ""))

    def abrir_boveda_seleccionada(self, event):
        seleccion = self.lista_bovedas.curselection()
        if not seleccion:
            return

        nombre_boveda = self.lista_bovedas.get(seleccion[0])
        ruta_boveda_completa = os.path.join(self.ruta_boveda, nombre_boveda + ".locked")

        clave = self.pedir_clave(f"Ingresar Contraseña para {nombre_boveda}")
        if not clave:
            return

        if not self.verificar_clave_maestra(clave, ruta_boveda_completa):
            messagebox.showerror("Error", "Contraseña incorrecta.")
            return

        self.clave_maestra = clave
        self.ruta_boveda_abierta = ruta_boveda_completa
        self.boveda_abierta = True
        self.label_estado.config(text=f"Bóveda Abierta: {nombre_boveda}", style="EstadoAbierta.TLabel")
        self.mostrar_ventana_herramientas(nombre_boveda)

    def mostrar_ventana_herramientas(self, nombre_boveda):
        ventana = tk.Toplevel(self.master)
        ventana.title(f"Herramientas de Bóveda: {nombre_boveda}")
        ventana.geometry("800x600")
        ventana.configure(bg="#3B4252")

        # --- Lista de Archivos ---
        frame_archivos = ttk.LabelFrame(ventana, text="Archivos en la Bóveda")
        frame_archivos.pack(padx=10, pady=10, fill="both", expand=True)

        self.lista_archivos = tk.Listbox(frame_archivos, width=60, height=10, bg="#4C566A", fg="white", font=('Arial', 10))
        self.lista_archivos.pack(padx=5, pady=5, fill="both", expand=True)
        self.lista_archivos.bind("<<ListboxSelect>>", self.previsualizar_archivo)
        self.cargar_lista_archivos()

        # --- Botones ---
        frame_botones = ttk.Frame(ventana)
        frame_botones.pack(pady=5)

        ttk.Button(frame_botones, text="Agregar Archivos", command=self.agregar_archivos_a_boveda).pack(side="left", padx=5)
        ttk.Button(frame_botones, text="Eliminar Archivo", command=self.eliminar_archivo_de_boveda).pack(side="left", padx=5)
        ttk.Button(frame_botones, text="Descargar Archivo", command=self.descargar_archivo_de_boveda).pack(side="left", padx=5)

        # --- Previsualización ---
        self.frame_previsualizacion = ttk.LabelFrame(ventana, text="Previsualización")
        self.frame_previsualizacion.pack(padx=10, pady=10, fill="both", expand=True)

        self.label_previsualizacion = ttk.Label(self.frame_previsualizacion, text="Selecciona un archivo para previsualizar.", background="#3B4252", foreground="white")
        self.label_previsualizacion.pack(padx=5, pady=5, fill="both", expand=True)

    def previsualizar_archivo(self, event):
        seleccion = self.lista_archivos.curselection()
        if not seleccion:
            return

        nombre_archivo = self.lista_archivos.get(seleccion[0])
        ruta_archivo = os.path.join(self.ruta_boveda_abierta, nombre_archivo)

        try:
            if nombre_archivo.lower().endswith(('.png', '.jpg', '.jpeg', '.gif')):
                imagen = Image.open(ruta_archivo)
                imagen = imagen.resize((300, 300), Image.ANTIALIAS)
                foto = ImageTk.PhotoImage(imagen)
                self.label_previsualizacion.config(image=foto, text="")
                self.label_previsualizacion.image = foto
            elif nombre_archivo.lower().endswith(('.txt', '.log')):
                with open(ruta_archivo, 'r', encoding='utf-8') as archivo:
                    contenido = archivo.read()
                self.label_previsualizacion.config(image=None, text=contenido)
            else:
                self.label_previsualizacion.config(image=None, text="Previsualización no disponible para este tipo de archivo.")
        except Exception as e:
            self.label_previsualizacion.config(image=None, text=f"Error al previsualizar: {e}")

    def agregar_archivos_a_boveda(self):
        if not self.boveda_abierta:
            messagebox.showerror("Error", "La bóveda debe estar abierta para agregar archivos.")
            return

        rutas_archivos = filedialog.askopenfilenames()
        if not rutas_archivos:
            return

        for ruta_archivo in rutas_archivos:
            nombre_archivo = os.path.basename(ruta_archivo)
            ruta_destino = os.path.join(self.ruta_boveda_abierta, nombre_archivo)

            try:
                shutil.copy2(ruta_archivo, ruta_destino)
            except Exception as e:
                messagebox.showerror("Error", f"No se pudo agregar el archivo {nombre_archivo}: {e}")

        self.cargar_lista_archivos()
        messagebox.showinfo("Éxito", "Archivos agregados a la bóveda con éxito.")

    def cargar_lista_archivos(self):
        self.lista_archivos.delete(0, tk.END)
        if self.boveda_abierta:
            for nombre_archivo in os.listdir(self.ruta_boveda_abierta):
                ruta_archivo = os.path.join(self.ruta_boveda_abierta, nombre_archivo)
                if os.path.isfile(ruta_archivo) and nombre_archivo != "clave_maestra.key":
                    self.lista_archivos.insert(tk.END, nombre_archivo)

    def eliminar_archivo_de_boveda(self):
        try:
            index = self.lista_archivos.curselection()[0]
            nombre_archivo = self.lista_archivos.get(index)
            ruta_archivo = os.path.join(self.ruta_boveda_abierta, nombre_archivo)

            confirmar = messagebox.askyesno("Confirmar", "¿Estás seguro de que quieres eliminar este archivo de la bóveda?")
            if confirmar:
                os.remove(ruta_archivo)
                self.cargar_lista_archivos()
                messagebox.showinfo("Éxito", "Archivo eliminado de la bóveda con éxito.")

        except IndexError:
            messagebox.showerror("Error", "Por favor, selecciona un archivo para eliminar.")
        except Exception as e:
            messagebox.showerror("Error", f"No se pudo eliminar el archivo: {e}")

    def descargar_archivo_de_boveda(self):
        try:
            index = self.lista_archivos.curselection()[0]
            nombre_archivo = self.lista_archivos.get(index)
            ruta_archivo = os.path.join(self.ruta_boveda_abierta, nombre_archivo)

            ruta_destino = filedialog.asksaveasfilename(defaultextension=".*", initialfile=nombre_archivo)
            if not ruta_destino:
                return

            shutil.copy2(ruta_archivo, ruta_destino)
            messagebox.showinfo("Éxito", "Archivo descargado con éxito.")

        except IndexError:
            messagebox.showerror("Error", "Por favor, selecciona un archivo para descargar.")
        except Exception as e:
            messagebox.showerror("Error", f"No se pudo descargar el archivo: {e}")

    # --- Funciones Archivos Individuales ---
    def seleccionar_archivo(self):
        ruta = filedialog.askopenfilename()
        self.entry_archivo.insert(0, ruta)

    def encriptar_archivo_individual(self):
        ruta_archivo = self.entry_archivo.get()
        clave = self.entry_clave_archivo.get()

        if not ruta_archivo or not os.path.isfile(ruta_archivo):
            messagebox.showerror("Error", "Por favor, selecciona un archivo válido.")
            return

        if not clave:
            messagebox.showerror("Error", "Por favor, ingresa una clave.")
            return

        try:
            self.encriptar_archivo(ruta_archivo, clave)
            messagebox.showinfo("Éxito", "Archivo encriptado con éxito.")
        except Exception as e:
            messagebox.showerror("Error", f"No se pudo encriptar el archivo: {e}")

    def desencriptar_archivo_individual(self):
        ruta_archivo = self.entry_archivo.get()
        clave = self.entry_clave_archivo.get()

        if not ruta_archivo or not os.path.isfile(ruta_archivo):
            messagebox.showerror("Error", "Por favor, selecciona un archivo válido.")
            return

        if not clave:
            messagebox.showerror("Error", "Por favor, ingresa una clave.")
            return

        try:
            contenido = self.desencriptar_archivo(ruta_archivo, clave)
            messagebox.showinfo("Éxito", "Archivo desencriptado con éxito.")
        except Exception as e:
            messagebox.showerror("Error", f"No se pudo desencriptar el archivo: {e}")

    def encriptar_archivo(self, ruta_archivo, clave):
        clave_derivada, salt = self.generar_clave_derivada(clave)
        f = Fernet(clave_derivada)

        with open(ruta_archivo, "rb") as archivo:
            datos = archivo.read()

        datos_encriptados = f.encrypt(datos)

        with open(ruta_archivo, "wb") as archivo:
            archivo.write(salt + datos_encriptados)

    def desencriptar_archivo(self, ruta_archivo, clave):
        with open(ruta_archivo, "rb") as archivo:
            contenido = archivo.read()

        salt = contenido[:16]
        datos_encriptados = contenido[16:]

        clave_derivada, _ = self.generar_clave_derivada(clave, salt)
        f = Fernet(clave_derivada)

        try:
            datos_desencriptados = f.decrypt(datos_encriptados)
            return datos_desencriptados.decode('utf-8')
        except:
            return datos_desencriptados

    def generar_clave_derivada(self, clave, salt=None):
        if salt is None:
            salt = os.urandom(16)
        kdf = PBKDF2HMAC(
            algorithm=hashes.SHA256(),
            length=32,
            salt=salt,
            iterations=100000,
            backend=default_backend()
        )
        clave_derivada = base64.urlsafe_b64encode(kdf.derive(clave.encode()))
        return clave_derivada, salt

    def guardar_clave_maestra(self, clave, ruta_boveda):
        clave_derivada, salt = self.generar_clave_derivada(clave)
        f = Fernet(clave_derivada)
        clave_cifrada = f.encrypt(clave.encode())

        with open(os.path.join(ruta_boveda, "clave_maestra.key"), "wb") as archivo_clave:
            archivo_clave.write(salt + b"|" + clave_cifrada)

    def verificar_clave_maestra(self, clave, ruta_boveda):
        try:
            with open(os.path.join(ruta_boveda, "clave_maestra.key"), "rb") as archivo_clave:
                contenido = archivo_clave.read()
                salt, clave_cifrada = contenido.split(b"|", 1)

            clave_derivada, _ = self.generar_clave_derivada(clave, salt)
            f = Fernet(clave_derivada)
            clave_descifrada = f.decrypt(clave_cifrada).decode()

            return clave == clave_descifrada
        except Exception as e:
            print(f"Error al verificar la clave maestra: {e}")
            return False

    def pedir_clave(self, titulo):
        clave = simpledialog.askstring(titulo, "Ingresa la contraseña:", show="*")
        return clave


# --- Ejecución ---
if __name__ == "__main__":
    root = tk.Tk()
    boveda = BovedaDigital(root)
    root.mainloop()