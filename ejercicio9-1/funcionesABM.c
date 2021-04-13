#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

//define codigoNacionalidad
#define EEUU 10
#define CHINA 11
#define OTRO 12
//define codigoTipo
#define IPHONE 70
#define MAC 71
#define IPAD 72
#define ACCESORIOS 73
//define el primer id
#define PRIMERID 1
#define ULTIMOID 99999//vergonzoso define solo para que bajaProducto quede bien
//precio min y maximo deberan adaptarse si surgieren productos cuyo precio rebase los limites
#define PRECIOMINIMO 0.1
#define PRECIOMAXIMO 9999999.0

typedef struct
{
    int id;     //if id==-1 --> IS EMPTY
    char descripcion[64];
    int codigoNacionalidad;
    int codigoTipo;
    float precio;
} eProducto;



/** \brief iniciliza el listado recibido seteando todos los lista[i].id=-1
 *
 * \param listado a inicilizar
 * \param longitud listado
 * \return retorna 0 siempre
 *
 */
int inicializarListado(eProducto lista[], int length)
{
    for(int i=0; i<length; i++)
    {
        lista[i].id=-1;
    }
    return 0;
}


/** \brief busca lugar libre para cargar producto
 *
 * \param lista donde buscar lugar
 * \param longitud de lista
 * \return retorna -1 si no hay lugar disponible, else retorna un indice valido para cargar
 *
 */
int buscarLibre(eProducto lista[], int length)
{
    int retorno=-1;//pesimista

    for(int i=0; i<length; i++)
    {
        if(lista[i].id==-1)//es decir, el lugar está disponible
        {
            retorno = i;
            break;
        }
    }

    return retorno;
}

int mostrarMenu()
{
    int a;
    utn_getNumero(&a, "\n*Menu de opciones\n1-Alta producto\n2-Baja\n3-Modificacion\n4-Listados\n5-Informes varios\n6-Salir\n**ElijaOpcion: ", "\n**Error: elija una opcion valida\n", 1, 6, 3);
    return a;
}



/** \brief busca el Id en la lista de productos
 *
 * \param listado de eProducto
 * \param longitud del listado
 * \param id a buscar
 * \return retorna el indice del elemento con igual Id, or -1 si no existe el id ingresado
 *
 */
int buscarId(eProducto lista[], int length, int idBuscado)
{
    int retorno=-1;//pesimista
    for(int i=0; i<length; i++)
    {
        if(lista[i].id== idBuscado)
        {
            retorno=i;//retornar la posicion del producto que tiene el id ocupado
            break;
        }
    }
    return retorno;
}

/** \brief fx() auxiliar de alta producto: muestra las nacionalidades y elige una
 *
 * \return retorna 1||2||3 (exito) que será el codigo de la nacionalidad, sin retorno para falla
 *
 */
int elegirPaisDeOirigen()
{
    int retorno=0;

    printf("\n**Elija Codigo pais de origen.");
    printf("\nEEUU:%d --China:%d --Otro:%d", EEUU, CHINA, OTRO);
    do
    {
        utn_getNumero(&retorno, "\n**Elija Codigo pais de origen: ", "\n**Error: elija una opcion valida", EEUU, OTRO, 3);
    }
    while(retorno < EEUU && retorno > OTRO);

    return retorno;
}


/** \brief fx() auxiliar de alta producto: muestra tipos de productos y elige uno
 *
 * \return retorna el codigo (INT) del tipo de producto, sin retorno para falla
 *
 */
int elegirTipoDeProducto()
{
    int retorno=0;

    printf("\n**Codigos de Tipo de Producto.");
    printf("\nIphone:%d --Mac:%d --IPad:%d --Accesorios:%d", IPHONE, MAC, IPAD, ACCESORIOS);
    do
    {
        utn_getNumero(&retorno, "\n**Ingrese codigo de tipo producto: ", "\n**Error: elija una opcion valida", IPHONE, ACCESORIOS, 3);
    }
    while(retorno < EEUU && retorno > OTRO);

    return retorno;
}
//usa buscarLibre() y chequearId()
/** \brief solicita el alta un eProducto, buscando lugar libre previamente
 *
 * \param listado donde cargar eProducto
 * \param longitud del array de estructuras
 * \return 1 en caso de carga exitosa, -1 si no hay lugar, 0 error desconocido o.O
 *
 */
int altaProducto(eProducto lista[], int length)
{
    int retorno=0;
    int indiceLibre;
    int banderaIdRepetido;
    eProducto auxiliar;//ahi se cargarán los datos, luego de ciertas validaciones se copiara al indice libre

    indiceLibre= buscarLibre(lista, length);//busco lugar libre

    if( indiceLibre == -1)
    {
        printf("\n**No hay lugar disponible**\n");
        system("pause");
        retorno=-1;
    }
    else  //hay lugar, proceder a carga
    {
        do//pedir id: REVISAR QUE NO SEA ID REPETIDO buscarId(eProducto lista[], int length)
        {
            utn_getNumero(&auxiliar.id, "\nIngrese ID producto (es clave primaria): ", "\n***Error: id fuera de rango", PRIMERID, PRIMERID+1000, 3);
            banderaIdRepetido = buscarId(lista, length, auxiliar.id);
        }
        while(banderaIdRepetido!=-1);

        //pedir descripcion producto
        utn_getTexto(auxiliar.descripcion, 64, "\nDescripcion: ");

        //mostrar y elegirir codigo pais de origen
        auxiliar.codigoNacionalidad = elegirPaisDeOirigen();

        //mostrar y elegir codigo de tipo de producto
        auxiliar.codigoTipo= elegirTipoDeProducto();

        utn_getNumeroReal(&auxiliar.precio, "\nIngrese el precio del producto: ", "\nError, elija un valor válido", PRECIOMINIMO, PRECIOMAXIMO, 3);

        lista[indiceLibre] = auxiliar;
        retorno=1;
    }
    return retorno;
}


//---------------------
//FUNCIONES TRADUCTORAS

/** \brief f(x) auxiliar: recibe un codigo de pais y copia el nombre del pais
 *
 * \param codigoDePaisRecibido
 * \param puntero a string donde almacenar el nombre del pais
 * \return 1 exito, -1 fracaso
 *
 */
int pasarDeCodigoAPais(int codigoRecibido, char* pResultado)
{
    int retorno=1;
    if( pResultado != NULL)
    {
        switch (codigoRecibido)
        {
        case EEUU:
            strcpy(pResultado, "EEUU");
            break;
        case CHINA:
            strcpy(pResultado, "CHINA");
            break;
        case OTRO:
            strcpy(pResultado, "OTRO");
            break;
        default:
            strcpy(pResultado, "ERROR 222");
            retorno=-1;
        }
    }

    return retorno;
}


/** \brief recibe un codigo de Tipo de Producto y copia string tipo al char* pResultado recibido
 *
 * \param codigoDeProducto Recibido
 * \param puntero a string donde almacenar el tipo poroducto
 * \return 1 exito, -1 fracaso
 *
 */
int pasarDeCodigoATipoProducto(int codigoRecibido, char* pResultado)
{
    int retorno=1;
    if(pResultado != NULL)
    {
        switch (codigoRecibido)
        {
        case IPHONE:
            strcpy(pResultado, "IPHONE");
            break;
        case MAC:
            strcpy(pResultado, "MAC");
            break;
        case IPAD:
            strcpy(pResultado, "IPAD");
            break;
        case ACCESORIOS:
            strcpy(pResultado, "ACCESORIOS");
            break;
        default:
            strcpy(pResultado, "ERROR 251");
            retorno=-1;
        }
    }

    return retorno;
}

//FIN traductoras
//---------------------

int mostrarProducto(eProducto x)
{
    int retorno=-1;;
    char cadenaAuxiliarPais[64]; //sirven para el intercambio de codigo pais/tipoProducto por su desripcion
    char cadenaAuxiliarTipoProducto[64];

    if( pasarDeCodigoAPais(x.codigoNacionalidad, cadenaAuxiliarPais) && pasarDeCodigoATipoProducto(x.codigoNacionalidad, cadenaAuxiliarTipoProducto) )
    {
        printf("\n%d -- %s -- %.1f -- %d -- %d", x.id, x.descripcion, x.precio, x.codigoTipo, x.codigoNacionalidad);
        retorno=0;
    }else
    {
        printf("\nWOW, sucedio algo inesperado\nSo, sad.\n");
        system("pause");
    }

    return retorno;
}





//BAJA producto-->poner id=-1
/** \brief realiza la baja logica de un producto seteando id=-1
 *
 * \param listado de productos
 * \param longitud del array
 * \return retorna 1 si consiguio la baja, 0 si no lo logró, sea por ID inexistente o no confirmacion
 *
 */
int bajaProducto(eProducto lista[], int length)
{
    int retorno=0;
    int idParaBajar;
    int indiceParaBajar; //si el id existe, aqui se guardara su index
    char confirmacion;

    printf("\n**Baja de un producto");
    utn_getNumero(&idParaBajar, "\nIngrese el ID del producto: ", "\n**Error de rango\n", PRIMERID, ULTIMOID, 3);

    indiceParaBajar = buscarId(lista, length, idParaBajar);
    if(indiceParaBajar==-1)
    {
        printf("\n**ID:%d inexistente.", idParaBajar);
    }
    else
    {
        mostrarProducto(lista[indiceParaBajar]);

        utn_getLetra(&confirmacion, "\n**Confirma eliminar registro? s/n: ", "\n**Error: opcion invalida.", 'n', 's', 3);
        if(confirmacion=='s')
        {
            lista[indiceParaBajar].id=-1; //esto es una baja logica
            retorno=1;//baja exitosa
        }
    }

    return retorno;
}


//MODIFICA UN PRODUCTO
/** \brief modifica los campos de un eProducto, salvo el id
 *
 * \param listado de productos
 * \param longitud del listado
 * \return 1 si se modifico el producto, 0 si no
 *
 */

int modificarProducto(eProducto lista[], int length)
{
    int retorno;
    int idProducto;
    int indiceProducto;//producto a modificar
    char confirmacion='n';

    printf("\n**MODIFICAR PRODUCTO\n");
    utn_getNumero(&idProducto, "\nIngrese id del producto a modificar: ", "\nError: fuera de rango\n", PRIMERID, ULTIMOID, 3);

    indiceProducto = buscarId(lista, length, idProducto);
    if(indiceProducto ==-1)
    {
        printf("\n**No existe el Id %d", idProducto);
        retorno = 0;
    }
    else
    {
        mostrarProducto(lista[indiceProducto]);

        utn_getLetra(&confirmacion, "\n**Quiere modificar este producto? s/n: ", "\n**Error: opcion invalida.", 'n', 's', 3);

        if(confirmacion=='s')
        {

            //pedir descripcion producto
            utn_getTexto(lista[indiceProducto].descripcion, 64, "\nDescripcion: ");

            //mostrar y elegirir codigo pais de origen
            lista[indiceProducto].codigoNacionalidad = elegirPaisDeOirigen();


            //mostrar y elegir codigo de tipo de producto
            lista[indiceProducto].codigoTipo= elegirTipoDeProducto();

            utn_getNumeroReal(&lista[indiceProducto].precio, "\nIngrese el precio del producto: ", "\nError, elija un valor válido", PRECIOMINIMO, PRECIOMAXIMO, 3);

            retorno=1;
        }
        else
        {
            printf("\n**Baja cancelada.");
            system("pause");
            retorno=0;
        }

    }

    return retorno;
}

int mostrarListadoDeProductos(eProducto lista[], int length)
{
    printf("\nID Descripcion Precio CodTipo CodPais");
    for(int i=0; i<length; i++)
    {
        if (lista[i].id != -1)
        {
            mostrarProducto(lista[i]);
        }
    }
    return 0;
}



/*
array listado a recorrer
elementos tamanio del listado
creciente solo 1/0 acepta if ==1 crece, else if==0 decrece, else retornara error
return 1 en caso de exitoso ordenamiento (sea crec or decrec) y 0 en caso de error
*/
/** \brief ordena array eProductos por precio
 *
 * \param listado de eProductos
 * \param longitud del listado
 * \param 1 para orden creciente, 0 para orden decreciente
 * \return retorna 1 si realizo el ordenmiento, else 0
 *
 */
int ordenarPorPrecio(eProducto lista[], int length, int ordenCreciente)
{
    int retorno;
    eProducto auxiliar;

    if (ordenCreciente == 1)
    {
        //swap creciente
        for (int i = 0; i < length - 1; i++)
        {
            for (int j = i + 1; j < length; j++)
            {
                if (lista[i].precio > lista[j].precio)
                {
                    auxiliar = lista[i];
                    lista[i] = lista[j];
                    lista[j] = auxiliar;
                }
            }
        }
        printf("\n**Se ordeno de forma creciente segun precio.\n");
        retorno = 1;

    }
    else if (ordenCreciente == 0)
    {
        //swap decreciente
        for (int i = 0; i < length - 1; i++)
        {
            for (int j = i + 1; j < length; j++)
            {
                if (lista[i].precio < lista[j].precio)
                {
                    auxiliar = lista[i];
                    lista[i] = lista[j];
                    lista[j] = auxiliar;
                }
            }
        }
        printf("\n**Se ordeno de forma decreciente segun precio.\n");
        retorno = 1;
    }
    else
    {
        printf ("\n**Error: elija 1 para creciente or 0 para decreciente");
        retorno = 0;
    }

    return retorno;
}



/** \brief ordena el listado de productos por descripcion, crecient
 *
 * \param lista[] eProducto array de productos a ordenar
 * \param length int longitud maximo del array de eProductos
 * \param ordenCreciente int 1 para orden creciente, 0 para orden decreciente
 * \return retorna 1 si realizo el ordenmiento, else 0
 *
 */
int ordenarPorDescripcion(eProducto lista[], int length, int ordenCreciente)
{
    int retorno;
    eProducto auxiliar;

    if (ordenCreciente==1)
    {
        for(int i=0; i<length-1; i++)
        {
            for(int j=i+1; j<length; j++)
            {
                if (strcmp(lista[i].descripcion, lista[j].descripcion) > 0)
                {
                    //swap
                    auxiliar = lista[i];
                    lista[i] = lista[j];
                    lista[j] = auxiliar;
                }
            }
        }
        retorno = 1;
    }
    else if( ordenCreciente == 0)
    {
        for(int i=0; i<length-1; i++)
        {
            for(int j=i+1; j<length; j++)
            {
                if( strcmp(lista[i].descripcion, lista[j].descripcion) < 0)
                {
                    //swap
                    auxiliar = lista[i];
                    lista[i] = lista[j];
                    lista[j] = auxiliar;
                }
            }
        }
        retorno = 1;

    }
    else
    {
        printf("\nError en ordenamiento: elija 1 para creciente, 0 para decreciente.\n");
        system("pause");
        retorno = 0;
    }

    return retorno;
}

/** \brief
 *
 * \return 0
 *
 */
int mostrarSubmenuListados(eProducto lista[], int length)
{
    int opcion;
    int subopcion;

    utn_getNumero(&opcion, "\n**Submenu de listado\n1-Listar productos\n2-Listar ordenado por precio\n3-Listar ordenado por descripcion\n4-Salir\nOpcion: ", "\n**ERROR: elija una opcion valida\n", 1, 4, 3);
    switch(opcion)
    {
    case 1:
        //listado normal
        mostrarListadoDeProductos(lista, length);
        break;
    case 2:
        //listar Ordenador x precio
        utn_getNumero(&subopcion, "\n**Ordenar por precio. Ingrese 1 para orden creciente, 0 para orden decreciente: ", "\n**Error: valor invalido\n", 0, 1, 3);
        if ( ordenarPorPrecio(lista, length, subopcion) )
        {
            printf("\n**Se ordeno el listado por precio");
            system("pause");
        }
        else
        {
            printf("\n**NO Se ordeno el listado\n");
            system("pause");
        }
        break;
    case 3:
        //listar Ordenado x Descripciones
        utn_getNumero(&subopcion, "\n**Ordenar por descripcion. Ingrese 1 para orden creciente, 0 para orden decreciente: ", "\n**Error: valor invalido\n", 0, 1, 3);
        if ( ordenarPorDescripcion(lista, length, subopcion) )
        {
            printf("\n**Se ordeno el listado por descripcion");
            system("pause");
        }
        else
        {
            printf("\n**NO Se ordeno el listado\n");
            system("pause");
        }
        break;
    case 4:
        break;
    }

    return 0;
}
