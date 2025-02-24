
import math
from sympy import symbols, simplify

def main():
    print("******************************************************\n")
    print("*                  HECHO POR:                        *\n")
    print("*          Noe Castillo Gaytan. 187855               *\n")
    print("******************************************************\n\n")
    print("Este programa calcula el límite de una función al aproximarse a un punto desde ambos lados.\n")
    print("Instrucciones de uso:")
    print("1. Ingresa la variable de la función (ejem. x, y, z).")
    print("2. Ingresa el punto al que tiende la variable (puede ser un número o una letra).")
    print("3. Ingresa la función usando sintaxis  válida:")
    print("   - Usa ** o ^ para exponentes (ejemp. x**2 o x^2)")
    print("   - Usa * para multiplicación")
    print("   - Funciones trigonométricas usan radianes.")
    print("4. Ingresa valores de aproximación por izquierda y derecha separados por comas.\n")
    
    # Obtener datos del usuario
    var = input("Variable: ")
    punto = input(f"Punto al que tiende {var} (puede ser un número o una letra): ")
    
    # Construir función
    while True:
        func_str = input(f"Función f({var}) = ").replace('^', '**')
        try:
            # Simplificar la función simbólicamente
            x = symbols(var)
            funcion_simplificada = simplify(func_str)
            print(f"Función simplificada: {funcion_simplificada}")

            # Crear función evaluable con funciones matemáticas permitidas
            funciones_permitidas = {
                "math": math, "sin": math.sin, "cos": math.cos, "tan": math.tan,
                "exp": math.exp, "log": math.log, "sqrt": math.sqrt, "pi": math.pi
            }
            funcion = eval(f"lambda {var}: {funcion_simplificada}", funciones_permitidas)
            break
        except Exception as e:
            print(f"Error en la función: {e}. Intenta de nuevo.")
    
    # Obtener aproximaciones
    while True:
        try:
            izq = input("Valores por izquierda (ejemp. -0.5,-0.1,-0.01,0.001,-0.0001): ").split(',')
            der = input("Valores por derecha (ejemp.): 0.5,0.1,0.01,0.001,0.0001").split(',')
            break
        except ValueError:
            print("Error: Ingresa valores válidos separados por comas. Intenta de nuevo.")
    
    # Evaluar función
    resultados = {"izquierda": [], "derecha": []}
    
    for lado in ['izquierda', 'derecha']:
        for val_str in izq if lado == 'izquierda' else der:
            try:
                # Evaluar numéricamente reemplazando el punto
                if punto.isalpha():  
                    val = eval(val_str.replace(punto, "1.0"), funciones_permitidas)  # Usamos 1.0 como referencia
                else:
                    val = eval(val_str.replace(punto, punto), funciones_permitidas)

                resultados[lado].append(funcion(val))
            except Exception as e:
                resultados[lado].append(f"Error: {type(e).__name__}")
    
    # Mostrar tabla
    print("\n{:^30} | {:^30}".format("Aproximación por izquierda", "Aproximación por derecha"))
    print("-" * 65)
    
    max_filas = max(len(izq), len(der))
    for i in range(max_filas):
        val_izq = f"{izq[i]:<8}" if i < len(izq) else ""
        res_izq = f"{round(resultados['izquierda'][i], 5):<8.5f}" if (i < len(resultados['izquierda']) and isinstance(resultados['izquierda'][i], float)) else str(resultados['izquierda'][i]) if i < len(resultados['izquierda']) else ""
        
        val_der = f"{der[i]:<8}" if i < len(der) else ""
        res_der = f"{round(resultados['derecha'][i], 5):<8.5f}" if (i < len(resultados['derecha']) and isinstance(resultados['derecha'][i], float)) else str(resultados['derecha'][i]) if i < len(resultados['derecha']) else ""
        
        print(f"{val_izq} → {res_izq:20} | {val_der} → {res_der:20}")
    
    # Determinar existencia del límite
    try:
        lim_izq = [x for x in resultados['izquierda'] if isinstance(x, float)][-1]
        lim_der = [x for x in resultados['derecha'] if isinstance(x, float)][-1]
        

        print(f"Por izquierda: {lim_izq:.5f}")
        print(f"Por derecha: {lim_der:.5f}")
    except:
        print("\nNo se pudo determinar el límite debido a errores en los cálculos.")

if __name__ == "__main__":
    main()
