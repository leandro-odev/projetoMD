#include <stdio.h>
#include <math.h>
#include <ctype.h>

int primo(long long int x, long long int i, long long int div) // Verificar se os números p e q são primos
{
    if (i > sqrt(x))
    {
        if (div != 1 || x == 1 || x == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (x % i == 0)
        {
            return primo(x, i + 2, div + 1);
        }
        else
        {
            return primo(x, i + 2, div);
        }
    }
}
long long int mdc(long long int n, long long int i) // Ver o mdc de todos possiveis numeros
{
    if (n % i == 0)
    {
        return i;
    }
    else
    {
        return mdc(i, n % i);
    }
}
long long int coprimo(long long int n) // Ver os numeros que são coprimos para a formação da chave 'e'
{
    long long int i;
    printf("Digite um número relativamente primo a %lld:", n);
    scanf("%lld", &i);
    if (i > n)
    {
        printf("Número inválido, digite novamente\n");
        return coprimo(n);
    }
    else
    {
        if (mdc(n, i) == 1)
        {
            return i;
        }
        else
        {
            printf("Número inválido, digite novamente\n");
            return coprimo(n);
        }
    }
}
void gerar() // Função que gera a chave pública
{
    long long int p, q, e, n, totiente;
    printf("Digite dois números:");
    scanf("%lld%lld", &p, &q);
    if (primo(p, 1, 0) == 1 && primo(q, 1, 0) == 1)
    {
        n = p * q;
        totiente = (p - 1) * (q - 1);
        printf("A chave pública é %lld %lld\n", coprimo(totiente), n);
        return;
    }
    else
    {
        printf("Número inválido, digite novamente\n");
        gerar();
    }
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
int criptografia(long long int convertido, long long int e, long long int n)
{
    printf("%d ", exp_mod_rapida(convertido, e, n));
    return 0;
}
int ordena(char palavra[], int cont, int i, char alfabeto[], int contAlfabeto, int e, int n)
{
    if (cont == i)
    {
        printf("\n");
        return 0;
    }
    else if (toupper(palavra[cont]) == alfabeto[contAlfabeto])
    {
        if (contAlfabeto == 26)
        {
            int convertido = 28;
            criptografia(convertido, e, n);
            return ordena(palavra, cont + 1, i, alfabeto, 0, e, n);
        }
        int convertido = alfabeto[contAlfabeto] - 63;
        criptografia(convertido, e, n);
        return ordena(palavra, cont + 1, i, alfabeto, 0, e, n);
    }
    return ordena(palavra, cont, i, alfabeto, contAlfabeto + 1, e, n);
}

void frase(char palavra[], int i, char alfabeto[])
{
    scanf("%c", &palavra[i]);
    if (palavra[i] == '\n')
    {
        int e, n;
        printf("Digite a chave publica: ");
        scanf("%d %d", &e, &n);
        ordena(palavra, 0, i, alfabeto, 0, e, n);
        return;
    }
    frase(palavra, i + 1, alfabeto);
}
int descriptografar(int mensagem, int d, int n) // Enviar chave criptografada para adquirir a mensagem pura
{
    scanf("%d", &mensagem);
    if (mensagem != 0)
    {
        int resultado = mensagem;
        resultado = exp_mod_rapida(mensagem, d, n);
        char letra = resultado + 63;
        if (letra > 90 || letra < 65)
        {
            letra = ' ';
        }
        printf("%c", letra);
        return descriptografar(mensagem, d, n);
    }
    else if (mensagem <= 0)
    {
        return 0;
    }
}

int main() // Escolha de função
{
    int escolha;
    char palavra[255];
    char alfabeto[27] = "abcdefghijklmnopqrstuvwxyz ";
    printf("Digite 1 para gerar a chave pública, 2 para Encriptar ou 3 para Desencriptar.\n");
    scanf("%d", &escolha);
    if (escolha == 1)
    {
        gerar();
        return 0;
    }
    if (escolha == 2)
    {
        printf("Digite a frase que você quer criptografar: ");
        scanf("%c", &palavra[0]);
        frase(palavra, 0, alfabeto);
        return 0;
    }
    if (escolha == 3)
    {
        int e, p, q;
        printf("Digite o 'p', 'q' e 'e': ");
        scanf("%d %d %d", &p, &q, &e);
        int mensagem;
        printf("Digite a mensagem que você quer descriptografar: ");
        int d = chavePrivada(e, ((p - 1) * (q - 1)));
        descriptografar(mensagem, d, p * q);
    }
    else
    {
        printf("Opção invalida, por favor, digite novamente");
        return main();
    }
}

