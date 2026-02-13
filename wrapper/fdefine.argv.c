//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.globals.h"
//silver_chain_scope_end

const char *wrapper_get_arg_value(const void *argv,int index){
    return CArgvParse_get_arg((CArgvParse *)argv,index);
}
int wrapper_get_arg_count(const void *argv){
    return ((CArgvParse *)argv)->total_args;
}

const char *wrapper_get_arg_flag_value(const void *argv,const char **flags,int total_flags,int index){
    return CArgvParse_get_flag((CArgvParse *)argv,flags,total_flags,index);
}

int wrapper_get_arg_flag_count(const void *argv,const char **flags,int total_flags){
    return CArgvParse_get_flag_size((CArgvParse *)argv,flags,total_flags);
}

appbool wrapper_has_arg_flag(const void *argv,const char **flags,int total_flags){
    return CArgvParse_is_flags_present((CArgvParse *)argv,flags,total_flags);
}