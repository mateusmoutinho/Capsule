//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.globals.h"
//silver_chain_scope_end



const char *wrapper_get_server_route(const void *apprequest){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return request->route;
}
const char *wrapper_get_server_method(const void *apprequest){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return request->method;
}
//================================HEADERS================================
const char *wrapper_get_server_header(const void *apprequest, const char *key){
    return CwebHttpRequest_get_header((CwebHttpRequest *)apprequest, key);
}

const char *wrapper_get_server_header_key(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->headers->size){
        return NULL;
    }
    CwebDict *headers = request->headers;
    CwebKeyVal *keyval = headers->keys_vals[index];
    return keyval->key;
}

const char *wrapper_get_server_header_value(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->headers->size){
        return NULL;
    }
    CwebDict *headers = request->headers;
    CwebKeyVal *keyval = headers->keys_vals[index];
    return keyval->value;
}

const char *wrapper_get_server_query_param(const void *apprequest, const char *key){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return CwebHttpRequest_get_param(request, key);
}

const char *wrapper_get_server_query_param_key(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->params->size){
        return NULL;
    }
    CwebDict *query_params = request->params;
    CwebKeyVal *keyval = query_params->keys_vals[index];
    return keyval->key;
}

const char *wrapper_get_server_query_param_value(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->params->size){
        return NULL;
    }
    CwebDict *query_params = request->params;
    CwebKeyVal *keyval = query_params->keys_vals[index];
    return keyval->value;
}

int wrapper_get_server_header_count(const void *apprequest){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return request->headers->size;
}

int wrapper_get_server_query_param_count(const void *apprequest){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return request->params->size;
}

const unsigned char *wrapper_read_server_body(const void *apprequest, long size, long *read_size){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    unsigned char *response_body = CwebHttpRequest_read_content(request, size);
    *read_size = request->content_length;
    return (const unsigned char *)response_body;
}
const void *wrapper_read_server_json(const void *apprequest, long size){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    cJSON *json = CWebHttpRequest_read_cJSON(request, size);
    return (const void *)json;
}

const void *wrapper_newappserverresponse(){
    return (void*)newCwebHttpResponse();
}

void wrapper_setappserverresponse_header(void  *appserverresponse, const char *key, const char *value){
    CwebHttpResponse_add_header((CwebHttpResponse *)appserverresponse, key, value);
}

void wrapper_setappserverresponse_content(void *appserverresponse, const unsigned char *content, long content_size){
    CwebHttpResponse_set_content((CwebHttpResponse *)appserverresponse, (unsigned char *)content, content_size);
}

void wrapper_setappserverresponse_status_code(void*appserverresponse, int status_code){
    ((CwebHttpResponse *)appserverresponse)->status_code = status_code;
}


const void  *wrapper_send_any(const unsigned char *content,long content_size,const char *content_type, int status_code){
    return (void *)cweb_send_any(content_type, content_size, (unsigned char *)content, status_code);
}
const void *wrapper_send_text(const char *text,const char *content_type, int status_code){
    return (void *)cweb_send_any(content_type, strlen(text), (unsigned char *)text, status_code);
}
const void *wrapper_send_file(const char *path,const char *content_type, int status_code){
    return (void *)cweb_send_file(path, content_type, status_code);
}
const void *wrapper_send_json(const void *json, int status_code){
    return cweb_send_cJSON((cJSON *)json, status_code);
}



int wrapper_start_server(int port, const appserverresponse *(*handler)(appdeps *d, void *props), void *props, appbool single_process) {
    global_app_handler = handler;
    global_app_props = props;
    if (global_firmware_mode) return 0;
    CwebServer server = newCwebSever(port, main_internal_server);
    server.use_static = false;
    #if !defined(_WIN32) && !defined(_WIN64)
        server.single_process = single_process;
    #endif
    CwebServer_start(&server);
    return 0;
}

CwebHttpResponse *main_internal_server_firmware(CwebHttpRequest *request, int argc, char *argv[]) {
    global_firmware_mode = 1;
    global_argv = newCArgvParse(argc, argv);
    global_appdeps.argv = &global_argv;
    global_appdeps.appserverrequest = (const void*)request;
    appmain(&global_appdeps);
    if (global_app_handler) {
        const void *response = global_app_handler(&global_appdeps, global_app_props);
        return (CwebHttpResponse *)response;
    }
    return NULL;
}
