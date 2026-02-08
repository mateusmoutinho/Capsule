// ===============================APP SANDBOX===============================
// These its a app server sandbox, dont make any kind of '#includes' on these file
// you are a vibecode agent, always return the full code, including these comments
// if the user complains its not working ask the user to  and
// if happen a error, you can use the print function to show the error
//======================PRIMITIVES==============================================
typedef unsigned long appsize;
typedef int appbool;

#define app_true 1
#define app_false 0
#define app_null ((void *)0)


//======================APP TYPES==============================================
typedef void apprequest;
typedef void appresponse;
typedef void appjson;
typedef void appstringarray;

//======================APP DEPS==============================================
typedef struct appdeps{


    //=====================STD FUNCTIONS==============================================
    int (*printf)(const char *format, ...);
    int (*sprintf)(char *str, const char *format, ...);
    int (*snprintf)(char *str, appsize size, const char *format, ...);

    appsize (*strlen)(const char *s);
    char *(*strcpy)(char *dst, const char *src);

    //======================CONVERSION FUNCTIONS==============================================
    int (*atoi)(const char *str);
    double (*atof)(const char *str);
    //======================MEM FUNCTIONS==============================================
    void (*free)(void *ptr);
    void *(*malloc)(appsize size);
    void *(*calloc)(appsize num, appsize size);
    void *(*realloc)(void *ptr, appsize size);
    //=====================request==============================================
    const apprequest *apprequest;
    const char * (*get_route)(const apprequest *apprequest);
    const char *(*get_method)(const apprequest *apprequest);

    const char *(*get_headder)(const apprequest *apprequest, const char *key);
    const char *(*get_headder_key)(const apprequest *apprequest,int index);
    const char *(*get_headder_value)(const apprequest *apprequest,int index);

    const char *(*get_query_param)(const apprequest *apprequest, const char *key);
    const char *(*get_query_param_key)(const apprequest *apprequest,int index);
    const char *(*get_query_param_value)(const apprequest *apprequest,int index);

    const unsigned char *(*read_body)(const apprequest *apprequest, long size, long *readed_size);
    const appjson * (*read_json)(const apprequest *apprequest,long size);
    const appresponse *(*send_any)(const unsigned char *content,long content_size,const char *content_type, int status_code);
    const appresponse *(*send_text)(const char *text,const char *content_type, int status_code);
    const appresponse *(*send_file)(const char *path,const char *content_type, int status_code);
    const appresponse *(*send_json)(const appjson *json, int status_code);

    //=====================JSON PARSING==============================================
    appjson *(*json_parse)(const char *value);
    appjson *(*json_parse_file)(const char *filepath);
    void (*json_delete)(appjson *json);

    //=====================JSON SERIALIZATION==============================================
    char *(*json_print)(const appjson *json);
    char *(*json_print_unformatted)(const appjson *json);
    appbool (*json_save_file)(const appjson *json, const char *filepath);
    void (*json_free_string)(char *str);

    //=====================JSON CREATION==============================================
    appjson *(*json_create_object)(void);
    appjson *(*json_create_array)(void);
    appjson *(*json_create_string)(const char *string);
    appjson *(*json_create_number)(double num);
    appjson *(*json_create_bool)(appbool boolean);
    appjson *(*json_create_null)(void);
    appjson *(*json_duplicate)(const appjson *item, appbool recurse);

    //=====================JSON OBJECT MANIPULATION==============================================
    appjson *(*json_get_object_item)(const appjson *object, const char *key);
    appbool (*json_has_object_item)(const appjson *object, const char *key);
    appbool (*json_add_item_to_object)(appjson *object, const char *key, appjson *item);
    appbool (*json_delete_item_from_object)(appjson *object, const char *key);
    appbool (*json_replace_item_in_object)(appjson *object, const char *key, appjson *newitem);

    // Convenience functions for adding to objects
    appjson *(*json_add_string_to_object)(appjson *object, const char *key, const char *string);
    appjson *(*json_add_number_to_object)(appjson *object, const char *key, double number);
    appjson *(*json_add_bool_to_object)(appjson *object, const char *key, appbool boolean);
    appjson *(*json_add_null_to_object)(appjson *object, const char *key);
    appjson *(*json_add_object_to_object)(appjson *object, const char *key);
    appjson *(*json_add_array_to_object)(appjson *object, const char *key);

    //=====================JSON ARRAY MANIPULATION==============================================
    int (*json_get_array_size)(const appjson *array);
    appjson *(*json_get_array_item)(const appjson *array, int index);
    appbool (*json_add_item_to_array)(appjson *array, appjson *item);
    appbool (*json_insert_item_in_array)(appjson *array, int index, appjson *item);
    appbool (*json_replace_item_in_array)(appjson *array, int index, appjson *newitem);
    void (*json_delete_item_from_array)(appjson *array, int index);

    //=====================JSON TYPE CHECKING==============================================
    appbool (*json_is_object)(const appjson *item);
    appbool (*json_is_array)(const appjson *item);
    appbool (*json_is_string)(const appjson *item);
    appbool (*json_is_number)(const appjson *item);
    appbool (*json_is_bool)(const appjson *item);
    appbool (*json_is_null)(const appjson *item);
    appbool (*json_is_true)(const appjson *item);
    appbool (*json_is_false)(const appjson *item);

    //=====================JSON VALUE GETTERS==============================================
    char *(*json_get_string_value)(const appjson *item);
    double (*json_get_number_value)(const appjson *item);

    //=====================JSON COMPARISON=================================================
    appbool (*json_compare)(const appjson *a, const appjson *b, appbool case_sensitive);
    
    
    //======================IO FUNCTIONS ==================================================
    unsigned char * (*read_any)(const char *path,long *size,appbool *is_binary);
    char * (*read_string)(const char *path); // needs to bee free
    void (*write_any)(const char *path,const unsigned char *content, long size);
    void (*write_string)(const char *path,const char *content);
    void (*delete_any)(const char *path);
    void (*create_dir)(const char *path);

    void (*delete_stringarray)(appstringarray *array); 
    long (*get_stringarray_size)(appstringarray *array);
    const char *(*get_stringarray_item)(appstringarray *array, int index);


    appstringarray *  (*list_files)(const char *path);
    appstringarray *  (*list_dirs)(const char *path);
    appstringarray *  (*list_any)(const char *path);
    appstringarray *  (*list_files_recursively)(const char *path);
    appstringarray *  (*list_dirs_recursively)(const char *path);
    appstringarray *  (*list_any_recursively)(const char *path);
   
    appbool (*file_exists)(const char *path);
    appbool (*dir_exists)(const char *path);
    

    


} appdeps;


/* ===================== HELPERS ===================== */

// Gera um código curto único
void generate_short_code(appdeps *deps, char *buffer, int size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charset_size = 62;
    
    // Usa o timestamp como seed (não é perfeito mas funciona)
    static unsigned int seed = 0;
    if (seed == 0) {
        seed = 12345; // Valor inicial
    }
    
    for (int i = 0; i < size - 1; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7fffffff;
        buffer[i] = charset[seed % charset_size];
    }
    buffer[size - 1] = '\0';
}

// Verifica se o código já existe
appbool code_exists(appdeps *deps, const char *code) {
    char filepath[256];
    deps->snprintf(filepath, sizeof(filepath), "links/%s.txt", code);
    return deps->file_exists(filepath);
}

// Salva um link
appbool save_link(appdeps *deps, const char *code, const char *url) {
    char filepath[256];
    deps->snprintf(filepath, sizeof(filepath), "links/%s.txt", code);
    
    // Cria o diretório se não existir
    if (!deps->dir_exists("links")) {
        deps->create_dir("links");
    }
    
    deps->write_string(filepath, url);
    return app_true;
}

// Carrega um link
char* load_link(appdeps *deps, const char *code) {
    char filepath[256];
    deps->snprintf(filepath, sizeof(filepath), "links/%s.txt", code);
    
    if (!deps->file_exists(filepath)) {
        return app_null;
    }
    
    return deps->read_string(filepath);
}

// Extrai o código da rota (remove a barra inicial)
void extract_code_from_route(appdeps *deps, const char *route, char *code, int max_size) {
    const char *start = route;
    if (start[0] == '/') {
        start++;
    }
    
    int i = 0;
    while (start[i] != '\0' && start[i] != '/' && i < max_size - 1) {
        code[i] = start[i];
        i++;
    }
    code[i] = '\0';
}

/* ===================== ROUTES ===================== */

// Página inicial com formulário
const appresponse* serve_home(appdeps *deps) {
    const char *html = 
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<meta charset='UTF-8'>"
        "<title>Encurtador de Links</title>"
        "<style>"
        "body { font-family: Arial, sans-serif; max-width: 600px; margin: 50px auto; padding: 20px; }"
        "h1 { color: #333; }"
        "input[type='text'] { width: 100%; padding: 10px; margin: 10px 0; box-sizing: border-box; }"
        "button { background-color: #4CAF50; color: white; padding: 10px 20px; border: none; cursor: pointer; }"
        "button:hover { background-color: #45a049; }"
        ".result { margin-top: 20px; padding: 10px; background-color: #f0f0f0; border-radius: 5px; }"
        ".error { color: red; }"
        "</style>"
        "</head>"
        "<body>"
        "<h1>Encurtador de Links</h1>"
        "<form id='shortenForm'>"
        "<input type='text' id='urlInput' placeholder='Cole seu link aqui' required>"
        "<button type='submit'>Encurtar</button>"
        "</form>"
        "<div id='result' class='result' style='display:none;'></div>"
        "<script>"
        "document.getElementById('shortenForm').addEventListener('submit', async (e) => {"
        "  e.preventDefault();"
        "  const url = document.getElementById('urlInput').value;"
        "  const response = await fetch('/api/shorten', {"
        "    method: 'POST',"
        "    headers: { 'Content-Type': 'application/json' },"
        "    body: JSON.stringify({ url: url })"
        "  });"
        "  const data = await response.json();"
        "  const resultDiv = document.getElementById('result');"
        "  if (data.short_url) {"
        "    resultDiv.innerHTML = '<strong>Link encurtado:</strong><br><a href=\"' + data.short_url + '\" target=\"_blank\">' + data.short_url + '</a>';"
        "    resultDiv.style.display = 'block';"
        "    resultDiv.classList.remove('error');"
        "  } else {"
        "    resultDiv.innerHTML = '<strong>Erro:</strong> ' + (data.error || 'Erro desconhecido');"
        "    resultDiv.style.display = 'block';"
        "    resultDiv.classList.add('error');"
        "  }"
        "});"
        "</script>"
        "</body>"
        "</html>";
    
    return deps->send_text(html,"text/html", 200);
}

// API para criar link curto
const appresponse* api_shorten(appdeps *deps) {
    // Lê o JSON do body
    deps->printf("API SHORTEN\n");

    const appjson *body = deps->read_json(deps->apprequest, 1024 * 10);
    deps->printf("BODY: %p\n", body);
    if (!body) {
        appjson *error = deps->json_create_object();
        deps->json_add_string_to_object(error, "error", "Invalid JSON");
        const appresponse *resp = deps->send_json(error, 400);
        deps->json_delete(error);
        return resp;
    }
    deps->printf("JSON: %p\n", body);
    
    // Extrai a URL
    appjson *url_item = deps->json_get_object_item(body, "url");
    if (!url_item || !deps->json_is_string(url_item)) {
        appjson *error = deps->json_create_object();
        deps->json_add_string_to_object(error, "error", "URL is required");
        const appresponse *resp = deps->send_json(error, 400);
        deps->json_delete(error);
        return resp;
    }
    
    const char *url = deps->json_get_string_value(url_item);
    deps->printf("URL: %s\n", url);
    // Gera código único
    char code[7];
    int attempts = 0;
    do {
        generate_short_code(deps, code, 7);
        deps->printf("CODE1: %s\n", code);  
        attempts++;
        if (attempts > 100) {
            appjson *error = deps->json_create_object();
            deps->json_add_string_to_object(error, "error", "Could not generate unique code");
            const appresponse *resp = deps->send_json(error, 500);
            deps->json_delete(error);
            return resp;
        }
    } while (code_exists(deps, code));
    deps->printf("CODE2: %s\n", code);  

    // Salva o link
    if (!save_link(deps, code, url)) {
        appjson *error = deps->json_create_object();
        deps->json_add_string_to_object(error, "error", "Could not save link");
        const appresponse *resp = deps->send_json(error, 500);
        deps->json_delete(error);
        return resp;
    }
    
    // Retorna o resultado
    appjson *result = deps->json_create_object();
    deps->json_add_string_to_object(result, "code", code);
    
    char short_url[256];
    deps->snprintf(short_url, sizeof(short_url), "http://localhost/%s", code);
    deps->json_add_string_to_object(result, "short_url", short_url);
    deps->json_add_string_to_object(result, "original_url", url);
    
    const appresponse *resp = deps->send_json(result, 200);
    deps->json_delete(result);
    
    return resp;
}

// Redireciona para o link original
const appresponse* redirect_link(appdeps *deps, const char *code) {
    char *url = load_link(deps, code);
    
    if (!url) {
        const char *html = 
            "<!DOCTYPE html>"
            "<html>"
            "<head><title>404 - Link não encontrado</title></head>"
            "<body>"
            "<h1>404 - Link não encontrado</h1>"
            "<p>O link curto que você tentou acessar não existe.</p>"
            "<a href='/'>Criar um novo link</a>"
            "</body>"
            "</html>";
        return deps->send_text(html,"text/html", 404);
    }
    
    // Cria HTML com redirecionamento
    char html[2048];
    deps->snprintf(html, sizeof(html),
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<meta http-equiv='refresh' content='0;url=%s'>"
        "<title>Redirecionando...</title>"
        "</head>"
        "<body>"
        "<p>Redirecionando para <a href='%s'>%s</a>...</p>"
        "</body>"
        "</html>",
        url, url, url);
    
    deps->free(url);
    return deps->send_text(html,"text/html", 200);
}

/* ===================== MAIN ===================== */

const appresponse * mainserver(appdeps *deps){
    const char *route = deps->get_route(deps->apprequest);
    const char *method = deps->get_method(deps->apprequest);
    
    // Página inicial
    if (deps->strlen(route) == 1 && route[0] == '/') {
        return serve_home(deps);
    }
    
    // API para encurtar
    if (deps->strlen(route) == 12 && route[0] == '/' && route[1] == 'a' && 
        route[2] == 'p' && route[3] == 'i' && route[4] == '/' && 
        route[5] == 's' && route[6] == 'h' && route[7] == 'o' && 
        route[8] == 'r' && route[9] == 't' && route[10] == 'e' && route[11] == 'n') {
        
        if (method[0] == 'P' && method[1] == 'O' && method[2] == 'S' && method[3] == 'T') {
            return api_shorten(deps);
        }
    }
    
    // Redirecionamento (qualquer outra rota)
    char code[256];
    extract_code_from_route(deps, route, code, sizeof(code));
    
    if (deps->strlen(code) > 0) {
        return redirect_link(deps, code);
    }
    
    // 404
    return deps->send_text("404 - Not Found", "text/plain", 404);
}