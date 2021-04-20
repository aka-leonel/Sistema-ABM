#ifndef FUNCIONESABM_H_INCLUDED
#define FUNCIONESABM_H_INCLUDED
/*
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


typedef struct
{
    int idTipo;
    char descripcionTipo[64];
}eTipoProducto;


typedef struct
{
    int idNacionalidad;
    char descripcionNacionalidad[64];
}eNacionalidad;


typedef struct
{
    int id;     //if id==-1 --> IS EMPTY
    char descripcion[64];
    int codigoNacionalidad;
    int codigoTipo;
    float precio;
} eProducto;


int inicializarListadoProductos(eProducto lista[], int length);
int inicializarListadoTipos(eTipoProducto listaTipos[], int length);
int inicializarListadoNaciones(eNacionalidad listaNaciones[], int length);

int hardcodearListado(eProducto lista[], int length, int* nextId);
int mostrarMenu();

int mostrarProducto(eProducto x);
int mostrarListadoDeProductos(eProducto lista[], int length);

//funciones 'traductoras'
int pasarDeCodigoAPais(int codigoRecibido, char* pResultado);
int pasarDeCodigoATipoProducto(int codigoRecibido, char* pResultado);

//ALTA producto
int buscarLibre(eProducto lista[], int length);//busca lugar
int buscarId(eProducto lista[], int length, int idBuscado);//pide id y se fija que no este repetido
int elegirPaisDeOirigen();
int elegirTipoDeProducto();
int altaProducto(eProducto lista[], int length, int* nextId);

//BAJA producto-->poner id=-1
int bajaProducto(eProducto lista[], int length);

//MODIFICA producto
int modificarProducto(eProducto lista[], int length);

//SubMenus
int mostrarSubmenuListados(eProducto lista[], int length);


//ordenamientos
int ordenarPorPrecio(eProducto lista[], int length, int ordenCreciente);
int ordenarPorDescripcion(eProducto lista[], int length, int ordenCreciente);
int mostrarOrdenadoPorTipo(eProducto lista[], int length);
int ordenarListaPorTipo(eProducto lista[], int length);



//menu de informes
int mostrarSubmenuInformes(eProducto lista[], int length);
int informarProductosMasCaros(eProducto lista[], int length);
int informarPrecioPromedioPorTipo(eProducto lista[], int length);

//int contarPorTipo(eProducto lista[], int length);
//pendientes
//int informarTipoProductoMasElaborado(eProducto lista[], int length);


#endif // FUNCIONESABM_H_INCLUDED
