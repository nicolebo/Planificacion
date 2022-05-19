// *************************************************************************
// 
//  Departamento de Inform�tica de Sistema y Computadores (DISCA)
//  Universidad Politecnica de Valencia.                         
// 
//  Autor: Sergio S�ez (ssaez@disca.upv.es)
// 
//  Fichero: PlanifSJF.cc
//  
//  Fecha: 
// 
//  Descripci�n: 
// 	 Implementaci�nde la clase 'PlanifSJF'
// 
// *************************************************************************

#define PlanifSJF_CC

// *** Includes ***********************************************

#include "PlanifSJF.hh"

// *** Definiciones Externas **********************************

// *** M�todos P�blicos ***************************************

// *** PlanifSJF::TareaNueva
// Informa al planificador de la llegada de una nueva tarea

int PlanifSJF::TareaNueva 
( 
 tarea_activa_t *	tarea
 )
{
  // *** Cuerpo principal del m�todo

  cl_preparadas.push(tarea);

  return OK;

} // end PlanifSJF::TareaNueva


// *** PlanifSJF::SiguienteActivacion
// Indica cuando se debe realizar la nueva activaci�n

tiempo_t PlanifSJF::SiguienteActivacion 
( 
 const ProcesadorCls&	procesador,
 tiempo_t		tiempo_actual
 )
{
  // *** Cuerpo principal del m�todo

  if (!cl_preparadas.empty())
    if (procesador.EstaLibre())
      return tiempo_actual;
    else
      return procesador.SiguienteLibre(tiempo_actual);
  else
    return MAX_TIEMPO;

} // end PlanifSJF::SiguienteActivacion


// *** PlanifSJF::BorraSiguiente
// Extrae la siguinte tarea a planificar

tarea_activa_t * PlanifSJF::BorraSiguiente ( )
{
  // *** Objetos Locales. Inicializaci�n

  tarea_activa_t *	sig_tarea;

  // *** Cuerpo principal del m�todo

  if (!cl_preparadas.empty())
    {
      sig_tarea= cl_preparadas.top();
      cl_preparadas.pop();
    }
  else
    sig_tarea= NULL;

  return sig_tarea;

} // end PlanifSJF::BorraSiguiente


// *** PlanifSJF::~PlanifSJF

PlanifSJF::~PlanifSJF ()
{

} // end PlanifSJF::~PlanifSJF

// *** M�todos Privados ***************************************

