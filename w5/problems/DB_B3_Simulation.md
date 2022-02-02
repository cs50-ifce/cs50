# Consolidar dados da B3 (More)
Implemente um programa que exibe dados da B3 em um formato de tabela
```
$ ./b3data arquivo.csv
```

# Fundamentação

A B3 (Brasil, Bolsa e Balcão) disponibiliza diversos arquivos com dados sobre os diversos produtos negociados em bolsa e balcão. Muitos destes arquivos estão no formato CSV (_Comma Separeted Value_, ou Valores Separados por Vírgula).

Nesse formato de arquivo, temos uma tabela com várias linhas e colunas. As linhas são delimitadas por caracteres específicos `\r`, `\n` ou `\r\n`. As colunas são delimitadas por vírgula ou qualquer outro caractere que não apareça nos próprios dados.

No caso dos arquivos disponíveis na B3, como a vírgula é um caractere usado para separar as partes inteira e fracionária (ou inteira e decimal) de números como moedas ou cotações, então os arquivos usam um ponto e vírgula como separador. Além disso, alguns arquivos usam `\n` como fim de linha enquanto outros usam `\r\n`.

## Exemplo
O código abaixo representa o trecho de um desses arquivos, mais especificamente o arquivo sobre **limite de posições em aberto**.
```
PosLmtTpCd | TickerSymbol | XprtnDt | PosLmtDesc | AggrLvlCd | L1LmtQty | L2LmtQty | FreeFloatQty
OPCAO ACAO | BBSE3 | 2022-06-17 | POTENCIAL ENTREGA | AG1 | 17282000 | 33581484 | 671629692
OPCAO ACAO | BBSE3 | 2022-09-16 | POTENCIAL ENTREGA | AG1 | 17282000 | 33581484 | 671629692
OPCAO ACAO | BBSE3 | 2022-12-16 | POTENCIAL ENTREGA | AG1 | 17282000 | 33581484 | 671629692
OPCAO ACAO | BEEF3 | 2022-02-18 | POTENCIAL ENTREGA | AG1 | 12256817 | 12256817 | 245136356
OPCAO ACAO | BEEF3 | 2022-03-18 | POTENCIAL ENTREGA | AG1 | 12256817 | 12256817 | 245136356
OPCAO ACAO | BEEF3 | 2022-04-14 | POTENCIAL ENTREGA | AG1 | 12256817 | 12256817 | 245136356
OPCAO ACAO | BEEF3 |  | POTENCIAL ENTREGA | AG1 | 12256817 | 12256817 | 245136356
TERMO | HAGA4 |  | COMPRADO | AG1 | 198000 | 396000 | 7931437
TERMO | HAPV3 |  | COMPRADO | AG1 | 31647000 | 63294000 | 1306955040
TERMO | HASH11 |  | COMPRADO | AG1 | 4394000 | 8788000 | 0
TERMO | HBOR3 |  | COMPRADO | AG1 | 3265329 | 3265329 | 65306596
BTB | LCAM3 |  | VENDIDO | AG2 | 7332000 | 14664000 | 324522975
BTB | LEVE3 |  | VENDIDO | AG2 | 1776000 | 1924625 | 38492518
BTB | LIGT3 |  | VENDIDO | AG2 | 5222000 | 13055000 | 372555324
BTB | LILY34 |  | VENDIDO | AG2 | 287000 | 717500 | 0
BTB | LIPR3 |  | VENDIDO | AG2 | 4800 | 4800 | 1915985
BTB | LJQQ3 |  | VENDIDO | AG2 | 4664000 | 8958845 | 
```

Pereba que existem múltiplas linhas mas todas possuem a mesma quantidade de colunas.

# Obtendo dados e entendendo o conteúdo do arquivo
Para obter esses dados, você pode acessar o [site da B3](https://www.b3.com.br/pt_br/market-data-e-indices/servicos-de-dados/market-data/consultas/boletim-diario/dados-publicos-de-produtos-listados-e-de-balcao/), escolher o dia e o arquivo que deseja baixar.

Para saber como cada arquivo está organizado, basta acessar esse outro [link](https://www.b3.com.br/pt_br/market-data-e-indices/servicos-de-dados/market-data/consultas/boletim-diario/dados-publicos-de-produtos-listados-e-de-balcao/glossario/), também no site da B3.

O arquivo do trecho está acima trata-se das posições em aberto de empréstimo de ativos cujo conteúdo é descrito pelo [seguinte documento](https://www.b3.com.br/data/files/0F/47/1F/F6/D7A6E610B60806E6AC094EA8/Posicoes%20em%20Aberto%20de%20Emprestimo%20de%20Ativos.pdf).

# Objetivo
O objetivo do presente trabalho é você lê o conteúdo do arquivo, por meio de um programa escrito em linguagem C, e exibir o conteúdo no formato de uma tabela como abaixo:

```
PosLmtTpCd | TickerSymbol | XprtnDt    | PosLmtDesc        | AggrLvlCd | L1LmtQty | L2LmtQty | FreeFloatQty
OPCAO ACAO | BBSE3        | 2022-06-17 | POTENCIAL ENTREGA | AG1       | 17282000 | 33581484 |  671629692
OPCAO ACAO | BBSE3        | 2022-09-16 | POTENCIAL ENTREGA | AG1       | 17282000 | 33581484 |  671629692
OPCAO ACAO | BBSE3        | 2022-12-16 | POTENCIAL ENTREGA | AG1       | 17282000 | 33581484 |  671629692
OPCAO ACAO | BEEF3        | 2022-02-18 | POTENCIAL ENTREGA | AG1       | 12256817 | 12256817 |  245136356
OPCAO ACAO | BEEF3        | 2022-03-18 | POTENCIAL ENTREGA | AG1       | 12256817 | 12256817 |  245136356
OPCAO ACAO | BEEF3        | 2022-04-14 | POTENCIAL ENTREGA | AG1       | 12256817 | 12256817 |  245136356
OPCAO ACAO | BEEF3        |            | POTENCIAL ENTREGA | AG1       | 12256817 | 12256817 |  245136356
TERMO      | HAGA4        |            | COMPRADO          | AG1       | 198000   |   396000 |    7931437
TERMO      | HAPV3        |            | COMPRADO          | AG1       | 31647000 | 63294000 | 1306955040
TERMO      | HASH11       |            | COMPRADO          | AG1       | 4394000  |  8788000 |          0
TERMO      | HBOR3        |            | COMPRADO          | AG1       | 3265329  |  3265329 |   65306596
BTB        | LCAM3        |            | VENDIDO           | AG2       | 7332000  | 14664000 |  324522975
BTB        | LEVE3        |            | VENDIDO           | AG2       | 1776000  |  1924625 |   38492518
BTB        | LIGT3        |            | VENDIDO           | AG2       | 5222000  | 13055000 |  372555324
BTB        | LILY34       |            | VENDIDO           | AG2       | 287000   |   717500 |          0
BTB        | LIPR3        |            | VENDIDO           | AG2       | 4800     |     4800 |    1915985
BTB        | LJQQ3        |            | VENDIDO           | AG2       | 4664000  |  8958845 | 
```
- Se o arquivo contiver números em formato decimal, a vírgula deve ser substituída por um ponto.
- Números devem ser alinhados à direita e textos (strings) devem ser alinhados à esquerda.

# Desafio
- Você consegue fazer seu código de modo que ele trate arquivos com os diversos tipos de final de linha?

<!---
## Testando seu código

Certifique-se de testar seu código nas imagens de bitmap fornecidas

Execute o comando abaixo para verificar a **corretude** do seu código. Mas tente compilar e testar antes de executar o comando
```
check50 cs50/problems/2020/x/filter/less
```

Execute o comando abaixo para garantir a **estilização** do código
```
style50 helpers.c
```


## Enviando seu código
Execute o comando abaixo, logando com seu **nome de usuário** do GitHub, para enviar seu código. Por questões de segurança, asteríscos serão exibidos em vez dos caracteres da sua senha
```
submit50 cs50/problems/2020/x/filter/less
```
--->