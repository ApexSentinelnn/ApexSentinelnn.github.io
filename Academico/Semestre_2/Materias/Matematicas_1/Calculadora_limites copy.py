import math
from sympy import symbols, simplify, sympify

def main():
    print("""
**************************************************
*                   HECHO POR:                    *
*           Noe Castillo Gaytan. 187855          *
**************************************************

Instrucciones:
1. Variable (x, y, z)
2. Punto límite (número o letra)
3. Función (usa **, * para exponentes y multiplicación)
4. Valores de aproximación (separados por comas)
""")
    
    var = input("Variable: ").strip()
    punto = input(f"Punto al que tiende {var}: ").strip()
    
    while True:
        try:
            func_str = input(f"Función f({var}) = ").replace('^', '**').strip()
            x = symbols(var)
            funcion_simplificada = sympify(func_str)
            print(f"Función simplificada: {funcion_simplificada}")
            funcion = eval(f"lambda {var}: {str(funcion_simplificada)}", 
                         {"math": math, "sin": math.sin, "cos": math.cos, "tan": math.tan,
                          "exp": math.exp, "log": math.log, "sqrt": math.sqrt, "pi": math.pi, "e": math.e})
            break
        except Exception as e:
            print(f"Error: {e}. Intenta de nuevo.")
    
    while True:
        try:
            izq = [float(x.strip()) for x in input("Valores izquierda (-0.5,-0.1,-0.01...): ").split(',')]
            der = [float(x.strip()) for x in input("Valores derecha (0.5,0.1,0.01...): ").split(',')]
            break
        except ValueError:
            print("Error: Ingresa valores numéricos válidos.")
    
    resultados = {"izquierda": [], "derecha": []}
    for lado, valores in [("izquierda", izq), ("derecha", der)]:
        for val in valores:
            try:
                res = funcion(val)
                resultados[lado].append(res if not (isinstance(res, complex) or 
                    math.isnan(res) or math.isinf(res)) else "Indeterminado")
            except Exception:
                resultados[lado].append("Error")

    print("\n**************************************************")
    print("*              Tabla de aproximaciones            *")
    print("**************************************************")
    print("*  Aproximación izquierda   |  Aproximación derecha  *")
    print("**************************************************")
    
    for i in range(max(len(izq), len(der))):
        izq_val = f"{izq[i]:.8f}" if i < len(izq) else ""
        izq_res = f"{resultados['izquierda'][i]:.8f}" if (i < len(resultados['izquierda']) and 
            isinstance(resultados['izquierda'][i], float)) else str(resultados['izquierda'][i])
        der_val = f"{der[i]:.8f}" if i < len(der) else ""
        der_res = f"{resultados['derecha'][i]:.8f}" if (i < len(resultados['derecha']) and 
            isinstance(resultados['derecha'][i], float)) else str(resultados['derecha'][i])
        print(f"* {izq_val:>10} → {izq_res:<15} | {der_val:>10} → {der_res:<15} *")
    
    print("**************************************************")
    
    try:
        lim_izq = next((x for x in reversed(resultados['izquierda']) if isinstance(x, float)), None)
        lim_der = next((x for x in reversed(resultados['derecha']) if isinstance(x, float)), None)
        if lim_izq is not None and lim_der is not None:
            print(f"\nLímite por izquierda: {lim_izq:.8f}")
            print(f"Límite por derecha: {lim_der:.8f}")
            print(f"\nEl límite {'EXISTE y es: ' + f'{(lim_izq + lim_der)/2:.8f}' if abs(lim_izq - lim_der) < 1e-3 else 'NO EXISTE'}")
    except Exception as e:
        print(f"\nError al calcular el límite: {e}")

if __name__ == "__main__":
    main()