/*
Leonel Godoy, 1C, UTN. El sol otoñal brilla.

 Ejercicio 11-1:
Una empresa importadora que comercializa productos Apple, decide registrar de sus productos los siguientes datos:
    idProducto (numerico)
    descripcion (alfanumérico)
    nacionalidad (numerico)
    tipo (numérico)
    precio (numérico decimal)

    Agregar la estructura etipoProducto, que definirá los siguientes campos:
    idTipo (numérico)
        descripcionTipo(alfanumérico)
    Para esta estructura en principio trabajaremos con datos hardcodeados:
    idTipo descripcionTipo
    1000    Iphone
    1001    Ipad
    1002    Mac
    1003    Accesorios


Agregar la estructura eNacionalidad, que definirá los siguientes campos:
    idNacionalidad (numérico)
    descripcionNacionalidad(alfanumérico)
Para esta estructura en principio trabajaremos con datos hardcodeados:
idTipo    descripcionTipo
    1    EEUU
    2    CHINA
    3    OTRO


Realizar un programa que permita interactuar con un menú de usuarios con las siguientes opciones:

1-    ALTA Producto: Se ingresan los datos de UN solo producto. Siempre y cuando haya espacio disponible en el array. Al momento de dar de alta el producto, el usuario podrá elegir el tipo de producto, de una lista que se le desplegará en pantalla.
2-    BAJA Producto: A partir del ingreso del ID. Si existe el producto desaparece de la lista, dejando espacio disponible para un nuevo producto.
3-    MODIFICACIÓN Producto: A partir del ingreso del ID. Si existe se podrá modificar el precio o el tipo. Si modifica el tipo de producto, se utilizara el mismo criterio que para dar de alta.
4-
    4.1   LISTADO Productos.
    4.2   LISTADO ordenado por precio.
    4.3   LISTADO ordenado por descripción.

Agregar los siguientes informes:
5.1 El/los  productos más caros.
5.2 Precio promedio por tipo de producto. Se deberá mostrar la descripción del tipo y a continuación el precio promedio.
(hecho en 4.1) El listado de todos los productos con la descripción del tipo.

4.4 Por cada tipo la lista de productos.

Se agregan los siguientes listados:
El/los tipos de productos con mas productos elaborados.
    (voy a necesitar un array de eTipoProducto?)
    (o un arrayDeContadores[i]?)
    Interpretación: hacer un contador de cada tipo de producto
    buscar el/los maximo/s
        if unMaximo-> mostrar el Maximo
       else if MasDeUnMax-> mostrarlos todos


NOTAS DEL PROFE:
Octavio Villegas17:16
Cosas a verificar para la semana que viene:

Que las estructuras esten relacionadas correctamente.
Evitar utilizar printf y scanf cada vez que se pide un dato (utilizar biblioteca inputs.h)
En las busquedas: los datos de tipo y nacionalidad no pueden estar hardcodeados. La logica no se puede basar en los datos. Se basa en las estructuras. Hacer un if preguntando por un id en particular esta mal.
Un for con un if implica una busqueda... Eso deberia estar en una funcion que puedan reutilizar.
Orde
Ordenar el menu para que no queden todas las opciones en un mismo nivel (trabajar con submenu)

Agregar alta - baja - modificacion de tipo y nacionalidad


-----------
//SIN TERMINAR...
int informarTipoProductoMasElaborado(eProducto lista[], int length)
*/

#include <stdio.h>
#include <stdlib.h>
#include "funcionesABM.h"
//tamanio maximo del array eproducto
#define TAM 10
#define TAMTIPOS 6
#define TAMNACIONES 6

//define el primer id
#define PRIMERID 1

int main()
{
    //declaro mi array de eproductos
    eProducto listado[TAM];
    eTipoProducto listadoTipos[TAMTIPOS];
    eNacionalidad listadoNaciones[TAMNACIONES];

    int opcion;
    int proximoId=PRIMERID;

    inicializarListadoProductos(listado, TAM);//todos los id=-1
    inicializarListadoTipos(listadoTipos, TAMTIPOS);
    inicializarListadoNaciones(listadoNaciones, TAMNACIONES);

    do
    {
        opcion=mostrarMenu();
        switch(opcion)
        {
        case 1:
            //alta
            system("cls");
            altaProducto(listado, TAM, &proximoId);
            break;
        case 2:
            //baja
            system("cls");
            bajaProducto(listado, TAM);
            break;
        case 3:
            //modificacion
            printf("\nDEBUG \n");
            system("cls");
            modificarProducto(listado, TAM);
            break;
        case 4:
            //listados
            system("cls");
            mostrarSubmenuListados(listado, TAM);
            break;
        case 5:
            //informar mas caro/s, informar precio promedio
            system("cls");
            mostrarSubmenuInformes(listado, TAM);

            break;
        case 6:
            printf("\n**Salir del programa**\n");
            break;
        case 7:

            break;
        case 9:
            printf("\nDebuggear y hacer submenu de hardcodeo");
            system("pause");
            hardcodearListado(listado, TAM, &proximoId);
            break;
        default:
            printf("\nDEBUGG: eligio una opcion valida?\n");
            system("pause");
        }

    }
    while(opcion!=6);

    return 0;
}
