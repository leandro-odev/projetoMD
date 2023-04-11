#include <stdio.h>
#include <math.h>
/*O código funciona para pequenos numeros, no momento temos que melhorar o algoritmo de verificação de primo, caso o valor seja muito alto pode dar problema
isso é fácil de resolver e irei resolver assim que acordar, o problema do algoritmo no momento é na criação da chave privada, já que o método que estou usando
para cria-la é ineficaz em números grandes, mas é só usar o código da questão 6 que já resolvemos o problema. Sobrando só a otimização do código e a transformação
de letras em números(e a quebra dos números, j*/
int primo(long long int x, long long int i, long long int div)
{
    if (i > x)
    {
        if (div == 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (x % i == 0)
        {
            return primo(x, i + 1, div + 1);
        }
        else
        {
            return primo(x, i + 1, div);
        }
    }
}
long long int mdc(long long int n, long long int i)
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
int coprimo(long long int n, long long int i)
{
    if (i > n)
    {
        printf("\n");
        return 0;
    }
    else
    {
        if (mdc(n, i) == 1)
        {
            printf("%lld ", i);
            return coprimo(n, i + 1);
        }
        else
        {
            return coprimo(n, i + 1);
        }
    }
}
long long int euclidesExtendido(long long int a, long long int b, long long int *s, long long int *t)
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
long long int chavePrivada(long long int a, long long int m)
{
    long long int s, t;
    int mdc = euclidesExtendido(a, m, &s, &t);
    if (mdc != 1)
    {
        return -1;
    }
    return (s % m + m) % m;
}
int gerar()
{
    long long int p, q, e, n, totiente;
    printf("Digite dois números:");
    scanf("%lld%lld", &p, &q);
    if (primo(p, 1, 0) == 1 && primo(q, 1, 0) == 1)
    {
        n = p * q;
        printf("Escolha um desses coprimos para ser o e da sua chave pública\n");
        totiente = (p - 1) * (q - 1);
        coprimo(totiente, 1);
        scanf("%lld", &e);
        printf("A chave pública é %lld %lld\n", e, n);
        return 0;
    }
    else
    {
        printf("Número inválido, digite novamente\n");
        return gerar();
    }
}
int criptografar()
{
    long long int mensagemNormal, mensagemCrip, e, n;
    printf("Digite a mensagem que você quer criptografar:");
    scanf("%lld", &mensagemNormal);
    printf("Digite a chave pública: ");
    scanf("%lld%lld", &e, &n);
    mensagemCrip = pow(mensagemNormal, e);
    printf("A mensagem criptografada é %lld", mensagemCrip % n);
    return 0;
}

int descriptografar()
{
    long long int mensagemCriptografada, p, q, e;
    printf("Digite a mensagem que você quer descriptografar:");
    scanf("%lld", &mensagemCriptografada);
    printf("Digite o p, q e o 'e'");
    scanf("%lld%lld%lld", &p, &q, &e);
    mensagemCriptografada = pow(mensagemCriptografada, chavePrivada(e, ((p - 1) * (q - 1))));
    printf("A mensagem é %lld", mensagemCriptografada % (p * q));
    return 0;
}

int main()
{
    int escolha;
    printf("Digite 1 para gerar a chave pública, 2 para Encriptar ou 3 para Desencriptar.\n");
    scanf("%d", &escolha);
    if (escolha == 1)
    {
        gerar();
        return 0;
    }
    if (escolha == 2)
    {
        criptografar();
        return 0;
    }
    if (escolha == 3)
    {
        descriptografar();
        return 0;
    }
    else
    {
        printf("Opção invalida, por favor, digite novamente");
        return main();
    }
}
