#ifndef FICHERO_H
#define FICHERO_H
#include "matrix.h"
#include <QFileDialog>
#include <Qfile.h>
#include <QTextStream>
#include <QtGui>

class fichero
{
    public:
      fichero();
      ~fichero();

      matrix cargar_matrix( );
      void salvar_tabla( QTableWidget*, int, int ncl = 0 );

      matrix convertir_tabla_matrix( QTableWidget*, int, int ncl = 0 );
};

#endif // FICHERO_H
