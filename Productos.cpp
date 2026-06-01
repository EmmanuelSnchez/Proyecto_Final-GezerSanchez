//================ productos.cpp ================//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstring>

#include "productos.h"
#include "utilidades.h"

using namespace std;

const char* archivoProductos = "productos.dat";

//================ CARGAR PRODUCTOS ================//

vector<Producto> CargarProductos() {

    vector<Producto> productos;

    Producto p;

    ifstream archivo(
        archivoProductos,
        ios::binary
    );

    if(!archivo) {

        return productos;
    }

    while(
        archivo.read(
        (char*)&p,
        sizeof(Producto))
    ) {

        if(p.activo) {

            productos.push_back(p);
        }
    }

    archivo.close();

    return productos;
}

//================ EXISTE PRODUCTO ================//

bool ExisteProducto(int codigo) {

    Producto p;

    ifstream archivo(
        archivoProductos,
        ios::binary
    );

    if(!archivo) {

        return false;
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

            archivo.close();

            return true;
        }
    }

    archivo.close();

    return false;
}

//================ MENU PRODUCTOS ================//

void MenuProductos() {

    int opcion;

    do {

        Encabezado(
        "GESTION DE PRODUCTOS"
        );

        cout << "1. Registrar producto\n";
        cout << "2. Mostrar productos\n";
        cout << "3. Buscar por codigo\n";
        cout << "4. Buscar por nombre\n";
        cout << "5. Actualizar stock\n";
        cout << "6. Modificar precio\n";
        cout << "7. Eliminar producto\n";
        cout << "8. Ordenar por precio\n";
        cout << "9. Ordenar por stock\n";
        cout << "10. Ordenar por vendidos\n";
        cout << "11. Regresar\n";

        cout << "\nSeleccione opcion: ";
        cin >> opcion;

        if(cin.fail()) {

            cin.clear();
            cin.ignore(1000,'\n');

            opcion = 0;
        }

        switch(opcion) {

            case 1:
                RegistrarProducto();
                break;

            case 2:
                MostrarProductos();
                break;

            case 3:
                BuscarPorCodigo();
                break;

            case 4:
                BuscarPorNombre();
                break;

            case 5:
                ActualizarStock();
                break;

            case 6:
                ModificarPrecio();
                break;

            case 7:
                EliminarProducto();
                break;

            case 8:
                OrdenarPorPrecio();
                break;

            case 9:
                OrdenarPorStock();
                break;

            case 10:
                OrdenarPorVendidos();
                break;
        }

    } while(opcion != 11);
}

//================ REGISTRAR PRODUCTO ================//

void RegistrarProducto() {

    Producto p;

    cout << "\nCodigo: ";
    cin >> p.codigo;

    if(cin.fail()) {

        cin.clear();
        cin.ignore(1000,'\n');

        cout << "Codigo invalido.\n";
        return;
    }

    if(ExisteProducto(p.codigo)) {

        cout << "El codigo ya existe.\n";
        return;
    }

    cin.ignore();

    cout << "Nombre: ";
    cin.getline(p.nombre, 40);

    cout << "Precio: ";
    cin >> p.precio;

    if(cin.fail() || p.precio <= 0) {

        cin.clear();
        cin.ignore(1000,'\n');

        cout << "Precio invalido.\n";
        return;
    }

    cout << "Stock: ";
    cin >> p.stock;

    if(cin.fail() || p.stock < 0) {

        cin.clear();
        cin.ignore(1000,'\n');

        cout << "Stock invalido.\n";
        return;
    }

    p.vendidos = 0;
    p.activo = true;

    ofstream archivo(
        archivoProductos,
        ios::binary | ios::app
    );

    if(!archivo) {

        cout << "Error al abrir archivo.\n";
        return;
    }

    archivo.write(
        (char*)&p,
        sizeof(Producto)
    );

    archivo.close();

    cout << "\nProducto registrado correctamente.\n";
}

//================ MOSTRAR PRODUCTOS ================//

void MostrarProductos() {

    vector<Producto> productos =
    CargarProductos();

    if(productos.empty()) {

        cout << "\nNo existen productos registrados.\n";
        return;
    }

    Encabezado("LISTA DE PRODUCTOS");

    FormatoDecimal();

    cout << left
         << setw(10) << "Codigo"
         << setw(25) << "Nombre"
         << setw(12) << "Precio"
         << setw(10) << "Stock"
         << setw(10) << "Vendidos"
         << endl;

    cout << "-------------------------------------------------------------\n";

    for(size_t i = 0;
        i < productos.size();
        i++) {

        cout << left
             << setw(10)
             << productos[i].codigo

             << setw(25)
             << productos[i].nombre

             << setw(12)
             << productos[i].precio

             << setw(10)
             << productos[i].stock

             << setw(10)
             << productos[i].vendidos

             << endl;
    }
}

//================ BUSCAR POR CODIGO ================//

void BuscarPorCodigo() {

    vector<Producto> productos =
    CargarProductos();

    if(productos.empty()) {

        cout << "\nNo existen productos registrados.\n";
        return;
    }

    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo: ";
    cin >> codigo;

    if(cin.fail()) {

        cin.clear();
        cin.ignore(1000,'\n');

        cout << "Codigo invalido.\n";
        return;
    }

    for(size_t i = 0;
        i < productos.size();
        i++) {

        if(productos[i].codigo == codigo) {

            encontrado = true;

            Encabezado("PRODUCTO ENCONTRADO");

            FormatoDecimal();

            cout << "Codigo: "
                 << productos[i].codigo
                 << endl;

            cout << "Nombre: "
                 << productos[i].nombre
                 << endl;

            cout << "Precio: Q"
                 << productos[i].precio
                 << endl;

            cout << "Stock: "
                 << productos[i].stock
                 << endl;

            cout << "Vendidos: "
                 << productos[i].vendidos
                 << endl;

            break;
        }
    }

    if(!encontrado) {

        cout << "\nProducto no encontrado.\n";
    }
}

//================ BUSCAR POR NOMBRE ================//

void BuscarPorNombre() {

    vector<Producto> productos =
    CargarProductos();

    if(productos.empty()) {

        cout << "\nNo existen productos registrados.\n";
        return;
    }

    char nombreBuscar[40];

    bool encontrado = false;

    cin.ignore();

    cout << "\nIngrese nombre: ";
    cin.getline(nombreBuscar,40);

    Encabezado("RESULTADOS BUSQUEDA");

    for(size_t i = 0;
        i < productos.size();
        i++) {

        if(
            strstr(
                productos[i].nombre,
                nombreBuscar
            )
        ) {

            encontrado = true;

            cout << "\nCodigo: "
                 << productos[i].codigo
                 << endl;

            cout << "Nombre: "
                 << productos[i].nombre
                 << endl;

            cout << "Precio: Q"
                 << productos[i].precio
                 << endl;

            cout << "Stock: "
                 << productos[i].stock
                 << endl;
        }
    }

    if(!encontrado) {

        cout << "\nNo se encontraron coincidencias.\n";
    }
};

//================ ACTUALIZAR STOCK ================//

void ActualizarStock() {

    Producto p;

    int codigo;
    bool encontrado = false;

    cout << "\nCodigo del producto: ";
    cin >> codigo;

    if(cin.fail()) {

        cin.clear();
        cin.ignore(1000,'\n');

        cout << "Codigo invalido.\n";
        return;
    }

    fstream archivo(
        archivoProductos,
        ios::binary |
        ios::in |
        ios::out
    );

    if(!archivo) {

        cout << "Error al abrir archivo.\n";
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

            cout << "Stock actual: "
                 << p.stock
                 << endl;

            cout << "Nuevo stock: ";
            cin >> p.stock;

            if(cin.fail() ||
               p.stock < 0) {

                cin.clear();
                cin.ignore(1000,'\n');

                cout << "Stock invalido.\n";

                archivo.close();
                return;
            }

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

            cout
            << "\nStock actualizado correctamente.\n";

            break;
        }
    }

    archivo.close();

    if(!encontrado) {

        cout << "\nProducto no encontrado.\n";
    }
}

//================ MODIFICAR PRECIO ================//

void ModificarPrecio() {

    Producto p;

    int codigo;
    bool encontrado = false;

    cout << "\nCodigo del producto: ";
    cin >> codigo;

    if(cin.fail()) {

        cin.clear();
        cin.ignore(1000,'\n');

        cout << "Codigo invalido.\n";
        return;
    }

    fstream archivo(
        archivoProductos,
        ios::binary |
        ios::in |
        ios::out
    );

    if(!archivo) {

        cout << "Error al abrir archivo.\n";
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

            cout << "Precio actual: Q"
                 << p.precio
                 << endl;

            cout << "Nuevo precio: ";
            cin >> p.precio;

            if(cin.fail() ||
               p.precio <= 0) {

                cin.clear();
                cin.ignore(1000,'\n');

                cout << "Precio invalido.\n";

                archivo.close();
                return;
            }

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

            cout
            << "\nPrecio actualizado correctamente.\n";

            break;
        }
    }

    archivo.close();

    if(!encontrado) {

        cout << "\nProducto no encontrado.\n";
    }
}

//================ ELIMINAR PRODUCTO ================//

void EliminarProducto() {

    Producto p;

    int codigo;
    bool encontrado = false;

    cout << "\nCodigo del producto: ";
    cin >> codigo;

    if(cin.fail()) {

        cin.clear();
        cin.ignore(1000,'\n');

        cout << "Codigo invalido.\n";
        return;
    }

    fstream archivo(
        archivoProductos,
        ios::binary |
        ios::in |
        ios::out
    );

    if(!archivo) {

        cout << "Error al abrir archivo.\n";
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

            p.activo = false;

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

            cout
            << "\nProducto eliminado correctamente.\n";

            break;
        }
    }

    archivo.close();

    if(!encontrado) {

        cout << "\nProducto no encontrado.\n";
    }
}

//================ ORDENAR POR PRECIO =================//

void OrdenarPorPrecio() {

    vector<Producto> productos =
    CargarProductos();

    if(productos.empty()) {

        cout << "\nNo existen productos registrados.\n";
        return;
    }

    // Bubble Sort Ascendente

    for(size_t i = 0;
        i < productos.size() - 1;
        i++) {

        for(size_t j = 0;
            j < productos.size() - 1 - i;
            j++) {

            if(
                productos[j].precio >
                productos[j + 1].precio
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

    Encabezado(
    "PRODUCTOS ORDENADOS POR PRECIO"
    );

    FormatoDecimal();

    for(size_t i = 0;
        i < productos.size();
        i++) {

        cout
        << productos[i].codigo
        << " | "
        << productos[i].nombre
        << " | Q"
        << productos[i].precio
        << endl;
    }
}

//================ ORDENAR POR STOCK =================//

void OrdenarPorStock() {

    vector<Producto> productos =
    CargarProductos();

    if(productos.empty()) {

        cout << "\nNo existen productos registrados.\n";
        return;
    }

    // Selection Sort

    for(size_t i = 0;
        i < productos.size() - 1;
        i++) {

        size_t menor = i;

        for(size_t j = i + 1;
            j < productos.size();
            j++) {

            if(
                productos[j].stock <
                productos[menor].stock
            ) {

                menor = j;
            }
        }

        Producto aux =
        productos[i];

        productos[i] =
        productos[menor];

        productos[menor] =
        aux;
    }

    Encabezado(
    "PRODUCTOS ORDENADOS POR STOCK"
    );

    for(size_t i = 0;
        i < productos.size();
        i++) {

        cout
        << productos[i].codigo
        << " | "
        << productos[i].nombre
        << " | Stock: "
        << productos[i].stock
        << endl;
    }
}

//================ ORDENAR POR VENDIDOS =================//

void OrdenarPorVendidos() {

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

    Encabezado(
    "PRODUCTOS MAS VENDIDOS"
    );

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
