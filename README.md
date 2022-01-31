# Jogo-Resta-Um
Trabalho Prático desenvolvido na disciplina de Introdução a Programação. 

## O que é o jogo Resta Um? 
Resta um é um jogo de quebra cabeça, conhecido também como Solitaire (solitário), no qual consiste em um tabuleiro que se inicia com 32 peças, sendo que a posição central fica vazia. É um passatempo conhecido por muitas pessoas há séculos, no entanto, não possui sua  origem confirmada. 
Como dito, o modelo tradicional possui 32 peças e a posição central é vazia, o grande desafio deste quebra cabeças é “comer” as peças deixando apenas uma na posição central, que no ínicio fica vazia. Os movimentos permitidos são apenas na direção horizontal e vertical. Nesse sentido, pode-se “saltar” uma peça sendo que seu vizinho deve estar vazio e dessa forma a peça saltada sai do tabuleiro. Esses movimentos válidos são repetidos até que sobre apenas uma peça, para vencer o jogo.

## O que foi desenvolvido? 
O presente trabalho consiste na implementação de um programa na linguagem C para jogar o resta um. No entanto, deve ser ressaltado que o tabuleiro não segue o padrão tradicional e suas dimensões podem ser variadas, bem como, a quantidade de peças e espaços vazios. O programa lê um arquivo de texto de entrada contendo o tabuleiro, caso não seja informado o argumento no terminal o programa gera um tabuleiro aleatório para ser jogado (um dos desafios propostos). Devo destacar que optei por limitar o tamanho do tabuleiro com a quantidade de letras do alfabeto, ou seja, sua dimensão pode chegar até 26 linhas ou 26 colunas. Além disso, o usuário tem a opção de salvar o jogo em andamento, no qual será gerado um arquivo texto de saída.
O programa possui diversas funções dentre as quais para a: 
* leitura do tabuleiro; 
* impressão do tabuleiro;
* salvar o jogo;
* imprimir o menu para o usuário; 
* ler os comandos digitados pelo usuário; 
* realizar os movimentos (para cima, baixo, esquerda e direita);
* ajudar o usuário, ou seja, o próprio programa realiza os movimentos; 
* encerrar o programa sem salvar; 
* informar o usuário se ganhou ou perdeu o jogo;
* liberar a memória alocada para o tabuleiro.
