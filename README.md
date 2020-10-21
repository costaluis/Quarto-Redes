# Quarto Online

### **Alunos responsáveis**

| Nome                            | NUSP     |
| ------------------------------- | -------- |
| João Pedro Fidelis Belluzzo     | 10716661 |
| Leonardo Cerce Guioto           | 10716640 |
| Luís Fernando Costa de Oliveira | 10716532 |
| Rodrigo Augusto Valeretto       | 10684792 |

---

### Projeto

O projeto em questão corresponde à implementação de um jogo chamado Quarto para um trabalho
da disciplina **SSC 0641 - Redes de Computadores**. O jogo foi implementado com uma GUI em terminal
e foi baseado no primeiro projeto de ICC que os alunos fizeram na graduação. A linguagem utilizada
foi C++ e o código foi escrito e compilado em Linux - Ubuntu 16.04

---

### Regras do Jogo

O Quarto é jogado em um tabuleiro 4x4 (16 posições), e é muito semelhante a um jogo da velha, porém envolve números
binários em sua execução. <br>
Ao iniciar o programa será realizada uma conexão com o servidor e será pedido o nome do jogador. <br/>
Após inserir o nome, o jogo tem início, sendo que o primeiro a jogar é aquele que se conectou ao servidor primeiro. <br>
Inicialmente, o jogador 1 deve escolher um número, que vai de 0 a F (hexadecimal),
para o jogador 2. Este por sua vez escolherá a posição (também em hexadecimal) em que quer inserir
o número que foi escolhido pelo primeiro jogador, e também o próximo número, que corresponde ao número do jogador 1. <br/>
A jogada inicial é feita inserindo apenas um caractere, que representa o número escolhido para o jogador
oponente. A partir disso são escolhidos dois caracteres na entrada, sendo que o primeiro deles representa
a posição em que será inserido o número escolhido para o jogador em questão e o outro, o número que
esse jogador deseja enviar ao oponente. <br>
Os números são armazenados no tabuleiro em sua forma binária, e o tabuleiro é exibido após cada jogada;
o objetivo do jogo é fazer com que um dos caracteres dos números binários se repita por uma linha, uma coluna
ou uma diagonal. Por exemplo: <br>

|      |      |      |      |
| ---- | ---- | ---- | ---- |
| 0000 | 0001 | 0010 | 0011 |

No caso acima, o jogador que colocou o número 0011 (3 em hexa) na posição 3 ganharia o
jogo pois tanto o primeiro caractere quanto o segundo caracter dos números em binário são iguais
ao longo de uma linha completa (todos 0 nos dois casos). Isso é válido caso fosse feita uma sequência
em coluna ou diagonal. <br>
Caso a tabela toda fique preenchida e não seja encontrada nenhuma sequência em linhas, colunas ou diagonais,
é declarado empate. <br>
Sempre que o jogo termina o cliente é finalizado e deve ser reiniciado caso queira-se jogar uma nova partida.

---

### Compilar e rodar o código

Para facilitar o processo de compilação do código foi criado um makefile para o programa, o qual compila tanto o cliente
quanto o servidor, portanto basta acessar o diretório do programa e executar o comando:

```
make
```

Com todos os arquivos compilados deve-se acessar a pasta bin com o comando:

```
cd bin
```

Após isso, executar primeiramente o código do servidor e depois o cliente duas vezes.<br>
Para o servidor:

```
./server
```

Para o cliente:

```
./client
```
