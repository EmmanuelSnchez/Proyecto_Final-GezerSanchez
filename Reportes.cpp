//================ reportes.cpp ================//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "reportes.h"
#include "productos.h"
#include "ventas.h"
#include "utilidades.h"

using namespace std;

//================ ARCHIVOS ================//

const char* archivoVentasReporte =
"ventas.dat";

//================ MATRIZ =================//

float ventasPorMes[12][31] = {0};

//================ MENU REPORTES =================//

void MenuReportes() {

    int opcion;

    do {

        Encabezado("MODULO REPORTES");

        cout << "1. Productos con stock bajo\n";
        cout << "2. Productos mas vendidos\n";
        cout << "3. Ventas totales\n";
        cout << "4. Ventas del dia\n";
        cout << "5. Ventas por mes\n";
        cout << "6. Estadisticas generales\n";
        cout << "7. Exportar reporte TXT\n";
        cout << "8. Regresar\n";

        cout << "\nSeleccione opcion: ";
        cin >> opcion;

        if(cin.fail()) {

            cin.clear();
            cin.ignore(1000,'\n');

            opcion = 0;
        }

        switch(opcion) {

            case 1:
                ReporteStockBajo();
                break;

            case 2:
                ProductosMasVendidos();
                break;

            case 3:
                VentasTotales();
                break;

            case 4:
                VentasDelDia();
                break;

            case 5:
                VentasPorMes();
                break;

            case 6:
                EstadisticasGenerales();
                break;

            case 7:
                ExportarReporteTXT();
                break;

            case 8:
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }

        if(opcion != 8) {

            PausarSistema();
            LimpiarPantalla();
        }

    } while(opcion != 8);
}
//================ STOCK BAJO =================//

void ReporteStockBajo() {

    vector<Producto> productos =
    CargarProductos();

    if(productos.empty()) {

        cout << "\nNo existen productos registrados.\n";
        return;
    }

    Encabezado("PRODUCTOS CON STOCK BAJO");

    bool encontrado = false;

    for(size_t i = 0;
        i < productos.size();
        i++) {

        if(productos[i].stock <= 5) {

            encontrado = true;

            cout
            << productos[i].codigo
            << " | "
            << productos[i].nombre
            << " | Stock: "
            << productos[i].stock
            << endl;
        }
    }

    if(!encontrado) {

        cout
        << "\nNo existen productos con stock bajo.\n";
    }
}

//================ PRODUCTOS MAS VENDIDOS =================//

void ProductosMasVendidos() {

    vector<Producto> productos =
    CargarProductos();

    if(productos.empty()) {

        cout << "\nNo existen productos registrados.\n";
        return;
    }

    // Bubble Sort Descendente

    for(size_t i = 0;
        i < productos.size() - 1;
        i++) {

        for(size_t j = 0;
            j < productos.size() - 1 - i;
            j++) {

            if(
                productos[j].vendidos <
                productos[j + 1].vendidos
            ) {

                Producto aux =
                productos[j];

                productos[j] =
                productos[j + 1];

                productos[j + 1] =
                aux;
            }
        }
    }

    Encabezado("PRODUCTOS MAS VENDIDOS");

    for(size_t i = 0;
        i < productos.size();
        i++) {

        cout
        << productos[i].codigo
        << " | "
        << productos[i].nombre
        << " | Vendidos: "
        << productos[i].vendidos
        << endl;
    }
}
//================ VENTAS TOTALES =================//

void VentasTotales() {

    Venta v;

    float totalVentas = 0;

    int cantidadVentas = 0;

    ifstream archivo(
        archivoVentasReporte,
        ios::binary
    );

    if(!archivo) {

        cout << "\nNo existen ventas registradas.\n";
        return;
    }

    while(
        archivo.read(
        (char*)&v,
        sizeof(Venta))
    ) {

        totalVentas +=
        v.totalFinal;

        cantidadVentas++;
    }

    archivo.close();

    Encabezado("VENTAS TOTALES");

    FormatoDecimal();

    cout
    << "Cantidad de ventas: "
    << cantidadVentas
    << endl;

    cout
    << "Total vendido: Q"
    << totalVentas
    << endl;
}

//================ VENTAS DEL DIA =================//

void VentasDelDia() {

    int diaBuscar;
    int mesBuscar;
    int anioBuscar;

    cout << "\nDia: ";
    cin >> diaBuscar;

    cout << "Mes: ";
    cin >> mesBuscar;

    cout << "Anio: ";
    cin >> anioBuscar;

    Venta v;

    float totalDia = 0;

    int ventasDia = 0;

    ifstream archivo(
        archivoVentasReporte,
        ios::binary
    );

    if(!archivo) {

        cout << "\nNo existen ventas registradas.\n";
        return;
    }

    while(
        archivo.read(
        (char*)&v,
        sizeof(Venta))
    ) {

        if(
            v.dia == diaBuscar &&
            v.mes == mesBuscar &&
            v.anio == anioBuscar
        ) {

            totalDia +=
            v.totalFinal;

            ventasDia++;
        }
    }

    archivo.close();

    Encabezado("VENTAS DEL DIA");

    FormatoDecimal();

    cout
    << "Cantidad de ventas: "
    << ventasDia
    << endl;

    cout
    << "Total vendido: Q"
    << totalDia
    << endl;
}
//================ VENTAS POR MES =================//

void VentasPorMes() {

    Venta v;

    // Reiniciar matriz

    for(int i = 0; i < 12; i++) {

        for(int j = 0; j < 31; j++) {

            ventasPorMes[i][j] = 0;
        }
    }

    ifstream archivo(
        archivoVentasReporte,
        ios::binary
    );

    if(!archivo) {

        cout << "\nNo existen ventas registradas.\n";
        return;
    }

    while(
        archivo.read(
        (char*)&v,
        sizeof(Venta))
    ) {

        if(
            v.mes >= 1 &&
            v.mes <= 12 &&
            v.dia >= 1 &&
            v.dia <= 31
        ) {

            ventasPorMes
            [v.mes - 1]
            [v.dia - 1]

            +=

            v.totalFinal;
        }
    }

    archivo.close();

    Encabezado("VENTAS POR MES");

    FormatoDecimal();

    for(int mes = 0;
        mes < 12;
        mes++) {

        float totalMes = 0;

        for(int dia = 0;
            dia < 31;
            dia++) {

            totalMes +=
            ventasPorMes[mes][dia];
        }

        cout
        << "Mes "
        << mes + 1
        << ": Q"
        << totalMes
        << endl;
    }
}

//================ ESTADISTICAS GENERALES =================//

void EstadisticasGenerales() {

    vector<Producto> productos =
    CargarProductos();

    Venta v;

    int totalProductos =

    productos.size();

    int stockTotal = 0;

    float totalVentas = 0;

    int cantidadVentas = 0;

    //================ PRODUCTOS =================//

    for(size_t i = 0;
        i < productos.size();
        i++) {

        stockTotal +=
        productos[i].stock;
    }

    //================ VENTAS =================//

    ifstream archivo(
        archivoVentasReporte,
        ios::binary
    );

    while(
        archivo.read(
        (char*)&v,
        sizeof(Venta))
    ) {

        totalVentas +=
        v.totalFinal;

        cantidadVentas++;
    }

    archivo.close();

    //================ MOSTRAR =================//

    Encabezado(
    "ESTADISTICAS GENERALES"
    );

    FormatoDecimal();

    cout
    << "Productos registrados: "
    << totalProductos
    << endl;

    cout
    << "Stock total: "
    << stockTotal
    << endl;

    cout
    << "Cantidad ventas: "
    << cantidadVentas
    << endl;

    cout
    << "Total vendido: Q"
    << totalVentas
    << endl;
}
//================ EXPORTAR REPORTE TXT =================//

void ExportarReporteTXT() {

    vector<Producto> productos =
    CargarProductos();

    Venta v;

    int cantidadVentas = 0;

    float totalVentas = 0;

    ofstream reporte(
        "reporte_general.txt"
    );

    if(!reporte) {

        cout
        << "\nNo fue posible crear el reporte.\n";

        return;
    }

    //================ PRODUCTOS =================//

    reporte
    << "========================================\n";

    reporte
    << "   REPORTE GENERAL DEL SISTEMA\n";

    reporte
    << "========================================\n\n";

    reporte
    << "PRODUCTOS REGISTRADOS\n\n";

    reporte
    << left
    << setw(10)
    << "Codigo"

    << setw(25)
    << "Nombre"

    << setw(12)
    << "Precio"

    << setw(10)
    << "Stock"

    << setw(10)
    << "Vendidos"

    << endl;

    reporte
    << "------------------------------------------------------------\n";

    for(size_t i = 0;
        i < productos.size();
        i++) {

        reporte
        << left

        << setw(10)
        << productos[i].codigo

        << setw(25)
        << productos[i].nombre

        << setw(12)
        << fixed
        << setprecision(2)
        << productos[i].precio

        << setw(10)
        << productos[i].stock

        << setw(10)
        << productos[i].vendidos

        << endl;
    }

    //================ VENTAS =================//

    ifstream archivo(
        archivoVentasReporte,
        ios::binary
    );

    while(
        archivo.read(
        (char*)&v,
        sizeof(Venta))
    ) {

        totalVentas +=
        v.totalFinal;

        cantidadVentas++;
    }

    archivo.close();

    reporte
    << "\n\n========================================\n";

    reporte
    << "RESUMEN DE VENTAS\n";

    reporte
    << "========================================\n\n";

    reporte
    << "Cantidad de ventas: "
    << cantidadVentas
    << endl;

    reporte
    << "Total vendido: Q"
    << fixed
    << setprecision(2)
    << totalVentas
    << endl;

    reporte.close();

    cout
    << "\nReporte exportado correctamente.\n";

    cout
    << "Archivo generado: reporte_general.txt\n";
}