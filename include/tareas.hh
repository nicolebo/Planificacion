/****************************************************************************
** $Id: dirview.h,v 1.5 1998/05/21 19:24:51 agulbra Exp $
**
** Copyright (C) 1992-1998 Troll Tech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#ifndef DIRVIEW_H
#define DIRVIEW_H

#include <qlistview.h>
#include <qstring.h>
#include <stdio.h>
//#include <qfile.h>

#include "tipos.h"


//-------------------------------------------------------------------
//------Clase chanchullo para que no esté ordenada la QListViewItem
//-------------------------------------------------------------------
class Tareas_ventana: public QListView {
  Q_OBJECT
 public:
  Tareas_ventana();
  ~Tareas_ventana();
  
 private slots:
  
    
};

//-------------------------------------------------------------------
//------Clase chanchullo para que no esté ordenada la QListViewItem
//-------------------------------------------------------------------
class TareaViewItem: public QListViewItem {
 private:
  int contador;
  int posicion;  /* Esto es para que no ordene */


 public:
  TareaViewItem( QListViewItem * parent, const char * label1=0,  
		 const char * label2=0, const char * label3=0):
    QListViewItem(parent,label1,label2, label3) {
    posicion = contador++;
  };
  
  
  
  virtual const char *key(int col, bool asc) const{
    static char cade[10];
    sprintf(cade,"%3d",posicion);
    return cade;
  };  
   

  

};

#endif
