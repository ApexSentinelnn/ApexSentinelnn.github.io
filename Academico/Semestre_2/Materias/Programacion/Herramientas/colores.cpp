#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Programa de selección de colores ANSI usando printf y scanf
// Compilar: gcc -o selector_colores selector_colores.c

// Códigos ANSI para colores y formato
// Resetear todos los estilos
#define RESET "\033[0m"

// Estilos de texto
#define BOLD "\033[1m"          // Negrita
#define DIM "\033[2m"           // Atenuado
#define ITALIC "\033[3m"        // Cursiva
#define UNDERLINE "\033[4m"     // Subrayado
#define BLINK "\033[5m"         // Parpadeo
#define REVERSE "\033[7m"       // Invertir colores
#define HIDDEN "\033[8m"        // Oculto
#define STRIKETHROUGH "\033[9m" // Tachado

// Colores de texto básicos
#define NEGRO "\033[30m"        // Negro
#define ROC "\033[31m"          // Rojo
#define VERD "\033[32m"         // Verde
#define AMAR "\033[33m"         // Amarillo
#define AZUL "\033[34m"         // Azul
#define MAGENTA "\033[35m"      // Magenta
#define CYAN "\033[36m"         // Cyan
#define BLANCO "\033[37m"       // Blanco

// Colores de texto brillantes
#define GRIS "\033[90m"         // Gris (Negro brillante)
#define ROC_BRIGHT "\033[91m"   // Rojo brillante
#define VERD_BRIGHT "\033[92m"  // Verde brillante
#define AMAR_BRIGHT "\033[93m"  // Amarillo brillante
#define AZUL_BRIGHT "\033[94m"  // Azul brillante
#define MAG_BRIGHT "\033[95m"   // Magenta brillante
#define CYAN_BRIGHT "\033[96m"  // Cyan brillante
#define BLANC_BRIGHT "\033[97m" // Blanco brillante

// Colores de fondo
#define BG_NEGRO "\033[40m"     // Fondo negro
#define BG_ROC "\033[41m"       // Fondo rojo
#define BG_VERD "\033[42m"      // Fondo verde
#define BG_AMAR "\033[43m"      // Fondo amarillo
#define BG_AZUL "\033[44m"      // Fondo azul
#define BG_MAGENTA "\033[45m"   // Fondo magenta
#define BG_CYAN "\033[46m"      // Fondo cyan
#define BG_BLANCO "\033[47m"    // Fondo blanco

// Colores de fondo brillantes
#define BG_GRIS "\033[100m"       // Fondo gris
#define BG_ROC_BRIGHT "\033[101m" // Fondo rojo brillante
#define BG_VERD_BRIGHT "\033[102m" // Fondo verde brillante
#define BG_AMAR_BRIGHT "\033[103m" // Fondo amarillo brillante
#define BG_AZUL_BRIGHT "\033[104m" // Fondo azul brillante
#define BG_MAG_BRIGHT "\033[105m"  // Fondo magenta brillante
#define BG_CYAN_BRIGHT "\033[106m" // Fondo cyan brillante
#define BG_BLANC_BRIGHT "\033[107m" // Fondo blanco brillante

// Algunos colores de 256 colores
#define NARANJA "\033[38;5;208m"      // Naranja
#define ROSA "\033[38;5;199m"         // Rosa
#define PURPURA "\033[38;5;93m"       // Púrpura
#define LIMA "\033[38;5;118m"         // Lima
#define TURQUESA "\033[38;5;45m"      // Turquesa
#define DORADO "\033[38;5;220m"       // Dorado
#define LAVANDA "\033[38;5;183m"      // Lavanda
#define MARRON "\033[38;5;130m"       // Marrón
#define MELOCOTON "\033[38;5;203m"    // Melocotón
#define ACERO "\033[38;5;67m"         // Azul acero

// Ejemplos RGB (colores personalizados)
#define SALMON "\033[38;2;255;128;114m" // Salmón
#define AQUA "\033[38;2;0;255;255m"     // Aqua
#define VIOLETA "\033[38;2;138;43;226m" // Violeta
#define ORO "\033[38;2;255;215;0m"     // Oro

void mostrarMenu() {
    printf("%s", RESET);
    printf("\n===== SELECTOR DE COLORES ANSI =====\n");
    printf("Seleccione un color o formato:\n\n");
    
    // Colores básicos
    printf("== COLORES BÁSICOS ==\n");
    printf("1. %sNegro%s (puede no ser visible)\n", NEGRO, RESET);
    printf("2. %sRojo%s\n", ROC, RESET);
    printf("3. %sVerde%s\n", VERD, RESET);
    printf("4. %sAmarillo%s\n", AMAR, RESET);
    printf("5. %sAzul%s\n", AZUL, RESET);
    printf("6. %sMagenta%s\n", MAGENTA, RESET);
    printf("7. %sCyan%s\n", CYAN, RESET);
    printf("8. %sBlanco%s\n", BLANCO, RESET);
    
    // Colores brillantes
    printf("\n== COLORES BRILLANTES ==\n");
    printf("9. %sGris%s\n", GRIS, RESET);
    printf("10. %sRojo brillante%s\n", ROC_BRIGHT, RESET);
    printf("11. %sVerde brillante%s\n", VERD_BRIGHT, RESET);
    printf("12. %sAmarillo brillante%s\n", AMAR_BRIGHT, RESET);
    printf("13. %sAzul brillante%s\n", AZUL_BRIGHT, RESET);
    printf("14. %sMagenta brillante%s\n", MAG_BRIGHT, RESET);
    printf("15. %sCyan brillante%s\n", CYAN_BRIGHT, RESET);
    printf("16. %sBlanco brillante%s\n", BLANC_BRIGHT, RESET);
    
    // Fondos básicos
    printf("\n== FONDOS BÁSICOS ==\n");
    printf("17. %sFondo negro%s\n", BG_NEGRO, RESET);
    printf("18. %sFondo rojo%s\n", BG_ROC, RESET);
    printf("19. %sFondo verde%s\n", BG_VERD, RESET);
    printf("20. %sFondo amarillo%s\n", BG_AMAR, RESET);
    printf("21. %sFondo azul%s\n", BG_AZUL, RESET);
    printf("22. %sFondo magenta%s\n", BG_MAGENTA, RESET);
    printf("23. %sFondo cyan%s\n", BG_CYAN, RESET);
    printf("24. %sFondo blanco%s\n", BG_BLANCO NEGRO, RESET);
    
    // Fondos brillantes
    printf("\n== FONDOS BRILLANTES ==\n");
    printf("25. %sFondo gris%s\n", BG_GRIS, RESET);
    printf("26. %sFondo rojo brillante%s\n", BG_ROC_BRIGHT, RESET);
    printf("27. %sFondo verde brillante%s\n", BG_VERD_BRIGHT, RESET);
    printf("28. %sFondo amarillo brillante%s\n", BG_AMAR_BRIGHT NEGRO, RESET);
    printf("29. %sFondo azul brillante%s\n", BG_AZUL_BRIGHT, RESET);
    printf("30. %sFondo magenta brillante%s\n", BG_MAG_BRIGHT, RESET);
    printf("31. %sFondo cyan brillante%s\n", BG_CYAN_BRIGHT NEGRO, RESET);
    printf("32. %sFondo blanco brillante%s\n", BG_BLANC_BRIGHT NEGRO, RESET);
    
    // Estilos de texto
    printf("\n== ESTILOS DE TEXTO ==\n");
    printf("33. %sNegrita%s\n", BOLD, RESET);
    printf("34. %sAtenuado%s\n", DIM, RESET);
    printf("35. %sCursiva%s (no compatible con todas las terminales)\n", ITALIC, RESET);
    printf("36. %sSubrayado%s\n", UNDERLINE, RESET);
    printf("37. %sParpadeo%s (no compatible con todas las terminales)\n", BLINK, RESET);
    printf("38. %sInvertido%s\n", REVERSE, RESET);
    printf("39. %sTachado%s (no compatible con todas las terminales)\n", STRIKETHROUGH, RESET);
    
    // Colores adicionales (256 colores)
    printf("\n== COLORES ADICIONALES (256 colores) ==\n");
    printf("40. %sNaranja%s\n", NARANJA, RESET);
    printf("41. %sRosa%s\n", ROSA, RESET);
    printf("42. %sPúrpura%s\n", PURPURA, RESET);
    printf("43. %sLima%s\n", LIMA, RESET);
    printf("44. %sTurquesa%s\n", TURQUESA, RESET);
    printf("45. %sDorado%s\n", DORADO, RESET);
    printf("46. %sLavanda%s\n", LAVANDA, RESET);
    printf("47. %sMarrón%s\n", MARRON, RESET);
    printf("48. %sMelocotón%s\n", MELOCOTON, RESET);
    printf("49. %sAzul acero%s\n", ACERO, RESET);
    
    // Colores personalizados (RGB)
    printf("\n== COLORES RGB PERSONALIZADOS ==\n");
    printf("50. %sSalmón%s\n", SALMON, RESET);
    printf("51. %sAqua%s\n", AQUA, RESET);
    printf("52. %sVioleta%s\n", VIOLETA, RESET);
    printf("53. %sOro%s\n", ORO, RESET);
    
    // Combinaciones personalizadas
    printf("\n== COMBINACIONES ==\n");
    printf("54. %sRojo en negrita%s\n", BOLD ROC, RESET);
    printf("55. %sCyan brillante subrayado%s\n", UNDERLINE CYAN_BRIGHT, RESET);
    printf("56. %sAmarillo brillante sobre azul%s\n", BG_AZUL AMAR_BRIGHT, RESET);
    printf("57. %sRojo brillante en negrita sobre negro%s\n", BG_NEGRO ROC_BRIGHT BOLD, RESET);
    printf("58. %sNegro en negrita sobre magenta brillante%s\n", BG_MAG_BRIGHT NEGRO BOLD, RESET);
    
    // Salir
    printf("\n0. Salir\n");
    printf("\nSeleccione una opción: ");
}

void mostrarEjemplo(const char* estilo, const char* nombreEstilo) {
    printf("\n%sHas seleccionado: %s\n", RESET, nombreEstilo);
    printf("Ejemplo: %sEste es un texto de ejemplo con el estilo seleccionado.%s\n", estilo, RESET);
    printf("%sLorem ipsum dolor sit amet, consectetur adipiscing elit.%s\n", estilo, RESET);
    printf("%s¡Hola, mundo! Este es un ejemplo de texto con formato ANSI.%s\n\n", estilo, RESET);
    printf("Presiona Enter para continuar...");
    
    // Limpiar el buffer de entrada
    while (getchar() != '\n');
}

int main() {
    int opcion = -1;
    
    while (opcion != 0) {
        mostrarMenu();
        
        // Leer la opción con scanf
        if (scanf("%d", &opcion) != 1) {
            // Limpiar el buffer si la entrada no es un número
            while (getchar() != '\n');
            printf("Entrada inválida. Por favor, ingrese un número.\n");
            opcion = -1;  // Reiniciar para que el bucle continúe
            continue;
        }
        
        // Limpiar cualquier carácter adicional en el buffer
        while (getchar() != '\n');
        
        // Usando switch-case para mostrar ejemplos de cada color
        switch (opcion) {
            // Salir
            case 0:
                printf("\nSaliendo del programa. ¡Hasta luego!\n");
                break;
                
            // Colores básicos
            case 1:
                mostrarEjemplo(NEGRO, "Negro (puede no ser visible en algunas terminales)");
                break;
            case 2:
                mostrarEjemplo(ROC, "Rojo");
                break;
            case 3:
                mostrarEjemplo(VERD, "Verde");
                break;
            case 4:
                mostrarEjemplo(AMAR, "Amarillo");
                break;
            case 5:
                mostrarEjemplo(AZUL, "Azul");
                break;
            case 6:
                mostrarEjemplo(MAGENTA, "Magenta");
                break;
            case 7:
                mostrarEjemplo(CYAN, "Cyan");
                break;
            case 8:
                mostrarEjemplo(BLANCO, "Blanco");
                break;
                
            // Colores brillantes
            case 9:
                mostrarEjemplo(GRIS, "Gris");
                break;
            case 10:
                mostrarEjemplo(ROC_BRIGHT, "Rojo brillante");
                break;
            case 11:
                mostrarEjemplo(VERD_BRIGHT, "Verde brillante");
                break;
            case 12:
                mostrarEjemplo(AMAR_BRIGHT, "Amarillo brillante");
                break;
            case 13:
                mostrarEjemplo(AZUL_BRIGHT, "Azul brillante");
                break;
            case 14:
                mostrarEjemplo(MAG_BRIGHT, "Magenta brillante");
                break;
            case 15:
                mostrarEjemplo(CYAN_BRIGHT, "Cyan brillante");
                break;
            case 16:
                mostrarEjemplo(BLANC_BRIGHT, "Blanco brillante");
                break;
                
            // Fondos básicos
            case 17:
                mostrarEjemplo(BG_NEGRO, "Fondo negro");
                break;
            case 18:
                mostrarEjemplo(BG_ROC, "Fondo rojo");
                break;
            case 19:
                mostrarEjemplo(BG_VERD, "Fondo verde");
                break;
            case 20:
                mostrarEjemplo(BG_AMAR, "Fondo amarillo");
                break;
            case 21:
                mostrarEjemplo(BG_AZUL, "Fondo azul");
                break;
            case 22:
                mostrarEjemplo(BG_MAGENTA, "Fondo magenta");
                break;
            case 23:
                mostrarEjemplo(BG_CYAN, "Fondo cyan");
                break;
            case 24:
                mostrarEjemplo(BG_BLANCO NEGRO, "Fondo blanco (texto negro)");
                break;
                
            // Fondos brillantes
            case 25:
                mostrarEjemplo(BG_GRIS, "Fondo gris");
                break;
            case 26:
                mostrarEjemplo(BG_ROC_BRIGHT, "Fondo rojo brillante");
                break;
            case 27:
                mostrarEjemplo(BG_VERD_BRIGHT, "Fondo verde brillante");
                break;
            case 28:
                mostrarEjemplo(BG_AMAR_BRIGHT NEGRO, "Fondo amarillo brillante (texto negro)");
                break;
            case 29:
                mostrarEjemplo(BG_AZUL_BRIGHT, "Fondo azul brillante");
                break;
            case 30:
                mostrarEjemplo(BG_MAG_BRIGHT, "Fondo magenta brillante");
                break;
            case 31:
                mostrarEjemplo(BG_CYAN_BRIGHT NEGRO, "Fondo cyan brillante (texto negro)");
                break;
            case 32:
                mostrarEjemplo(BG_BLANC_BRIGHT NEGRO, "Fondo blanco brillante (texto negro)");
                break;
                
            // Estilos de texto
            case 33:
                mostrarEjemplo(BOLD, "Negrita");
                break;
            case 34:
                mostrarEjemplo(DIM, "Atenuado");
                break;
            case 35:
                mostrarEjemplo(ITALIC, "Cursiva");
                break;
            case 36:
                mostrarEjemplo(UNDERLINE, "Subrayado");
                break;
            case 37:
                mostrarEjemplo(BLINK, "Parpadeo");
                break;
            case 38:
                mostrarEjemplo(REVERSE, "Invertido");
                break;
            case 39:
                mostrarEjemplo(STRIKETHROUGH, "Tachado");
                break;
                
            // Colores adicionales (256 colores)
            case 40:
                mostrarEjemplo(NARANJA, "Naranja");
                break;
            case 41:
                mostrarEjemplo(ROSA, "Rosa");
                break;
            case 42:
                mostrarEjemplo(PURPURA, "Púrpura");
                break;
            case 43:
                mostrarEjemplo(LIMA, "Lima");
                break;
            case 44:
                mostrarEjemplo(TURQUESA, "Turquesa");
                break;
            case 45:
                mostrarEjemplo(DORADO, "Dorado");
                break;
            case 46:
                mostrarEjemplo(LAVANDA, "Lavanda");
                break;
            case 47:
                mostrarEjemplo(MARRON, "Marrón");
                break;
            case 48:
                mostrarEjemplo(MELOCOTON, "Melocotón");
                break;
            case 49:
                mostrarEjemplo(ACERO, "Azul acero");
                break;
                
            // Colores personalizados (RGB)
            case 50:
                mostrarEjemplo(SALMON, "Salmón");
                break;
            case 51:
                mostrarEjemplo(AQUA, "Aqua");
                break;
            case 52:
                mostrarEjemplo(VIOLETA, "Violeta");
                break;
            case 53:
                mostrarEjemplo(ORO, "Oro");
                break;
                
            // Combinaciones personalizadas
            case 54:
                mostrarEjemplo(BOLD ROC, "Rojo en negrita");
                break;
            case 55:
                mostrarEjemplo(UNDERLINE CYAN_BRIGHT, "Cyan brillante subrayado");
                break;
            case 56:
                mostrarEjemplo(BG_AZUL AMAR_BRIGHT, "Amarillo brillante sobre azul");
                break;
            case 57:
                mostrarEjemplo(BG_NEGRO ROC_BRIGHT BOLD, "Rojo brillante en negrita sobre negro");
                break;
            case 58:
                mostrarEjemplo(BG_MAG_BRIGHT NEGRO BOLD, "Negro en negrita sobre magenta brillante");
                break;
                
            default:
                printf("\nOpción no válida. Por favor, seleccione una opción del menú.\n");
                printf("Presiona Enter para continuar...");
                while (getchar() != '\n');
                break;
        }
    }
    
    return 0;
}