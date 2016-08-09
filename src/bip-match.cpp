#define $ if(0)

#include <bits/stdc++.h>
using namespace std;

#define for_( i , from , to ) for ( int i = (from) ; i <= (to) ; i ++ )
#define for_e_( e , v ) for ( int e = (v)[head] ; e ; e = e [next] )

const int __ = (int) 1.2e6 , inf = (int) 1e9 ;

int nl , nr ;

// {{{ Graph

// All about an edge
int to [ __ ] , cap [ __ ] , rev [ __ ] , next [ __ ] , flag [ __ ] , chead [ __ ] ; 

int etop = 1 , head [ __ ] ;

void newEdge ( int u , int v , int c , int fl ) {
    $ cout << "Labeled[" << u << "\\[DirectedEdge]" << v << "," << c << "],\n" ;
    int e1 = etop ++ , e2 = etop ++ ;

    e1 [flag] = fl;
    e1 [to] = v ; e1 [cap] = c ;
    e1 [rev] = e2 ;
    e1 [next] = u [head] ; u [head] = e1 ;

    e2 [to] = u ; e2 [cap] = 0 ;
    e2 [rev] = e1 ;
    e2 [next] = v [head] ; v [head] = e2 ;
}

void dump () {
    cout << "------------------------------------\n" ;
    for_( i , 1 , nl + nr + 2 )
        for_e_( e , i )
            cout << "Labeled[" << i << "\\[DirectedEdge]" << e [to] << "," << e [cap] <<"],\n" ;
    cout << "------------------------------------\n" ;
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

int result [ __ ] ;

int main () {
    ios :: sync_with_stdio ( false ) ;

    int M ;
    cin >> nl >> nr >> M ;

    src = nl + nr + 1 ; sink = src + 1 ;

    for_( i , 1 , nl ) newEdge ( src , i , 1 , 0 ) ;
    for_( i , 1 , nr ) newEdge ( nl + i , sink , 1 , 0 ) ;

    while ( M -- ) {
        int u , v ;
        cin >> u >> v ;
        newEdge ( u , nl + v , 1 , 1 ) ;
    }

    cout << dinic () << endl ;

    for_( i , 1 , nl )
        for_e_( e , i )
            if ( e [flag] && e [cap] == 0 ) {
                cout << e [to] - nl << ( i == nl ? '\n' : ' ' );
                break;
            } else if ( ! e [next] )
                cout << 0 << ( i == nl ? '\n' : ' ' );

    return 0;
}

// }}}
