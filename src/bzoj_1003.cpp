#define $ if ( 0 )
#include <bits/stdc++.h>
using namespace std;

#define for_( i , from , to ) for ( int i = (from) ; i <= (to) ; ++ i )

const int __ = 2000 ;

int n , m , k , e , d ;

int to [__] , next [__] , len [__] ;
int ep = 1 , head [__] ;
int unavail [__] [__] ;
long long sp [__] [__] , dp [__] ;

void newEdge ( int u , int v , int w ) {
    int e = ep ++ ;
    e [to] = v ; e [len] = w ;
    e [next] = u [head] ; u [head] = e ;
}

long long died [30] , dist [30] ;

struct cmp {
    bool operator () ( int u , int v ) {
        return u [dist] == v [dist]
            ?  u < v
            :  u [dist] < v [dist] ;
    }
} ;

set < int , cmp > S;

long long spfa ( int l , int r ) {
    memset ( died , 0 , sizeof died ) ;
    memset ( dist , 0x1 , sizeof dist ) ;

    for_( i , 1 , m ) for_( j , l , r )
        if ( unavail [ i ] [ j ] ) i [died] = 1 ;

    S .insert ( 1 ) ;
    1 [dist] = 0 ;

    set < int , cmp > :: iterator it ;

    while ( ( it = S .begin ( ) ) != S .end ( ) ) {
        int t = * it ; S .erase ( it ) ;
        for ( int r = t [head] ; r ; r = r [next] )
            if ( ! r [to] [died]
                    && r [to] [dist] > t [dist] + r [len] ) {
                S .erase ( r [to] ) ;
                r [to] [dist] = t [dist] + r [len] ;
                S .insert ( r [to] ) ;
            }
    }
    
    $ {
        printf ( "-- spfa %d ~ %d : " , l , r ) ;
        for_( i , 1 , m )
            printf ( "%lld%c" , i [dist] , " \n" [ i == m ] ) ;
    }
    return m [dist] ;
}

int main ( ) {
    scanf ( "%d%d%d%d" , & n , & m , & k , & e ) ;
    for_( _ , 1 , e ) {
        int u , v , l ; scanf ( "%d%d%d" , & u , & v , & l ) ;
        newEdge ( u , v , l ) ; newEdge ( v , u , l ) ;
    }

    scanf ( "%d" , & d ) ;

    for_( _ , 1 , d ) {
        int p , st , ed ; scanf ( "%d%d%d" , & p , & st , & ed ) ;
        for_( i , st , ed ) unavail [ p ] [ i ] = 1 ;
    }

    for_( i , 1 , n ) for_( j , i , n )
        sp [ i ] [ j ] = spfa ( i , j ) ;

    for_( i , 1 , n ) {
        dp [ i ] = (long long) sp [ 1 ] [ i ] * i ;
        for_( j , 1 , i - 1 )
            dp [ i ] = min ( dp [ i ] ,
                    dp [ j ] + k + (long long)(i - j) * sp [ j + 1 ] [ i ] ) ;
    }
    
    $ {
        puts("----------------------");

        for_( i , 1 , n )
            printf ( "%lld%c" , dp [ i ] , " \n" [ i == n ] ) ;

        for_( i , 1 , n ) for_( j , i , n )
            printf ( "%lld%c" , sp [ i ] [ j ] , " \n" [ j == n ] ) ;
    }
    printf ( "%lld\n" , dp [ n ] ) ;

    return 0 ;   
}
