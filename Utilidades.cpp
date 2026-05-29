//================ utilidades.cpp ================//

#include <iostream>
#include <iomanip>

#include "utilidades.h"

using namespace std;

//================ ENCABEZADO ================//

void Encabezado(string titulo) {

    cout << "\n====================================\n";
    cout << "        " << titulo << endl;
    cout << "====================================\n";
}

//================ FORMATO DECIMALES ================//

void FormatoDecimal() {

    cout << fixed << setprecision(2);
}