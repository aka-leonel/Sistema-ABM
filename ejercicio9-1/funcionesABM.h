#ifndef FUNCIONESABM_H_INCLUDED
#define FUNCIONESABM_H_INCLUDED

typedef struct
{
    int id;     //if id==-1 --> IS EMPTY
    char descripcion[64];
    int codigoNacionalidad;
    int codigoTipo;
    float precio;
} eProducto;

int inicializarListado(eProducto lista[], int length);
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
int altaProducto(eProducto lista[], int length);

//BAJA producto-->poner id=-1
int bajaProducto(eProducto lista[], int length);

//MODIFICA producto
int modificarProducto(eProducto lista[], int length);

//MenuListados
int mostrarSubmenuListados(eProducto lista[], int length);

//ordenamientos
int ordenarPorPrecio(eProducto lista[], int length, int ordenCreciente);
int ordenarPorDescripcion(eProducto lista[], int length, int ordenCreciente);



#endif // FUNCIONESABM_H_INCLUDED
