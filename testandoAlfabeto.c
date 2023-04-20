#include <stdio.h>
/*TODO: Transformar letras minúsculas em maiúsculas, enviar valores convertidos para a função criptografia e descriptografia(nesse caso creio que seja 
preciso uma função extra para destransformar para letra)*/
int ordena(char palavra[], int cont, int i, char alfabeto[], int contAlfabeto)
{
    if (cont == i)
    {
        printf("\n");
        return 0;
    }
    else if (palavra[cont] == alfabeto[contAlfabeto])//verifica se a letra da palavra é igual a letra do alfabeto da posição do array e ativa a função caso seja
    {
        if (contAlfabeto == 26)//Valor do espaço, já que não segue o mesmo padrão das letras em ascii
        {
            int convertido = 28;
            printf("%d ", convertido);
            return ordena(palavra, cont + 1, i, alfabeto, 0);
        }
        int convertido = alfabeto[contAlfabeto] - 63;//Conversor de letra para numero (ASCII - 63)
        printf("%d ", convertido);
        return ordena(palavra, cont + 1, i, alfabeto, 0);
    }
    return ordena(palavra, cont, i, alfabeto, contAlfabeto + 1);//caso a letra não seja igual ao alfabeto, adiciona 1 no contador do alfabeto e verifica novamente;
}

void frase(char palavra[], int i, char alfabeto[])
{
    scanf("%c", &palavra[i]);//scan da letra na posição do array, inicialmente 0, caso dê um \n, o programa enviar
    if (palavra[i] == '\n')
    {
        ordena(palavra, 0, i, alfabeto, 0);
        return;
    }
    frase(palavra, i + 1, alfabeto);
}

int main()
{
    char palavra[100];
    char alfabeto[27] = "abcdefghijklmnopqrstuvwxyz ";
    frase(palavra, 0, alfabeto);
    return 0;
}
