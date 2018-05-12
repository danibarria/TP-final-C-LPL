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

void cli_show(void *c)
{
  obj_cliente *cli = (obj_cliente*)c;
     printf("ID:%d\n",cli->getClienteId(cli));
}

int main(int argc, char *argv[])
{
  obj_empleado *emp,*e_row;
  obj_categoria *cat,*c_row;
  obj_cliente *cli,*cli_row;
  obj_proveedor *prov  ,*pv_row;
  obj_producto *p,*p_rw;
  obj_orden *o;
  obj_orden_det *odet;
  
  int result;
  int i=0,size=0;
  void *list;
  /*
  emp = empleado_new();
  listObj(emp,NULL,true,NULL);
  printf("\n----------------------------------\n");
  prov = proveedor_new();
  listObj(prov,NULL,true,NULL);
  printf("\n----------------------------------\n");
  cat = categoria_new();
  listObj(cat,NULL,true,NULL);
  printf("\n----------------------------------\n");*/
  
  p = producto_new();
  listObj(p,NULL,true,NULL);
  printf("\n----------------------------------\n");
  
  system("PAUSE");	
  return 0;
}
