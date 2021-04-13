/*
Leonel Godoy, 1C, UTN. El sol otoñal brilla.

   Clase 9
Ejercicio 9-1:
Una empresa importadora que comercializa productos Apple,
decide registrar de sus productos los siguientes datos:

idProducto (numerico)
descripcion (alfanumérico)
nacionalidad (numérico, por el momento utilizaremos un define: EEUU - CHINA - OTRO)
tipo (numérico, por el momento utilizaremos un define: IPHONE -MAC - IPAD - ACCESORIOS)
precio (numérico decimal)



Realizar un programa que permita interactuar con un menú de usuarios con las siguientes opciones:

ALTA Producto: Se ingresan los datos de UN solo producto. Siempre y cuando haya espacio disponible en el array. Al momento de dar de alta el producto, el usuario podrá elegir el tipo de producto, de una lista que se le desplegará en pantalla.
BAJA Producto: A partir del ingreso del ID. Si existe el producto desaparece de la lista, dejando espacio disponible para un nuevo producto.
MODIFICACIÓN Producto: A partir del ingreso del ID. Si existe se podrá modificar el precio o el tipo. Si modifica el tipo de producto, se utilizara el mismo criterio que para dar de alta.
LISTADOS:
    LISTADO Productos.
    LISTADO ordenado por precio.
    LISTADO ordenado por descripción.

Agregar los siguientes informes:
El/los  productos más caros.
Precio promedio por tipo de producto. Se deberá mostrar la descripción del tipo y a continuación el precio promedio.

Se agregan los siguientes listados:
El listado de todos los productos con la descripción del tipo.
Por cada tipo la lista de productos.


*/

#include <stdio.h>
#include <stdlib.h>
#include "funcionesABM.h"
//tamanio maximo del array eproducto
#define TAM 10
//define codigoNacionalidad
#define EEUU 10
#define CHINA 11
#define OTRO 12
//define codigoTipo
#define IPHONE 70
#define MAC 71
#define IPAD 72
#define ACCESORIOS 73

int main()
{
    //declaro mi array de eproductos
    eProducto listado[TAM];
    int opcion;

    inicializarListado(listado, TAM);

    do
    {
        opcion=mostrarMenu();
        switch(opcion)
        {
        case 1:
            //alta
            altaProducto(listado, TAM);
            break;
        case 2:
            //baja
            bajaProducto(listado, TAM);
            break;
        case 3:
            //modificacion
            modificarProducto(listado, TAM);
            break;
        case 4:
            //listados
            mostrarSubmenuListados(listado, TAM);
            break;
        case 5:
            //informar mas caro/s, informar precio promedio
            break;
        case 6:
            printf("\n**Salir del programa**\n");
            system("pause");
            break;
        case 7:
            //informar el producto mas caro
            break;
        case 9:
            hardcodearListado(listado, TAM);
            break;
        default:
            printf("\nDEBUGG: eligio una opcion valida?\n");
            system("pause");
        }

    }
    while(opcion!=6);

    return 0;
}
