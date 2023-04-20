#include <stdio.h>
long long int potencia(int mensagem, int e) // Função que calcula a potência, sendo o primeiro numero a base e o segundo o expoente
{
    long long int resultado = mensagem;
    for (int i = 0; i < e - 1; i++)
    {
        resultado = resultado * mensagem;
    }
    return resultado;
}
int criptografia(long long int convertido, long long int e, long long int n)
{
    convertido = potencia(convertido, e);
    printf("%lld ", convertido % n);
    return 0;
}
int ordena(char palavra[], int cont, int i, char alfabeto[], int contAlfabeto, int e, int n)
{
    if (cont == i)
    {
        printf("\n");
        return 0;
    }
    else if (palavra[cont] == alfabeto[contAlfabeto])
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

int main()
{
    char palavra[100];
    char alfabeto[27] = "abcdefghijklmnopqrstuvwxyz ";
    printf("Digite a frase que você quer criptografar: ");
    frase(palavra, 0, alfabeto);
    return 0;
}
