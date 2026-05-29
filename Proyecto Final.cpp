//Proyecto Final Gestor de Inventario y Ventas//

#include <iostream>
#include <vector>

#include "productos.h"
#include "ventas.h"
#include "reportes.h"
#include "utilidades.h"

using namespace std;

//================ VECTOR MENU ================//

vector<string> opcionesMenu = {

    "1. Modulo Productos",
    "2. Modulo Ventas",
    "3. Reportes",
    "4. Salir"
};

//================ MENU PRINCIPAL ================//

void MenuPrincipal() {

    Encabezado("SISTEMA DE INVENTARIO");

    for(int i = 0; i < opcionesMenu.size(); i++) {

        cout << opcionesMenu[i] << endl;
    }

    cout << "Seleccione una opcion: ";
}

//================ MAIN ================//

int main() {

    int opcion;

    do {

        MenuPrincipal();
        cin >> opcion;

        switch(opcion) {

            case 1:
                MenuProductos();
                break;

            case 2:
                CrearVenta();
                break;

            case 3:

                ReporteStockBajo();
                ProductosMasVendidos();
                VentasTotales();

                break;

            case 4:

                cout << "\nSistema finalizado.\n";
                break;

            default:

                cout << "\nOpcion invalida.\n";
        }

    } while(opcion != 4);

    return 0;
}