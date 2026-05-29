//================ ventas.h ================//

#ifndef VENTAS_H
#define VENTAS_H

struct DetalleVenta {

    int codigoProducto;
    char nombreProducto[40];
    int cantidad;
    float precioUnitario;
    float subtotal;
};

struct Venta {

    int numeroVenta;
    int totalArticulos;
    float subtotalGeneral;
    float iva;
    float descuento;
    float totalFinal;
};

void CrearVenta();

#endif