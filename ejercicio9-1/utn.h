#ifndef UTN_H_INCLUDED
#define UTN_H_INCLUDED

//OMG! El caos en busca del orden. Un jueves 8 de abril de 2021.
//Domingo 11/4. Cruda mañana. Dolor Estomacal.

//-----------TODES USAN myGets()
//clave para no rebasar el buffer
int myGets(char* cadena, int longitud);

//------------------

//Pedir INT POSITIVO--//no acepta float ni negativos
int esNumerica(char* cadena);
int getInt(int* pResultado);
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);

//Pedir INT NEGATIVO/POSITIVO--//no acepta float
int esNumericaConSigno(char* cadena);
int getIntConSigno(int* pResultado);
int utn_getNumeroConSigno(int* pResultado,char* mensaje, char* mensajeError,int minimo, int maximo, int reintentos);
//-------------

//Pedir REAL: Float positivo/negativo
int esNumeroReal(char* str);
int getFloatConSigno(float* pResultado);
int utn_getNumeroReal(float* pResultado,char* mensaje, char* mensajeError,float minimo, float maximo, int reintentos);
//-------------------

//Ingresar TEXTO
int utn_getTexto(char* pTexto,int tamBuffer, char* mensaje);

//ingresar CHAR
int utn_getLetra(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos);


//TELEFONO--------------------
//usada por getTelefono()
int esTelefono(char str[]);
int getTelefono(char* pResultado);
int utn_getTelefono(char* pResultado,char* mensaje, char* mensajeError, int reintentos);
//--------------------;



#endif // UTN_H_INCLUDED
