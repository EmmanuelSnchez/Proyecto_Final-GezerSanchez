//================ utilidades.cpp ================//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

#include "utilidades.h"
#include "productos.h"

using namespace std;

//================ ENCABEZADO =================//

void Encabezado(string titulo) {

    cout << "\n========================================\n";
    cout << "      " << titulo << endl;
    cout << "========================================\n";
}

//================ FORMATO DECIMAL =================//

void FormatoDecimal() {

    cout << fixed << setprecision(2);
}

//================ PAUSAR SISTEMA =================//

void PausarSistema() {

    cin.ignore(1000, '\n');

    cout << "\nPresione ENTER para continuar...";
    cin.get();
}

//================ LIMPIAR PANTALLA =================//

void LimpiarPantalla() {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//================ REINICIAR INVENTARIO =================//

void ReiniciarInventario() {

    char respuesta;

    cout << "\nADVERTENCIA\n";
    cout << "Esta accion eliminara todos los productos.\n";
    cout << "Desea continuar? (S/N): ";
    cin >> respuesta;

    respuesta = toupper(respuesta);

    if(respuesta == 'S') {

        ofstream archivo(
            "productos.dat",
            ios::binary | ios::trunc
        );

        archivo.close();

        cout << "\nInventario reiniciado correctamente.\n";
    }
    else {

        cout << "\nOperacion cancelada.\n";
    }
}

//================ MENU UTILIDADES =================//

void MenuUtilidades() {

    int opcion;

    do {

        Encabezado("UTILIDADES DEL SISTEMA");

        cout << "1. Reiniciar inventario\n";
        cout << "2. Regresar\n";

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        if(cin.fail()) {

            cin.clear();
            cin.ignore(1000, '\n');

            opcion = 0;
        }

        switch(opcion) {

            case 1:

                ReiniciarInventario();
                break;

            case 2:

                break;

            default:

                cout << "\nOpcion invalida.\n";
        }

        if(opcion != 2) {

            PausarSistema();
            LimpiarPantalla();
        }

    } while(opcion != 2);
}
