#include <bits/stdc++.h> 
#include <vector>
#include <pthread.h>

using namespace std;

pthread_mutex_t travador;

vector<int> numeros_primos;

void *calcular_primos(void *inferior)
{
    pthread_mutex_lock(&travador);

    int *a = (int *)inferior;

    int menor = *a;
    int maior = menor + 1000;

    while(menor <= maior)
    {
        //ideia para realizar esse código pode
        //ser encontrada em https://www.guj.com.br/t/thread-e-numeros-primos/117427/4
        int is_primo = 0;
        for(int i = 2; i < menor ; i++)
        {
            int resultado = menor % i;
            if(resultado == 0)
            {
                is_primo = 1;
                break;
            }
        }
        if(is_primo == 0)
        {
            numeros_primos.push_back(menor);
        }
        menor++;
    }
    pthread_mutex_unlock(&travador);
}

int main()
{
    pthread_t threads[101];
    int i, status, menor = 2;

    if(pthread_mutex_init(&travador,NULL))
    {
        return 1;
    }
    else
    {
        for(i = 0; i < 100; i++)
        {
            status = pthread_create(&threads[i],NULL,calcular_primos,(void *)& menor);
            
            if(status != 0)
            {
                exit(-1);
            }
            pthread_join(threads[i],NULL);
            menor += 1000;
        }
    
    }

    sort(numeros_primos.begin(), numeros_primos.end());

    cout << "Lista dos Numeros Primos" << endl;

    for(i = 0 ; i < numeros_primos.size() ; i++)
    {
        cout << "Valor " << i+1 << " : " << numeros_primos[i] << endl; 
    }

    pthread_exit(NULL);
    pthread_mutex_destroy(&travador);

}