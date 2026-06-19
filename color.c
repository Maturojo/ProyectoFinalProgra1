#include "color.h"

void color(int x){
    /*
    0 - Negro
    1 - Azul
    2 - Verde
    3 - Celeste
    4 - Rojo
    5 - Violeta
    6 - Naranja
    7 - Gris Claro (default)
    8 - Gris Oscuro
    9 - Azul claro
    10- Verde claro
    11- Celeste brillante
    12- Salmon
    13- Violeta Chillon
    14- Amarillo Claro
    15- Blanco
    */
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}
