//Proyecto Final Gestor de Inventario y Ventas//


#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//Esstructuras (pueden cambiar)

struct Producto {
    int codigo;
    char nombre[40];
    float precio;
    int stock;
    bool activo;
};

struct Venta {
    int numeroVenta;
    int codigoProducto;
    int cantidad;
    float subtotal;
    float iva;
    float descuento;
    float total;
};

//Archivos a utilizar 

const char* archivoProductos = "productos.dat";
const char* archivoVentas = "ventas.dat";

//Prototipos (Quitar para version final :) )

void MostrarMenu();
void AgregarProducto();
void MostrarInventario();
void RealizarVenta();
bool BuscarCodigo(int codigo);


int main() {

    int opcion;

    do {

        MostrarMenu();
        cin >> opcion;

        switch(opcion) {

            case 1:
                AgregarProducto();
                break;

            case 2:
                MostrarInventario();
                break;

            case 3:
                RealizarVenta();
                break;

            case 4:
                cout << "\nSistema finalizado.\n";
                break;

            default:
                cout << "\nOpcion incorrecta.\n";
        }

    } while(opcion != 4);

    return 0;
}

//Procedimientos y funciones//
//Agregar 5 ++, nombrar cada una por si no entender yo jajaj//
//Crear uno de encabezado para acciones a realizar//

void MostrarMenu() {

    cout << "\n======= TIENDA VIRTUAL =======\n";
    cout << "1. Registrar producto\n";
    cout << "2. Ver inventario\n";
    cout << "3. Crear venta\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opcion: ";
}



bool BuscarCodigo(int codigo) {

    Producto p;

    ifstream lectura(archivoProductos, ios::binary);

    while(lectura.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo) {
            lectura.close();
            return true;
        }
    }

    lectura.close();

    return false;
}



void AgregarProducto() {

    Producto p;

    cout << "\n====== NUEVO PRODUCTO ======\n";

    cout << "Codigo: ";
    cin >> p.codigo;

    if(BuscarCodigo(p.codigo)) {
        cout << "El codigo ya esta registrado.\n";
        return;
    }

    cin.ignore();

    cout << "Nombre: ";
    cin.getline(p.nombre, 40);

    cout << "Precio: ";
    cin >> p.precio;

    cout << "Cantidad en stock: ";
    cin >> p.stock;

    p.activo = true;

    ofstream escritura(archivoProductos, ios::binary | ios::app);

    escritura.write((char*)&p, sizeof(Producto));

    escritura.close();

    cout << "Producto almacenado correctamente.\n";
}



void MostrarInventario() {

    Producto p;

    ifstream lectura(archivoProductos, ios::binary);

    cout << "\n=========== INVENTARIO ===========\n";

    while(lectura.read((char*)&p, sizeof(Producto))) {

        if(p.activo) {

            cout << "\nCodigo: " << p.codigo << endl;
            cout << "Producto: " << p.nombre << endl;
            cout << "Precio: Q" << fixed << setprecision(2) << p.precio << endl;
            cout << "Stock: " << p.stock << endl;
        }
    }

    lectura.close();
}


void RealizarVenta() {

    Producto p;
    Venta v;

    int codigoBuscar;
    bool encontrado = false;

    cout << "\n======= NUEVA VENTA =======\n";

    cout << "Numero de venta: ";
    cin >> v.numeroVenta;

    cout << "Codigo del producto: ";
    cin >> codigoBuscar;

    fstream archivo(archivoProductos, ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigoBuscar && p.activo) {

            encontrado = true;

            cout << "\nProducto encontrado\n";
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock disponible: " << p.stock << endl;

            cout << "Cantidad a comprar: ";
            cin >> v.cantidad;

            if(v.cantidad > p.stock) {

                cout << "Stock insuficiente.\n";
                break;
            }

            v.codigoProducto = p.codigo;

            v.subtotal = v.cantidad * p.precio;

            v.iva = v.subtotal * 0.12;

            v.descuento = 0;

            if(v.subtotal > 500) {
                v.descuento = v.subtotal * 0.05;
            }

            v.total = (v.subtotal + v.iva) - v.descuento;

            cout << "\n========== FACTURA ==========\n";
            cout << "Subtotal: Q" << v.subtotal << endl;
            cout << "IVA: Q" << v.iva << endl;
            cout << "Descuento: Q" << v.descuento << endl;
            cout << "TOTAL: Q" << v.total << endl;

            p.stock -= v.cantidad;

            int posicion = archivo.tellg() - sizeof(Producto);

            archivo.seekp(posicion);

            archivo.write((char*)&p, sizeof(Producto));

            ofstream ventas(archivoVentas, ios::binary | ios::app);

            ventas.write((char*)&v, sizeof(Venta));

            ventas.close();

            cout << "\nVenta registrada exitosamente.\n";

            break;
        }
    }

    archivo.close();

    if(!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}