# Cash

# Atenção
Para aqueles que já resolveram este problema antes, algumas mudanças foram realizadas.
Então vocês devem checar se está tudo funcionando corretamente.


# Começando
Abra o [VS Code](code.cs50.io).

Clique no janela de terminal na parte de baixo da tela e execute o comando `cd`. Você verá um "prompt" como abaixo:
```
$
```

Execute o comando abaixo
```
wget https://cdn.cs50.net/2021/fall/psets/1/cash.zip
```
e tecle ENTER. Em seguida use o comando abaixo para descompactar o arquivo:
```
unzip cash.zip
```
e o comando abaixo para remover o arquivo `cash.zip`:
```
rm -f cash.zip
```

Por fim, execute o comando `ls` e você verá uma pasta chamada `cash`. Então execute o comando
```
cd cash
```
e você verá o prompt
```
cash/ $
```
onde você poderá executar o comando `ls` mais uma vez. Você deverá ver o arquivo `cash.c`.


## Algoritmos Gulosos
Ao fazer uma venda, é provável que você queira minimizar o número de moedas que
você entrega para cada cliente, para que não acabe (ou irrite o cliente!).
Felizmente, a ciência da computação deu aos caixas em todos os lugares maneiras
de minimizar o número de moedas usando: **algoritmos gulosos**.

De acordo com o Instituto Nacional de Padrões e Tecnologia (NIST), um algoritmo
guloso é aquele "que sempre pega a melhor solução imediata, ou local,
enquanto encontra uma resposta. Algoritmos gulosos encontram a solução geral
ou globalmente ideal para alguns problemas de otimização, mas podem encontrar
soluções piores que as ideais para algumas instâncias de outros problemas."

O que tudo isso significa? Bem, suponha que um caixa deva a um cliente algum
troco e na gaveta desse caixa tenha moedas (R$ 0,25), dez centavos (R$ 0,10)
cinco centavos (R$ 0,05) e centavos (R$ 0,01). O problema a ser resolvido é
decidir quais moedas e quantas de cada uma entregar ao cliente. Pense em um
caixa "guloso" como alguém que quer tirar o maior proveito possível desse
problema com cada moeda que tira da gaveta. Por exemplo, se algum cliente tem
41 centavos de troco, a maior primeira (ou seja, melhor "mordida" imediata ou
local) que pode ser feita é 25 centavos. (Essa mordida é "melhor" na medida em
que nos deixa mais perto de R$ 0,00 mais rápido do que qualquer outra moeda
faria.) Observe que uma mordida deste tamanho reduziria o que era um problema
de R$ 0,41 a um problema de R$ 0,16, já que 41 - 25 = 16. Ou seja, o restante é
um problema semelhante, mas menor. Desnecessário dizer que outra mordida de 25
centavos seria muito grande (supondo que o caixa prefere não perder dinheiro),
e assim nosso caixa guloso passaria para uma mordida de 10 centavos, deixando-o
com um problema de 6 centavos. Nesse ponto, a ganância pede uma mordida de
R$ 0,05 seguida por uma mordida de R$ 0,01, ponto em que o problema é resolvido.
O cliente recebe uma moeda de R$ 0,25, uma de R$ 0,10, uma de R$ 0,05 e uma de
R$ 0,01: quatro moedas no total.

Acontece que esta abordagem gulosa (ou seja, algoritmo) não é apenas ideal
localmente, mas também globalmente para a moeda dos EEUU (e também da União
Europeia). Ou seja, enquanto o caixa tiver o suficiente de cada moeda, essa
abordagem do maior para o menor renderá o menor número possível de moedas.
Quão poucos? Bem, diga-nos você!

## Detalhes de Implementação
Implemente, em um arquivo chamado `cash.c` em um diretório `~/cash`, um
programa que primeiro pergunta ao usuário quanto dinheiro é devido e depois
imprime o número mínimo de moedas com o qual esse troco pode ser pago.

Note que ao abrir o arquivo `cash.c`, a função `main` já está implementada e chama várias outras funções. As demais funções precisam ser implementadas, uma delas é a função `get_cents` que não recebe parâmetros (`void`) e devolve um inteiro (`int`). As demais funções recebem e devolvem `int`.

- Implemente `get_cents` de tal forma que a função solicite ao usuário um número de centavos usando `get_int` e, em seguida, retorne esse número como um `int`. Se o usuário inserir um inteiro negativo, seu código deverá solicitar ao usuário novamente. (Mas você não precisa se preocupar com a entrada do usuário, por exemplo, uma `string`, pois `get_int` cuidará disso para você.) É provável que você encontre um loop do `while`, como em `mario.c`!
- Implemente `calculate_quarters` de tal forma que a função calcule (e retorne como um `int`) quantas moedas de `0.25` um cliente deve receber se tiver algum número de centavos devidos. Por exemplo, se centavos for 25, `calculate_quarters` deve retornar 1. Se centavos for 26 ou 49 (ou qualquer coisa entre esses números, `calculate_quarters` também deverá retornar 1. Se centavos for 50 ou 74 (ou qualquer coisa entre eles), `calculate_quarters` deverá retornar 2. E assim por diante.
- Implemente `calculate_dimes` de tal forma que a função calcule o mesmo para dimes.
- Implemente `calculate_nickels` de tal forma que a função calcule o mesmo para níquel.
- Implemente `calculate_pennies` de tal forma que a função calcule o mesmo para centavos.

Observe que, diferentemente das funções que têm apenas efeitos colaterais, as funções que retornam um valor devem fazê-lo explicitamente com return! Tome cuidado para não modificar o próprio código de distribuição, apenas substitua os `TODOs` fornecidos e o valor de retorno subsequente!

Observe também que, lembrando a ideia de abstração, cada uma de suas funções de cálculo deve aceitar qualquer valor de centavos, não apenas aqueles valores que o algoritmo guloso pode sugerir. Se centavos for 85, por exemplo, `calculate_dimes` deve retornar 8.


Seu programa deveria se comportar como abaixo
```
$ ./cash
Change owed: 0.41
4
```

```
$ ./cash
Change owed: -0.41
Change owed: foo
Change owed: 0.41
4
```


## Como testar seu código
Seu código funciona conforme prescrito quando você insere

- Se você inserir -1, seu programa solicita novamente?
- Se você inserir 0, seu programa produzirá 0?
- Se você inserir 1, seu programa produzirá 1 (ou seja, um centavo)?
- Se você inserir 4, seu programa produzirá 4 (ou seja, quatro centavos)?
- Se você inserir 5, seu programa produzirá 1 (ou seja, um níquel)?
- Se você inserir 24, seu programa produzirá 6 (ou seja, duas moedas de dez centavos e quatro centavos)?
- Se você inserir 25, seu programa produzirá 1 (ou seja, um quarto)?
- Se você inserir 26, seu programa produzirá 2 (ou seja, um quarto e um centavo)?
- Se você inserir 99, seu programa produzirá 9 (ou seja, três quartos, duas moedas de dez centavos e quatro centavos)?
Você também pode executar o abaixo para avaliar a correção do seu código usando check50. Mas certifique-se de compilar e testar você mesmo também!

Você também pode executar o comando seguinte para avaliar a exatidão do seu código usando `check50`. Mas certifique-se de compilar e testar você mesmo!

```
check50 cs50/problems/2022/x/cash
```

Execute, também o comando `style50` como abaixo
```
style50 cash.c
```
para garantir que seu código segue adequadamente as regras de **estilização de código**.

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
submit50 cs50/problems/2022/x/cash
```
