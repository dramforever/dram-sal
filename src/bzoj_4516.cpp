#define $ if ( 0 )

#include <bits/stdc++.h>
using namespace std ;

const int __ = int ( 3e5 ) ;

int pool = 3 , last = 1 , head = 1 ;
int depth [ __ ] , parent [ __ ] ;
map < int , int > go [ __ ] ;

inline void add ( int c ) {
    int current = pool ++ ;
    current [depth] = last [depth] + 1 ;

    int p ;
    for ( p = last ; p && ! p [go] [ c ] ; p = p [parent] )
        p [go] [ c ] = current ;

    if ( p ) {
        int conflict = p [go] [ c ] ;
        if ( conflict [depth] == p [depth] + 1 ) {
            current [parent] = conflict ;
        } else {
            int clone = pool ++ ;
            clone [depth] = p [depth] + 1 ;
            clone [go] = conflict [go] ;
            clone [parent] = conflict [parent] ;
            current [parent] = conflict [parent] = clone ;
            for ( ; p && p [go] [ c ] == conflict ; p = p [parent] )
                p [go] [ c ] = clone ;
        }
    } else {
        current [parent] = head ;
    }

    last = current ;
}

char * buf ;

inline void read_all () {
    size_t len = (size_t) 1e6, read_len = 0 ;
    do {
        buf = (char *) realloc ( buf , (size_t) len * 2 ) ;
        read_len += fread ( buf + read_len , 1 , len , stdin ) ;
        len *= 2 ;
    } while ( ! feof ( stdin ) ) ;
    * ( buf + read_len ) = 0 ;
}

inline void get ( long long & x ) {
    x = strtoll ( buf , & buf , 0) ;
}

inline void get ( int & x ) {
    x = (int) strtol ( buf , & buf , 0 ) ;
}

int main () {
    read_all ( ) ;
    int n ;
    long long ans = 0 ;
    get ( n ) ;
    while ( n -- ) {
        int x ; get ( x ) ;
        add ( x ) ;
        printf ( "%lld\n" , ans += last [depth] - last [parent] [depth] ) ;
    }
    return 0 ;
}

