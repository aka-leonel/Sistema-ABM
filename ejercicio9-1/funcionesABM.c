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
    system("cls");
    utn_getNumero(&a, "\n*Menu de opciones\n1-Alta producto\n2-Baja\n3-Modificacion\n4-Listados\n5-Informes\n6-Salir\n**9-Para Hardcodear Registros\n\n**Elija opcion: ", "\n**Error: elija una opcion valida\n", 1, 9, 3);
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
        printf("\n**Se cargo correctamente el item %s\n", lista[indiceLibre].descripcion);
        system("pause");
    }
    system("cls");
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
            printf("\n**DEBUG: codigo recibido %d", codigoRecibido);
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

    if( pasarDeCodigoAPais(x.codigoNacionalidad, cadenaAuxiliarPais) && pasarDeCodigoATipoProducto(x.codigoTipo, cadenaAuxiliarTipoProducto) )
    {
        printf("\n%d -- %20s -- %8.1f -- %10s -- %8s", x.id, x.descripcion, x.precio, cadenaAuxiliarTipoProducto, cadenaAuxiliarPais);
        retorno=0;
    }
    else
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
    system("cls");
    int bandera=0;//aun no se mostro nada ni a nadie

    for(int i=0; i<length; i++)
    {
        if (lista[i].id != -1)
        {
            if(bandera==0)
            {
                printf("\nID   Descripcion              Precio    Tipo  PaisDeOrigen");
                bandera=1;
            }

            mostrarProducto(lista[i]);
        }
    }

    if(bandera==0)//no se mostro nada
    {
        printf("\n*******No hay productos dados de alta.\n");
    }
    printf("\n");
    system("pause");
    system("cls");
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


/** \brief hardcodea hasta cinco(5) registros en un listado de eProductos
 *
 * \param lista[] eProducto donde hardcodear productos
 * \param length int
 * \return retorna 1 si pudo hardcodear, else 0
 *
 */
int hardcodearListado(eProducto lista[], int length)
{
    int retorno;
    int ids[5]= {1,2,3,4,5};
    char descripciones[5][20]= {"BlackIphone", "NewPinkEarBuds", "MegaIpad", "MacboockProAir", "GoldBatteryCharger"};
    float precios[5]= {80720.1, 12700.99, 94000.1, 680000.0, 21000.6};
    int codigosNacionalidades[5]= {11,11,12,11,10};
    int codigoTipoProductos[5]= {70, 73, 72, 71, 73};

    if(length>5)
    {
        for(int i=0; i<5; i++)
        {
            lista[i].id= ids[i];
            strcpy(lista[i].descripcion, descripciones[i]);
            lista[i].precio = precios[i];
            lista[i].codigoNacionalidad= codigosNacionalidades[i];
            lista[i].codigoTipo=codigoTipoProductos[i];
        }
        retorno=1;
        printf("\n**se hardcodearon los registros.");
        system("pause");
    }
    else
    {
        printf("\nerror al hardcodear. Se solicito un hardcodeo mayor al tamanio del array.");
        system("pause");
        retorno=-1;
    }
    system("cls");
    return retorno;
}



/** \brief informa el/los producto/s mas caro/s
 *
 * \param lista[] eProducto
 * \param length int
 * \return int
 *
 */
int informarProductosMasCaros(eProducto lista[], int length)
{
    int indiceDelMasCaro=-1;//
    int cantidadDeMaximos=0;//en caso de haber mas de un producto con el precio maximo, se contara

    system("cls");

    for(int i=0; i<length; i++)
    {
        if(lista[i].id != -1)//si tiene un producto cargado
        {
            if( indiceDelMasCaro==-1 || lista[i].precio > lista[indiceDelMasCaro].precio)
            {
                indiceDelMasCaro = i;
            }
        }
    }
    //y si no es mayor sino que igual?
    //recorrere el vector en contando precios equivalentes
    if(indiceDelMasCaro != -1)
    {
        for(int i=0; i<length; i++)
        {
            if(lista[i].id != -1)
            {
                if(lista[i].precio == lista[indiceDelMasCaro].precio)
                {
                    cantidadDeMaximos++;
                }
            }
        }
    }

    //bien, ya sé cuantos maximos tengo
    //if uno, muestro uno, if muchos limprimo en pantalla tambien
    if(cantidadDeMaximos==0)
    {
        printf("\n**La lista estaba vacia\n");
    }
    else if (cantidadDeMaximos==1)
    {
        //muestro normal
        printf("\n**El producto mas caro hallado fue:\n");
        mostrarProducto(lista[indiceDelMasCaro]);

    }
    else
    {
        printf("\n**Se hallO mAs de un producto con el precio mAximo\n.");
        for(int i=0; i<length; i++)
        {
            if(lista[i].precio == lista[indiceDelMasCaro].precio)
            {
                mostrarProducto(lista[i]);
            }
        }
    }

    system("pause");

    return 0;

}




/** \brief calcula el precio promedio de cada tipoProducto (IPHONE MAC IPAD ACCESORIOS) y lo informa
 *
 * \param lista[] eProducto
 * \param length int
 * \return int
 *
 */
int informarPrecioPromedioPorTipo(eProducto lista[], int length)
{
    /*estructura de mi matriz
    int contadorIphone contadorMac contadorIpad contadorAccesorios contadorDesconocidos
    float acumuladorIphone       acuMac      acuIpad         acuAccesorios   acuDesconocidos */
    char tipos[5][21]= {"Iphone", "Mac", "Ipad","accesorios", "desconocido"};
    int contadores[5]= {0,0,0,0,0};
    float acumuladores[5]= {0,0,0,0,0};
    float preciosPromedio[5]= {-1,-1,-1,-1,-1};

    /*ayuda memoria
    #define IPHONE 70
    #define MAC 71
    #define IPAD 72
    #define ACCESORIOS 73
    noHayDefine de Desconocidos
    */
    //primer for para cargar contador y acumulador
    for(int i=0; i<length; i++)
    {
        if(lista[i].id != -1)
        {

            switch(lista[i].codigoTipo)
            {
            case 70:
                contadores[0]++;
                acumuladores[0]+=lista[i].precio;
                break;
            case 71:
                contadores[1]++;
                acumuladores[1]+=lista[i].precio;
                break;
            case 72:
                contadores[2]++;
                acumuladores[2]+=lista[i].precio;
                break;
            case 73:
                contadores[3]++;
                acumuladores[3]+=lista[i].precio;
                break;
            default:
                contadores[4]++;
                acumuladores[4]+=lista[i].precio;
            }
        }
    }

    //segundo for para sacar promedio
    for(int i=0; i<5; i++)
    {
        if(contadores[i]>0)
        {
            preciosPromedio[i]= (float) acumuladores[i] / contadores[i];
        }

    }

    for(int i=0; i<5; i++)
    {
        if(preciosPromedio[i]==-1)
        {
            printf("\nNo hay productos del tipo %s", tipos[i]);
        }
        else
        {
            printf("\nEl precio promedio de producto tipo %s es %.1f ", tipos[i], preciosPromedio[i]);
        }
    }
    system("pause");
    return 0;

}




/** \brief
 *
 * \param lista[] eProducto
 * \param length int
 * \return int
 *
 */
int mostrarSubmenuInformes(eProducto lista[], int length)
{
    int opcion;


    while(opcion!=3)
    {
        system("cls");
        utn_getNumero(&opcion, "\n**Submenu de informes\n\n1-Informar el/los producto/s mas caro/s\n2-Informar precio promedio por tipo de producto\n3-Salir\nOpcion: ", "\n**ERROR: elija una opcion valida\n", 1, 3, 3);
        switch(opcion)
        {
        case 1:
            //informar mas caro
            system("cls");
            informarProductosMasCaros(lista, length);
            break;
        case 2:
            //precios promedio x tipo
            system("cls");
            informarPrecioPromedioPorTipo(lista, length);
            break;
        }
    }


    return 0;
}



/** \brief
 *
 * \param lista[] eProducto
 * \param length int
 * \return int
 *
 */
int ordenarListaPorTipo(eProducto lista[], int length)
{
    eProducto auxiliar;

    for(int i=0; i<length-1; i++)
    {
        for(int j=i+1; j<length; j++)
        {
            if(lista[i].id != -1 && lista[j].id != -1)
            {
                if (lista[i].codigoTipo > lista[j].codigoTipo)
                {
                    //hacer intercambio
                    auxiliar.id = lista[i].id;
                    strcpy(auxiliar.descripcion, lista[i].descripcion);
                    auxiliar.precio = lista[i].precio;
                    auxiliar.codigoTipo = lista[i].codigoTipo;
                    auxiliar.codigoNacionalidad = lista[i].codigoNacionalidad;

                    lista[i].id = lista[j].id;
                    strcpy(lista[i].descripcion, lista[j].descripcion);
                    lista[i].precio = lista[j].precio;
                    lista[i].codigoTipo = lista[j].codigoTipo;
                    lista[i].codigoNacionalidad = lista[j].codigoNacionalidad;

                    lista[j].id = auxiliar.id;
                    strcpy(lista[j].descripcion, auxiliar.descripcion);
                    lista[j].precio = auxiliar.precio;
                    lista[j].codigoTipo = auxiliar.codigoTipo;
                    lista[j].codigoNacionalidad = auxiliar.codigoNacionalidad;

                }
            }
        }
    }
    return 0;
}

int mostrarOrdenadoPorTipo(eProducto lista[], int length)
{
    ordenarListaPorTipo(lista, length);
    mostrarListadoDeProductos(lista, length);
    return 0;
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

    utn_getNumero(&opcion, "\n**Submenu de listado\n1-Listar productos\n2-Listar ordenado por precio\n3-Listar ordenado por descripcion\n4-Listar Ordenado por tipo producto\n5-Salir\nOpcion: ", "\n**ERROR: elija una opcion valida\n", 1, 5, 3);
    switch(opcion)
    {
    case 1:
        //listado normal
        mostrarListadoDeProductos(lista, length);
        break;
    case 2:
        //listar Ordenador x precio
        utn_getNumero(&subopcion, "\n**2-Listar ordenado por precio.\nIngrese 1 para orden creciente, 0 para orden decreciente: ", "\n**Error: valor invalido\n", 0, 1, 3);
        if ( ordenarPorPrecio(lista, length, subopcion) )
        {
            printf("\n**Se ordeno el listado por precio");
            system("pause");
            mostrarListadoDeProductos(lista, length);
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
            mostrarListadoDeProductos(lista, length);
        }
        else
        {
            printf("\n**NO Se ordeno el listado\n");
            system("pause");
        }
        break;
    case 4:
        mostrarOrdenadoPorTipo(lista, length);
        break;
    case 5:
        break;
    }

    return 0;
}

