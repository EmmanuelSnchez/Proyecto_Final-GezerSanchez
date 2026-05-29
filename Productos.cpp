//================ productos.cpp ================//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>

#include "productos.h"

using namespace std;

const char* archivoProductos = "productos.dat";

//================ VECTOR PRODUCTOS ================//

vector<Producto> CargarProductos() {

    vector<Producto> lista;

    Producto p;

    ifstream lectura(archivoProductos, ios::binary);

    while(lectura.read((char*)&p, sizeof(Producto))) {

        if(p.activo) {
            lista.push_back(p);
        }
    }

    lectura.close();

    return lista;
}

//================ MENU ================//

void MenuProductos() {

    int opcion;

    do {

        cout << "\n====== MODULO PRODUCTOS ======\n";
        cout << "1. Registrar producto\n";
        cout << "2. Mostrar productos\n";
        cout << "3. Buscar por codigo\n";
        cout << "4. Buscar por nombre\n";
        cout << "5. Actualizar stock\n";
        cout << "6. Modificar precio\n";
        cout << "7. Eliminar producto\n";
        cout << "8. Ordenar por precio\n";
        cout << "9. Ordenar por stock\n";
        cout << "10. Regresar\n";
        cout << "Seleccione opcion: ";
        cin >> opcion;

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
        }

    } while(opcion != 10);
}

//================ VALIDAR PRODUCTO ================//

bool ExisteProducto(int codigo) {

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

//================ REGISTRAR ================//

void RegistrarProducto() {

    Producto p;

    cout << "\nCodigo: ";
    cin >> p.codigo;

    if(ExisteProducto(p.codigo)) {

        cout << "Codigo existente.\n";
        return;
    }

    cin.ignore();

    cout << "Nombre: ";
    cin.getline(p.nombre, 40);

    cout << "Precio: ";
    cin >> p.precio;

    cout << "Stock: ";
    cin >> p.stock;

    p.vendidos = 0;
    p.activo = true;

    ofstream escritura(archivoProductos,
    ios::binary | ios::app);

    escritura.write((char*)&p, sizeof(Producto));

    escritura.close();

    cout << "Producto registrado.\n";
}

//================ MOSTRAR PRODUCTOS ================//

void MostrarProductos() {

    vector<Producto> productos = CargarProductos();

    cout << "\n======= INVENTARIO =======\n";

    for(int i = 0; i < productos.size(); i++) {

        cout << "\nCodigo: "
             << productos[i].codigo << endl;

        cout << "Nombre: "
             << productos[i].nombre << endl;

        cout << "Precio: Q"
             << fixed << setprecision(2)
             << productos[i].precio << endl;

        cout << "Stock: "
             << productos[i].stock << endl;

        cout << "Vendidos: "
             << productos[i].vendidos << endl;
    }
}

//================ BUSCAR CODIGO ================//

void BuscarPorCodigo() {

    vector<Producto> productos = CargarProductos();

    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo: ";
    cin >> codigo;

    for(int i = 0; i < productos.size(); i++) {

        if(productos[i].codigo == codigo) {

            encontrado = true;

            cout << "\nProducto encontrado\n";

            cout << "Nombre: "
                 << productos[i].nombre << endl;

            cout << "Precio: Q"
                 << productos[i].precio << endl;

            break;
        }
    }

    if(!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

//================ BUSCAR NOMBRE ================//

void BuscarPorNombre() {

    vector<Producto> productos = CargarProductos();

    char nombreBuscar[40];

    bool encontrado = false;

    cin.ignore();

    cout << "\nIngrese nombre: ";
    cin.getline(nombreBuscar, 40);

    for(int i = 0; i < productos.size(); i++) {

        if(strstr(productos[i].nombre, nombreBuscar)) {

            encontrado = true;

            cout << "\nCodigo: "
                 << productos[i].codigo << endl;

            cout << "Nombre: "
                 << productos[i].nombre << endl;
        }
    }

    if(!encontrado) {
        cout << "No existen coincidencias.\n";
    }
}

//================ ACTUALIZAR STOCK ================//

void ActualizarStock() {

    Producto p;

    int codigo;
    bool encontrado = false;

    cout << "\nCodigo producto: ";
    cin >> codigo;

    fstream archivo(archivoProductos,
    ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo) {

            encontrado = true;

            cout << "Stock actual: "
                 << p.stock << endl;

            cout << "Nuevo stock: ";
            cin >> p.stock;

            int posicion =
            archivo.tellg() - sizeof(Producto);

            archivo.seekp(posicion);

            archivo.write((char*)&p,
            sizeof(Producto));

            cout << "Stock actualizado.\n";

            break;
        }
    }

    archivo.close();

    if(!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

//================ MODIFICAR PRECIO ================//

void ModificarPrecio() {

    Producto p;

    int codigo;

    bool encontrado = false;

    cout << "\nCodigo producto: ";
    cin >> codigo;

    fstream archivo(archivoProductos,
    ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo) {

            encontrado = true;

            cout << "Precio actual: Q"
                 << p.precio << endl;

            cout << "Nuevo precio: ";
            cin >> p.precio;

            int posicion =
            archivo.tellg() - sizeof(Producto);

            archivo.seekp(posicion);

            archivo.write((char*)&p,
            sizeof(Producto));

            cout << "Precio actualizado.\n";

            break;
        }
    }

    archivo.close();

    if(!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

//================ ELIMINAR PRODUCTO ================//

void EliminarProducto() {

    Producto p;

    int codigo;

    bool encontrado = false;

    cout << "\nCodigo producto: ";
    cin >> codigo;

    fstream archivo(archivoProductos,
    ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo) {

            encontrado = true;

            p.activo = false;

            int posicion =
            archivo.tellg() - sizeof(Producto);

            archivo.seekp(posicion);

            archivo.write((char*)&p,
            sizeof(Producto));

            cout << "Producto eliminado.\n";

            break;
        }
    }

    archivo.close();

    if(!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

//================ ORDENAR PRECIO ================//

void OrdenarPorPrecio() {

    vector<Producto> productos = CargarProductos();

    for(int i = 0; i < productos.size() - 1; i++) {

        for(int j = 0;
            j < productos.size() - 1 - i;
            j++) {

            if(productos[j].precio >
               productos[j + 1].precio) {

                Producto aux = productos[j];

                productos[j] = productos[j + 1];

                productos[j + 1] = aux;
            }
        }
    }

    cout << "\n=== PRODUCTOS ORDENADOS PRECIO ===\n";

    for(int i = 0; i < productos.size(); i++) {

        cout << productos[i].nombre
             << " | Q"
             << productos[i].precio << endl;
    }
}

//================ ORDENAR STOCK ================//

void OrdenarPorStock() {

    vector<Producto> productos = CargarProductos();

    for(int i = 0; i < productos.size() - 1; i++) {

        int menor = i;

        for(int j = i + 1;
            j < productos.size();
            j++) {

            if(productos[j].stock <
               productos[menor].stock) {

                menor = j;
            }
        }

        Producto aux = productos[i];

        productos[i] = productos[menor];

        productos[menor] = aux;
    }

    cout << "\n=== PRODUCTOS ORDENADOS STOCK ===\n";

    for(int i = 0; i < productos.size(); i++) {

        cout << productos[i].nombre
             << " | Stock: "
             << productos[i].stock << endl;
    }
}