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

//================ ARCHIVOS ================//

const char* archivoProductosVentas =
"productos.dat";

const char* archivoVentas =
"ventas.dat";

//================ CREAR VENTA ================//

void CrearVenta() {

    try {

        Venta venta;

        vector<DetalleVenta> detalles;

        int cantidadProductos;

        Encabezado("NUEVA VENTA");

        cout << "Numero de venta: ";
        cin >> venta.numeroVenta;

        if(cin.fail()) {
            throw 1;
        }

        //================ FECHA =================//

        cout << "Dia: ";
        cin >> venta.dia;

        if(cin.fail() ||
           venta.dia < 1 ||
           venta.dia > 31) {

            throw 2;
        }

        cout << "Mes: ";
        cin >> venta.mes;

        if(cin.fail() ||
           venta.mes < 1 ||
           venta.mes > 12) {

            throw 3;
        }

        cout << "Anio: ";
        cin >> venta.anio;

        if(cin.fail() ||
           venta.anio < 2020) {

            throw 4;
        }

        cout << "Cantidad de productos: ";
        cin >> cantidadProductos;

        if(cin.fail() ||
           cantidadProductos <= 0) {

            throw 5;
        }

        venta.subtotalGeneral = 0;
        venta.totalArticulos = 0;

        //================ RECORRER PRODUCTOS =================//

        for(int i = 0;
            i < cantidadProductos;
            i++) {

            Producto p;

            DetalleVenta detalle;

            bool encontrado = false;

            int codigo;

            cout
            << "\nCodigo producto #"
            << i + 1
            << ": ";

            cin >> codigo;

            if(cin.fail()) {
                throw 6;
            }

            fstream archivo(
                archivoProductosVentas,
                ios::binary |
                ios::in |
                ios::out
            );

            if(!archivo) {

                cout
                << "Error al abrir productos.dat\n";

                return;
            }
                     while(
                archivo.read(
                (char*)&p,
                sizeof(Producto))
            ) {

                if(
                    p.codigo == codigo &&
                    p.activo
                ) {

                    encontrado = true;

                    detalle.codigoProducto =
                    p.codigo;

                    strcpy(
                        detalle.nombreProducto,
                        p.nombre
                    );

                    detalle.precioUnitario =
                    p.precio;

                    cout << "Cantidad: ";
                    cin >> detalle.cantidad;

                    if(
                        cin.fail() ||
                        detalle.cantidad <= 0
                    ) {

                        archivo.close();
                        throw 7;
                    }

                    //================ VALIDAR STOCK =================//

                    if(
                        detalle.cantidad >
                        p.stock
                    ) {

                        cout
                        << "\nStock insuficiente.\n";

                        archivo.close();
                        return;
                    }

                    //================ CALCULAR SUBTOTAL =================//

                    detalle.subtotal =
                    detalle.cantidad *
                    detalle.precioUnitario;

                    //================ GUARDAR EN VECTOR =================//

                    detalles.push_back(
                    detalle);

                    venta.subtotalGeneral +=
                    detalle.subtotal;

                    venta.totalArticulos +=
                    detalle.cantidad;

                    //================ ACTUALIZAR INVENTARIO =================//

                    p.stock -=
                    detalle.cantidad;

                    p.vendidos +=
                    detalle.cantidad;

                    streampos posicion =
                    archivo.tellg();

                    archivo.seekp(
                        posicion -
                        static_cast<streamoff>(
                        sizeof(Producto))
                    );

                    archivo.write(
                        (char*)&p,
                        sizeof(Producto)
                    );

                    break;
                }
            }

            archivo.close();

            if(!encontrado) {

                cout
                << "\nProducto no encontrado.\n";

                return;
            }

        } // FIN DEL FOR DE PRODUCTOS

                //================ IVA =================//

        venta.iva =
        venta.subtotalGeneral * 0.12f;

        //================ DESCUENTOS =================//

        venta.descuento = 0;

        // Descuento 5%
        // si subtotal > Q500

        if(
            venta.subtotalGeneral >
            500
        ) {

            venta.descuento +=
            venta.subtotalGeneral *
            0.05f;
        }

        // Bono adicional

        if(
            venta.totalArticulos % 5
            == 0
        ) {

            venta.descuento += 25;
        }

        //================ TOTAL FINAL =================//

        venta.totalFinal =

        (
            venta.subtotalGeneral +
            venta.iva
        )
        -
        venta.descuento;

        //================ FACTURA =================//

        Encabezado("FACTURA");

        FormatoDecimal();

        cout
        << "\nNo. Venta: "
        << venta.numeroVenta
        << endl;

        cout
        << "Fecha: "
        << venta.dia
        << "/"
        << venta.mes
        << "/"
        << venta.anio
        << endl;

        cout
        << "\nPRODUCTOS\n";

        cout
        << "---------------------------------\n";

        for(
            size_t i = 0;
            i < detalles.size();
            i++
        ) {

            cout
            << detalles[i].nombreProducto
            << " x"
            << detalles[i].cantidad
            << " = Q"
            << detalles[i].subtotal
            << endl;
        }

        cout
        << "---------------------------------\n";

        cout
        << "Subtotal: Q"
        << venta.subtotalGeneral
        << endl;

        cout
        << "IVA (12%): Q"
        << venta.iva
        << endl;

        cout
        << "Descuento: Q"
        << venta.descuento
        << endl;

        cout
        << "TOTAL: Q"
        << venta.totalFinal
        << endl;

                //================ GUARDAR VENTA =================//

        ofstream guardar(
            archivoVentas,
            ios::binary | ios::app
        );

        if(!guardar) {

            cout
            << "\nError al abrir ventas.dat\n";

            return;
        }

        guardar.write(
            (char*)&venta,
            sizeof(Venta)
        );

        guardar.close();

        cout
        << "\nVenta almacenada correctamente.\n";
    }

    //================ MANEJO DE EXCEPCIONES =================//

    catch(int error) {

        cin.clear();
        cin.ignore(1000,'\n');

        cout
        << "\nError en los datos ingresados.\n";

        switch(error) {

            case 1:
                cout
                << "Numero de venta invalido.\n";
                break;

            case 2:
                cout
                << "Dia invalido.\n";
                break;

            case 3:
                cout
                << "Mes invalido.\n";
                break;

            case 4:
                cout
                << "Anio invalido.\n";
                break;

            case 5:
                cout
                << "Cantidad de productos invalida.\n";
                break;

            case 6:
                cout
                << "Codigo de producto invalido.\n";
                break;

            case 7:
                cout
                << "Cantidad invalida.\n";
                break;

            default:
                cout
                << "Error desconocido.\n";
        }
    }
}