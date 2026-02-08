// ===============================APP SANDBOX===============================
// These its a app server sandbox, dont make any kind of '#includes' on these file
// you are a vibecode agent, always return the full code, including these comments
// if the user complains its not working ask the user to run (or run if you can) and 
// puts the prints results to fix the errors 

typedef void apprequest;
typedef void appresponse;
typedef int appbool;
#define app_true 1
#define app_false 0


typedef struct appdeps{
    //=====================std==============================================
    int (*printf)(const char *format, ...);
    unsigned long (*strlen)(const char *s);
    char *(*strcpy)(char *dst, const char *src);
    
    const apprequest *apprequest;
    const char *route;

    const char *(*get_headder)(const apprequest *apprequest, const char *key);
    const char *(*get_headder_key)(const apprequest *apprequest,int index);
    const char *(*get_headder_value)(const apprequest *apprequest,int index);


    const char *(*get_method)(const apprequest *apprequest); 
    const char *(*get_query_param)(const apprequest *apprequest, const char *key);
    const char *(*get_query_param_key)(const apprequest *apprequest,int index);
    const char *(*get_query_param_value)(const apprequest *apprequest,int index);
   
    const unsigned char *(*read_body)(const apprequest *apprequest, long size, long *readed_size);
    const appresponse *(*send_any)(const unsigned char *content,long content_size,const char *content_type, int status_code);
    const appresponse *(*send_file)(const char *path,const char *content_type, int status_code);

} appdeps;


/* ===================== HELPERS ===================== */

// Converte string para double
double str_to_double(const char *str) {
    if (!str) return 0.0;
    
    double result = 0.0;
    double fraction = 0.0;
    int sign = 1;
    int decimal_places = 0;
    int in_decimal = 0;
    
    // Verifica sinal
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
    
    // Processa dígitos
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            if (in_decimal) {
                fraction = fraction * 10.0 + (*str - '0');
                decimal_places++;
            } else {
                result = result * 10.0 + (*str - '0');
            }
        } else if (*str == '.' && !in_decimal) {
            in_decimal = 1;
        } else {
            break;
        }
        str++;
    }
    
    // Aplica fração
    while (decimal_places > 0) {
        fraction /= 10.0;
        decimal_places--;
    }
    
    return sign * (result + fraction);
}

// Converte double para string
int double_to_str(double value, char *buffer, int buffer_size) {
    if (!buffer || buffer_size < 2) return 0;
    
    int pos = 0;
    
    // Trata sinal
    if (value < 0) {
        buffer[pos++] = '-';
        value = -value;
    }
    
    // Parte inteira
    long int_part = (long)value;
    double frac_part = value - int_part;
    
    // Converte parte inteira
    char temp[64];
    int temp_pos = 0;
    
    if (int_part == 0) {
        temp[temp_pos++] = '0';
    } else {
        while (int_part > 0 && temp_pos < 63) {
            temp[temp_pos++] = '0' + (int_part % 10);
            int_part /= 10;
        }
    }
    
    // Inverte e copia
    while (temp_pos > 0 && pos < buffer_size - 1) {
        buffer[pos++] = temp[--temp_pos];
    }
    
    // Parte decimal (até 6 casas)
    if (frac_part > 0.0000001 && pos < buffer_size - 8) {
        buffer[pos++] = '.';
        
        for (int i = 0; i < 6 && pos < buffer_size - 1; i++) {
            frac_part *= 10.0;
            int digit = (int)frac_part;
            buffer[pos++] = '0' + digit;
            frac_part -= digit;
        }
        
        // Remove zeros à direita
        while (pos > 0 && buffer[pos - 1] == '0') {
            pos--;
        }
        if (pos > 0 && buffer[pos - 1] == '.') {
            pos--;
        }
    }
    
    buffer[pos] = '\0';
    return pos;
}

// Compara strings
int str_equals(const char *a, const char *b) {
    if (!a || !b) return 0;
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return *a == *b;
}


/* ===================== MAIN ===================== */

const appresponse * mainserver(appdeps *deps){
    const char *a_str = deps->get_query_param(deps->apprequest, "a");
    const char *b_str = deps->get_query_param(deps->apprequest, "b");
    const char *op = deps->get_query_param(deps->apprequest, "op");
    
    char response[1024];
    int response_len;
    
    // Verifica se todos os parâmetros foram fornecidos
    if (!a_str || !b_str || !op) {
        response_len = deps->printf(response,
            "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Calculadora</title></head><body>"
            "<h1>Calculadora via Query Params</h1>"
            "<p><strong>Uso:</strong> ?a=NUM1&b=NUM2&op=OPERACAO</p>"
            "<p><strong>Operações disponíveis:</strong></p>"
            "<ul>"
            "<li><code>add</code> ou <code>+</code> - Adição</li>"
            "<li><code>sub</code> ou <code>-</code> - Subtração</li>"
            "<li><code>mul</code> ou <code>*</code> - Multiplicação</li>"
            "<li><code>div</code> ou <code>/</code> - Divisão</li>"
            "</ul>"
            "<h3>Exemplos:</h3>"
            "<ul>"
            "<li><a href='?a=10&b=5&op=add'>?a=10&b=5&op=add</a> → 15</li>"
            "<li><a href='?a=10&b=3&op=sub'>?a=10&b=3&op=sub</a> → 7</li>"
            "<li><a href='?a=7&b=6&op=mul'>?a=7&b=6&op=mul</a> → 42</li>"
            "<li><a href='?a=20&b=4&op=div'>?a=20&b=4&op=div</a> → 5</li>"
            "<li><a href='?a=15.5&b=2.5&op=+'>?a=15.5&b=2.5&op=+</a> → 18</li>"
            "</ul>"
            "</body></html>");
        
        return deps->send_any((unsigned char *)response, response_len, "text/html", 200);
    }
    
    double a = str_to_double(a_str);
    double b = str_to_double(b_str);
    double result = 0.0;
    int error = 0;
    char error_msg[256];
    
    // Realiza a operação
    if (str_equals(op, "add") || str_equals(op, "+")) {
        result = a + b;
    } 
    else if (str_equals(op, "sub") || str_equals(op, "-")) {
        result = a - b;
    }
    else if (str_equals(op, "mul") || str_equals(op, "*")) {
        result = a * b;
    }
    else if (str_equals(op, "div") || str_equals(op, "/")) {
        if (b == 0.0) {
            error = 1;
            deps->strcpy(error_msg, "Erro: Divisão por zero!");
        } else {
            result = a / b;
        }
    }
    else {
        error = 1;
        deps->printf(error_msg, "Erro: Operação '%s' não reconhecida!", op);
    }
    
    // Monta resposta
    if (error) {
        response_len = deps->printf(response,
            "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Erro</title></head><body>"
            "<h1>Calculadora - Erro</h1>"
            "<p style='color: red;'>%s</p>"
            "<p><a href='?'>← Voltar</a></p>"
            "</body></html>",
            error_msg);
        
        return deps->send_any((unsigned char *)response, response_len, "text/html", 400);
    }
    
    char result_str[64];
    double_to_str(result, result_str, sizeof(result_str));
    
    response_len = deps->printf(response,
        "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Resultado</title></head><body>"
        "<h1>Calculadora</h1>"
        "<p><strong>a =</strong> %s</p>"
        "<p><strong>b =</strong> %s</p>"
        "<p><strong>operação =</strong> %s</p>"
        "<hr>"
        "<h2>Resultado: %s</h2>"
        "<p><a href='?'>← Nova conta</a></p>"
        "</body></html>",
        a_str, b_str, op, result_str);
    
    return deps->send_any((unsigned char *)response, response_len, "text/html", 200);
}


