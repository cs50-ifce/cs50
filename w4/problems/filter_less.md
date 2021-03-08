# Filtro (Less)
Implemente um programa que aplica filtros em imagens BMP. O programa deve ser executado como abaixo:
```
$ ./filter -r image.bmp reflected.bmp
```

# Fundamentação

## Imagens bitmap
Talvez a maneira mais simples de representar uma imagem seja com uma grade de _pixels_ (ou seja, pontos), cada um dos quais pode ser de uma cor diferente. Para imagens em preto e branco, precisamos, portanto, de 1 _bit_ por _pixel_, já que 0 pode representar preto e 1 pode representar branco, como mostrado a seguir.

![Bitmap](./bitmap.png)

Nesse sentido, então, uma imagem é apenas um _bitmap_ (ou seja, um mapa de _bits_). Para imagens mais coloridas, você simplesmente precisa de mais _bits_ por pixel. Um formato de arquivo (como BMP, JPEG ou PNG) que suporta “cores de 24 _bits_” usa 24 _bits_ por pixel. (BMP, na verdade, suporta cores de 1, 4, 8, 16, 24 e 32 _bits_.)

Um BMP de 24 _bits_ usa 8 _bits_ para significar a quantidade de vermelho na cor de um _pixel_, 8 bits para significar a quantidade de verde na cor de um _pixel_ e 8 bits para significar a quantidade de azul na cor de um _pixel_. Se você já ouviu falar em cores RGB, bem, aí está: vermelho (Red), verde (Green), azul (Blue).

Se os valores R, G e B de algum _pixel_ em um BMP são, digamos, 0xff, 0x00 e 0x00 em hexadecimal, esse pixel é puramente vermelho, pois 0xff (também conhecido como 255 em decimal) implica "muito vermelho", Enquanto 0x00 e 0x00 implicam “sem verde” e “sem azul”, respectivamente.

## Um Bitmap mais técnico

Lembre-se de que um arquivo é apenas uma sequência de bits, organizados de alguma forma. Um arquivo BMP de 24 bits, então, é essencialmente apenas uma sequência de bits, (quase) cada 24 dos quais representam a cor de algum pixel. Mas um arquivo BMP também contém alguns "metadados", informações como a altura e largura de uma imagem. Esses metadados são armazenados no início do arquivo na forma de duas estruturas de dados geralmente chamadas de "cabeçalhos", para não ser confundido com os arquivos de cabeçalho de C. (Aliás, esses cabeçalhos evoluíram com o tempo. Esse problema usa a versão mais recente do formato BMP da Microsoft, 4.0, que estreou com o Windows 95.)

O primeiro desses cabeçalhos, chamado BITMAPFILEHEADER, tem 14 bytes de comprimento. (Lembre-se de que 1 byte é igual a 8 bits.) O segundo desses cabeçalhos, chamado BITMAPINFOHEADER, tem 40 bytes de comprimento. Imediatamente após esses cabeçalhos está o bitmap real: uma matriz de bytes, triplos dos quais representam a cor de um pixel. No entanto, o BMP armazena esses triplos ao contrário (ou seja, como BGR), com 8 bits para o azul, seguido por 8 bits para o verde, seguido por 8 bits para o vermelho. (Alguns BMPs também armazenam todo o bitmap de trás para frente, com a linha superior de uma imagem no final do arquivo BMP. Mas armazenamos os BMPs desse conjunto de problemas conforme descrito aqui, com cada linha superior do bitmap primeiro e a linha inferior por último.) palavras, se convertêssemos o smiley de 1 bit acima em um smiley de 24 bits, substituindo o preto pelo vermelho, um BMP de 24 bits armazenaria esse bitmap da seguinte maneira, onde `0000ff` significa vermelho e `ffffff` significa branco; destacamos em vermelho todas as instâncias de `0000ff`.

![Red Smile](./red_smile.png)

Como apresentamos esses pedaços da esquerda para a direita, de cima para baixo, em 8 colunas, você pode realmente ver o emoticon vermelho se der um passo para trás.

Para ser claro, lembre-se de que um dígito hexadecimal representa 4 bits. Consequentemente, `ffffff` em hexadecimal realmente significa `111111111111111111111111` em binário.

Observe que você pode representar um bitmap como uma matriz bidimensional de pixels: onde a imagem é uma matriz de linhas, cada linha é uma matriz de pixels. Na verdade, é assim que escolhemos representar imagens de bitmap neste problema.

## Filtrando uma imagem
O que significa filtrar uma imagem? Você pode pensar em filtrar uma imagem como pegar os pixels de alguma imagem original e modificar cada pixel de forma que um efeito específico seja aparente na imagem resultante.

### Escala de cinza

Um filtro comum é o filtro “escala de cinza”, onde pegamos uma imagem e queremos convertê-la em preto e branco. Como isso funciona?

Lembre-se de que, se os valores de vermelho, verde e azul estiverem todos definidos como 0x00 (hexadecimal para 0), o pixel é preto. E se todos os valores forem configurados para 0xff (hexadecimal para 255), o pixel é branco. Contanto que os valores de vermelho, verde e azul sejam todos iguais, o resultado será tons de cinza variados ao longo do espectro preto e branco, com valores mais altos significando tons mais claros (mais próximos do branco) e valores mais baixos significando tons mais escuros (mais perto de Preto).

Portanto, para converter um pixel em tons de cinza, só precisamos ter certeza de que os valores de vermelho, verde e azul são todos iguais. Mas como sabemos que valor devemos criá-los? Bem, é provavelmente razoável esperar que se os valores originais de vermelho, verde e azul fossem todos muito altos, então o novo valor também deveria ser muito alto. E se os valores originais fossem todos baixos, o novo valor também deveria ser baixo.

Na verdade, para garantir que cada pixel da nova imagem ainda tenha o mesmo brilho ou escuridão geral da imagem antiga, podemos obter a média dos valores de vermelho, verde e azul para determinar qual tom de cinza deve ser criado para o novo pixel.

Se você aplicar isso a cada pixel da imagem, o resultado será uma imagem convertida em tons de cinza.

### Sépia
A maioria dos programas de edição de imagem oferece suporte a um filtro “sépia”, que dá às imagens uma aparência antiga, fazendo com que toda a imagem pareça um pouco marrom-avermelhada.

Uma imagem pode ser convertida em sépia tomando cada pixel e computando novos valores de vermelho, verde e azul com base nos valores originais dos três.

Existem vários algoritmos para converter uma imagem em sépia, mas, para esse problema, pediremos que você use o seguinte algoritmo. Para cada pixel, os valores da cor sépia devem ser calculados com base nos valores da cor original conforme a seguir.

```
  sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
  sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
  sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
```


Obviamente, o resultado de cada uma dessas fórmulas pode não ser um número inteiro, mas cada valor pode ser arredondado para o número inteiro mais próximo. Também é possível que o resultado da fórmula seja um número maior que 255, o valor máximo para um valor de cor de 8 bits. Nesse caso, os valores de vermelho, verde e azul devem ser limitados a 255. Como resultado, podemos garantir que os valores de vermelho, verde e azul resultantes serão números inteiros entre 0 e 255, inclusive.

## Espelhamento
Alguns filtros também podem mover pixels. Refletir uma imagem, por exemplo, é um filtro em que a imagem resultante é o que você obteria colocando a imagem original na frente de um espelho. Portanto, quaisquer pixels no lado esquerdo da imagem devem terminar no lado direito e vice-versa.

Observe que todos os pixels originais da imagem original ainda estarão presentes na imagem refletida, mas esses pixels podem ter sido reorganizados para estar em um lugar diferente na imagem.

### Borrão
Existem várias maneiras de criar o efeito de desfocar ou suavizar uma imagem. Para este problema, usaremos o “desfoque de caixa”, que funciona pegando cada pixel e, para cada valor de cor, dando a ele um novo valor calculando a média dos valores de cor dos pixels vizinhos.

Considere a seguinte grade de pixels, onde numeramos cada pixel.

![Grid](./grid.png)

O novo valor de cada pixel seria a média dos valores de todos os pixels que estão dentro de 1 linha e coluna do pixel original (formando uma caixa 3x3). Por exemplo, cada um dos valores de cor para o pixel 6 seria obtido pela média dos valores de cor originais dos pixels 1, 2, 3, 5, 6, 7, 9, 10 e 11 (observe que o próprio pixel 6 está incluído no média). Da mesma forma, os valores de cor para o pixel 11 seriam obtidos pela média dos valores de cor dos pixels 6, 7, 8, 10, 11, 12, 14, 15 e 16.

Para um pixel ao longo da borda ou canto, como o pixel 15, ainda procuraríamos todos os pixels em 1 linha e coluna: neste caso, os pixels 10, 11, 12, 14, 15 e 16.

## Iniciando

Veja como baixar o "código de distribuição" deste problema (ou seja, código inicial) em seu próprio CS50 IDE. Faça login no CS50 IDE e, em uma janela de terminal, execute cada um dos itens abaixo.

- Execute `cd` para garantir que você está em `~/` (ou seja, seu diretório inicial).
- Execute `mkdir pset4` para fazer (ou seja, criar) um diretório chamado pset4 em seu diretório inicial.
- Execute `cd pset4` para mudar para (ou seja, abrir) esse diretório.
- Execute wget ```https://cdn.cs50.net/2019/fall/psets/4/filter/less/filter.zip``` para baixar um arquivo ZIP (compactado) com a distribuição desse problema.
- Execute `unzip filter.zip` para descompactar esse arquivo.
- Execute `rm filter.zip` seguido por `yes` ou `y` para excluir o arquivo ZIP (opcional).
- Execute `ls`. Você deve ver um diretório chamado `filter`, que estava dentro desse arquivo ZIP.
- Execute `cd filter` para mudar para esse diretório.
- Execute `ls`. Você deve ver a distribuição deste problema, incluindo `bmp.h`, `filter.c`, `helpers.h`, `helpers.c` e `Makefile`. Você também verá um diretório chamado imagens, com algumas imagens de bitmap de amostra.

## Entendendo

Vamos agora dar uma olhada em alguns dos arquivos fornecidos a você como código de distribuição para entender o que há dentro deles.

### bmp.h

Abra o `bmp.h` (clicando duas vezes nele no navegador de arquivos) e dê uma olhada.

Você verá as definições dos cabeçalhos que mencionamos (`BITMAPINFOHEADER` e `BITMAPFILEHEADER`). Além disso, esse arquivo define `BYTE`, `DWORD`, `LONG` e `WORD`, tipos de dados normalmente encontrados no mundo da programação do Windows. Observe como eles são apenas apelidos para primitivos com os quais você (espero) já esteja familiarizado. Parece que `BITMAPFILEHEADER` e `BITMAPINFOHEADER` fazem uso desses tipos.

Talvez o mais importante para você, este arquivo também define uma estrutura chamada `RGBTRIPLE` que, simplesmente, "encapsula" três bytes: um azul, um verde e um vermelho (a ordem, lembre-se, em que esperamos encontrar triplos RGB realmente em disco).

Por que essas estruturas são úteis? Bem, lembre-se de que um arquivo é apenas uma sequência de bytes (ou, no final das contas, bits) no disco. Mas esses bytes são geralmente ordenados de forma que os primeiros representem algo, os próximos representem outra coisa e assim por diante. Os “formatos de arquivo” existem porque o mundo padronizou o significado de bytes. Agora, poderíamos simplesmente ler um arquivo do disco para a RAM como um grande array de bytes. E poderíamos apenas lembrar que o byte em `array[i]` representa uma coisa, enquanto o byte em `array[j]` representa outra. Mas por que não dar nomes a alguns desses bytes para que possamos recuperá-los da memória com mais facilidade? Isso é precisamente o que as estruturas em `bmp.h` nos permitem fazer. Em vez de pensar em algum arquivo como uma longa sequência de bytes, podemos pensar nele como uma sequência de estruturas.

### filter.c

Agora, vamos abrir `filter.c`. Este arquivo já foi escrito para você, mas há alguns pontos importantes que devem ser observados aqui.

Primeiro, observe a definição de filtros na linha 11. Essa `string` informa ao programa quais são os argumentos de linha de comando permitidos para o programa: `b`, `g`, `r` e `s`. Cada um deles especifica um filtro diferente que podemos aplicar às nossas imagens: desfoque, tons de cinza, reflexo e sépia.

As próximas linhas abrem um arquivo de imagem, certifique-se de que é realmente um arquivo BMP e leia todas as informações de pixel em uma matriz 2D chamada imagem.

Role para baixo até a instrução `switch` que começa na linha 102. Observe que, dependendo do filtro que escolhemos, uma função diferente é chamada: se o usuário escolher o filtro `b`, o programa chama a função de desfoque; se `g`, a escala de cinza é chamada; se `r`, então reflete é chamado; e se `s`, sépia é chamado. Observe também que cada uma dessas funções toma como argumentos a altura da imagem, a largura da imagem e a matriz 2D de pixels.

Estas são as funções que você (em breve!) Implementará. Como você pode imaginar, o objetivo é que cada uma dessas funções edite o array 2D de pixels de forma que o filtro desejado seja aplicado à imagem.

As linhas restantes do programa pegam a imagem resultante e as gravam em um novo arquivo de imagem.

### helpers.h

A seguir, dê uma olhada em `helpers.h`. Este arquivo é bastante curto e fornece apenas os protótipos de funções para as funções que você viu anteriormente.

Aqui, observe o fato de que cada função recebe uma matriz 2D chamada `image` como argumento, onde `image` é uma matriz de altura com várias linhas, e cada linha é ela própria outra matriz de largura de muitos `RGBTRIPLE`s. Portanto, se a `image` representa a imagem inteira, a `image[0]` representa a primeira linha e a `image[0][0]` representa o pixel no canto superior esquerdo da imagem.

### helpers.c
Agora, abra `helpers.c`. É aqui que pertence a implementação das funções declaradas em `helpers.h`. Mas note que, agora, as implementações estão faltando! **Esta parte é com você**.

### Makefile

Finalmente, vamos dar uma olhada no `Makefile`. Este arquivo especifica o que deve acontecer quando executamos um comando de terminal como `make filter`. Enquanto os programas que você pode ter escrito antes estavam confinados a apenas um arquivo, o filtro parece usar vários arquivos: filter.c, bmp.h, `helpers.h` e `helpers.c`. Então, vamos precisar dizer ao `make` como compilar este arquivo.

Tente compilar o filtro para você indo para o seu terminal e executando
```
$ make filter
```

Então, você pode executar o programa com o comando:
```
$ ./filter -g images/yard.bmp out.bmp
```
que obtém a imagem em `images/yard.bmp` e gera uma nova imagem chamada `out.bmp` após executar os pixels por meio da função de tons de cinza. a função `grayscale` ainda não faz nada, portanto, a imagem de saída deve ser igual ao jardim original.

## Especificação

Implemente as funções em `helpers.c` de forma que um usuário possa aplicar filtros de escala de cinza, sépia, reflexão ou desfoque às suas imagens.

- A função `grayscale` deve pegar uma imagem e transformá-la em uma versão em preto e branco da mesma imagem.
- A função s`epia` deve pegar uma imagem e transformá-la em uma versão sépia da mesma imagem.
- A função de `reflect` deve pegar uma imagem e refleti-la horizontalmente.
- Finalmente, a função `blur` deve pegar uma imagem e transformá-la em uma versão desfocada da mesma imagem.

Você não deve modificar nenhuma das assinaturas de função, nem deve modificar nenhum outro arquivo além de `helpers.c`.

# Uso
Seu programa deveria funcionar executando as linhas abaixo:

```$ ./filter -g infile.bmp outfile.bmp```

```$ ./filter -s infile.bmp outfile.bmp```

```$ ./filter -r infile.bmp outfile.bmp```

```$ ./filter -b infile.bmp outfile.bmp```

## Dica
Os valores dos componentes `rgbtRed`, `rgbtGreen` e `rgbtBlue` de um pixel são todos inteiros, então certifique-se de arredondar quaisquer números de ponto flutuante para o inteiro mais próximo ao atribuí-los a um valor de pixel!


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