/* Fichero: tareas.cc
   Autor: Ismael Ripoll <iripoll@disca.upv.es>
   Fecha: 28/09/1998
*/

#include "tipos.h"
#include "tareas.hh"

#include <qpopmenu.h>
#include <qkeycode.h>
#include <qmsgbox.h>
#include <qframe.h>
#include <qscrbar.h>
#include <qfiledlg.h>  
#include <qpoint.h>
#include <qpntarry.h>
#include <qwmatrix.h>
#include <qcolor.h>
#include <qpen.h>
#include <qpainter.h>



Tareas_ventana::Tareas_ventana():QListView(NULL){
  QListViewItem *tmp,*padre;
  char cade[100];

  addColumn( "             Atributo" );
  setColumnWidth(0,200);

  addColumn( "Valor" );
  setColumnWidth(1,50);

  setRootIsDecorated(TRUE);
  setFixedWidth(250);
  

  for (int x=0; x<num_tareas; x++){
    tmp = new QListViewItem( this, Tareas[x].nombre, 0 );
    //    tmp->setOpen ( TRUE);  
    sprintf(cade,"%d",Tareas[x].prioridad);
    new TareaViewItem ( tmp, "Prioridad",cade,0);
    sprintf(cade,"%d",Tareas[x].periodo);
    new TareaViewItem ( tmp, "Periodo", cade,0);
    sprintf(cade,"%d",Tareas[x].llegada);
    new TareaViewItem ( tmp, "Llegada", cade,0);
    tmp->setExpandable( TRUE );
    //tmp->setOpen(TRUE);

    QListViewItem *sub = new QListViewItem ( tmp, "Secuencia de Ejecuci�n",0);
    for (int y=0; y<= Tareas[x].Nsubtareas; y++){
      char str_computo[100];

      sprintf(str_computo,"%d",Tareas[x].subtarea[y].tiempo);

      if (Tareas[x].subtarea[y].recurso == 0){
	new TareaViewItem ( sub, "CPU" ,(const char *) str_computo, (const char *)0);
      } else {
	new TareaViewItem ( sub, Recursos[Tareas[x].subtarea[y].recurso].nombre, str_computo,0);
      }
    }
    
  }

  show();
  
}



Tareas_ventana::~Tareas_ventana(){

  //  printf("Por aqu� paso\n");

}

