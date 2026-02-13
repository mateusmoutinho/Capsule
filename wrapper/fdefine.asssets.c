//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.globals.h"
//silver_chain_scope_end

const unsigned char *wrapper_get_asset_content(const char *path,long *size,int *is_binary){
    for(int i=0; i < embedded_assets_total_size; i++){
        if(strcmp(embedded_assets[i].path, path) == 0){
            *size = embedded_assets[i].size;
            *is_binary = embedded_assets[i].is_binary;
            return embedded_assets[i].content;
        }
    }
    return NULL;
 
}
void *wrapper_list_assets(const char *path){
    DtwStringArray *array = newDtwStringArray();
    for(int i=0; i < embedded_assets_total_size; i++){
        if(dtw_starts_with(embedded_assets[i].path, path)){
            DtwStringArray_append(array, embedded_assets[i].path);
        }
    }
    return (void *)array;
  
}
