# Substitution (Cifra de Substituição)

Implemente um programa que implementa a cifra de substituição que funciona como o exemplo abaixo:
```bash
./substitution JTREKYAVOGDXPSNCUIZLFBMWHQ
plaintext:  OLA
ciphertext: NXJ
```

# Fundamentos
Em uma cifra de substituição, "criptografamos" (ou seja, ocultamos de forma reversível) uma mensagem substituindo cada letra por outra. Para isso, usamos uma chave: neste caso, um mapeamento de cada uma das letras do alfabeto para a letra a que deve corresponder quando criptografamos. Para “descriptografar” a mensagem, o receptor da mensagem precisa saber a chave, para que possa reverter o processo: traduzir o texto criptografado (geralmente chamado de **texto cifrado**) de volta na mensagem original (geralmente chamado de **texto simples**).

Uma **chave**, por exemplo, pode ser a string `NQXPOMAFTRHLZGECYJIUWSKDVB`. Esta chave de 26 caracteres significa que A (a primeira letra do alfabeto) deve ser convertida em N (o primeiro caractere da chave), B (a segunda letra do alfabeto) deve ser convertida em Q (o segundo caractere do chave), e assim por diante.

Uma mensagem como `OLÁ`, então, seria criptografada como `ELN`, substituindo cada uma das letras de acordo com o mapeamento determinado pela chave.

Vamos escrever um programa chamado `substitution` que permite criptografar mensagens usando uma cifra de substituição. No momento em que o usuário executa o programa, ele deve decidir, fornecendo um argumento de linha de comando, qual deve ser a chave na mensagem secreta que fornecerá no tempo de execução.

Aqui estão alguns exemplos de como o programa pode funcionar. Por exemplo, se o usuário inserir uma chave de `YTNSHKVEFXRBAUQZCLWDMIPGJO` e um texto simples de `OLA`:
```bash
$ ./substitution YTNSHKVEFXRBAUQZCLWDMIPGJO
plaintext:  OLA
ciphertext: QBY
```

Veja como o programa pode funcionar se o usuário fornecer uma chave de `VCHPRZGJNTLSKFBDQWAXEUYMOI` e um texto simples de `hello, world`:
```bash
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
plaintext:  hello, world
ciphertext: jrssb, ybwsp
```

Observe que nem a vírgula nem o espaço foram substituídos pela cifra. Substitua apenas caracteres alfabéticos! Observe, também, que maiúsculas/minúsculas da mensagem original foram preservadas. As letras minúsculas permanecem minúsculas e as maiúsculas permanecem maiúsculas.

Se os caracteres da chave em si são maiúsculas ou minúsculas, não importa. Uma chave de `VCHPRZGJNTLSKFBDQWAXEUYMOI` é funcionalmente idêntica a uma chave de `vchprzgjntlskfbdqwaxeuymoi` (como é, nesse caso, `VcHpRzGjNtLsKfBdQwAxEuYmOi`).

E se um usuário não fornecer uma chave válida?

```bash
$ ./substitution ABC
Key must contain 26 characters.
```
Ou se ele realmente não cooperar?

```bash
$ ./substitution
Usage: ./substitution key
```

Ou mesmo
```bash
$ ./substitution 1 2 3
Usage: ./substitution key
```

# Especificação
Projete e implemente um programa, `substitution`, que criptografa mensagens usando uma cifra de substituição.

- Implemente seu programa em um arquivo denominado `substitution.c` em um diretório denominado `substitution`.
- Seu programa deve aceitar um único argumento de linha de comando, a chave a ser usada para a substituição. A chave em si não deve fazer distinção entre maiúsculas e minúsculas, portanto, se algum caractere na chave estiver em maiúsculas ou minúsculas, isso não deve afetar o comportamento do seu programa.
- Se o seu programa for executado sem nenhum argumento de linha de comando ou com mais de um argumento de linha de comando, seu programa deve imprimir uma mensagem de erro de sua escolha (com `printf`) e retornar de `main` um valor de `1` (o que tende a significar um erro ) imediatamente.
Se a chave for inválida (por não conter `26` caracteres, conter qualquer caractere que não seja alfabético, ou não conter cada letra exatamente uma vez), seu programa deve imprimir uma mensagem de erro de sua escolha (com `printf`) e retornar do main um valor de `1` imediatamente.
- Seu programa deve exibir a `string` `plain text`: (sem uma nova linha) e então solicitar ao usuário uma `string` de texto simples (usando `get_string`).
- Seu programa deve exibir a `string` cipher text: (sem uma nova linha) seguido pelo texto cifrado correspondente do texto simples, com cada caractere alfabético no texto simples substituído pelo caractere correspondente no texto cifrado; caracteres não alfabéticos devem ser permanecer inalterados.
- Seu programa deve preservar maiúsculas e minúsculas: as letras maiúsculas devem permanecer letras maiúsculas; as letras minúsculas devem permanecer em minúsculas.
- Após a saída do texto cifrado, você deve imprimir uma nova linha. Seu programa deve então sair retornando `0` da função `main`.

# Como testar seu código
Execute o comando abaixo para verificar a **corretude** do seu código. Mas tente compilar e testar antes de executar o comando

```check50 cs50/problems/2020/x/substitution```

Execute o comando abaixo para garantir a **estilização** do código

```style50 substitution.c```

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
submit50 cs50/problems/2020/x/substitution
```