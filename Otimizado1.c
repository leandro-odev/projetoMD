#include <stdio.h>
#include <math.h>
/*O código funciona para pequenos numeros, no momento temos que melhorar o algoritmo de verificação de primo, caso o valor seja muito alto pode dar problema
isso é fácil de resolver e irei resolver assim que acordar, o problema do algoritmo no momento é na criação da chave privada, já que o método que estou usando
para cria-la é ineficaz em números grandes, mas é só usar o código da questão 6 que já resolvemos o problema. Sobrando só a otimização do código e a transformação
de letras em números(e a quebra dos números, j*/
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
long long int coprimo(long long int totiente) // Ver os numeros que são coprimos para a formação da chave 'e'
{
    long long int e;
    printf("Digite um número relativamente primo a %lld:", totiente);
    scanf("%lld", &i);
    if (e > totiente)
    {
        printf("Número inválido, digite novamente\n");
        return coprimo(totiente);
    }
    else
    {
        if (mdc(totiente, e) == 1)
        {
            return e;
        }
        else
        {
            printf("Número inválido, digite novamente\n");
            return coprimo(totiente);
        }
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
long long int potencia(int mensagem, int e) // Função que calcula a base, sendo o primeiro numero a base e o segundo a potência
{
    long long int resultado = mensagem;
    for (int i = 0; i < e - 1; i++)
    {
        resultado = resultado * mensagem;
    }
    return resultado;
}
void criptografar() // Enviar mensagem normal para adquirir a criptografada
{
    long long int mensagem, e, n;
    printf("Digite a mensagem que você quer criptografar:");
    scanf("%lld", &mensagem);
    printf("Digite a chave pública: ");
    scanf("%lld%lld", &e, &n);
    printf("A mensagem criptografada é %lld", potencia(mensagem, e) % n);
    return;
}

void descriptografar() // Enviar chave criptografada para adquirir a mensagem pura
{
    long long int mensagemCriptografada, p, q, e;
    printf("Digite a mensagem que você quer descriptografar:");
    scanf("%lld", &mensagemCriptografada);
    printf("Digite o p, q e o 'e'");
    scanf("%lld%lld%lld", &p, &q, &e);
    mensagemCriptografada = potencia(mensagemCriptografada, chavePrivada(e, ((p - 1) * (q - 1))));
    printf("A mensagem é %lld", mensagemCriptografada % (p * q));
    return;
}

int main() // Escolha de função
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
