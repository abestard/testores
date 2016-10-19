#include "Teoria_de_Testores.h"

Teoria_de_Testores::Teoria_de_Testores()
{
    //ctor
}

Teoria_de_Testores::~Teoria_de_Testores()
{
   /* testores.clear();
    if( mask )delete[] mask;
    if( mask_TT )delete[] mask_TT;
    if( limit )delete []limit;
    if( cr ) delete []cr;
    //if( mask ) delete MB;
    if( Trasg ) delete []Trasg;*/

    //dtor
}

void Teoria_de_Testores::conv_a_bits_MB( matrix original ){
    int fil = original.getfil();
    int col = original.getcol();
    MB = new bits *[fil];
    for( int i = 0; i < fil; i ++ ){
       MB[i] = new bits( col + 1 );
       for( int j = 0; j < col; j ++ )
           MB[i]->setbit( j, ( original.getVaule( i, j ) == "1" ) );
    }
}

/** Algotitmo BT de Teoria de Testores de Zhuravliov de escala exterior **/

void Teoria_de_Testores::Algortitmo_BT( matrix original ){
    Artic = original.getfil();
    Rasg = original.getcol();

    conv_a_bits_MB( original );

    bits *tmp;

    mask = new bits( Rasg+1 );
    limit = new bits( Rasg+1 );
    mask_TT = new bits( Rasg+1 );
    tmp = new bits( Rasg+1 );

    //imprimir( *mask );

    num_TT = 0;
    testt = new bits[tamano];
    //testores.clear();
    mask->igual_pot2( 0 );

    //imprimir( *mask );

    limit->igual_pot2( Rasg );

    iniciado = true;

    while( *mask < *limit ){
        if( detener == true ) return;

        band = true;
        k = 0;
        for( int i = 0; i < Artic; i ++ ){
            //tmp = *MB[i] & *mask;
            for( int h = 0; h < Rasg; h ++ )
                if( MB[i]->getbit( h ) && mask->getbit( h ) )
                    tmp->setbit( h, true );
                else
                    tmp->setbit( h, false );
            /////////////////////
            if( tmp->is_cero() ){
                k = max( k, MB[i]->ultimo_bittrue() );
                band = false;
            }
        }

        if( band ){
            if( is_tipico( *mask ) ){
               testt[num_TT] = *mask;
               num_TT ++;
               //testores.push_back( *mask );
               //*mask_TT = *mask_TT | *mask;
               for( int h = 0; h < Rasg; h ++ )
                    if( mask_TT->getbit( h ) || mask->getbit( h ) )
                         mask_TT->setbit( h, true );
                    else
                         mask_TT->setbit( h, false );
               ///////////////////////////////
            }

            k = mask->ultimo_bittrue();
            tmp->igual_pot2( k );
            *mask = *mask + *tmp;
        }else{
            *mask = propiedad_1_5( *mask, k );
        }

        //imprimir( *mask );
    }

    detener = true;
}

bits Teoria_de_Testores::propiedad_1_5( bits mask1, int k ){
  bits nueva( mask1.size() );

  for( int i = 0; i < mask1.size()-1; i ++ )
    if( i > k )
     nueva.setbit( i, mask1.getbit( i ) );
    else
     nueva.setbit( i, ( i == k ) );

  return nueva;
}

bool Teoria_de_Testores::is_testor( bits mask1 ){
    bits *tmp;
    tmp = new bits( Rasg + 1 );
    for( int i = 0; i < Artic; i ++ ){
        //tmp = *MB[i] & mask1;
        for( int h = 0; h < Rasg; h ++ )
            if( MB[i]->getbit( h ) && mask1.getbit( h ) )
               tmp->setbit( h, true );
            else
               tmp->setbit( h, false );
        /////////////////////
        if( tmp->is_cero() )
           return false;
    }
    return true;
}

bool Teoria_de_Testores::is_tipico( bits mask1 ){
    int n = num_TT;
    int num = mask1.cant_bits();
    bits *tmp;
    tmp = new bits( Rasg + 1 );
    if( n <= Artic*num ){
        for( int i = n-1; i >= 0; i -- ){
            //tmp = (testores[i] | mask1);
            for( int h = 0; h < Rasg; h ++ )
                if( testt[i].getbit( h ) || mask1.getbit( h ) )
                   tmp->setbit( h, true );
                else
                   tmp->setbit( h, false );
            /////////////////////
            if( *tmp == mask1 )
                return false;
        }

         return true;
     }

    for( int i = 0; i < Rasg; i ++ )if( mask1.getbit( i ) == true ){
        *tmp = mask1;
        tmp->setbit( i, false );
        if( is_testor( *tmp ) == true )
          return false;
    }

    return true;
}

/** End Algoritmo BT **/

/** (opcional)Algotitmo BT de Teoria de Testores de Zhuravliov de escala exterior **/

bool Teoria_de_Testores::is_testor_long_long( long long num ){
    for( int j = 0; j < Artic; j ++ ){
       band = false;
       for( int k = 0; k < Rasg; k ++ )
           if( MB[j]->getbit( k ) == true && (num & (1ll << k)) ){
                band = true;
                break;
           }

       if( !band )
           return false;
    }

  return true;
}

bool Teoria_de_Testores::is_tipico_long_long( long long num ){
   int n = num_TT;

   if( n <= Rasg ){
       bits mask1(Rasg+1);
       mask1.igual_num( num );
       bits *tmp;
       tmp = new bits( Rasg+1 );
       for( int i = n-1; i >= 0; i -- ){
            //tmp = (testores[i] | mask1);
            for( int h = 0; h < Rasg; h ++ )
                if( testt[i].getbit( h ) || mask1.getbit( h ) )
                   tmp->setbit( h, true );
                else
                   tmp->setbit( h, false );
            /////////////////////
            if( *tmp == mask1 )
                return false;
        }

         return true;
   }

   for( int i = 0; i < Rasg; i ++ )
       if( num & (1ll << i) && is_testor_long_long( num - (1ll << i ) ) )
           return false;
   return true;
}

void Teoria_de_Testores::Algoritmo_BT_long_long( matrix original ){
    Artic = original.getfil();
    Rasg = original.getcol();

    conv_a_bits_MB( original );

    bits *tt;
    tt = new bits( Rasg+1 );
    num_TT = 0;
    testt = new bits[tamano];
    //testores.clear();
    mask_TT = new bits( Rasg+1 );

    int ult, tmp, num;

    bool band;
    long long limite = (1ll << Rasg);
    iniciado = true;
    for( long long i = 1; i < limite;  ){/// las combinaciones usando numeros bits
        ult = -1;
        for( int j = 0; j < Artic; j ++ ){
            tmp = -1, band = false;
            for( int k = 0; k < Rasg; k ++ ){

                if( original.getVaule( j, k ) == "1" && (i & (1ll << k)) ){
                    band = true;
                    break;
                }

                if( original.getVaule( j, k ) == "1" && tmp == -1 )
                 tmp = k;
            }

            if( !band )
                ult = max(tmp, ult );
        }

        if( ult == -1 ){/// es el caso en que es un testor, aplico el salto de 2^(n-h-1) y guardo el testor
            if( is_tipico_long_long( i ) ){
                tt->igual_num( i );
                testt[num_TT] = *tt;
                num_TT ++;
                //testores.push_back( *tt );
                for( int h = 0; h < Rasg; h ++ )
                   if( mask_TT->getbit( h ) || tt->getbit( h ) )
                        mask_TT->setbit( h, true );
                   else
                        mask_TT->setbit( h, false );
            }
            i += (1ll << __builtin_ctz(i));
        }else{ ///es el caso que no lo es aplico el salto de
            tmp = (1ll << ult);

            num = (limite-1);
            num -= (tmp*2ll-1ll);
            num &= i;
            num += tmp;
            i = num;
        }
     }

  detener = true;
}

/** (opcional)End Algoritmo BT **/

/** Algotitmo LEX de Teoria de Testores de Zhuravliov de escala exterior **/

void Teoria_de_Testores::Start_LEX( matrix original ){
   Artic = original.getfil();
   Rasg = original.getcol();

   num_TT = 0;
   //testores.clear();
   testt = new bits [tamano];


   int c = 1<<30, id = -1, tmp;
   for( int i = 0; i < Artic; i ++ ){
      tmp = 0;
      for( int j = 0; j < Rasg; j ++ )
         if( original.getVaule( i, j ) == "1" )
            tmp ++;
      if( c > tmp )
        c = tmp, id = i;
   }

  original.swap_fila( 0, id );

  for( int i = 0; i < Rasg; i ++ )
   if( original.getVaule( 0, i ) == "0" ){
     for( int j = i+1; j < Rasg; j ++ )
         if( original.getVaule( 0, j ) == "1" ){
            original.swap_columna( i, j );
            break;
         }
   }

  conv_a_bits_MB( original );
  cr = new int[Artic];
  for( int i = 0; i < Artic; i ++ ) cr[i] = 0;

  mask_TT = new bits( Rasg+1 );
  Trasg = new QString[Rasg];
  for( int i = 0; i < Rasg; i ++ )
      Trasg[i] = original.rasg[i];

  bits B( Rasg+1 );
  iniciado = true;
  Algortitmo_LEX( B, 0, 0 );
  detener = true;
}

bool Teoria_de_Testores::preposicion_1( bits L, int t ){
    bool excl, ya;
    for( int j = 0; j < Rasg; j ++ )
       if( L.getbit( j ) == true ){
          excl = true, ya = false;
          for( int h = 0; h < Artic; h ++ )
              if( cr[h] == 1 && MB[h]->getbit( j ) == true ){
                if( MB[h]->getbit( t ) != true )
                   excl = false;
                else
                    ya = true;
              }

            if( excl == true && ya == true )
                return true;
        }

    return false;
}

bool Teoria_de_Testores::preposicion_2( int t ){
    for( int h = 0; h < Artic; h ++ )
        if( MB[h]->getbit( t ) == true && cr[h] == 0 )
            return false;
    return true;
}

void Teoria_de_Testores::Algortitmo_LEX( bits mask1, int nF, int pp ){
    if( detener == true ) return;

    if( nF && cr[0] == 0 ) return;

    if( nF == Artic ){


        //testores.push_back( mask1 );
        testt[num_TT] = mask1;
        num_TT ++;
        //*mask_TT = *mask_TT | mask1;
        for( int h = 0; h < Rasg; h ++ )
           if( mask_TT->getbit( h ) || mask1.getbit( h ) )
                mask_TT->setbit( h, true );
           else
                mask_TT->setbit( h, false );
       /////////////////////
        return;
    }

    bits tmp;
    for( int t = pp; t < Rasg; t ++ ){
        if( preposicion_2( t ) )
           continue;

        if( preposicion_1( mask1, t ) )
           continue;

        int c = 0;
        for( int h = 0; h < Artic; h ++ )
            if( MB[h]->getbit( t ) == true )
                cr[h] ++, c += ( cr[h] == 1 );

        tmp = mask1;
        tmp.setbit( t, true );
        Algortitmo_LEX( tmp, nF+c, t + 1 );

        for( int h = 0; h < Artic; h ++ )
            if( MB[h]->getbit( t ) == true )
                cr[h] --;
    }
}
/** End Algoritmo LEX **/



/*
void Teoria_de_Testores::imprimir( bits tmp1 ){
    for( int h = 0; h < tmp1.size()-1; h ++ )
        if( tmp1.getbit( h ) )
            cout << "1 ";
        else
            cout << "0 ";
    cout << "\n";
}*/
