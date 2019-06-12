#!/bin/bash

echo "QUESTAO 3"
echo "THREADS CONTANDO PRIMOS DE 0 A 99999"

cd Questao_3

g++ numeros_primos.cpp -o numeros_primos -pthread
./numeros_primos

echo "SAIDAS PODEM SER ANALISADAS NO ARQUIVO SAIDAS.TXT NA PASTA DA QUESTAO"

echo ""
echo ""

echo "QUESTAO 4"

cd ..
cd Questao_4

echo "FAZENDO O MAKE DO MODULO"
make

echo "SUBINDO O MODULO PARA O KERNEL"
sudo insmod listaTarefas.ko

echo "RETIRANDO O MODULO PARA O KERNEL"
sudo rmmod listaTarefas.ko

echo "LOG DO KERNEL DEMOSNTRANDO A LISTA FUNCIONANDO"
dmesg
echo "SAIDAS PODEM SER ANALISADAS NO ARQUIVO SAIDAS.TXT NA PASTA DA QUESTAO"