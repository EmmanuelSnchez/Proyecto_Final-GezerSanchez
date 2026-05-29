//================ reportes.cpp ================//

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "productos.h"
#include "ventas.h"
#include "reportes.h"

using namespace std;

const char* archivoProductos = "productos.dat";
const char* archivoVentas = "ventas.dat";

//================ STOCK BAJO ================//

void ReporteStockBajo() {

    vector<Producto> productos = CargarProductos();

    cout << "\n====== STOCK BAJO ======\n";

    for(int i = 0; i < productos.size(); i++) {

        if(productos[i].stock <= 5) {

            cout << productos[i].nombre
                 << " | Stock: "
                 << productos[i].stock << endl;
        }
    }
}

//================ MAS VENDIDOS ================//

void ProductosMasVendidos() {

    vector<Producto> productos = CargarProductos();

    for(int i = 0; i < productos.size() - 1; i++) {

        for(int j = 0;
            j < productos.size() - 1 - i;
            j++) {

            if(productos[j].vendidos <
               productos[j + 1].vendidos) {

                Producto aux = productos[j];

                productos[j] = productos[j + 1];

                productos[j + 1] = aux;
            }
        }
    }

    cout << "\n====== PRODUCTOS MAS VENDIDOS ======\n";

    for(int i = 0; i < productos.size(); i++) {

        cout << productos[i].nombre
             << " | Vendidos: "
             << productos[i].vendidos << endl;
    }
}

//================ VENTAS TOTALES ================//

void VentasTotales() {

    Venta v;

    float totalVentas = 0;

    int cantidadVentas = 0;

    ifstream lectura(archivoVentas, ios::binary);

    while(lectura.read((char*)&v, sizeof(Venta))) {

        totalVentas += v.totalFinal;

        cantidadVentas++;
    }

    lectura.close();

    cout << "\n====== REPORTE VENTAS ======\n";

    cout << "Cantidad ventas: "
         << cantidadVentas << endl;

    cout << "Total vendido: Q"
         << fixed << setprecision(2)
         << totalVentas << endl;
}