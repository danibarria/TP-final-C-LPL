//ELIMINAR INCLUDES QUE NO SE UTILIZAN EN EL MAIN
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "config/config.h"
#include "lib/orm/orm.h"
#include "lib/utils/utils.h"

#include "src/empleado/empleado.h"
#include "src/categoria/categoria.h"
#include "src/cliente/cliente.h"
#include "src/proveedor/proveedor.h"
#include "src/producto/producto.h"
#include "src/orden/orden.h"
#include "src/orden_det/orden_det.h"

//BUENA REFERENCIA PARA CREAR LA FUNCION QUE LISTE UNA TABLA EN UN ARCHIVO
void cli_show(void *c)
{
  obj_cliente *cli = (obj_cliente*)c;
     printf("ID:%d\n",cli->getClienteId(cli));
}
 /*
   COSAS QUE AUN FALTAN:
   1) falta implementar una forma de saber cuando se debe listar las ordenes con los detalles
   2)falta implementar las relaciones de las tablas que tenga
   3) 
*/ 
int main(int argc, char *argv[])
{
   //add_proveedor("Lucas", "Lucas@Lucas", "123", "456");
   menu(argc, argv);  
   system("PAUSE");	
   return 0;
}

