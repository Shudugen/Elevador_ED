## Como usar o programa

O Programa recebe como entrada dois arquivos gerados pelo modulo de criação de entradas

 O primeiro arquivo chamado de “Ambiente.txt” é composto por, sequencialmente em cada linha:

 1- Um número inteiro que representa o número de usuários que pretendem utilizar o elevador
 2- Dois números inteiros separados por um espaço, o primeiro representa a capacidade máxima do elevador e o segundo quantidade de andares do prédio. 

 O segundo arquivo chamado de “usuarios.txt” é composto por, sequencialmente em cada linha, três números inteiros separados por um espaço que representam os comandos de cada usuário. O primeiro representa em qual zepsolon o usuário requisitou o elevador, o segundo o andar da requisição, e o terceiro o andar para o qual o usuário pretende ir. Cada linha representa um usuário diferente.

 No terminal, o programa deve receber também as letras “sjf” caso queira ser utilizado o “Shortest Job First” ou “fcfs” em caso da utilização do “First Come, First Served”. E o programa depende diretamente desse gerador de entradas aleatórias para um bom funcionamento.

 O programa gera dois tipos de saída diferente: uma pelo terminal e outra em um arquivo “resultados.txt”. A saída corresponde a informações detalhadas da saída e da entrada de um usuário no elevador.

 Obs, Zepslon representa uma medida de tempo teorica. O elevador muda de andar, adiciona um zepslon, o usuario entra no elevador, adiciona um zepslon, e isso se aplica para outras acoes.

# Para compilar, rode o comando make no terminal.
