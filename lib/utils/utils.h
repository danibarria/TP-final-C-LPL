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

//_________________Funciones creadas por los alumnos_________________________________________________________________________________________________
/*muestra el ID de la tabla que corresponda a la cadena recibida*/
int id_tabla(char *);

/*muestra id de comando que corresponda con la cadena que se recibio*/
int id_comando(char**,int); 

/*recibe un entero, y segun el entero recibido se conoce que tabla y se lista*/
void listarTipo(int);
 
void listarTipoArchivo(int tipo,char *archivo);

/*recibe un nombre y lo crea como un archivo*/
int crearArchivo(char *); 
