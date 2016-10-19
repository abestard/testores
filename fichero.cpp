#include "fichero.h"

fichero::fichero()
{
}

fichero::~fichero()
{
}

matrix fichero::cargar_matrix( ){
    QString fileName = QFileDialog::getOpenFileName();
    QFile fich(fileName);
    fich.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&fich);

    /*if( in.atEnd() ){
      matrix tmp(0,0);
      return tmp;
    }*/

    int fil,col, tip, ncl = 0;
    QString tmp;

    in >> tip >> fil >> col;
    if( !tip ) in >> ncl;

    matrix *mat;
    if( !tip )
        mat = new matrix( fil, col, ncl );
    else
        mat = new matrix( fil, col );

    mat->tip = tip;

    /////////leer '\n'
    in.readLine();

    QString cad;
    for( int i = 0; i < fil; i ++ )
        mat->nomb[i] = in.readLine();

    for( int i = 0; i < col; i ++ )
        mat->rasg[i] = in.readLine();

    for( int i = 0; i < ncl; i ++ )
        mat->nombclas[i] = in.readLine();

    for(int i=0; i < fil;i++)
        for(int j=0; j < col+ncl;j++){
            in >> tmp;

            mat->setVaule( i, j, tmp );
       }

    return *mat;
}
/// 0-> MA 1-> MD 2-> MB
void fichero::salvar_tabla( QTableWidget *T, int tipo, int ncl ){
    matrix mat = convertir_tabla_matrix( T, tipo, ncl );

    QString fileName = QFileDialog::getSaveFileName();
    QFile fich(fileName);
    fich.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&fich);

    int fil = mat.getfil(), col = mat.getcol();

    out << tipo << '\n';
    out << mat.getfil() << '\n' << mat.getcol() << '\n';

    if( !tipo ) out << ncl << '\n';

    for( int i = 0; i < fil; i ++ )
        out << mat.nomb[i] << '\n';

    for( int i = 0; i < col; i ++ )
        out << mat.rasg[i] << '\n';

    for( int i = 0; i < ncl; i ++ )
        out << mat.nombclas[i] << '\n';

    for( int i = 0; i < mat.getfil(); i ++ ){
        for( int j = 0; j < mat.getcol()+ncl; j ++ )
            out << mat.getVaule( i, j ) << ' ';
        out << '\n';
    }

    fich.close();
}

matrix fichero::convertir_tabla_matrix( QTableWidget *T, int tipo, int ncl ){
  int fil = T->rowCount() - 1;
  int col = T->columnCount() - 1 - ncl;

  if( fil <= 0 || col <= 0 || ncl < 0 ){
      matrix ret( 0, 0 );
      return ret;
  }

  matrix *mat;

  if( ncl )
    mat = new matrix( fil, col, ncl );
  else
    mat = new matrix( fil, col );

  mat->tip = tipo;

  for( int i = 0; i < fil; i ++ )
      for( int j = 0; j < col+ncl; j ++ )
         mat->setVaule( i, j, T->item(i+1,j+1)->text() );

  for( int i = 1; i <= fil; i ++ ){
    mat->nomb[i-1] = T->item(i, 0)->text();
  }

  for( int i = 1; i <= col; i ++ ){
    mat->rasg[i-1] = T->item(0, i)->text();
  }


  for( int i = 0; i < ncl; i ++ ){
      mat->nombclas[i] = T->item(0, col+1+i)->text();
  }


  return *mat;
}
