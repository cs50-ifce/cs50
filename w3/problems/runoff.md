# Runoff
Implemente um programa que executa a eleição *runoff*. O resultado deve ser como no exemplo abaixo.
```
./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Alice
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice
```

## Introdução
Você já conhece as eleições majoritárias(*plurality*), que seguem um algoritmo muito simples para determinar o vencedor de uma eleição: cada eleitor tem um voto e o candidato com mais votos vence.

Mas o voto plural tem algumas desvantagens. O que acontece, por exemplo, em uma eleição com três candidatos, e as cédulas abaixo são lançadas?

![Votos](./runoff.jpg)

Uma votação de majoritária declararia aqui um empate entre Alice e Bob, já que cada um tem dois votos. Mas esse é o resultado certo?

Existe outro tipo de sistema de votação conhecido como sistema de votação por escolha por classificação. Em um sistema de escolha por classificação, os eleitores podem votar em mais de um candidato. Em vez de apenas votar na primeira escolha, eles podem classificar os candidatos em ordem de preferência. As cédulas resultantes podem, portanto, ter a aparência abaixo.

![Votos](./runoff2.jpg)

Aqui, cada eleitor, além de especificar seu primeiro candidato preferencial, também indicou sua segunda e terceira opções. E agora, o que antes era uma eleição empatada, pode ter um vencedor. A eleição foi originalmente empatada entre Alice e Bob, então Charlie estava fora da eleição. Mas o eleitor que escolheu Charlie preferiu Alice a Bob, então Alice poderia ser declarada vencedora.

A votação por escolha classificada também pode resolver outra desvantagem potencial da votação por pluralidade. Dê uma olhada nas seguintes cédulas.

![Votos](./runoff3.jpg)

Quem deve ganhar esta eleição? Em uma votação de majoritária em que cada eleitor escolhe apenas sua primeira preferência, Charlie vence esta eleição com quatro votos, em comparação com apenas três para Bob e dois para Alice. Mas a maioria dos eleitores (5 de 9) ficaria mais feliz com Alice ou Bob em vez de Charlie. Ao considerar as preferências classificadas, um sistema de votação pode ser capaz de escolher um vencedor que reflita melhor as preferências dos eleitores.

Uma dessas opções de sistema de votação por classificação é o sistema de *runoff* instantâneo. Em uma eleição de segundo turno instantânea, os eleitores podem classificar quantos candidatos quiserem. Se algum candidato tiver a maioria (mais de 50%) dos votos da primeira preferência, esse candidato é declarado vencedor da eleição.

Se nenhum candidato tiver mais de 50% dos votos, ocorre um “segundo turno”. O candidato que recebeu o menor número de votos é eliminado da eleição, e quem originalmente escolheu esse candidato como sua primeira preferência agora tem sua segunda preferência considerada. Por que fazer assim? Efetivamente, isso simula o que teria acontecido se o candidato menos popular não tivesse estado na eleição para começar.

O processo se repete: se nenhum candidato obtiver a maioria dos votos, o último candidato colocado é eliminado, e quem votou nele votará em sua próxima preferência (que ainda não foi eliminado). Uma vez que um candidato tenha a maioria, ele é declarado o vencedor.

Vamos considerar as nove cédulas acima e examinar como ocorreria um segundo turno.

Alice tem dois votos, Bob tem três votos e Charlie tem quatro votos. Para ganhar uma eleição com nove pessoas, é necessária uma maioria (cinco votos). Como ninguém tem maioria, é necessário realizar um segundo turno. Alice tem o menor número de votos (com apenas dois), então Alice é eliminada. Os eleitores que votaram originalmente em Alice listaram Bob como segunda preferência, então Bob obtém os dois votos extras. Bob agora tem cinco votos e Charlie ainda tem quatro votos. Bob agora tem a maioria e Bob é declarado o vencedor.

Que casos extremos precisamos considerar aqui?

Uma possibilidade é que haja um empate para quem deve ser eliminado. Podemos lidar com esse cenário dizendo que todos os candidatos que estão empatados no último lugar serão eliminados. Se todos os candidatos restantes tiverem exatamente o mesmo número de votos, porém, eliminar os candidatos empatados em último lugar significa eliminar todos! Então, nesse caso, teremos que ter cuidado para não eliminar todos, e apenas declarar a eleição um empate entre todos os candidatos restantes.

Algumas eleições de segundo turno instantâneas não exigem que os eleitores classifiquem todas as suas preferências - portanto, pode haver cinco candidatos em uma eleição, mas um eleitor pode escolher apenas dois. Para os fins deste problema, no entanto, vamos ignorar esse caso particular e assumir que todos os eleitores classificarão todos os candidatos em sua ordem preferida.

Parece um pouco mais complicado do que uma votação plural, não é? Mas pode-se dizer que tem a vantagem de ser um sistema eleitoral em que o vencedor da eleição representa com mais precisão as preferências dos eleitores.

## Começando
Veja como baixar o "código de distribuição" deste problema (ou seja, código inicial) em seu próprio CS50 IDE. Faça login no CS50 IDE e, em uma janela de terminal, execute cada um dos itens abaixo.

- Execute `cd` para garantir que você está em `~/` (ou seja, seu diretório inicial).
- Execute `cd pset3` para mudar para (ou seja, abrir) seu diretório `pset3` que já deveria existir. Caso não exista este diretório, crie com o comando `mkdir pset3`
- Execute `mkdir runoff` para fazer (ou seja, criar) um diretório chamado *runoff* em seu diretório `pset3`.
- Execute o comando `cd runoff` para mudar para (ou seja, abrir) esse diretório.
- Execute
```
wget https://cdn.cs50.net/2019/fall/psets/3/runoff/runoff.c
```
para baixar o código de distribuição deste problema.
- Execute `ls`. Você deve ver o código de distribuição deste problema, em um arquivo chamado `runoff.c`.

## Compreensão
Vamos abrir o `runoff.c` para dar uma olhada no que já está lá. Estamos definindo duas constantes: `MAX_CANDIDATES` para o número máximo de candidatos na eleição e `MAX_VOTERS` para o número máximo de eleitores na eleição.

Em seguida, temos a matriz bidimensional chamada `preferences`. A matriz de `preferences[i]` representará todas as preferências para o eleitor número i, e o inteiro em `preferences[i][j]` contém  a j-ésima preferência (a preferência pelo candidato j) do eleitor i.

O próximo é uma `struct` chamada `candidate`. Cada candidato tem um campo de `string` para seu nome e `int` que representa o número de votos que eles têm atualmente, e um valor `bool` chamado `eliminated` que indica se o candidato foi eliminado da eleição. A matriz de candidatos irá manter um registro de todos os candidatos que ainda estão na eleição.

O programa também possui duas variáveis ​​globais: `voter_count` e `candidate_count`.

Agora a função `main`. Observe que após determinar o número de candidatos e eleitores, o ciclo de votação principal começa, dando a cada eleitor a chance de votar. Conforme o eleitor insere suas preferências, a função `vote` é chamada para registrar todas as preferências. Se a qualquer momento a cédula for considerada inválida, o programa é encerrado.

Uma vez que todos os votos foram finalizados, outro ciclo começa: este continuará repetindo o processo de segundo turno para verificar se há um vencedor e eliminar o último candidato até que haja um vencedor.

A primeira chamada aqui é para uma função `tabulate`, que deve procurar por todas as preferências dos eleitores e calcular os totais de votos atuais, procurando o candidato com mais votos que ainda não foi eliminado. Em seguida, a função `print_winner` deve imprimir o vencedor, se houver; se houver, o programa acabou. Mas, caso contrário, o programa precisa determinar o candidato com menor número de votos na eleição (por meio de uma chamada para `find_min`). Se ficar claro que todos na eleição estão empatados com o mesmo número de votos (conforme determinado pela função `is_tie`), a eleição é declarada empatada; caso contrário, o candidato (ou candidatos) em último lugar é eliminado da eleição por meio de uma chamada para a função `eliminate`.

Se você olhar um pouco mais abaixo no arquivo, verá que essas funções - `vote`, `tabulate`, `print_winner`, `find_min`, `is_tie` e `eliminate` - foram todas deixadas para você concluir!

## Especificação
Conclua a implementação de `runoff.c` de forma que simule uma eleição de segundo turno. Você deve completar as implementações das funções `vote`, `tabulate`, `print_winner`, `find_min`, `is_tie` e `eliminate`, e não deve modificar mais nada em `runoff.c` (exceto que você pode incluir arquivos de cabeçalho adicionais, se desejar).

### `vote`
Conclua a função de `vote`.

- A função leva os argumentos `voter`, `rank` e `name`. Se o `name` corresponder ao nome de um candidato válido, você deve atualizar a matriz global `preferences` para indicar que o eleitor `voter` tem aquele candidato como sua preferência de classificação (onde 0 é a primeira preferência, 1 é a segunda preferência, etc. )
- Se a preferência for registrada com sucesso, a função deve retornar `true`; caso contrário, a função deve retornar `false` (se, por exemplo, `name` não for o nome de um dos candidatos).
- Você pode presumir que dois candidatos não terão o mesmo nome.
#### Dicas
- Lembre-se de que o `candidate_count` armazena o número de candidatos na eleição.
- Lembre-se de que você pode usar `strcmp` para comparar duas `strings`.
- Lembre-se de que as `preferences[i][j]` armazenam o índice do candidato que é a j-ésima preferência no ranking do i-ésimo eleitor.

### `tabulate`
Conclua a função `tabulate`.

- A função deve atualizar o número de votos que cada candidato possui nesta fase do segundo turno.
- Lembre-se de que, em cada estágio do segundo turno, cada eleitor vota efetivamente em seu candidato preferido que ainda não foi eliminado.

#### Dicas
- Lembre-se de que `voter_count` armazena o número de eleitores na eleição.
- Lembre-se de que, para um eleitor `i`, seu candidato de primeira escolha é representado por preferências `[i][0]`, seu candidato de segunda escolha por preferências `[i][1]`, etc.
- Lembre-se de que a estrutura do candidato possui um campo denominado eliminado, que será `true` caso o candidato tenha sido eliminado da eleição.
- Lembre-se de que a estrutura do candidato tem um campo chamado `votes`, que provavelmente você desejará atualizar para o candidato preferido de cada eleitor.

### print_winner
Conclua a função print_winner.

- Se algum candidato tiver mais da metade dos votos, seu nome deve ser impresso em `stdout` e a função deve retornar `true`.
- Se ninguém ganhou a eleição ainda, a função deve retornar `false`.

#### Dicas
- Lembre-se de que `voter_count` armazena o número de eleitores na eleição. Diante disso, como você expressaria o número de votos necessários para vencer a eleição?

### `find_min`
Conclua a função `find_min`.

- A função deve retornar o total votos do candidato com o menor número de votos e que ainda esteja na eleição.

#### Dicas
- Provavelmente, você vai querer percorrer os candidatos para encontrar aquele que ainda está na eleição e tem o menor número de votos. Que informações você deve acompanhar enquanto analisa os candidatos?

### `is_tie`
Conclua a função `is_tie`.

- A função leva um argumento `min`, que será o menor número de votos que alguém na eleição tem atualmente.
- A função deve retornar `true` se todos os candidatos restantes na eleição tiverem o mesmo número de votos, e deve retornar `false` caso contrário.

#### Dicas
- Lembre-se de que o empate ocorre se todos os candidatos ainda na eleição tiverem o mesmo número de votos. Observe também que a função `is_tie` recebe um argumento `min`, que é o menor número de votos que qualquer candidato possui atualmente. Como você pode usar essas informações para determinar se a eleição é um empate (ou, inversamente, não um empate)?

### `eliminate`
Conclua a função de `eliminate`.

- A função leva um argumento `min`, que será o número mínimo de votos que alguém na eleição tem atualmente.
- A função deve eliminar o candidato (ou candidatos) com número mínimo de votos.

## Uso
Seu programa deve se comportar conforme o exemplo abaixo:

```
./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice
```

## Testando seu código

Certifique-se de testar seu código para garantir que ele trata corretamente...

- Uma eleição com qualquer número de candidatos (até o MAX de 9)
- Votar em um candidato pelo nome
- Votos inválidos para candidatos que não estão na cédula
- Imprimir o vencedor da eleição, se houver apenas um
- Não eliminando ninguém em caso de empate entre todos os candidatos restantes

Execute o comando abaixo para verificar a **corretude** do seu código. Mas tente compilar e testar antes de executar o comando
```
check50 cs50/problems/2022/x/runoff
```

Execute o comando abaixo para garantir a **estilização** do código
```
style50 runoff.c
```


## Enviando seu código
Execute o comando abaixo, logando com seu **nome de usuário** do GitHub, para enviar seu código. Por questões de segurança, asteríscos serão exibidos em vez dos caracteres da sua senha
```
submit50 cs50/problems/2022/x/runoff
```