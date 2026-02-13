//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.globals.h"
//silver_chain_scope_end
void *wrapper_newhttpclient(const char *url){
 BearHttpsRequest *request = newBearHttpsRequest(url);
 return (void*)request;
}
void wrapper_httpclient_set_method(void *client,const char *method){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    BearHttpsRequest_set_method(request, method);
}
void wrapper_httpclient_set_max_redirections(void *client,int max_redirections){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    request->max_redirections = max_redirections;
}
void * wrapper_httpclient_fetch(void *client){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    return (void *)BearHttpsRequest_fetch(request);
}
int wrapper_httpclient_response_get_status_code(void *response){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return resp->status_code;
}

unsigned char * wrapper_httpclient_response_read_body(void *response,long *size){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    unsigned char *body = (unsigned char *)BearHttpsResponse_read_body(resp);
    *size = resp->body_size;
    return body;
}
long wrapper_httpclient_response_get_body_size(void *response){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return resp->body_size;
}

int wrapper_httpclient_response_get_header_size(void *response){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return resp->headers->size;
}
void wrapper_httpclient_set_header(void *client, const char *key, const char *value){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    BearHttpsRequest_add_header(request, key, value);
}
void wrapper_httpclient_set_body(void *client, unsigned char *content, long size){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    BearHttpsRequest_send_any(request, content, size);
}
void wrapper_httpclient_free(void *client){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    BearHttpsRequest_free(request);
}

char *wrapper_httpclient_response_get_header_value_by_key(void *response, const char *key){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return (char *)BearHttpsResponse_get_header_value_by_key(resp, key);
}
const char *wrapper_httpclient_response_get_header_key_by_index(void *response, int index){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return BearHttpsResponse_get_header_key_by_index(resp, index);
}
const char *wrapper_httpclient_response_get_header_value_by_index(void *response, int index){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return BearHttpsResponse_get_header_value_by_index(resp, index);
}

void wrapper_httpclient_response_free(void *response){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    BearHttpsResponse_free(resp);
}