#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "tp1.h"
#define limiteArrayMenu 1200

int main(void)
{
	int opcion;
	int resultadoMenu;

	float numeroA;
	float numeroB;
	char numeroAChar[15];
	char numeroBChar[15];

	int flagCalculo;
	int flagIngresoNumeroA;
	int flagIngresoNumeroB;
	int salir;

	char aResultadoSuma[15];
	char aResultadoResta[15];
	char aResultadoDivision[15];
	char aResultadoMultiplicacion[15];
	char aResultadoFactorialA[20];
	char aResultadoFactorialB[20];

	flagCalculo=-1;
	flagIngresoNumeroA=-1;
	flagIngresoNumeroB=-1;
	salir=-1;
	strncpy(numeroAChar,"x",sizeof(numeroAChar));
	strncpy(numeroBChar,"y",sizeof(numeroAChar));
	do
	{


		resultadoMenu=(tp1_pedirNumeroMensajeConMascaras(	&opcion,
															"\nIngrese la opcion deseada.\n\n"
															"1. Ingresar 1er operando (A=%s)\n"
															"2. Ingresar 2do operando (B=%s)\n"
															"3. Calcular todas las operaciones\n"
															"	a) Calcular la suma (A+B)\n"
															"	b)Calcular la resta (A-B)\n"
															"	c) Calcular la division (A/B)\n"
															"	d) Calcular la multiplicacion (A*B)\n"
															"	e) Calcular el factorial (A!)\n"
															"4. Informar resultados\n"
															"5. Salir\n\n",
															numeroAChar,
															numeroBChar,
															"\nError, la opcion ingresada es invalida.\n",
															1,
															5,
															2));
		if(!resultadoMenu)
		{
			switch(opcion)
			{
				case 1:
					tp1_pedirNumeroFloat(&numeroA,"\n\nIngrese primer numero: ",
										"\n\nError, el numero ingresado es invalido.\n\n",-32000,32000,2);
					__fpurge(stdin);
					snprintf(numeroAChar,sizeof(numeroAChar),"%.2f",numeroA);
					flagIngresoNumeroA=0;
					break;

				case 2:
					tp1_pedirNumeroFloat(&numeroB,"\n\nIngrese segundo numero: ",
										"\n\nError, el numero ingresado es invalido.\n\n",-32000,32000,2);
					sprintf(numeroBChar,"%.2f",numeroB);
					flagIngresoNumeroB=0;
					break;

				case 3:
					flagCalculo=0;
					break;

				case 4:
					if(!flagCalculo)
					{

						if(flagIngresoNumeroB || flagIngresoNumeroA)
						{
							printf("Deben ingresarse ambos operandos para mostrar resultados.\n");
						}
						else
						{
							tp1_validacionFunciones(tp1_sumaResultadoString(numeroA, numeroB, aResultadoSuma), 0,
																			"a) El resultado de A+B es: %s\n",
																			aResultadoSuma,"a) No se ha podido realizar la operacion\n");
							tp1_validacionFunciones(tp1_restaResultadoString(numeroA, numeroB, aResultadoResta), 0,
																			"b) El resultado de A-B es: %s\n",
																			aResultadoResta,"b) No se ha podido realizar la operacion\n");
							tp1_validacionFunciones(tp1_divisionResultadoString(numeroA, numeroB, aResultadoDivision), 0,
																				"c) El resultado de A/B es: %s\n", aResultadoDivision,
																				"c) No se a ingresado divisor.\n");
							tp1_validacionFunciones(tp1_multiplicacionResultadoString(numeroA, numeroB, aResultadoMultiplicacion),0,
																				"d) El resultado de A*B es: %s\n",aResultadoMultiplicacion,
																				"d) No se ha podido realizar la operacion\n");
							tp1_validacionFunciones(tp1_factorialResultadoString(numeroA, aResultadoFactorialA,20),0,
																				"e) El factorial de A es: %s",	aResultadoFactorialA,
																				"e) A: Solamente los numeros enteros >= 1 son factorizables");
							tp1_validacionFunciones(tp1_factorialResultadoString(numeroB, aResultadoFactorialB,20),0,
																				" y El factorial de B es: %s\n",aResultadoFactorialB,
																				" y B: Solamente los numeros enteros >= 1 son factorizables. \n ");
						}
					}
				else
				{
					printf("\n\nDebe realizarse las operaciones para mostrarse resultados.\n\n");
				}
					break;
				case 5:
					salir=0;
					break;
			}
		}
		else
		{
			printf("\nIngreso demasiadas veces valores invalidos.");
			break;
		}
	}while(salir);
	return EXIT_SUCCESS;
}
