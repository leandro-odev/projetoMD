#include <stdio.h>
#include <math.h>
/*O código funciona para pequenos numeros, no momento temos que melhorar o algoritmo de verificação de primo, caso o valor seja muito alto pode dar problema
isso é fácil de resolver e irei resolver assim que acordar, o problema do algoritmo no momento é na criação da chave privada, já que o método que estou usando
para cria-la é ineficaz em números grandes, mas é só usar o código da questão 6 que já resolvemos o problema. Sobrando só a otimização do código e a transformação
de letras em números(e a quebra dos números, j*/
int primo(long long int x, long long int i, long long int div) // Verificar se os números p e q são primos
{
    if (i > x / 2)
    {
        if (x % 2 == 0 && x != 2 || x == 1 || x == 0 || div != 1)
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
int coprimo(long long int n, long long int i) // Ver os numeros que são coprimos para a formação da chave 'e'
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
        FILE *gerar;
        gerar = fopen("chavePrivada.txt", "w");
        fprintf(gerar, "-1");
        fclose(gerar);
        return -1;
    }

    FILE *gerar;
    gerar = fopen("chavePrivada.txt", "w");
    fprintf(gerar, "%lld", (s % m + m) % m);
    fclose(gerar);

    return (s % m + m) % m;
}
void gerar() // Função que gera a chave pública
{
    long long int p, q, e, n, totiente;
    printf("Digite dois números: ");
    scanf("%lld%lld", &p, &q);
    if (primo(p, 1, 0) == 1 && primo(q, 1, 0) == 1)
    {
        n = p * q;
        printf("Escolha um desses coprimos para ser o e da sua chave pública\n");
        totiente = (p - 1) * (q - 1);
        coprimo(totiente, 1);
        scanf("%lld", &e);
        printf("A chave pública é %lld %lld\n", e, n);

        FILE *gerar;
        gerar = fopen("chavePublica.txt", "w");
        fprintf(gerar, "%lld %lld", e, n);
        fclose(gerar);

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

    FILE *gerar;
    gerar = fopen("mensagemCriptografada.txt", "w");
    fprintf(gerar, "%lld", potencia(mensagem, e) % n);
    fclose(gerar);

    return;
}

void descriptografar() // Enviar chave criptografada para adquirir a mensagem pura
{
    long long int mensagemCriptografada, p, q, e, msgCrip2;
    printf("Digite a mensagem que você quer descriptografar:");
    scanf("%lld", &mensagemCriptografada);

    //FILE *descriptografar;
    //descriptografar = fopen("mensagemCriptografada", "r");
    //mensagemCriptografada = fgets(msgCrip2, 100, descriptografar);
    //fclose(descriptografar);

    printf("Digite o p, q e o 'e'");
    scanf("%lld%lld%lld", &p, &q, &e);
    mensagemCriptografada = potencia(mensagemCriptografada, chavePrivada(e, ((p - 1) * (q - 1))));
    printf("A mensagem é %lld", mensagemCriptografada % (p * q));
    return;
}

int main() // Escolha de função
{

    printf("-----------------------------------\n");
    printf("      Bem vindo ao projeto de      \n");
    printf("          Cripografia RSA          \n");
    printf("-----------------------------------\n");
    printf("\n");

    int escolha;

    while (escolha != 4)
    {
        printf("Para comecar escolha a opcao desejada:\n");
        printf("1 - Gerar chave publica\n");
        printf("2 - Encriptar\n");
        printf("3 - Desencriptar\n");
        scanf("%d", escolha);
        printf("\n");

        if (escolha != 1 || escolha != 2 || escolha != 3)
        {
            printf("Opcao invalida!\n");
            printf("Por favor, digite novamente\n");
            printf("\n");
        }
        else if (escolha == 1)
        {
            printf("entrou no gerar\n");
            gerar();
        }
        else if (escolha == 2)
        {
            printf("entrou no criptografar\n");
            criptografar();
        }
        else if (escolha == 3)
        {
            printf("entrou no descriptografar\n");
            descriptografar();
        }
    }

    printf("Obrigado por usar o programa!\n");

    return 0;
}
