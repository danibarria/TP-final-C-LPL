#include <stdio.h>
#include <string.h>
#include <libpq-fe.h>  /* Inclusion de la libreria de acceso a funcionalidad para manipular objetos y conectarse a PostgreSQL */
#include <time.h>
#include <malloc.h>

#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../../config/config.h"
#include "../orm/orm.h"
#include "utils.h"

#include "../../src/empleado/empleado.h"
#include "../../src/categoria/categoria.h"
#include "../../src/cliente/cliente.h"
#include "../../src/proveedor/proveedor.h"
#include "../../src/producto/producto.h"
#include "../../src/orden/orden.h"
#include "../../src/orden_det/orden_det.h"


#include "utils.h"
#include "../../config/config.h"

//#define MAXFECHA 17
 //Instancia que permite manipular conexion con el servidor
//-----------------------------------------------------------------------------------------------------------------------------------------------
char* rtrim(char* string, char junk)
{
    char* original = string + strlen(string);
    while(*--original == junk);
    *(original + 1) = '\0';
    return string;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
char** fStrSplit(char *str, const char *delimiters)
{
    char * token; 
    char **tokenArray;
    int count=0;
    token = (char *)strtok(str, delimiters); // Get the first token
    tokenArray = (char**)malloc(1 * sizeof(char*));
    tokenArray[0] = NULL;
    if (!token) {       
        return tokenArray;  
    } 
    while (token != NULL) { // While valid tokens are returned
        tokenArray[count] = (char*)strdup(token);
        //printf ("%s", tokenArray[count]);
        count++;
        tokenArray = (char **)realloc(tokenArray, sizeof(char *) * (count + 1));
        token = (char *)strtok(NULL, delimiters); // Get the next token
    }
    tokenArray[count] = NULL;  /* Terminate the array */
    return tokenArray;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
char* fStrJoin(char **str, const char *delimiters, int sz_opt)
{
    char *joinedStr;
    int i = 1, size=0;
    
    if(sz_opt!=0 ) 
    {
      size = sz_opt;
    }
    else
      size = strlen(str[0])+1;
    joinedStr = (char *)realloc(NULL, size);
    strcpy(joinedStr, str[0]);
    if (str[0] == NULL){
        return joinedStr;
    }
    while (i< size ){
        joinedStr = (char*)realloc(joinedStr, strlen(joinedStr) + strlen(str[i]) + strlen(delimiters) + 1);
        strcat(joinedStr, delimiters);
        strcat(joinedStr, str[i]);
        i++;
    }
    return joinedStr;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
PGconn * connectdb(char *servidor,char *port,char *base,char *usuario,char *password)
{
   PGconn *conn;
   /*Realizar la conexion al servidor*/
   conn = PQsetdbLogin(servidor, port, NULL,NULL, base,usuario,password);
   /*Consultar estado de la operacion de conexion*/

   if (PQstatus(conn) != CONNECTION_OK)
      fprintf(stderr, "La conexion a la Base de Datos ha fallado: %s", PQerrorMessage(conn) );               
   
   return conn;
 }
//-----------------------------------------------------------------------------------------------------------------------------------------------
void disconnectdb(PGconn * conn)
{   
   /*Cerrar conexion y liberar recurso de conexion con el servidor*/
   PQfinish(conn);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
char *getFecha()
{
     char *ffecha;
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     ffecha = malloc(sizeof(char)*MAXFECHA);
     snprintf( ffecha, MAXFECHA, "%d-%02d-%02d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
     return ffecha;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
char *getFechaHora()
{
     char *ffecha;
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     ffecha = malloc(sizeof(char)*MAXFECHA);
     snprintf( ffecha, MAXFECHA, "%d-%02d-%02d %02d:%02d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,tm.tm_hour, tm.tm_min);
     return ffecha;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void inicializarArregloInt(int *arreglo, int cantidad, int valor){
    int i;
    for(i = 0; i< cantidad; i++){
        arreglo[i] = valor;
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------

static char *itoa_simple_helper(char *dest, int i) {
  if (i <= -10) {
    dest = itoa_simple_helper(dest, i/10);
  }
  *dest++ = '0' - i%10;
  return dest;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------

char *itoa_simple(char *dest, int i) {
  char *s = dest;
  if (i < 0) {
    *s++ = '-';
  } else {
    i = -i;
  }
  *itoa_simple_helper(s, i) = '\0';
  return dest;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------

int startswith(const char *pre, const char *str) {
    size_t lenpre = strlen(pre), lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
void prepararConsulta(char** consulta, char* valor, char* clave){
	*consulta = malloc (50*sizeof(char));
	strncpy(*consulta, valor, strlen(valor)+1);
	strcat(*consulta, " = ");
	strcat(*consulta, clave);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
void prepararConsultaString(char** consulta, char* valor, char* clave){
	*consulta = malloc (50*sizeof(char));
	strncpy(*consulta, valor, strlen(valor)+1);
	strcat(*consulta, " = '");
	strcat(*consulta, clave);
	strcat(*consulta, "'");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
void separarArgumentos(int inicio, char* patronFin, char**argv , int max, char***argumentos, int *cantidad){
	int i;
	int aux_cantidad = 0;
	char **aux_argumentos;
	for(i = inicio; i <= max; i++){
		if(strcmp(argv[i], patronFin) == 0){
			break;
		}
		aux_cantidad++;
	} 
	if (aux_cantidad == 0){
		mostrarAyuda("-l");
		return;
	}
	else{
		aux_argumentos = (char**)malloc(aux_cantidad*sizeof(char**)-1);
		for(i = 0; i < aux_cantidad; i++ )
			aux_argumentos[i] = argv[inicio + i];
	}
	*argumentos = aux_argumentos;
	*cantidad = aux_cantidad;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
void separarArgumentosProfesional(char **argumentos, int inicio, int maximo, int **argumentos_profesional){
	int i,j ;
	int aux_argumentos[3];
	inicializarArregloInt(aux_argumentos, 3, 0);
	for(i = inicio, j = 0; i < maximo && j < 2; i++, j++){
		if( strcmp(argumentos[i], "-esp") == 0 && !aux_argumentos[0])
			aux_argumentos[0] = 1;
		else if(strcmp(argumentos[i], "-act") == 0 && !aux_argumentos[1] && !aux_argumentos[2] ){
			aux_argumentos[1] = 1;
		}	
		else if(strcmp(argumentos[i], "-inac") == 0 && !aux_argumentos[1] && !aux_argumentos[2]){	
			aux_argumentos[2] = 1;
		}
	}
	*argumentos_profesional = aux_argumentos;
}	

//-----------------------------------------------------------------------------------------------------------------------------------------------
void separarArgumentosTurno(char **argumentos, int inicio, int maximo, char ***argumentos_profesional){
	char *aux_argumentos[2];
	aux_argumentos[0] = NULL;
	printf("Llega aca\n");

	if(inicio+1<maximo)
		if( strcmp(argumentos[inicio], "-pdni") == 0 || strcmp(argumentos[inicio], "-prof-matricula") == 0 || strcmp(argumentos[inicio], "-prof-id") == 0){
			aux_argumentos[0] = argumentos[inicio];
			aux_argumentos[1] = argumentos[inicio+1];
		}
	printf("pupu\n");
			
	*argumentos_profesional = aux_argumentos;	
}			

//-----------------------------------------------------------------------------------------------------------------------------------------------
void mostrarAyuda(char* argumento){
	printf("MODO DE USO: [-h] tpfinalc <comando> [<argumentos>]\n");
} 
//-----------------------------------------------------------------------------------------------------------------------------------------------

/*Devuelve el id de la tabla, sino devuelve -1*/
int id_tabla(char *word){
   
  int aux = -1;
  if(!strcmp(word,"empleado")) 
    aux=0; 
  if(!strcmp(word,"producto"))
    aux=1;
  if(!strcmp(word,"proveedor"))
    aux=2; 
  if(!strcmp(word,"orden"))
    aux=3; 
  if(!strcmp(word,"cliente"))
    aux=4;
  if(!strcmp(word,"categoria"))
    aux=5; 
  return aux;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------

int id_comando(char *comando[],int argc) /*muestra id de comando*/
{
  int aux = -1;
  if (!strcmp(comando[1],COMANDO_AGREGAR))
  {
    printf("es el comando agregar: -a\n  ");
    aux = 0;
  }
  if (!strcmp(comando[1],COMANDO_LISTAR))
  {
    printf("es el comando listar: -l\n" );
   if (argc-1>2){
      if ( !strcmp(comando[3],COMANDO_SALIDA))
      {
      printf("con redireccion a archivo\n" );
      aux = 2;
      }   
   }else{
        printf("sin redireccion a archivo\n" );    
        aux = 1;
    }
  }
  return aux;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
void menu(int cant_argumentos,char *argumentos[]){
	int operacion, tabla;
	operacion= id_comando(argumentos, cant_argumentos);
	
	switch(operacion){
      case 0:
         //que alta tenemos que hacer()
         //nombre.exe -a nombreTabla args
         tabla=id_tabla(argumentos[2]);
         switch(tabla){
            case 2:
               //add_proveedor
               //alta proveedor 
               //nombre.exe -a proveedor nombre contacto celu fijo
               add_proveedor(argumentos[3],argumentos[4],argumentos[5],argumentos[6]);
               break;
            case 5:
               //add_categoria
               //alta categoria
               //nombre.exe -a categoria nombre
               add_categoria(argumentos[3]);
               break;
            default:
               printf("no implementado. \n");
         }
         //alta categoria
         break;
      case 1:
         //listar comun
         tabla=id_tabla(argumentos[2]);
         listarTipo(tabla);
         //funcion listar
         break;
      case 2:
         //listar redireccion
         //nombre.exe -l tabla -f archivo
         crearArchivo(argumentos[4]);
         tabla=id_tabla(argumentos[2]);
         listarTipoArchivo(tabla,argumentos[4]);
         
         break;
   }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void listarTipo(int tipo)	{
  obj_empleado *emp,*e_row;
  obj_categoria *cat,*c_row;
  obj_cliente *cli,*cli_row;
  obj_proveedor *prov  ,*pv_row;
  obj_producto *p,*p_rw;
  obj_orden *o;
  obj_orden_det *odet;
  	
	switch(tipo){
	case 0:
		emp = empleado_new();
  		listObj(emp,NULL,true,NULL);
  		printf("\n----------------------------------\n");
  		break;
  	case 1:
  		p = producto_new();
  		listObj(p,NULL,true,NULL);
  		printf("\n----------------------------------\n");
  		break;
  	case 2:
		prov = proveedor_new();
  		listObj(prov,NULL,true,NULL);
  		printf("\n----------------------------------\n");
  		break;
  	case 3:
  	   //Se listara las ordenes con sus detalles por simplicidad
  		o = orden_new();
  		listObj(o,NULL,true,NULL);
  		printf("\n----------------------------------\n");
  		break;
	case 4:
		cli = cliente_new();
  		listObj(cli,NULL,true,NULL);
  		printf("\n----------------------------------\n");
		break;
	case 5:
		cat = categoria_new();
  		listObj(cat,NULL,true,NULL);
  		printf("\n----------------------------------\n");
  		break;
  	default:
  		printf("Se recibio un listado incorrecto\n");
		printf("\n----------------------------------\n");
	}
}
//---------------------------------------------------------------------
void listarTipoArchivo(int tipo, char *archivo)	{
  obj_empleado *emp,*e_row;
  obj_categoria *cat,*c_row;
  obj_cliente *cli,*cli_row;
  obj_proveedor *prov  ,*pv_row;
  obj_producto *p,*p_rw;
  obj_orden *o;
  obj_orden_det *odet;
  	
	switch(tipo){
	case 0:
		emp = empleado_new();
  		listObjArchivo(emp,NULL,true,NULL,archivo);
  		printf("\n----------------------------------\n");
  		break;
  	case 1:
  		p = producto_new();
  		listObjArchivo(p,NULL,true,NULL,archivo);
  		printf("\n----------------------------------\n");
  		break;
  	case 2:
		prov = proveedor_new();
  		listObjArchivo(prov,NULL,true,NULL,archivo);
  		printf("\n----------------------------------\n");
  		break;
  	case 3:
  		o = orden_new();
  		listObjArchivo(o,NULL,true,NULL,archivo);
  		printf("\n----------------------------------\n");
  		break;
	case 4:
		cli = cliente_new();
  		listObjArchivo(cli,NULL,true,NULL,archivo);
  		printf("\n----------------------------------\n");
		break;
	case 5:
		cat = categoria_new();
  		listObjArchivo(cat,NULL,true,NULL,archivo);
  		printf("\n----------------------------------\n");
  		break;
  	default:
  		printf("Se recibio un listado incorrecto\n");
		printf("\n----------------------------------\n");
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
int crearArchivo(char *nombre){
   FILE *fd;
   
   fd = fopen(nombre, "w+");
   if(fd == NULL){
      return 1;
   }
   fclose(fd);
   return 0;
}

