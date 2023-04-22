#include <stdio.h>
#include <math.h>

int primo(long long int x, long long int i, long long int div) // Verificar se os números p e q são primos
{
    while(i <= x / 2)
    {
        if (x % i == 0)
        {
            i += 2; 
            div += 1;
        }
        else
        {
            i += 2; 
        }
    
    }
    if (x % 2 == 0 && x != 2 || x == 1 || x == 0 || div != 1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
}

long long int mdc(long long int n, long long int i) // Ver o mdc de todos possiveis numeros
{
    while(n%i != 0)
    {
        long long int aux = i;
        i = n % i;
        n = aux;
    }
    return i;
}

int coprimo(long long int n, long long int i) // Ver os numeros que são coprimos para a formação da chave 'e'
{
    for(i=i, i>n, i++)
    {
        if (mdc(n, i) == 1)
        {
            printf("%lld ", i);
        }
    }
    printf("\n");
    return 0;
}

/*long long int euclidesExtendido(long long int a, long long int b, long long int *s, long long int *t) // Achar o 'd'
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
*/

long long int euclidesExtendido(long long int a, long long int b, long long int *s, long long int *t)
{
    long long int s0 = 1, s1 = 0, t0 = 0, t1 = 1, r0 = a, r1 = b;
    while (r1 != 0) {
        long long int q = r0 / r1;
        long long int r_temp = r0;
        r0 = r1;
        r1 = r_temp - q * r1;
        long long int s_temp = s0;
        s0 = s1;
        s1 = s_temp - q * s1;
        long long int t_temp = t0;
        t0 = t1;
        t1 = t_temp - q * t1;
    }
    *s = s0;
    *t = t0;
    return r0;
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

    return 0;
}