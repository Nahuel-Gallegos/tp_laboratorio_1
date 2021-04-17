#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "tp1.h"



static int esNumericoInt(char* cadena);
static int esNumericoFloat(char* cadena);
static int misGets(char* cadena,int longitud);
static int getInt(int* pResultado);
static int getFloat(float* pResultado);


/**
* \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en
* 		 'cadena' un máximo de 'longitud - 1' caracteres.
* \param char* cadena: Puntero al espacio de memoria donde se copiara la cadena obtenida.
* \param int longitud: longitud de array cadena.
* \param return retorno == 0; funcion VALIDA.
* 		 return retorno == -1; funcion INVALIDA.
*/
static int misGets(char* cadena,int longitud)
{
	int retorno = -1;
	if(cadena!=NULL && longitud>0 && fgets(cadena,longitud,stdin)==cadena)
	{
		__fpurge(stdin);
		if(cadena[strnlen(cadena,sizeof(cadena))-1]=='\n')
		{
			cadena[strnlen(cadena,sizeof(cadena))-1]= '\0';
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Valida si cadena es un valor numerico entero.
 * \param char* cadena: cadena de caracateres a ser analizada.
 * \param int i: es el contador con el cual se recorrera cadena.
 * \param int flagPrimerNumero: bandera que marca primera iteracion recorrida.
 * \param return retorno == 0; funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
static int esNumericoInt(char* cadena)
{
	int retorno = 0;
	int i=0;
	int flagPrimerNumero=-1;
	if(cadena[i]=='-' || cadena[i]=='+')
	{
		i=1;
	}
	for(;cadena[i]!='\0';i++)
	{
		if(flagPrimerNumero)
		{
			if(cadena[i]<'0' || cadena [i]>'9')
			{
				retorno = -1;
				break;
			}
			flagPrimerNumero=0;
		}
		if((cadena[i]<'0' || cadena [i]>'9') && (cadena[i]=='.' && (cadena[i+1]!='0' || cadena[i+2]!='0')))
			{
			retorno=-1;
			break;
			}
	}
	return retorno;
}

/**
 * \brief Valida si cadena ingresada es un valor numerico decimal.
 * \param char* cadena: Array con valor string dentro de si.
 * \param int i: Es el contador con el cual se recorrera el array cadena.
 * \param int condadorComa: Cuenta cantidad de '.' se encuentran en cadena.
 * \param int flagPrimerNumero: bandera que marca primera iteracion recorrida.
 * \param return retorno == 0; funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
static int esNumericoFloat(char* cadena)
{
	int retorno = 0;
	int i=0;
	int contadorComa=0;
	int flagPrimerNumero=-1;
	if(cadena[i]=='-' || cadena[i]=='+')
	{
		i=1;
	}
	for(;cadena[i]!='\0';i++)
	{
		if(flagPrimerNumero)
		{
			if(cadena[i]<'0' || cadena [i]>'9')
			{
				retorno = -1;
				break;
			}
			flagPrimerNumero=0;
		}
		if(cadena[i]=='.')
			contadorComa++;
		if((cadena[i]<'0' || cadena [i]>'9') && (cadena[i]=='.' && contadorComa>1))
		{
			retorno = -1;
			break;
		}
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es numerica entera.
 * \param int* pResultado: Puntero a direccion de memoria de variable tipo int destinada a la cadena ingresada si es valida.
 * \param char buffer[]: Array donde se guardara y validara los caracteres ingresados por el usuario.
 * \param return retorno == 0; funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[300];

	__fpurge(stdin);
	if(!misGets(buffer,sizeof(buffer)) && !esNumericoInt(buffer))
	{
		retorno = 0;
		*pResultado = atoi(buffer);
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es numerica decimal.
 * \param char buffer[]: Array donde se guardara y validara los caracteres ingresados por el usuario.
 * \param return retorno == 0; funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
static int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[300];

	__fpurge(stdin);
	if(misGets(buffer,sizeof(buffer))==0 && esNumericoFloat(buffer)==0)
	{
		retorno = 0;
		*pResultado = atof(buffer);
	}
	return retorno;
}

/**
 * \brief Pide un numero entero al usuario, valida si esta dentro del rango solicitado,
 * 		y reintenta de no estar dentro del rango.
 * \param int* pResultado: Puntero a la direccion de memoria de la variable tipo int destinada a ser escrita por el usuario.
 * \param char* mensaje: Puntero a la direccion de memoria de la cadena de caracteres que se mostrara
 * 						 antes de que el usuario ingrese pResultado
 * \param char* mensajeError: Puntero a la direccion de memoria de la cadena de caracteres que se mostrara
 * 							  si el usuario ingresa un valor diferente al tipo int.
 * \param int minimo: Numero minimo a ser aceptado como valido.
 * \param int maximo: Numero maximo a ser aceptado como valido.
 * \param int reintentos: Cantidad de reintentos antes de devolver INVALIDA la funcion
 * \param int bufferInt: Variable auxiliar que se utilizara para validar lo ingresado por el usuario antes
 * 						 de ser guardado en pResultado.
 * \param return retorno == 0; funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
int tp1_pedirNumeroInt(int* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos)
{
	int retorno = -1;
	int bufferInt;

	if(pResultado !=NULL && mensaje !=NULL && mensajeError!=NULL)
	{
		if(minimo<maximo && reintentos>=0)
		{
			retorno =-2;
			printf("%s",mensaje);
			do
			{
				__fpurge(stdin);
				if(getInt(&bufferInt)==0 && bufferInt>=minimo && bufferInt<=maximo)
				{
					retorno = 0;
					*pResultado = bufferInt;
					break;
				}
				printf("%s",mensajeError);
				reintentos--;
			}while(reintentos>=0);
		}
	}
	return retorno;
}

/**
 * \brief Pide un numero con decimal al usuario, valida si esta dentro del rango solicitado,
 * 		  y reintenta de no estar dentro del rango.
 * \param int* pResultado: Puntero a la direccion de memoria de la variable tipo int destinada a ser escrita por el usuario.
 * \param char* mensaje: Puntero a la direccion de memoria de la cadena de caracteres que se mostrara
 * 						 antes de que el usuario ingrese pResultado
 * \param char* mensajeError: Puntero a la direccion de memoria de la cadena de caracteres que se mostrara
 * 							  si el usuario ingresa un valor diferente al tipo int.
 * \param int minimo: Numero minimo a ser aceptado como valido.
 * \param int maximo: Numero maximo a ser aceptado como valido.
 * \param int reintentos: Cantidad de reintentos antes de devolver INVALIDA la funcion
 * \param int bufferInt: Variable auxiliar que se utilizara para validar lo ingresado por el usuario antes
 * 						 de ser guardado en pResultado.
 * \param return retorno == 0; funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
int tp1_pedirNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos)
{
	int retorno = -1;
	float bufferFloat;

	if(pResultado !=NULL && mensaje !=NULL && mensajeError!=NULL)
	{
		if(minimo<maximo && reintentos>=0)
		{
			retorno =-2;
			printf("%s",mensaje);
			do
			{
				__fpurge(stdin);
				if(getFloat(&bufferFloat)==0 && bufferFloat>=minimo && bufferFloat<=maximo)
				{
					retorno = 0;
					*pResultado = bufferFloat;
					break;
				}
				printf("%s",mensajeError);
				reintentos--;
			}while(reintentos>=0);
		}
	}
	return retorno;
}

/**
 * \brief Valida y suma dos numeros tipo float y devuelve el resultado grabado en una cadena de caracteres.
 * \param float primerFloat: Numero tipo float a sumar.
 * \param float segundoFloat: Numero tipo float a sumar.
 * \param char resultado[]: Resultado de la suma del primerFloat y segundoFloat grabado en cadena de caracteres.
 * \param char bufferA[]: Cadena de caracteres donde se grabara el valor del primerFloat para validarlo.
 * \param char bufferB[]: Cadena de caracteres donde se grabara el valor del segundoFloat para validarlo.
 * \param float suma: Resultado de la suma del primerFloat y el segundoFloat.
 * \param return retorno == 0; 	funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
int tp1_sumaResultadoString(float primerFloat,float segundoFloat,char resultado[])
{
	int retorno =-1;
	float suma;
	char bufferA[10];
	char bufferB[10];

		if(resultado!=NULL)
		{
		snprintf(bufferA,sizeof(bufferA),"%.2f",primerFloat);
		snprintf(bufferB,sizeof(bufferB),"%.2f",segundoFloat);
		if(!esNumericoFloat(bufferA) && !esNumericoFloat(bufferB))
		{
			suma = primerFloat + segundoFloat;
			snprintf(resultado,sizeof(&resultado),"%.2f",suma);
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief Valida y suma dos numeros tipo float y devuelve el resultado grabado en una cadena de caracteres.
 * \param float primerFloat: Numero tipo float a restar.
 * \param float segundoFloat: Numero tipo float a restar.
 * \param char resultado[]: Resultado de la resta del primerFloat y segundoFloat grabado en cadena de caracteres.
 * \param char bufferA[]: Cadena de caracteres donde se grabara el valor del primerFloat para validarlo.
 * \param char bufferB[]: Cadena de caracteres donde se grabara el valor del segundoFloat para validarlo.
 * \param float resta: Resultado de la resta del primerFloat y el segundoFloat.
 * \param return retorno == 0; 	funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
int tp1_restaResultadoString(float primerFloat,float segundoFloat,char resultado[])
{
	int retorno =-1;
	float resta;
	char bufferA[10];
	char bufferB[10];

		if(resultado!=NULL)
		{
		snprintf(bufferA,sizeof(bufferA),"%.2f",primerFloat);
		snprintf(bufferB,sizeof(bufferB),"%.2f",segundoFloat);
		if(!esNumericoFloat(bufferA) && !esNumericoFloat(bufferB))
		{
		resta = primerFloat - segundoFloat;
		snprintf(resultado,sizeof(&resultado),"%.2f",resta);
		retorno = 0;
		}
	}


	return retorno;
}

/**
 * \brief Valida y multiplica dos numeros tipo float y devuelve el resultado grabado en una cadena de caracteres.
 * \param float primerFloat: Numero tipo float a multiplicar.
 * \param float segundoFloat: Numero tipo float a multiplicar.
 * \param char resultado[]: Resultado de la multiplicacion del primerFloat y segundoFloat grabado en cadena de caracteres.
 * \param char bufferA[]: Cadena de caracteres donde se grabara el valor del primerFloat para validarlo.
 * \param char bufferB[]: Cadena de caracteres donde se grabara el valor del segundoFloat para validarlo.
 * \param float multiplicacion: Resultado de la multiplicacion del primerFloat y el segundoFloat.
 * \param return retorno == 0; 	funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
int tp1_multiplicacionResultadoString(float primerFloat,float segundoFloat,char resultado[])
{
	int retorno =-1;
	float multiplicacion;
	char bufferA[10];
	char bufferB[10];

		if(resultado!=NULL)
		{
		snprintf(bufferA,sizeof(bufferA),"%.2f",primerFloat);
		snprintf(bufferB,sizeof(bufferB),"%.2f",segundoFloat);
		if(!esNumericoFloat(bufferA) && !esNumericoFloat(bufferB))
		{
		multiplicacion = primerFloat * segundoFloat;
		snprintf(resultado,sizeof(&resultado),"%.2f",multiplicacion);
		retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief Valida y divide dos numeros tipo float y devuelve el resultado grabado en una cadena de caracteres.
 * \param float primerFloat: Numero tipo float a dividir.
 * \param float segundoFloat: Numero tipo float a dividir.
 * \param char resultado[]:	Resultado de la division del primerFloat y segundoFloat grabado en cadena de caracteres.
 * \param char bufferA[]: Cadena de caracteres donde se grabara el valor del primerFloat para validarlo.
 * \param char bufferB[]: Cadena de caracteres donde se grabara el valor del segundoFloat para validarlo.
 * \param float division: Resultado de la division del primerFloat y el segundoFloat.
 * \param return retorno == 0; 	funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
int tp1_divisionResultadoString(float primerFloat,float segundoFloat,char resultado[])
{
	int retorno =-1;
	float division;
	char bufferA[10];
	char bufferB[10];

	if(resultado!=NULL)
	{
		snprintf(bufferA,sizeof(bufferA),"%.2f",primerFloat);
		snprintf(bufferB,sizeof(bufferB),"%.2f",segundoFloat);
		if(segundoFloat!=0 && !esNumericoFloat(bufferA) && !esNumericoFloat(bufferB))
		{
			division = primerFloat/ segundoFloat;
			sprintf(resultado,"%.2f",division);
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief Valida y realiza el factorial de un numero tipo float, valida que sus decimales sean 0 y
 * 		 devuelve el resultado grabado en una cadena de caracteres.
 * \param float floatIngresado:	Numero tipo float a factorizar.
 * \param char resultado[]: Resultado de la factorizacion grabada en cadena de caracteres.
 * \param char buffer[]: Cadena de caracteres donde se grabara el valor del floatIngresado para validarlo.
 * \param long long factorial: Resultado de la division del primerFloat y el segundoFloat.
 * \param return retorno == 0; 	funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
int tp1_factorialResultadoString(float floatIngresado,char resultado[],int limiteResultado)
{
	int retorno =-1;
	long long factorial=1;
	char buffer[100];
	snprintf(buffer,sizeof(buffer),"%.2f",floatIngresado);
	if(floatIngresado>0 && resultado!=NULL && !esNumericoInt(buffer))
	{
		while(floatIngresado>1)
		{
			factorial = factorial* floatIngresado;
			floatIngresado--;
		}

		if(factorial>=1)
		{
			__fpurge(stdin);
			snprintf(resultado,limiteResultado,"%lld",factorial);
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief 	Imprime un mensaje que contiene 2 mascaras, pide un numero entero al usuario, valida si
 * 			esta dentro del rango solicitado, y reintenta de no estar dentro del mismo.
 * \param int* pResultado: Puntero a la direccion de memoria de la variable tipo int destinada a ser escrita por el usuario.
 * \param char* mensaje: Puntero a la direccion de memoria de la cadena de caracteres que se mostrara
 * 						 antes de que el usuario ingrese pResultado
 * char* mascara1:Puntero a direccion de memoria de cadena de caracteres a reemplazar el espacio de la primer mascara
 * 				  ubicada en mensaje.
 * char* mascara2: Puntero a direccion de memoria de cadena de caracteres a reemplazar el espacio de la segunda mascara
 * 				   ubicada en mensaje.
 * \param char* mensajeError: Puntero a la direccion de memoria de la cadena de caracteres que se mostrara
 * 							  si el usuario ingresa un valor diferente al tipo int.
 * \param int minimo: Numero minimo a ser aceptado como valido.
 * \param int maximo: Numero maximo a ser aceptado como valido.
 * \param int reintentos: Cantidad de reintentos antes de devolver INVALIDA la funcion
 * \param int bufferInt: Variable auxiliar que se utilizara para validar lo ingresado por el usuario antes
 * 						 de ser guardado en pResultado.
 * \param return retorno == 0; funcion VALIDA.
 * 		  return retorno == -1; funcion INVALIDA.
 */
int tp1_pedirNumeroMensajeConMascaras(	int* pResultado,char* mensaje,char* mascara1,char* mascara2,
										char* mensajeError,int minimo,int maximo,int reintentos)
{
	int retorno = -1;
	int bufferInt;

	if(pResultado !=NULL && mensaje!=NULL && mascara1!=NULL && mascara2!=NULL && mensajeError!=NULL)
	{
		if(minimo<maximo && reintentos>=0)
		{
			retorno =-2;
			printf(mensaje,mascara1,mascara2);
			do
			{
				__fpurge(stdin);
				if(getInt(&bufferInt)==0 && bufferInt>=minimo && bufferInt<=maximo)
				{
					retorno = 0;
					*pResultado = bufferInt;
					break;
				}
				printf("%s",mensajeError);
				reintentos--;
			}while(reintentos>=0);
		}
	}
	return retorno;
}

/**
 * \brief 	Valida funciones, imprime un mensaje de ser VALIDA con su respectiva mascara o
 * 			imprime otro mensaje de ser INVALIDA.
 * \param int funcion: Valor resultante de la operacion realizada por una funcion.
 * \param int valorTrue: Numero correspondiente al valor Valido que se tomara para funcion.
 * \param char* mensajeTrue: Mensaje que retorna si funcion es Valido.
 * \param char* mascaraTrue:Puntero a direccion de memoria de cadena de caracteres a reemplazar el espacio de la mascara
 * 							ubicada en mensajeTrue.
 * \param char* mascaraFalse: Mensaje que retorna si funcion es Invalido.
 * \param return void: No retorna ningun valor.
 */
void tp1_validacionFunciones(int funcion,int valorTrue, char* mensajeTrue,char* mascaraTrue,char* mensajeFalse)
{
	if(funcion==valorTrue)
	{
		printf(mensajeTrue,mascaraTrue);
	}
	else
	{
		printf("%s",mensajeFalse);
	}
}
