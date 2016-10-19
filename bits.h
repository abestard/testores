#ifndef BITS_H
#define BITS_H



class bits
{
    int numbits;
    bool *arrbits;

    public:
        bits();
        bits( int );
        bits( const bits & );
        ~bits();

        int size()const{ return numbits; }
        bool getbit( int x ) const { return arrbits[x]; }
        void setbit( int x, bool v ) { arrbits[x] = v; }
        bool is_cero( );
        int ultimo_bittrue( );
        void igual_pot2( int );
        void igual_num( long long );
        int cant_bits( );

        bits & operator =( bits );
        bits operator + ( bits );
        bits operator & ( bits );
        bits operator | ( bits );
        bool operator < ( bits );
        bool operator == ( bits );


    protected:

    private:
};

#endif // BITS_H
