//================ productos.h ================//

#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <vector>

using namespace std;

//================ ESTRUCTURA PRODUCTO ================//

struct Producto {

    int codigo;
    char nombre[40];
    float precio;
    int stock;
    int vendidos;
    bool activo;
};

//================ MENU ================//

void MenuProductos();

//================ CRUD ================//

void RegistrarProducto();
void MostrarProductos();

void BuscarPorCodigo();
void BuscarPorNombre();

void ActualizarStock();
void ModificarPrecio();

void EliminarProducto();

//================ ORDENAMIENTOS ================//

void OrdenarPorPrecio();      // Bubble Sort
void OrdenarPorStock();       // Selection Sort
void OrdenarPorVendidos();    // Bubble Sort

//================ UTILIDADES ================//

bool ExisteProducto(int codigo);

vector<Producto> CargarProductos();

#endif