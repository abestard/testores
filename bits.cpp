#include "bits.h"

bits::bits()
{
    numbits = 0;
    //ctor
}

bits::bits( int n )
{
    numbits = n;
    arrbits = new bool [n];
    for( int i = 0; i < n; i ++ )
        arrbits[i] = false;
    //ctor
}

bits::bits( const bits &num )
{
    numbits = num.size();
    arrbits = new bool [numbits];
    for( int i = 0; i < numbits; i ++ )
        arrbits[i] = num.getbit( i );
    //ctor
}

bits::~bits()
{
    if( numbits ) delete [] arrbits;
    arrbits = 0;
    //dtor
}

bool bits::is_cero( ){
    for( int i = 0; i < numbits; i ++ )
        if( arrbits[i] == true )
            return false;
    return true;
}

int bits::ultimo_bittrue( ){
    for( int i = 0; i < numbits; i ++ )
        if( arrbits[i] == true )
            return i;

    return -1;
}

void bits::igual_pot2( int n ){
    for( int i = 0; i < numbits; i ++ )
        arrbits[i] = ( i == n );
}

void bits::igual_num( long long n ){
    for( int i = 0; i < numbits; i ++ )
        arrbits[i] = ( n & (1ll << i) );
}

int bits::cant_bits( ){
    int n = 0;
    for( int i = 0; i < numbits; i ++ )
        if( arrbits[i] == true )
            n ++;
    return n;
}

bits & bits::operator = ( bits num  ){
    numbits = num.size();
    arrbits = new bool [numbits];
    for( int i = 0; i < numbits; i ++ )
        arrbits[i] = num.getbit( i );
    return *this;
}

bits bits::operator + ( bits num ){
  bits sum( numbits );
  int llevo = 0;
  for( int i = 0; i < numbits; i ++ ){
    llevo += ( arrbits[i] == true ) + ( num.getbit( i ) == true );
    sum.setbit( i, ( llevo % 2 != 0 ) );
    llevo /= 2;
  }

  return sum;
}

bits bits::operator & ( bits num ){
  bits _AND( numbits );
  for( int i = 0; i < numbits; i ++ )
    _AND.setbit( i, ( num.getbit( i ) && arrbits[i] ) );

  return _AND;
}

bits bits::operator | ( bits num ){
  bits _OR( numbits );
  for( int i = 0; i < numbits; i ++ )
    _OR.setbit( i, ( num.getbit( i ) || arrbits[i] ) );

  return _OR;
}

bool bits::operator < ( bits num ){
  for( int i = numbits-1; i >= 0; i -- )
     if( arrbits[i] != num.getbit( i ) )
       return (arrbits[i] == false);

  return false;
}

bool bits::operator == ( bits num ){
  for( int i = numbits-1; i >= 0; i -- )
     if( arrbits[i] != num.getbit( i ) )
       return false;

  return true;
}

