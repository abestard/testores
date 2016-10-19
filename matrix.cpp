#include "matrix.h"
#include <QtGui>
#include <string.h>
#include <stdio.h>

matrix::matrix()
{
    fil = 0, col = 0, nclas = 0, tip = -1;
}

matrix::matrix( int f, int c )
{
    tip = -1;
    fil = f, col = c, nclas = 0;
    mat = new QString*[f];
    for( int i = 0; i < f; i ++ )
        mat[i] = new QString[c];
    nomb = new QString [f];
    rasg = new QString [c];
}

matrix::matrix( int f, int c, int ncl )
{
    tip = 0;
    fil = f, col = c, nclas = ncl;
    mat = new QString*[f];
    for( int i = 0; i < f; i ++ )
        mat[i] = new QString[c+ncl];
    nomb = new QString [f];
    rasg = new QString [c];
    nombclas = new QString [ncl];
}

matrix ::matrix( const matrix &MM ){

    int f = MM.getfil();
    int c = MM.getcol();
    int ncl = MM.nclas;

    //--crando areglos--
    fil = f, col = c, nclas = ncl;
    mat = new QString*[f];
    for( int i = 0; i < f; i ++ )
        mat[i] = new QString[c+ncl];
    nomb = new QString [f];
    rasg = new QString [c];
    nombclas = new QString [ncl];
    //----

    tip = MM.tip;
    for( int i = 0; i < fil; i ++ )
        for( int j = 0; j < col+ncl; j ++ )
            mat[i][j] = MM.getVaule( i, j );

    for( int i = 0; i < fil; i ++ )
      nomb[i] = MM.nomb[i];

    for( int i = 0; i < col; i ++ )
        rasg[i] = MM.rasg[i];

    for( int i = 0; i < ncl; i ++ )
        nombclas[i] = MM.nombclas[i];
}

matrix::~matrix(){
    for( int i = 0; i < fil && col > 0; i ++ ){
        delete [] mat[i];
        mat[i] = NULL;
    }


    if( fil > 0 ){

        if( mat ){ delete [] mat; mat = NULL; }
        if( nomb ){ delete [] nomb; nomb = NULL; }
    }

    if( nclas > 0 ){ delete [] nombclas; nombclas = NULL; }

    if( col > 0 && rasg)
        { delete [] rasg; rasg = NULL; }
    fil = 0, col = 0, tip = -1;
}

matrix &matrix::operator = ( matrix MM ){
    int f = MM.getfil();
    int c = MM.getcol();
    int ncl = MM.nclas;

    //--crando areglos--
    fil = f, col = c, nclas = ncl;
    mat = new QString*[f];
    for( int i = 0; i < f; i ++ )
        mat[i] = new QString[c+ncl];
    nomb = new QString [f];
    rasg = new QString [c];
    nombclas = new QString [ncl];
    //----

    tip = MM.tip;
    for( int i = 0; i < fil; i ++ )
        for( int j = 0; j < col+ncl; j ++ )
            mat[i][j] = MM.getVaule( i, j );

    for( int i = 0; i < fil; i ++ )
      nomb[i] = MM.nomb[i];

    for( int i = 0; i < col; i ++ )
        rasg[i] = MM.rasg[i];

    for( int i = 0; i < ncl; i ++ )
        nombclas[i] = MM.nombclas[i];

    return *this;
}


double matrix::abss( double a ){
    if( a < 0 ) return a*-1;
    return a;
}


matrix matrix::conv_MA_MD( double *umb ){
     int *clas;
     clas = new int[fil];
     for( int i = 0; i < fil; i ++ ){
         clas[i] = -1;
         for( int j = 0; j < nclas; j ++ )
             if( mat[i][col+j] == "1" ){
               if( clas[i] == -1 )
                   clas[i] = j;
               else{
                   //escribir error en matrix*/
                   QMessageBox *error;
                   error = new QMessageBox ();
                   error->setText("Error: Un objeto pertenece a mas de una clase");
                   error->show();
                   return matrix( 0, 0 );
               }
             }
     }

     int tam = 0;
     for( int i = 0; i < fil; i ++ )
         for( int j = i+1; j < fil; j ++ )
             if( clas[i] != clas[j] )
                 tam ++;

     matrix MD( tam, col );
     for( int i = 0; i < col; i ++ )
         MD.rasg[i] = rasg[i];

     tam = 0;
     for( int i = 0; i < fil; i ++ )
         for( int j = i+1; j < fil; j ++ )if( clas[i] != clas[j] ){

            for( int k = 0; k < col; k ++ ) if( umb[k] == 0 )
                MD.setVaule( tam, k, ( mat[i][k] == mat[j][k] )? "0" : "1" );
              else
                MD.setVaule( tam, k, ( abss( mat[i][k].toDouble() - mat[j][k].toDouble() ) <= umb[k] )? "0" : "1" );

            MD.nomb[tam] = nomb[i]+"-"+nomb[j];
            tam ++;
         }

    return MD;
}

bool matrix::superfila( int i, bool *mark ){
    bool band;
    for( int j = 0; j < fil; j ++ )
        if( !mark[j] && i != j ){
          band = true;
          for( int k = 0; k < col; k ++ )
              if( mat[j][k] == "1" && mat[i][k] == "0" ){
                band = false;
                break;
              }
          if( band )
            return true;
        }
    return false;
}

bool matrix::is_full_cero( int i ){
    for( int j = 0; j < col; j ++ )
      if( mat[i][j] != "0" )
          return false;
    return true;
}

matrix matrix::conv_MD_MB( bool messg ){
     int elim = fil;
     bool *mark;
     mark = new bool[fil];
     for( int i = 0; i < fil; i ++ )
         mark[i] = false;

     for( int i = 0; i < fil; i ++ )
         if( is_full_cero( i ) ){
           //enviar un error
           QMessageBox *error;
           error = new QMessageBox ();
           error->setText("Error: Fila completa de 0");
           if( !messg )error->show();
           return matrix(0,0);
         }

     for( int i = 0; i < fil; i ++ )
         if( superfila( i, mark ) )
           elim --, mark[i] = true;

     matrix MB( elim, col );
     MB.tip = 2;

     for( int i = 0; i < col; i ++ )
         MB.rasg[i] = rasg[i];

     elim = 0;
     for( int i = 0; i < fil; i ++ )
        if( !mark[i] ){
           for( int j = 0; j < col; j ++ )
              MB.setVaule( elim, j, mat[i][j]);
           MB.nomb[elim] = nomb[i];
           elim ++;
        }

     return MB;
}

/// true -> MA
void matrix::conv_a_Tabla( QTableWidget *T, bool band ){

   if( fil <= 0 || col <= 0 ) return;

   T->setRowCount( fil+1 );
   T->setColumnCount( col+1+(( band == true )?nclas:0) );

   QTableWidgetItem *valor;
   for(int i=1; i <= fil; i++)
       for(int j=1; j <= col+nclas; j++){
           valor = new QTableWidgetItem( mat[i-1][j-1] );
           if( j > col )
             valor->setBackground( Qt::gray );
           else
             valor->setBackground( Qt::lightGray );
           T->setItem( i,j,valor );
       }

   for( int i = 1; i <= fil; i ++ ){
     valor = new QTableWidgetItem ( nomb[i-1] );
     valor->setBackground( Qt::darkGray );
     T->setItem( i,0,valor );
   }
   for( int i = 1; i <= col; i ++ ){
     valor = new QTableWidgetItem ( rasg[i-1] );
     valor->setBackground( Qt::darkGray );
     T->setItem( 0, i,valor );
   }

   valor = new QTableWidgetItem("Objts/Descipciones");
   valor->setFlags(Qt::NoItemFlags);
   valor->setFlags(Qt::ItemIsEnabled);
   valor->setBackground( Qt::darkGray );
   T->setItem( 0, 0, valor );

   if( band ){
     for( int i = 0; i < nclas; i ++ ){
         valor = new QTableWidgetItem ( nombclas[i] );
         valor->setBackground( Qt::darkGray );
         T->setItem( 0, col+1+i, valor );
    }
   }
}

void matrix::swap_fila( int a, int b ){
    swap( nomb[a], nomb[b] );

    for( int i = 0; i < col; i ++ )
        swap( mat[a][i], mat[b][i] );
}

void matrix::swap_columna( int a, int b ){
    swap( rasg[a], rasg[b] );

    for( int i = 0; i < fil; i ++ )
        swap( mat[i][a], mat[i][b] );
}

void matrix::generar_MA( ){
   double tmp;
   char cad[56];
   for(int i=0; i < fil;i++)
       for(int j=0; j < col;j++)
       {
          tmp = rand()%100;
          sprintf(cad, "%.2lf", tmp);
          mat[i][j] = cad;
       }

   for( int j = 0; j < col; j ++ ){
      sprintf(cad, "X%d", j+1);
      rasg[j] = cad;
   }

  for( int i = 0; i < fil; i ++ ){
       sprintf(cad, "Obj %d", i+1);
       nomb[i] = cad;
   }

  for( int j = 0; j < nclas; j ++ ){
       sprintf(cad, "K%d", j+1);
       nombclas[j] = cad;
  }

   int val;
   for( int i = 0; i < fil; i ++ ){
      val = rand()%nclas;
      for( int j = 0; j < nclas; j ++ ){
        mat[i][col+j] = ( val == j )?"1":"0";
      }
   }
}

void matrix::generar_MD( int tip, double porciento ){
    double vv = porciento*fil*col;
    vv /= 100.0;
    int cant1;

    if( tip == 1 )
      cant1 = (int)vv;
    else
      cant1 = fil*col;

    int tmp;
    for( int i = 0; i < fil; i ++ )
        for( int j = 0; j < col; j ++ ){
          tmp = rand()%2;
          if( tmp == 1 && cant1 )
             mat[i][j] = "1", cant1 --;
          else
             mat[i][j] = "0";
        }

    if( tip == 0 )
        cant1 = 0;

    for( int i = 0; i < fil && cant1; i ++ )
        for( int j = 0; j < col && cant1; j ++ )
            if( mat[i][j] == "0" )
                mat[i][j] = "1", cant1 --;

   char tmp1[100];
   for( int j = 0; j < col; j ++ ){
      sprintf(tmp1, "X%d", j+1);
      rasg[j] = tmp1;
   }

  for( int i = 0; i < fil; i ++ ){
       sprintf(tmp1, "Obj %d", i+1);
       nomb[i] = tmp1;
   }
}

/*
void matrix::conv_a_bits( bits &matbits[] ){
    //matbits = new bits[fil];
    for( int i = 0; i < fil; i ++ ){
       matbits[i] = bits( col + 1 );
       for( int j = 0; j < col; j ++ )
           matbits[i].setbit( j, ( mat[i][j] == "1" ) );
    }
}*/



