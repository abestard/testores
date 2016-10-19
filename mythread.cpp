#include "mythread.h"

MyThread::MyThread()
{
}

MyThread::~MyThread()
{
    delete Algoritmos;
}

void MyThread::run( ){
    if( Nombre == "BT" ){
       if( mat.getcol() > 60 )
          Algoritmos->Algortitmo_BT( mat );
       else
          Algoritmos->Algoritmo_BT_long_long( mat );
    }else
       if( Nombre == "LEX" )
          Algoritmos->Start_LEX( mat );
}
