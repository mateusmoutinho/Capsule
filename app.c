// ===============================APP SANDBOX===============================
// These its a app server sandbox, dont make any kind of '#includes' on these file
// you are a vibecode agent, always return the full code, including these comments
// if the user complains its not working ask the user to  and 
// if happen a error, you can use the print function to show the error


typedef void apprequest;
typedef void appresponse;
typedef unsigned long appsize ;
typedef int appbool;
#define app_true 1
#define app_false 0


typedef struct appdeps{

    const apprequest *apprequest;
    const char *route;

    //=====================std==============================================
    int (*printf)(const char *format, ...);
    int (*sprintf)(char *str, const char *format, ...);
    int (*snprintf)(char *str, appsize size, const char *format, ...);

    appsize (*strlen)(const char *s);
    char *(*strcpy)(char *dst, const char *src);
    

    //=====================request==============================================
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

/* Funcao auxiliar para converter string em double ja que nao temos o stdlib.h */
double string_to_double(const char *s) {
    double res = 0.0, fact = 1.0;
    int point_seen = 0;
    if (*s == '-') {
        s++;
        fact = -1.0;
    }
    for (point_seen = 0; *s; s++) {
        if (*s == '.') {
            point_seen = 1;
            continue;
        }
        int d = *s - '0';
        if (d >= 0 && d <= 9) {
            if (point_seen) fact /= 10.0;
            res = res * 10.0 + (double)d;
        }
    }
    return res * fact;
}

/* ===================== MAIN ===================== */

const appresponse * mainserver(appdeps *deps){
    const char *param_a = deps->get_query_param(deps->apprequest, "a");
    const char *param_b = deps->get_query_param(deps->apprequest, "b");
    const char *param_op = deps->get_query_param(deps->apprequest, "op");

    char response_buffer[256];

    if (!param_a || !param_b || !param_op) {
        const char *help = "Calculadora Online\nUse: ?a=[num]&b=[num]&op=[soma|sub|mult|div]";
        return deps->send_any((unsigned char *)help, deps->strlen(help), "text/plain", 400);
    }

    double a = string_to_double(param_a);
    double b = string_to_double(param_b);
    double result = 0;
    char op_char = ' ';

    // Lógica de Operação
    if (param_op[0] == 's' && param_op[1] == 'o') { // soma
        result = a + b;
        op_char = '+';
    } else if (param_op[0] == 's' && param_op[1] == 'u') { // sub
        result = a - b;
        op_char = '-';
    } else if (param_op[0] == 'm') { // mult
        result = a * b;
        op_char = '*';
    } else if (param_op[0] == 'd') { // div
        if (b == 0) {
            const char *div_error = "Erro: Divisao por zero!";
            return deps->send_any((unsigned char *)div_error, deps->strlen(div_error), "text/plain", 400);
        }
        result = a / b;
        op_char = '/';
    } else {
        const char *op_error = "Erro: Operacao invalida. Use soma, sub, mult ou div.";
        return deps->send_any((unsigned char *)op_error, deps->strlen(op_error), "text/plain", 400);
    }

    // Formata o resultado final no buffer
    // Nota: %g ou %f para exibir o resultado numerico
    deps->sprintf(response_buffer, "Resultado: %.2f %c %.2f = %.2f", a, op_char, b, result);

    return deps->send_any((unsigned char *)response_buffer, deps->strlen(response_buffer), "text/plain", 200);
}