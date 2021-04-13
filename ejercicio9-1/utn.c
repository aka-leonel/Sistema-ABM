/**
 * Biblioteca de ingreso de datos
 * Autor: El Joven Leonel Godoy
 * Abril de 2021
 * Programado en Codeblocks, en windows10
 * NOTA: programa aun sin terminar
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
 * un máximo de 'longitud - 1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamaño de cadena
 * \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
*
*/
static int myGets(char* cadena, int longitud)
{
    int retorno=-1;
    if(cadena!= NULL && longitud > 0 && fgets(cadena, longitud, stdin)==cadena)
    {
        fflush(stdin);//or __fpurgue
        if(cadena[strlen(cadena)-1] =='\n')
        {
            cadena[strlen(cadena)-1]='\0';
        }
        retorno=0;

    }
    return retorno;
}

//----------------------

//FUNCIONES PARA PEDIR ENTERO POSITIVO
//usada por getInt()
/**
* \brief Verifica si la cadena ingresada es numerica
* \param cadena Cadena de caracteres a ser analizada
* \return Retorna 1 (vardadero) si la cadena es numerica y 0 (falso) si no lo es
*/
static int esNumerica(char* cadena)
{
    int i=0;
    int retorno=1;
    if(cadena!=NULL && strlen(cadena) >0)
    {
        while(cadena[i] != '\0')
        {
            if(cadena[i] <'0' || cadena[i] >'9')
            {
                retorno=0;
                break;
            }
            i++;
        }
    }
    return retorno;
}

//utiliza myGets() y esNumerica()
//es usada por utn_getNumero()
/**
 * \brief Verifica si la cadena ingresada es numerica
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no
*
*/
static int getInt(int* pResultado)
{
    int retorno=-1;
    char buffer[64];
    myGets(buffer, sizeof(buffer));

    if(pResultado != NULL)
    {
        if(esNumerica(buffer))
        {
            *pResultado=atoi(buffer);
            retorno=0;
        }
    }

    return retorno;
}


//esta funcion utiliza getInt(), quien usa mygets() y esNumerica()
/**
 * \brief Solicita un numero Natural Positivo (x>=0) al usuario
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es el numero maximo a ser aceptado
 * \param maximo Es el minimo minimo a ser aceptado
 * \return Retorna 0(exito) si se obtuvo el numero y -1(error) si no
 */
int utn_getNumero(int* pResultado,
                  char* mensaje,
                  char* mensajeError,
                  int minimo,
                  int maximo,
                  int reintentos)
{
    //version del apunte

    int bufferInt;
    int retorno=-1;

    if(minimo < 0)
    {
        retorno=-1;
        printf("\nAdvertencia: esta funcion solo trabaja con valores positivos enteros.");
        printf("\nPlease, try usign utn_getNumeroReal() \n");
        system("pause");
    }
    else
    {
        do
        {
            reintentos--;
            printf("%s", mensaje);
            if(getInt(&bufferInt)==0)
            {
                if(bufferInt >= minimo && bufferInt <= maximo)
                {
                    *pResultado = bufferInt;
                    retorno=0;
                    break;
                }
            }
            printf("%s", mensajeError);
        }
        while(reintentos>-1);
    }

    return retorno;
}

//FIN FUNCIONES PARA PEDIR ENTERO POSITIVO
//------------------------------------
//FUNCIONES PARA PEDIR ENTERO (NEGATIVO&POSITIVO)
//usada por getIntConSigno()
/** \brief Verifica si la cadena ingresada es INT, acepta NEGATIVO. NO ACEPTA FLOAT, SOLO INT
 * \param cadena a ser analizada
 * \return Retorna 1(verdadero) si la cadena es numerica y 0(falso) si no lo es
 */
static int esNumericaConSigno(char* cadena)
{
    int retorno=1;
    int i=0;
    if(cadena!=NULL && strlen(cadena)>0)
    {
        if(cadena[0]== '-')//bien, sigo
        {
            i++;
        }
        while(cadena[i]!='\0')
        {
            if(cadena[i] < '0' || cadena[i]>'9')
            {
                retorno = 0;
                break;
            }
            i++;
        }
    }
    return retorno;
}
//utiliza myGets() y esNumericaConSigno()
/** \brief es usada por utn_getNumeroConSigno(). usa myGets() y esNumericaConSigno()
 * \param pResultado puntero al espacio de memoria donde se deja el resultado de la funcion
 * \return Retorna 0 (exito) si se obtiene un numero entero y -1(error) si no
 */
int getIntConSigno(int* pResultado)
{
    int retorno=-1;
    char buffer[64];

    if(pResultado != NULL)
    {
        if(myGets(buffer, sizeof(buffer))==0 && esNumericaConSigno(buffer))
        {
            *pResultado= atoi(buffer);
            retorno=0;
        }
    }
    return retorno;
}
/**
 * \brief Solicita un numero Entero(+/-)
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es el numero maximo a ser aceptado
 * \param maximo Es el minimo minimo a ser aceptado
 * \return Retorna 0(exito) si se obtuvo el numero y -1(error) si no
 */
int utn_getNumeroConSigno(int* pResultado,char* mensaje, char* mensajeError,int minimo, int maximo, int reintentos)
{
    int bufferInt;
    int retorno=-1;

    while(reintentos>0)
    {
        reintentos--;
        printf("%s", mensaje);

        //llamado a getInt()
        if(getIntConSigno(&bufferInt)==0)
        {
            if(bufferInt >= minimo && bufferInt <= maximo)
            {
                *pResultado = bufferInt;
                retorno =0;
                break;
            }
        }
        printf("%s",mensajeError);
    }
    return retorno;
}
//FIN FUNCIONES ENTERO (+/-)

//-------------------------

//FUNCIONES PARA PEDIR REAL: FLOTANTE(+/-)

/**
 * \brief Verifica si el string recibido es numero REAL (float +/-)
 * \param puntero a cadena a ser analizada
 * \return 1(exito) si es numero real y 0(error) si no lo es, si se insertó mas de un punto o mas de un signo +/-
 *
 */
int esNumeroReal(char* str)
{
    int retorno=1;
    int i=0;
    int cantidadPuntos=0;
    if(str!=NULL && strlen(str)>0)
    {
        if(str[0] == '-' || str[0] == '+')
        {
            i++;
        }
        while(str[i] != '\0')
        {
            if (str[i] == '.')
            {
                cantidadPuntos++;
                i++;
                continue;
            }
            else if(str[i] < '0' || str[i] > '9')
                retorno = 0;
            i++;
        }
        if(cantidadPuntos>1)
        {
            retorno=0;
        }
    }
    return retorno;
}


//usa myGets() y esNumeroReal()
//es usada por utn_getNumeroReal()
/** \brief es usada por utn_getNumeroReal(), verifica si la cadena ingresada es numerica REAL, Float+/-
 * \param pResultado puntero al espacio de memoria donde se deja el resultado de la funcion
 * \return Retorna 0 (exito) si se obtiene un numero entero y -1(error) si no
 */
int getFloatConSigno(float* pResultado)
{
    int retorno=-1;
    char buffer[64];

    if(pResultado != NULL)
    {
        if(myGets(buffer, sizeof(buffer))==0 && esNumeroReal(buffer))
        {
            *pResultado= atof(buffer);
            retorno=0;
        }
    }
    return retorno;
}

//usa getFloatConSigno()
/**
 * \brief Solicita un numero REAL (float +/-) al usuario
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es el numero maximo a ser aceptado
 * \param maximo Es el minimo minimo a ser aceptado
 * \return Retorna 0(exito) si se obtuvo el numero y -1(error) si no
 */
int utn_getNumeroReal(float* pResultado,char* mensaje, char* mensajeError,float minimo, float maximo, int reintentos)
{
    float bufferFloat;
    int retorno=-1;

    do
    {
        reintentos--;
        printf("%s", mensaje);

        //llamado a getFloat()
        if(getFloatConSigno(&bufferFloat)==0)
        {
            if(bufferFloat >= minimo && bufferFloat <= maximo)
            {
                *pResultado = bufferFloat;
                retorno =0;
                break;
            }
        }
        printf("%s",mensajeError);
    }while(reintentos>0);

    return retorno;
}
//FIN FUNCIONES PARA FLOAT


//FUNCION p/ SOLICITAR TEXTO. usa myGets()

/** \brief solicita el ingreso de texto
 *
 * \param puntero a espacio donde almacenar array de char
 * \param tamanio del buffer, se copiara n-1 caracteres
 * \param mensaje para solicitar el texto
 * \return
 *
 */

int utn_getTexto(char* pTexto,int tamBuffer, char* mensaje)
{
    int retorno=-1;
    char buffer[tamBuffer];
    if(pTexto != NULL && tamBuffer>0)
    {
        printf("\n%s", mensaje);
        if(myGets(buffer,sizeof(buffer))==0)
        {
            //pTexto = buffer;//que boludo...
            strcpy(pTexto, buffer);
            retorno = 1;
        }
    }
    return retorno;
}

//FUNCION PARA PEDIR LETRA
/** \brief solicita el ingreso de un char
 *
 * \param
 * \param
 * \return
 *
 */
int utn_getLetra(char* pResultado,
                 char* mensaje,
                 char* mensajeError,
                 char minimo,
                 char maximo,
                 int reintentos)
{
    char bufferChar;
    int retorno=-1;

    if(pResultado != NULL && mensaje != NULL && mensajeError != NULL)
    {
        while(reintentos>0)
        {
            reintentos--;
            printf("%s", mensaje);
            scanf("%c",&bufferChar);
            if(bufferChar >= minimo && bufferChar <= maximo)
            {
                *pResultado = bufferChar;
                retorno =0;
                break;
            }

            printf("%s",mensajeError);
        }
    }

    return retorno;
}

//FUNCIONES PARA PEDIR TELEFONO
/**
 * \brief Verifica si el valor recibido contiene solo números y '-'
 * \param cadena a ser analizada
 * \return 1(exito) si contiene solo numeros, espacios y hasta dos(2) guiones, else retorna 0(error)
 *
 */
int esTelefono(char str[])
{
    int retorno=1;
    int i=0;
    int contadorGuiones=0;
    while(str[i] != '\0')
    {
        if((str[i] != ' ') && (str[i] != '-') && (str[i] < '0' || str[i] > '9'))
            retorno = 0;
        if(str[i] == '-')
            contadorGuiones++;
        i++;
    }
    if(contadorGuiones > 2)
    {
        retorno = 0;
    }
    return retorno;
}

//utiliza myGets() y esTelefono()
//es usada por utn_getTelefono()
/** \brief funcion accesoria usada por utn_getTelefono()
 * \param pResultado puntero al espacio de memoria donde se deja el resultado de la funcion
 * \return Retorna 0 (exito) si se obtiene un telefono, -1(error)
 */
static int getTelefono(char* pResultado)
{
    int retorno=-1;
    char buffer[64];

    if(pResultado != NULL)
    {
        if(myGets(buffer, sizeof(buffer))==0 && esTelefono(buffer))
        {
            strcpy(pResultado, buffer);
            retorno=0;
        }
    }
    return retorno;
}

//usa getTelefono()
/** \brief solicita al usuario un numero de telefono(acepta espacios, hasta dos(2) guiones'-')
 *
 * \param puntero a espacio donde almacenar el telefono
 * \param mensaje para pedir telefono
 * \param mensaje de error
 * \param reintentos
 * \return
 *
 */
int utn_getTelefono(char* pResultado,char* mensaje, char* mensajeError, int reintentos)
{

    int retorno=-1;//fracaso
    char bufferChar[64];
    while(reintentos>0)
    {
        reintentos--;
        printf("%s", mensaje);

        if(getTelefono(bufferChar)==0)
        {
            //*pResultado = bufferChar;
            strcpy(pResultado, bufferChar);
            retorno =0;
            system("pause");
            break;
        }
        printf("%s",mensajeError);
    }
    return retorno;
}

//FIN FUNCIONES TELEFONO


