#define $ if ( 0 )

#include <bits/stdc++.h>

using namespace std;

#define for_( i , from , to ) for ( int i = (from) ; i <= (to) ; i ++ )
#define for_e_( e , v ) for ( int e = (v)[head] ; e ; e = e [next] )
#define for_m_( i , j ) for_( i , 1 , n ) for_( j , 1 , m )

const int __ = (int) 1.2e6 , inf = (int) 1e9 ;

int n , m ;

// {{{ Pack
int pack ( int i , int j ) {
    return (i - 1) * m + j ;
}
// }}}

// {{{ Graph

// All about an edge
int to [ __ ] , cap [ __ ] , rev [ __ ] , next [ __ ] ;

int etop = 1 , head [ __ ] ;

void newEdge ( int u , int v , int c ) {
    $ cout << "Labeled[" << u << "\\[DirectedEdge]" << v << "," << c << "],\n" ;
    int e1 = etop ++ , e2 = etop ++ ;

    e1 [to] = v ; e1 [cap] = c ;
    e1 [rev] = e2 ;
    e1 [next] = u [head] ; u [head] = e1 ;

    e2 [to] = u ; e2 [cap] = 0 ;
    e2 [rev] = e1 ;
    e2 [next] = v [head] ; v [head] = e2 ;
}
// }}}

// {{{ Dinic

int src , sink ;
int level [ __ ] ;

bool bfs() {
    static queue < int > Q ;
    while ( ! Q .empty () ) Q .pop () ;
    Q.push ( src ) ;
    memset ( level , 0 , sizeof level ) ;
    src [level] = 1;
    while ( ! Q .empty () ) {
        int cur = Q .front () ; Q .pop () ;
        for_e_( e , cur )
            if ( ! e [to] [level] && e [cap] ) {
                e [to] [level] = cur [level] + 1 ;
                Q.push ( e [to] ) ;
                if ( e [to] == sink ) return true;
            }
    }
    return false;
}

int dfs ( int u , int mxv = inf ) {
    if ( u == sink ) return mxv ;
    
    int tot = 0 ;

    for_e_( e , u )
        if ( e [cap] && e [to] [level] == u [level] + 1 ) {
            int res = dfs ( e [to] , min ( mxv - tot , e [cap] ) ) ;
            e [cap] -= res ; e [rev] [cap] += res ;
            tot += res ;
            if ( mxv - tot <= 0 )
                break ;
        }

    if ( tot == 0 ) u [level] = -1 ;
    return tot ;
}


void dump () {
    cout << "------------------------------------\n" ;
    for_( i , 1 , n + m + 2 )
        for_e_( e , i )
            cout << "Labeled[" << i << "\\[DirectedEdge]" << e [to] << "," << e [cap] <<"],\n" ;
    cout << "------------------------------------\n" ;
}

int dinic () {
    int res = 0 ;
    while ( bfs () ) {
        $ dump () ;
        res += dfs ( src ) ;
    }
    $ dump () ;
    return res ;
}
// }}}

// {{{ Main

int A [ 200 ] [ 200 ] , B [ 200 ] [ 200 ] , C [ 200 ] [ 200 ];

int dx [] = { 0 , 0 , -1 , 1 } , dy [] = { 1 , -1 , 0 , 0 } ;

int main () {
    ios :: sync_with_stdio ( false ) ;

    cin >> n >> m ;
    src = (n + 1) * (m + 1) + 1 ; sink = src + 1 ;
    
    int all = 0 ;
    for_m_( i , j ) cin >> A [ i ] [ j ] , all += A [ i ] [ j ] ;
    for_m_( i , j ) cin >> B [ i ] [ j ] , all += B [ i ] [ j ] ;
    for_m_( i , j ) cin >> C [ i ] [ j ] ;

    for_m_( i , j ) {
        if ( 1 & ( i + j ) )
            swap ( A [ i ] [ j ] , B [ i ] [ j ] ) ;

        newEdge ( src , pack ( i , j ) , A [ i ] [ j ] ) ;
        newEdge ( pack ( i , j ) , sink , B [ i ] [ j ] ) ;

        if ( 1 & ( i + j ) )
            for ( int dir = 0 ; dir < 4 ; dir ++ ) {
                int ix = i + dx [ dir ] , jx = j + dy [ dir ] ;
                int p = pack ( i , j ) , px = pack ( ix , jx ) ;
                if (   1 <= ix && ix <= n
                    && 1 <= jx && jx <= m ) {
                    int profit = C [ i ] [ j ] + C [ ix ] [ jx ] ;
                    newEdge ( p , px , profit ) ;
                    newEdge ( px , p , profit ) ;
                    all += profit ;
                }
            }
                
     }

    cout << all - dinic () << endl ;

    return 0;
}

// }}}
