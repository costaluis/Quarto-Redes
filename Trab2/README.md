# Trabalho 2 de Redes de Computadores

### **Alunos responsáveis**

| Nome                            | NUSP     |
| ------------------------------- | -------- |
| João Pedro Fidelis Belluzzo     | 10716661 |
| Leonardo Cerce Guioto           | 10716640 |
| Luis Fernando Costa de Oliveira | 10716532 |
| Rodrigo Augusto Valeretto       | 10684792 |

---

### Projeto

Para o segundo projeto da disciplina **SSC 0641 - Redes de computadores** foi requisitado
aos discentes que realizassem uma implementação que simulasse o funcionamento da camada de enlace
de uma rede. Dessa forma foi implementado um programa que simula o envio de uma mensagem de um computador
para outro.<br>
Nesse processo foram realizadas todas as conversões necessárias de forma a trabalhar com bits, além da
implementação de protocolos para verificar a qualidade da mensagem recebida, de forma a detectar possíveis
erros gerados pelo meio de transmissão.

---

### Compilar e rodar o código

Diferentemente do trabalho 1, nesse trabalho foi feito apenas um arquivo .cpp com todo o código necessário
para a implementação, dessa forma basta executar os comandos de compilação no terminal e depois rodar
o executável gerado.<br>
Estando dentro da pasta raiz do programa executamos o seguinte comando para compilar:

```
g++ trab2.cpp -o trab2
```

O comando acima gerará um arquivo executável e para utilizá-lo basta digitar no terminal:

```
./trab2
```

Com isso o programa inicia sua execução, na qual é pedida uma mensagem que, quando inserida, simula a passagem
por todos as camadas numa transmissão de rede. Ao fim disso tudo é exibido no terminal a mensagem recebida,
juntamente com uma aviso caso tenha sido detectado algum erro de transmissão gerado pelo meio.
