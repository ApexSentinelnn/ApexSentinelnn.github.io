import tkinter as tk
from tkinter import messagebox, Menu
import subprocess

def ejecutar_conversor():
    try:
        subprocess.run(["python", "conversor.py"], check=True)
    except Exception as e:
        messagebox.showerror("Error", f"No se pudo ejecutar el conversor: {e}")

def ejecutar_img_to_pdf():
    try:
        subprocess.run(["python", "Conversor_img_to_pdf.py"], check=True)
    except Exception as e:
        messagebox.showerror("Error", f"No se pudo ejecutar el conversor a PDF: {e}")

def salir():
    root.quit()

def acerca_de():
    messagebox.showinfo("Acerca de", "Menú de herramientas v1.0\nDesarrollado en Python con Tkinter")

# Crear ventana principal
root = tk.Tk()
root.title("Menú de Herramientas")
root.geometry("400x300")
root.resizable(False, False)
root.configure(bg="#2C3E50")

# Estilos de botones
def crear_boton(texto, comando, color):
    return tk.Button(root, text=texto, command=comando, font=("Arial", 12), bg=color, fg="white", width=30, height=2, relief="raised")

# Menú superior
menu_bar = Menu(root)
root.config(menu=menu_bar)

herramientas_menu = Menu(menu_bar, tearoff=0)
herramientas_menu.add_command(label="Conversor de Imágenes", command=ejecutar_conversor)
herramientas_menu.add_command(label="Conversor de Imágenes a PDF", command=ejecutar_img_to_pdf)
menu_bar.add_cascade(label="Herramientas", menu=herramientas_menu)

ayuda_menu = Menu(menu_bar, tearoff=0)
ayuda_menu.add_command(label="Acerca de", command=acerca_de)
menu_bar.add_cascade(label="Ayuda", menu=ayuda_menu)

# Título
titulo = tk.Label(root, text="Menú de Herramientas", font=("Arial", 16, "bold"), fg="white", bg="#2C3E50")
titulo.pack(pady=10)

# Botones
crear_boton("Conversor de Imágenes", ejecutar_conversor, "#3498DB").pack(pady=5)
crear_boton("Conversor de Imágenes a PDF", ejecutar_img_to_pdf, "#E74C3C").pack(pady=5)
crear_boton("Salir", salir, "#95A5A6").pack(pady=20)

# Iniciar la aplicación
root.mainloop()