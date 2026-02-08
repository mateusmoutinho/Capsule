
typedef struct appdeps{
    const char *route;
    const char *(*get_headder)( const char *key);
    const char *(*get_query_param)( const char *key);
    const unsigned char *(*read_body)(long size);

    


} appdeps;