#ifndef MATRIX_H
#define MATRIX_H
#include <QtGui>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <iostream>
//#include "bits.h"

using namespace std;

class matrix
{
    int fil, col;
    QString **mat;

    public:
        QString *rasg, *nomb, *nombclas;
        int tip, nclas;

        matrix();
        matrix( int f, int c );
        matrix( int f, int c, int ncl );
        matrix( const matrix & );
        ~matrix();
        matrix & operator =( matrix );

        int getfil()const{ return fil; }
        int getcol()const{ return col; }
        void setVaule( int f, int c, QString v ){ mat[f][c] = v; }
        QString getVaule( int f, int c )const { return mat[f][c]; }
        double abss( double );

        matrix conv_MA_MD( double *umb );
        matrix conv_MD_MB( bool );
        void conv_a_Tabla( QTableWidget *, bool );
        //void conv_a_bits( bits matbits[] );
        void swap_fila( int, int );
        void swap_columna( int, int );

        bool superfila( int, bool* );
        bool is_full_cero( int );

        void generar_MA( );
        void generar_MD( int, double porciento=0 );

};

#endif // MATRIX_H
