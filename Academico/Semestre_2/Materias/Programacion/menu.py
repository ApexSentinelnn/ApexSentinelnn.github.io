import tkinter as tk
from tkinter import messagebox
import pyautogui
import time

def seleccionar_area():
    messagebox.showinfo("Seleccionar área", "Selecciona el área de captura arrastrando el cursor")
    x1, y1, x2, y2 = pyautogui.locateOnScreen(pyautogui.screenshot())
    captura = pyautogui.screenshot(region=(x1, y1, x2 - x1, y2 - y1))
    captura.save("captura.png")
    messagebox.showinfo("Captura de pantalla", "Se ha guardado la captura como 'captura.png'")

def salir():
    ventana.destroy()

# Crear la ventana principal
ventana = tk.Tk()
ventana.title("Menú de opciones")
ventana.geometry("300x200")

# Botón para seleccionar área y tomar captura de pantalla
btn_captura = tk.Button(ventana, text="Seleccionar área y capturar", command=seleccionar_area, width=25, height=2)
btn_captura.pack(pady=10)

# Botón para salir
btn_salir = tk.Button(ventana, text="Salir", command=salir, width=20, height=2)
btn_salir.pack(pady=10)

# Ejecutar la ventana
ventana.mainloop()
