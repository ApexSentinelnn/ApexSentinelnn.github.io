document.addEventListener("DOMContentLoaded", function () {
  const operand1 = document.getElementById("operand1");
  const operand2 = document.getElementById("operand2");
  const operation = document.getElementById("operation");
  const result = document.getElementById("result");
  const calculateBtn = document.getElementById("calculateBtn");
  const resetBtn = document.getElementById("resetBtn");

  //colores para los resultados dependiendo de su valor
  const okColor = document.getElementById("okColor");
  const emptyColor = document.getElementById("emptyColor");
  const positiveColor = document.getElementById("positiveColor");
  const negativeColor = document.getElementById("negativeColor");

  //validamos que sea un numero
  function isNumeric(value) {
    return !isNaN(parseFloat(value)) && isFinite(value);
  }

  //calculamos el resultados de los datos ingresados
  function calculate() {
    //valores
    const value1 = operand1.value.trim();
    const value2 = operand2.value.trim();
    const selectedOperation = operation.value;

    //validamos si los campos de operadores estan llenos
    if (!value1 || !value2 || !selectedOperation) {
      result.value = "Faltan datos";
      result.style.backgroundColor = emptyColor.value;
      operand1.style.backgroundColor = emptyColor.value;
      operand2.style.backgroundColor = emptyColor.value;
      operation.style.backgroundColor = emptyColor.value;
      return;
    } else {
        operand1.style.backgroundColor = okColor.value;
        operand2.style.backgroundColor = okColor.value;
        operation.style.backgroundColor = okColor.value;
        }

    // Validar que ambos operandos sean numéricos
    if (!isNumeric(value1) || !isNumeric(value2)) {
      result.value = "Valores no numéricos";
      result.style.backgroundColor = emptyColor.value;
      operand1.style.backgroundColor = emptyColor.value;
      operand2.style.backgroundColor = emptyColor.value;
      operation.style.backgroundColor = emptyColor.value;
      return;
    }else {
        operand1.style.backgroundColor = okColor.value;
        operand2.style.backgroundColor = okColor.value;
        operation.style.backgroundColor = okColor.value;
        }

    //convertimos
    const num1 = parseFloat(value1);
    const num2 = parseFloat(value2);
    let calculatedResult;

    //operacion segun seleccionn
    switch (selectedOperation) {
      case "suma":
        calculatedResult = num1 + num2;
        break;
      case "resta":
        calculatedResult = num1 - num2;
        break;
      case "multiplica":
        calculatedResult = num1 * num2;
        break;
      case "divide":
        //divicion por 0
        if (num2 === 0) {
          result.value = "Error: División por cero";
          result.style.backgroundColor = emptyColor.value;
          return;
        }
        calculatedResult = num1 / num2;
        break;
      default:
        result.value = "Operación no válida";
        result.style.backgroundColor = emptyColor.value;
        return;
    }

    //2 decimales si es necesario
    if (calculatedResult % 1 !== 0) {
      calculatedResult = calculatedResult.toFixed(2);
    }

    //aplicamos color según sea positivo o negativo
    result.value = calculatedResult;
    if (parseFloat(calculatedResult) > 0) {
      result.style.backgroundColor = positiveColor.value;
    } else if (parseFloat(calculatedResult) < 0) {
      result.style.backgroundColor = negativeColor.value;
    }
  }

  //reiniciar el formulario
  function reset() {
    operand1.value = "";
    operand2.value = "";
    operation.selectedIndex = 0;
    result.value = "";
    result.style.backgroundColor = "";
    operand1.style.backgroundColor = "";
    operand2.style.backgroundColor = "";
    operation.style.backgroundColor = "";
  }

  // Event
  calculateBtn.addEventListener("click", calculate);
  resetBtn.addEventListener("click", reset);

  //cálculo presionando Enter
  document
    .getElementById("calculatorForm")
    .addEventListener("keypress", function (e) {
      if (e.key === "Enter") {
        e.preventDefault();
        calculate();
      }
    });
});
