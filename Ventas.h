//================ ventas.h ================//

#ifndef VENTAS_H
#define VENTAS_H

//================ DETALLE VENTA ================//

struct DetalleVenta {

    int codigoProducto;

    char nombreProducto[40];

    int cantidad;

    float precioUnitario;

    float subtotal;
};

//================ VENTA ================//

struct Venta {

    int numeroVenta;

    int dia;
    int mes;
    int anio;

    int totalArticulos;

    float subtotalGeneral;

    float iva;

    float descuento;

    float totalFinal;
};

//================ PROTOTIPOS ================//

void CrearVenta();

#endif