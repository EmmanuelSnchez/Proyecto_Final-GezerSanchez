//================ main.cpp ================//

#include <iostream>
#include <vector>

#include "productos.h"
#include "ventas.h"
#include "reportes.h"
#include "utilidades.h"

using namespace std;

//================ VECTOR MENU ================//

vector<string> opcionesMenu = {

    "1. Gestion de Productos",
    "2. Proceso de Venta",
    "3. Reportes",
    "4. Utilidades",
    "5. Salir"
};

//================ MENU PRINCIPAL ================//

void MenuPrincipal() {

    Encabezado("SISTEMA DE INVENTARIO Y VENTAS");

    for(size_t i = 0; i < opcionesMenu.size(); i++) {

        cout << opcionesMenu[i] << endl;
    }

    cout << "\nSeleccione una opcion: ";
}

//================ MAIN ================//

int main() {

    int opcion;

    do {

        MenuPrincipal();

        cin >> opcion;

        if(cin.fail()) {

            cin.clear();
            cin.ignore(1000, '\n');

            opcion = 0;
        }

        switch(opcion) {

            case 1:

                MenuProductos();
                break;

            case 2:

                CrearVenta();
                break;

            case 3:

                MenuReportes();
                break;

            case 4:

                MenuUtilidades();
                break;

            case 5:

                cout << "\nSistema finalizado.\n";
                break;

            default:

                cout << "\nOpcion invalida.\n";
        }

        if(opcion != 5) {

            PausarSistema();
            LimpiarPantalla();
        }

    } while(opcion != 5);

    return 0;
}