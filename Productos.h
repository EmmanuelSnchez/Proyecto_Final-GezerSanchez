//================ productos.h ================//

#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <vector>

using namespace std;

struct Producto {

    int codigo;
    char nombre[40];
    float precio;
    int stock;
    int vendidos;
    bool activo;
};

void MenuProductos();

void RegistrarProducto();
void MostrarProductos();
void BuscarPorCodigo();
void BuscarPorNombre();

void ActualizarStock();
void ModificarPrecio();
void EliminarProducto();

void OrdenarPorPrecio();
void OrdenarPorStock();

bool ExisteProducto(int codigo);

vector<Producto> CargarProductos();

#endif