

const appserverresponse *(*global_app_handler)(appdeps *d, void *props) = NULL;
void *global_app_props = NULL;
appbool global_firmware_mode = 0;


// ===============================GLOBALS======================================
CArgvParse global_argv = {0};
appdeps global_appdeps = {
    // Standard library functions
    .printf = printf,
    .sprintf = sprintf,
    .snprintf = wrapper_snprintf,
    .strlen = wrapper_strlen,
    .strcpy = strcpy,
    .strcat = strcat,
    .strcmp = strcmp,
    .strncmp = wrapper_strncmp,
    .strstr = strstr,
    .strdup = wrapper_strdup,
    .memcpy = wrapper_memcpy,
    .memset = wrapper_memset,
    .memcmp = wrapper_memcmp,
    .atoi = atoi,
    .atof = atof,
    .free = free,
    .malloc = wrapper_malloc,
    .calloc = wrapper_calloc,
    .realloc = wrapper_realloc,
    
    // HTTP request wrapper functions
    .get_server_route = wrapper_get_server_route,
    .get_server_header = wrapper_get_server_header,
    .get_server_header_key = wrapper_get_server_header_key,
    .get_server_header_value = wrapper_get_server_header_value,
    .get_server_method = wrapper_get_server_method,
    .get_server_query_param = wrapper_get_server_query_param,
    .get_server_query_param_key = wrapper_get_server_query_param_key,
    .get_server_query_param_value = wrapper_get_server_query_param_value,
    .get_server_header_count = wrapper_get_server_header_count,
    .get_server_query_param_count = wrapper_get_server_query_param_count,
    .read_server_body = wrapper_read_server_body,
    .read_server_json = wrapper_read_server_json,

    // HTTP response wrapper functions
    .newappserverresponse = wrapper_newappserverresponse,
    .setappserverresponse_header = wrapper_setappserverresponse_header,
    .setappserverresponse_content = wrapper_setappserverresponse_content,
    .setappserverresponse_status_code = wrapper_setappserverresponse_status_code,
    .send_any = wrapper_send_any,
    .send_text = wrapper_send_text,
    .send_file = wrapper_send_file,
    .send_json = wrapper_send_json,

    // JSON parsing functions
    .json_parse = wrapper_json_parse,
    .json_parse_file = wrapper_json_parse_file,
    .json_delete = wrapper_json_delete,

    // JSON serialization functions
    .json_print = wrapper_json_print,
    .json_print_unformatted = wrapper_json_print_unformatted,
    .json_save_file = wrapper_json_save_file,
    .json_free_string = wrapper_json_free_string,

    // JSON creation functions
    .json_create_object = wrapper_json_create_object,
    .json_create_array = wrapper_json_create_array,
    .json_create_string = wrapper_json_create_string,
    .json_create_number = wrapper_json_create_number,
    .json_create_bool = wrapper_json_create_bool,
    .json_create_null = wrapper_json_create_null,
    .json_duplicate = wrapper_json_duplicate,

    // JSON object manipulation functions
    .json_get_object_item = wrapper_json_get_object_item,
    .json_has_object_item = wrapper_json_has_object_item,
    .json_add_item_to_object = wrapper_json_add_item_to_object,
    .json_delete_item_from_object = wrapper_json_delete_item_from_object,
    .json_replace_item_in_object = wrapper_json_replace_item_in_object,
    .json_add_string_to_object = wrapper_json_add_string_to_object,
    .json_add_number_to_object = wrapper_json_add_number_to_object,
    .json_add_bool_to_object = wrapper_json_add_bool_to_object,
    .json_add_null_to_object = wrapper_json_add_null_to_object,
    .json_add_object_to_object = wrapper_json_add_object_to_object,
    .json_add_array_to_object = wrapper_json_add_array_to_object,

    // JSON array manipulation functions
    .json_get_array_size = wrapper_json_get_array_size,
    .json_get_array_item = wrapper_json_get_array_item,
    .json_add_item_to_array = wrapper_json_add_item_to_array,
    .json_insert_item_in_array = wrapper_json_insert_item_in_array,
    .json_replace_item_in_array = wrapper_json_replace_item_in_array,
    .json_delete_item_from_array = wrapper_json_delete_item_from_array,

    // JSON type checking functions
    .json_is_object = wrapper_json_is_object,
    .json_is_array = wrapper_json_is_array,
    .json_is_string = wrapper_json_is_string,
    .json_is_number = wrapper_json_is_number,
    .json_is_bool = wrapper_json_is_bool,
    .json_is_null = wrapper_json_is_null,
    .json_is_true = wrapper_json_is_true,
    .json_is_false = wrapper_json_is_false,

    // JSON value getters
    .json_get_string_value = wrapper_json_get_string_value,
    .json_get_number_value = wrapper_json_get_number_value,

    // JSON comparison
    .json_compare = wrapper_json_compare,

    // JSON iteration
    .json_get_child = wrapper_json_get_child,
    .json_get_next = wrapper_json_get_next,
    .json_get_key = wrapper_json_get_key,
    .json_get_object_size = wrapper_json_get_object_size,

    // IO functions
    .file_exists = wrapper_file_exists,
    .dir_exists = wrapper_dir_exists,
    .copy_any = wrapper_copy_any,
    .move_any = wrapper_move_any,
    .append_string = wrapper_append_string,
    .concat_path = wrapper_concat_path,
    .read_any = wrapper_read_any,
    .read_string = wrapper_read_string,
    .write_any = wrapper_write_any,
    .write_string = wrapper_write_string,
    .delete_any = wrapper_delete_any,
    .create_dir = wrapper_create_dir,

    // String array manipulation functions
    .delete_stringarray = wrapper_delete_stringarray,
    .get_stringarray_size = wrapper_get_stringarray_size,
    .get_stringarray_item = wrapper_get_stringarray_item,

    // List functions
    .list_files = wrapper_list_files,
    .list_dirs = wrapper_list_dirs,
    .list_any = wrapper_list_any,
    .list_files_recursively = wrapper_list_files_recursively,
    .list_dirs_recursively = wrapper_list_dirs_recursively,
    .list_any_recursively = wrapper_list_any_recursively,

    // ArgvParse functions
    .get_arg_value = wrapper_get_arg_value,
    .get_arg_count = wrapper_get_arg_count,
    .get_arg_flag_value = wrapper_get_arg_flag_value,
    .get_arg_flag_count = wrapper_get_arg_flag_count,
    .has_arg_flag = wrapper_has_arg_flag,

    // HTTP client functions
    .newappclientrequest = wrapper_newhttpclient,
    .appclientrequest_set_header = wrapper_httpclient_set_header,
    .appclientrequest_set_method = wrapper_httpclient_set_method,
    .appclientrequest_set_max_redirections = wrapper_httpclient_set_max_redirections,
    .appclientrequest_set_body = wrapper_httpclient_set_body,
    .appclientrequest_free = wrapper_httpclient_free,
    .appclientrequest_fetch = wrapper_httpclient_fetch,
    .appclientresponse_read_body = wrapper_httpclient_response_read_body,
    .appclientresponse_get_body_size = wrapper_httpclient_response_get_body_size,
    .appclientresponse_get_header_value_by_key = wrapper_httpclient_response_get_header_value_by_key,
    .appclientresponse_get_header_key_by_index = wrapper_httpclient_response_get_header_key_by_index,
    .appclientresponse_get_header_value_by_index = wrapper_httpclient_response_get_header_value_by_index,
    .appclientresponse_get_header_size = wrapper_httpclient_response_get_header_size,
    .free_clientresponse = wrapper_httpclient_response_free,
    .get_asset_content = wrapper_get_asset_content,
    .list_assets = wrapper_list_assets,
    .start_server = wrapper_start_server
};
CwebHttpResponse *main_internal_server(CwebHttpRequest *request) {
    global_appdeps.appserverrequest = (const void*)request;
    const void *response = global_app_handler(&global_appdeps, global_app_props);
    return (CwebHttpResponse *)response;
}
