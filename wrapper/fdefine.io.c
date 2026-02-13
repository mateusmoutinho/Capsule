//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.globals.h"
//silver_chain_scope_end
unsigned char *wrapper_read_any(const char *path, long *size, int *is_binary){
    return dtw_load_any_content(path, size, (bool *)is_binary);
}
char *wrapper_read_string(const char *path){
    return dtw_load_string_file_content(path);
}
void wrapper_write_any(const char *path, const unsigned char *content, long size){
    dtw_write_any_content(path, (unsigned char *)content, size);
}

void wrapper_write_string(const char *path, const char *content){
    dtw_write_string_file_content(path, content);
}
void wrapper_delete_any(const char *path){
    dtw_remove_any(path);
}
void wrapper_create_dir(const char *path){
    dtw_create_dir_recursively(path);
}

int wrapper_file_exists(const char *path){
    return dtw_entity_type(path) == DTW_FILE_TYPE;
}
int wrapper_dir_exists(const char *path){
    return dtw_entity_type(path) == DTW_FOLDER_TYPE;
}

int wrapper_copy_any(const char *src, const char *dst){
    return dtw_copy_any(src, dst, false);
}

int wrapper_move_any(const char *src, const char *dst){
    return dtw_move_any(src, dst, false);
}

void wrapper_append_string(const char *path, const char *content){
    char *existing = dtw_load_string_file_content(path);
    if(existing){
        long existing_len = strlen(existing);
        long content_len = strlen(content);
        char *combined = (char *)malloc(existing_len + content_len + 1);
        memcpy(combined, existing, existing_len);
        memcpy(combined + existing_len, content, content_len + 1);
        dtw_write_string_file_content(path, combined);
        free(existing);
        free(combined);
    } else {
        dtw_write_string_file_content(path, content);
    }
}

char *wrapper_concat_path(const char *path1, const char *path2){
    return dtw_concat_path(path1, path2);
}

void wrapper_delete_stringarray(void *array){
    DtwStringArray_free((DtwStringArray *)array);
}
long wrapper_get_stringarray_size(void *array){
    return ((DtwStringArray *)array)->size;
}
const char *wrapper_get_stringarray_item(void *array, int index){
    return ((DtwStringArray *)array)->strings[index];
}

void *wrapper_list_files(const char *path){
    DtwStringArray *files = dtw_list_files(path,false);
    return (void *)files;
}
void *wrapper_list_dirs(const char *path){
    DtwStringArray *dirs = dtw_list_dirs(path,false);
    return (void *)dirs;
}
void *wrapper_list_any(const char *path){
    DtwStringArray *all = dtw_list_all(path,false);
    return (void *)all;
}
void *wrapper_list_files_recursively(const char *path){
    DtwStringArray *files = dtw_list_files_recursively(path,false);
    return (void *)files;
}
void *wrapper_list_dirs_recursively(const char *path){
    DtwStringArray *dirs = dtw_list_dirs_recursively(path,false);
    return (void *)dirs;
}
void *wrapper_list_any_recursively(const char *path){
    DtwStringArray *all = dtw_list_all_recursively(path,false);
    return (void *)all;
}
