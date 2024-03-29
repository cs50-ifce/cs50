# Mario

# Começando
Abra o [VS Code](code.cs50.io).

Clique no janela de terminal na parte de baixo da tela e execute o comando `cd`. Você verá um "prompt" como abaixo:
```
$
```

Execute o comando abaixo
```
wget https://cdn.cs50.net/2021/fall/psets/1/mario-more.zip
```
e tecle ENTER. Em seguida use o comando abaixo para descompactar o arquivo:
```
unzip mario-more.zip
```
e o comando abaixo para remover o arquivo `mario-more.zip`:
```
rm -f mario-more.zip
```

Por fim, execute o comando `ls` e você verá uma pasta chamada `mario-more`. Então execute o comando
```
cd mario-more
```
e você verá o prompt
```
mario-more/ $
```
onde você poderá executar o comando `ls` mais uma vez. Você deverá ver o arquivo `mario-more.c`.

## World 1-1

No final da fase (world) 1-1 do jogo **Super Mario's Brothers**, o Mario precisa subir
uma pirâmide de blocos alinhados à direita como na imagem a seguir
!(https://cs50.harvard.edu/x/2020/psets/1/mario/more/pyramids.png)

Vamos recriar a pirâmide em C, mas em texto, usando _hashes_ (`#`) como tijolos.
Como cada _hash_ é mais estreito que alto, a pirâmide também será assim
```
       #  #
      ##  ##
     ###  ###
    ####  ####
   #####  #####
```

O programa que você irá escrever se chamará `mario`. Ele deve permitir ao usuário
escolher a altura da pirâmide. Para isto o programa deverá solicitar que o usuário
informe um inteiro positivo entre 1 e 8. Os dois extremos inclusos.

Aqui um exemplo de como o programa deve funcionar se o usuário informar o valor 8.

```
$ ./mario
Height: 8
       #  #
      ##  ##
     ###  ###
    ####  ####
   #####  #####
  ######  ######
 #######  #######
########  ########
```

Caso o usuário informe o valor 4, seu programa deve funcionar como abaixo:
```
$ ./mario
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
```

Se ele digitar 2, veremos algo como
```
$ ./mario
Height: 2
   #  #
  ##  ##
```

E caso o usuário digite 1 teremos
```
$ ./mario
Height: 1
#  #
```

Se o usuário informar um número fora do intervalo permitido, o programa deverá
continuar solicitando a entrada do usuário até que ele forneça um valor válido
como abaixo:
```
$ ./mario
Height: -1
Height: 0
Height: 42
Height: 50
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
```

Como fazer isto?

## Pseudo-código
Talvez você queira iniciar escrevendo suas ideias na forma de pseudo-código.
Crie uma pasta para esta atividade
```
~/ $ mkdir -p pset1/mario/more
```
entre na pasta

```
~/ $ cd pset1/mario/more
```

e crie os arqivos `pseudocode.txt` e `mario.c`
```
~/pset1/mario/more $ touch pseudocode.txt mario.c
```

Escreva em `pseudocode.txt` algum pseudo-código que implemente a lógica a ser usada
por seu programa, mesmo que você não esteja totalmente seguro de como o programa
será. Não há UM jeito certo de escrever pseudo-código, apenas escreva algumas
sentenças em português descrevendo quais ações devem ser realizadas em cada etapa
Você poderá fazer uso de funções, condicionais, expressões booleanas, laços e variáveis.

## Solicitando dados ao usuário
Uma vez que você tenha terminado seu pseudo-código, em seu programa `mario.c` as instruções necessárias para solicitar que o usuário digite um número entre 1 e 8. Em seguida exiba o valor escolhido. Abaixo, segue um exemplo do funcionamento do programa

```
$ ./mario
Height: -1
Height: 0
Height: 42
Height: 50
Height: 4
Stored: 4
```

* Lembre-se que você pode compilar seu programa usando `make`.
* Você pode imprimir um `int` na tela com `printf` usando `%i`.
* Você pode usar a função `get_int` para solicitar um inteiro ao usuário.
* Para usar `get_int`, é necessário incluir a biblioteca `cs50.h`.

## Teste seu código
Seu código funciona como esperado? O que ele faz em cada um dos casos a seguir?

* -1 (ou outros números negativos)
* 0
* 1 até 8
* 9 ou outros números positivos
* letras ou palavras
* entrada vazia, isto é, apenas apertando ENTER

Se tudo funciona como correto, então:

## Verifique seu código

Execute o comando `check50` como abaixo
```
check50 cs50/problems/2022/x/mario/more
```

Para verificar se seu código está devidamente **estilizado**, utilize o comando `style50`
```
style50 mario.c
```
Note que devemos informar o nome do arquivo de código-fonte.

## Informações adicionais e OBRIGATÓRIAS
As primeiras linhas do seu código devem consistir de um comentário de várias
linhas contendo sua matrícula, seu nome completo e seu nome de usuário do github
como no exemplo abaixo.
```
MATRÍCULA: ................. 
NOME: ..................
USUÁRIO: ...............
```
substitua os pontos com suas informações.

## Enviando seu programa
Uma vez que você tenha verificado o funcionamento, `check50` e a estilização do código, `style50`, execute o comando abaixo, logando com sua conta do GitHub através de **nome de usuário** e **senha**. Por questões de segurança, você verá asteríscos (*) em vez dos caracteres da sua senha.
```
submit50 cs50/problems/2022/x/mario/more
```
