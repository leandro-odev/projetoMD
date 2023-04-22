#include <stdio.h>
/*Temos que ajeitar o lance do scanf, já que o código não está parando e arranjar uma forma de ler o espaço corretamente, já que não segue o padrão
de transformação das letras normais, talvez eu tenha pensado numa forma de resolver, mais creio que só vai gastar mais linhas e não vai dar certo*/
int exp_mod_rapida(int mensagem, int e, int n)
{
    int res = 1;
    while (e > 0)
    {
        if (e % 2 == 1)
        {
            res = (res * mensagem) % n;
        }
        mensagem = (mensagem * mensagem) % n;
        e = e / 2;
    }
    return res;
}
long long int euclidesExtendido(long long int a, long long int b, long long int *s, long long int *t) // Achar o 'd'
{
    if (b == 0)
    {
        *s = 1;
        *t = 0;
        return a;
    }
    long long int s1, t1;
    int mdc = euclidesExtendido(b, a % b, &s1, &t1);
    *s = t1;
    *t = s1 - (a / b) * t1;
    return mdc;
}
long long int chavePrivada(long long int a, long long int m) // Enviar o 'd' da chave privada
{
    long long int s, t;
    int mdc = euclidesExtendido(a, m, &s, &t);
    if (mdc != 1)
    {
        return -1;
    }
    return (s % m + m) % m;
}
int main()
{
    int e, p, q;
    printf("Digite a chave publica: ");
    scanf("%d %d %d", &p, &q, &e);
    int mensagem;
    int d = chavePrivada(e, ((p - 1) * (q - 1)));
    while (scanf("%d", &mensagem) != 0)
    {
        int resultado = mensagem;
        resultado = exp_mod_rapida(mensagem, d, p * q);
        char letra = resultado + 63;
        printf("%c", letra);
    }
    return 0;
}
