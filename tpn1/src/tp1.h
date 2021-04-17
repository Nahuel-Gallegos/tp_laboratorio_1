#ifndef TP1_H_
#define TP1_H_

int tp1_pedirNumeroInt(int* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos);
int tp1_pedirNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos);
int tp1_pedirNumeroMensajeConMascaras(	int* pResultado,char* mensaje,char* mascara1,char* mascara2,char* mensajeError,int minimo,int maximo,int reintentos);
int tp1_factorialResultadoString(float primerInt,char resultado[],int limiteResultado);
int tp1_divisionResultadoString(float primerInt,float segundoInt,char resultado[]);
int tp1_multiplicacionResultadoString(float primerInt,float segundoInt,char resultado[]);
int tp1_sumaResultadoString(float primerInt,float segundoInt,char* resultado);
int tp1_restaResultadoString(float primerFloat,float segundoFloat,char* resultado);
void tp1_validacionFunciones(int funcion,int valorTrue, char* mensajeTrue,char* mascaraTrue,char*mensajeFalse);
#endif /* TP1_H_ */
