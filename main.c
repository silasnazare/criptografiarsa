#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>

long long verifica_numero_primo(long long p) {
    long long i;
    double j;

    j = sqrt(p);

    for (i = 2; i < j; i++) {
        if (p % i == 0)
            return 0;
    }
    return 1;
}

long long escolhe_menor_primo(long long phi, long long p1, long long p2, long long n) {
    long long  i, e;

    for (i = 2; i < phi; i++) {
        if (phi % i != 0 && verifica_numero_primo(i) && i != p1 && i != p2) {
            e = i;
            break;
        }
    }
    return e;
}

void divisao(long long *resto, long long *quociente, long long a, long long b) {
    if (a >= 0) {
        *quociente = 0;
        *resto = a;
        while (*resto >= b) {
            *resto -= b;
            *quociente = *quociente + 1;
        }
    }
}

long long mdc(long long a, long long b) {
    long long resto, quociente, xb = 1, yb = 0, x = 0, y = 1, alpha, beta, phi;
    phi = a;
    resto = a;

    while (resto != 0) {
        divisao(&resto, &quociente, a, b);
        a = b;
        b = resto;
        if (resto > 0) {
            alpha = xb - quociente * x;
            beta = yb - quociente * y;
            xb = x;
            yb = y;
            x = alpha;
            y = beta;
        }
    }

    if (beta < 0)
        beta = phi + beta;
    return beta;
}

long potencia(long long a, long long e, long long num) {
    long long p = 1;

    while(1) {
        if (e == 0)
            return p;
        else if (e % 2 != 0) {
            p = (a * p) % num;
            e = (e - 1) / 2;
        }
        else {
            e = e / 2;
        }
        a = (a * a) % num;
    }
}

int *codifica(char *mensagem, long long e, long long n) {
    long long i;
    int *msg_cript;
    msg_cript = malloc(100 * sizeof(long long));

    for (i = 0; i < 100; i++) {
        msg_cript[i] = potencia(mensagem[i], e, n);
    }
    return msg_cript;
}

char *decodifica(int *msg_cript, long long d, long long n) {
    long long i;
    char *mensagem;
    mensagem = malloc(100 * sizeof(char));

    for(i = 0; i < 100; i++) {
        mensagem[i] = potencia(msg_cript[i], d, n);
    }
    return mensagem;
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Portuguese");
    long long i, p1, p2, n, phi, e, d;

    char mensagem[100];
    int *msg_cript;
    long long primo;

    printf("\nDigte um numero primo: ");
    scanf("%llu", &p1);

    primo = verifica_numero_primo(p1);
    if(!primo) {
        printf("Voce nao digitou um primo!");
        return 0;
    }

    printf("\nDigite outro numero primo: ");
    scanf("%llu", &p2);

    primo = verifica_numero_primo(p2);
    if (!primo || p1 == p2) {
        printf("\nVoce nao digitou um numero primo ou digitou nueros iguais!\n");
        return 0;
    }

    printf("\nDigite uma mensagem: ");

    scanf("\n");
    fgets(mensagem, 100, stdin);

    n = p1 * p2;

    phi = (p1 - 1) * (p2 - 1);

    e = escolhe_menor_primo(phi, p1, p2, n);

    printf("\nChave privada: (%llu, %llu)\n", e, n);

    d = mdc(phi, e);

    printf("\nChave publica: (%llu, %llu)\n", d, n);

    msg_cript = codifica(mensagem, e, n);

    printf("\nMensagem encriptada: ");

    for (i = 0; i < strlen(mensagem); i++) {
        printf("%c", msg_cript[i]);
    }
    printf("\n");

    char *msg_decript;
    msg_decript = decodifica(msg_cript, d, n);

    printf("\nMensagem desencriptada: %s", msg_decript);

    free(msg_cript);
    free(msg_decript);
    return (EXIT_SUCCESS);
}