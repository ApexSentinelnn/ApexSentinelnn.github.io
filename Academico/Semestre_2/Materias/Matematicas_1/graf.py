import numpy as np
import matplotlib.pyplot as plt

# Definir la función
def f(x):
    return x**2 - 3*x - 4

# Crear valores de x
x = np.linspace(-5, 6, 400)
y = f(x)

# Graficar la función
plt.plot(x, y, label=r'$f(x) = x^2 - 3x - 4$')
plt.axhline(0, color='black', linewidth=0.5)  # Eje X
plt.axvline(0, color='black', linewidth=0.5)  # Eje Y

# Marcar puntos clave
plt.scatter([-1, 4], [0, 0], color='red', label="Raíces")  # Raíces
plt.scatter([0], [-4], color='blue', label="Intersección Y")  # Intersección Y
plt.scatter([1.5], [-25/4], color='green', label="Vértice")  # Vértice

# Configuración del gráfico
plt.legend()
plt.grid()
plt.title("Gráfica de f(x) = x^2 - 3x - 4")
plt.xlabel("x")
plt.ylabel("f(x)")

# Mostrar la gráfica
plt.show()
