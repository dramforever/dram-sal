// Usage: call readAll

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
