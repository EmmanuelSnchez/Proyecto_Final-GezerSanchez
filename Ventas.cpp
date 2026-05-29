//================ ventas.cpp ================//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstring>

#include "ventas.h"
#include "productos.h"
#include "utilidades.h"

using namespace std;

const char* archivoProductos = "productos.dat";
const char* archivoVentas = "ventas.dat";

//================ CREAR VENTA ================//

void CrearVenta() {

    Venta venta;

    vector<DetalleVenta> detalles;

    int cantidadProductos;

    Encabezado("NUEVA VENTA");

    cout << "Numero de venta: ";
    cin >> venta.numeroVenta;

    cout << "Cantidad de productos: ";
    cin >> cantidadProductos;

    venta.subtotalGeneral = 0;
    venta.totalArticulos = 0;

    for(int i = 0; i < cantidadProductos; i++) {

        Producto p;

        DetalleVenta detalle;

        int codigo;

        bool encontrado = false;

        cout << "\nCodigo producto #" << i + 1 << ": ";
        cin >> codigo;

        fstream archivo(archivoProductos,
        ios::binary | ios::in | ios::out);

        while(archivo.read((char*)&p, sizeof(Producto))) {

            if(p.codigo == codigo && p.activo) {

                encontrado = true;

                detalle.codigoProducto = p.codigo;

                strcpy(detalle.nombreProducto,
                p.nombre);

                cout << "Cantidad: ";
                cin >> detalle.cantidad;

                if(detalle.cantidad > p.stock) {

                    cout << "Stock insuficiente.\n";

                    archivo.close();
                    return;
                }

                detalle.precioUnitario = p.precio;

                detalle.subtotal =
                detalle.cantidad *
                detalle.precioUnitario;

                //Guardar detalle en vector//
                detalles.push_back(detalle);

                venta.subtotalGeneral +=
                detalle.subtotal;

                venta.totalArticulos +=
                detalle.cantidad;

                //Actualizar stock//
                p.stock -= detalle.cantidad;

                p.vendidos += detalle.cantidad;

                int posicion =
                archivo.tellg() - sizeof(Producto);

                archivo.seekp(posicion);

                archivo.write((char*)&p,
                sizeof(Producto));

                break;
            }
        }

        archivo.close();

        if(!encontrado) {

            cout << "Producto no encontrado.\n";
            return;
        }
    }

    //================ IVA ================//

    venta.iva = venta.subtotalGeneral * 0.12;

    //================ DESCUENTOS ================//

    venta.descuento = 0;

    if(venta.subtotalGeneral > 500) {

        venta.descuento +=
        venta.subtotalGeneral * 0.05;
    }

    if(venta.totalArticulos % 5 == 0) {

        venta.descuento += 25;
    }

    //================ TOTAL ================//

    venta.totalFinal =
    (venta.subtotalGeneral + venta.iva)
    - venta.descuento;

    //================ FACTURA ================//

    Encabezado("FACTURA");

    for(int i = 0; i < detalles.size(); i++) {

        cout << detalles[i].nombreProducto
             << " x" << detalles[i].cantidad
             << " = Q"
             << detalles[i].subtotal << endl;
    }

    FormatoDecimal();

    cout << "\nSubtotal: Q"
         << venta.subtotalGeneral << endl;

    cout << "IVA: Q"
         << venta.iva << endl;

    cout << "Descuento: Q"
         << venta.descuento << endl;

    cout << "TOTAL: Q"
         << venta.totalFinal << endl;

    //================ GUARDAR VENTA ================//

    ofstream guardar(archivoVentas,
    ios::binary | ios::app);

    guardar.write((char*)&venta,
    sizeof(Venta));

    guardar.close();

    cout << "\nVenta almacenada correctamente.\n";
}