#ifndef TEORIA_DE_TESTORES_H
#define TEORIA_DE_TESTORES_H
#include <bits.h>
#include <vector>
#include <matrix.h>
#define tamano 1000005
#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

class Teoria_de_Testores
{
    public:
        Teoria_de_Testores();
        ~Teoria_de_Testores();
        bool detener;
        bool iniciado;
        //vector<bits> testores;
        void conv_a_bits_MB( matrix );
        int num_TT;

        bits *testt;

        int Artic, Rasg;
        QString *Trasg;

        int k;
        bits *mask, *limit, *mask_TT, **MB;
        bool band;

        int *cr;

        /** Algotitmo BT de Teoria de Testores de Zhuravliov de escala exterior **/

        bits propiedad_1_5( bits, int );
        void Algortitmo_BT( matrix );
        bool is_tipico( bits );
        bool is_testor( bits ); 

        /** End Algoritmo BT **/

        /** (opcional)Algotitmo BT de Teoria de Testores de Zhuravliov de escala exterior **/

        bool is_testor_long_long( long long );
        bool is_tipico_long_long( long long );
        void Algoritmo_BT_long_long( matrix );

        /** (opcional)End Algoritmo BT **/

        /** Algotitmo LEX de Teoria de Testores de Zhuravliov de escala exterior **/

        void Start_LEX( matrix );
        void Algortitmo_LEX( bits, int, int );
        bool preposicion_1( bits, int );
        bool preposicion_2( int );
        bool exclu( );

        /** End Algoritmo LEX **/

        /** Algoritmo BR **/

        int rasg, fil;
        int X;
        vvi TL;
        vi RL, L, TMP, LP;
        bool fin;

        vi subst( vi V, int x, int p );
        vi elim( vi V, int x );
        bool col_testor( int x );
        void Algoritmo_BR( matrix );
        bool Excl( vi V, int x );
        vi noExcl( vi V1, vi V );
        vi TypL( vi V1, vi V );
        vi matrixaceptacion( vi V );

        /** End Algoritmo BR **/


        //void imprimir( bits );
};

#endif // TEORIA_DE_TESTORES_H
