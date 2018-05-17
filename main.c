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


void listarTipo(int tipo){
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
  		o = orden_new();
  		listObj(o,NULL,true,NULL);
  		printf("\n----------------------------------\n");
  		break;
  	case 6:
  		odet = orden_det_new();
  		listObj(odet,NULL,true,NULL);
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


int main(int argc, char *argv[])
{
  
  int result;
  int i=0,size=0;
  void *list;
  
  result=id_comando(argv[]);
   
  switch(1){
  case 0:
  		//realizar alta
  		break;
  case 1:
  		listarTipo(3);//agregar la funcion que nos dice que tabla se debe listar
  		break;
  case 2:
        //hacer el listado de la tabla y escribir la salida de el listado en el archivo
        break;
  }	
  
  system("PAUSE");	
  return 0;
}

