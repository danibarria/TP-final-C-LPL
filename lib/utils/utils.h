extern PGconn *conn;

#define COMANDO_AGREGAR "-a"
#define COMANDO_LISTAR "-l"
#define COMANDO_SALIDA "-f"

char* rtrim(char* string, char junk);
char** fStrSplit(char *str, const char *delimiters);
char* fStrJoin(char **str, const char *delimiters, int sz_opt);
void disconnectdb(PGconn *);
PGconn * connectdb(char *servidor,char *port,char *base,char *usuario,char *password);
void inicializarArregloInt(int *arreglo, int cantidad, int valor);
char *itoa_simple(char *dest, int i);
int startswith(const char *pre, const char *str);
char * getFechaHora();
char * getFecha();

void prepararConsulta(char**, char*, char*);
void prepararConsultaString(char**, char*, char*);
void separarArgumentos(int, char*, char**, int, char***, int *);
void separarArgumentosProfesional(char **, int, int, int **);
void separarArgumentosTurno(char **, int, int, char ***);
void mostrarAyuda(char *);


int id_tabla(char *);/*muestra el ID de la tabla*/
int id_comando(char**,int); /*muestra id de comando*/


void listarTipo(int); /*recibe un entero, lista segun la table*/

int crearArchivo(char *); /*recibe un archivo y lo crea*/
