#!/bin/bash

echo "QUESTAO 3"
echo "THREADS CONTANDO PRIMOS DE 0 A 99999"

cd Questao_3

g++ numeros_primos.cpp -o numeros_primos -pthread
./numeros_primos

echo "Salvando saidas em um arquivo"
./numeros_primos > saidas.txt