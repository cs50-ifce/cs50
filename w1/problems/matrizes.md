# Combinando Matrizes

Uma matriz é uma estrutura bidimensional formada por linhas e colunas.


$$
A=\begin{bmatrix}
1 & 2 & 1 & 4\\
3 & 1 & 0 & 1\\
1 & 1 & 1 & 2
\end{bmatrix}
$$

Em C, uma matriz pode ser declarada como segue:
```C
   int matriz[3][4];
```
em que o primeiro valor entre colchetes, 3, determina a quantidade de linhas e o segundo valor, 4, determina a quantidade de colunas.

Duas matrizes que possuem a mesma quantidade de linhas e de colunas podem ser somadas. Para tanto, basta somar os valores que estão na mesma linha e na mesma coluna em ambas as matrizes e armazenar o valor na matriz resultante.

Por exemplo, dadas as matrizes
$$
A=\begin{bmatrix}
1 & 2 & 1 & 4\\
3 & 1 & 0 & 1\\
1 & 1 & 1 & 2
\end{bmatrix}
$$
e
$$ 
B=\begin{bmatrix}
2 & 0 & 3 & 1\\
1 & 3 & 2 & 0\\
3 & 1 & 0 & 0
\end{bmatrix}  $$
podemos somar $A+B$ obtendo
$$
\begin{bmatrix}
1 & 2 & 1 & 4\\
3 & 1 & 0 & 1\\
1 & 1 & 1 & 2
\end{bmatrix} + 
\begin{bmatrix}
2 & 0 & 3 & 1\\
1 & 3 & 2 & 0\\
3 & 1 & 0 & 0
\end{bmatrix}  =
\begin{bmatrix}
1+2 & 2+0 & 1+3 & 4+1\\
3+1 & 1+3 & 0+2 & 1+0\\
1+3 & 1+1 & 1+0 & 2+0
\end{bmatrix} 
$$
que resulta em
$$
C=\begin{bmatrix}
3 & 2 & 4 & 5\\
4 & 4 & 2 & 1\\
4 & 2 & 1 & 2
\end{bmatrix} 
$$

Uma matriz também pode ser multiplicada por um número. Neste caso, todas as entradas (valores) da matriz são multiplicadas pelo mesmo número.

Por exemplo, se
$$
A=\begin{bmatrix}
1 & 2 & 1 & 4\\
3 & 1 & 0 & 1\\
1 & 1 & 1 & 2
\end{bmatrix}
$$
então $2\cdot A$ é 
$$
2\cdot
\begin{bmatrix}
1 & 2 & 1 & 4\\
3 & 1 & 0 & 1\\
1 & 1 & 1 & 2
\end{bmatrix} =
\begin{bmatrix}
2\cdot1 & 2\cdot2 & 2\cdot1 & 2\cdot4\\
2\cdot3 & 2\cdot1 & 2\cdot0 & 2\cdot1\\
2\cdot1 & 2\cdot1 & 2\cdot1 & 2\cdot2
\end{bmatrix} 
$$
que resulta em
$$
\begin{bmatrix}
2 & 4 & 2 & 8\\
6 & 2 & 0 & 2\\
2 & 2 & 2 & 4
\end{bmatrix}
$$

Combinando as duas operações acima. Por exemplo, se
$$
A=\begin{bmatrix}
1 & 2 & 1 & 4\\
3 & 1 & 0 & 1\\
1 & 1 & 1 & 2
\end{bmatrix}
$$
e
$$ 
B=\begin{bmatrix}
2 & 0 & 3 & 1\\
1 & 3 & 2 & 0\\
3 & 1 & 0 & 0
\end{bmatrix}  $$
podemos calcular uma expressão como $2\cdot A + 3\cdot B$
$$
2\cdot\begin{bmatrix}
1 & 2 & 1 & 4\\
3 & 1 & 0 & 1\\
1 & 1 & 1 & 2
\end{bmatrix}
+3\cdot\begin{bmatrix}
2 & 0 & 3 & 1\\
1 & 3 & 2 & 0\\
3 & 1 & 0 & 0
\end{bmatrix}
$$
que resulta em
$$
\begin{bmatrix}
2 & 4 & 2 & 8\\
6 & 2 & 0 & 2\\
2 & 2 & 2 & 4
\end{bmatrix}
+\begin{bmatrix}
6 & 0 & 9 & 3\\
3 & 9 & 6 & 0\\
9 & 3 & 0 & 0
\end{bmatrix}=
\begin{bmatrix}
8 & 4 & 11 & 11\\
9 & 11 & 6 & 2\\
11 & 5 & 2 & 4
\end{bmatrix}
$$

Escreva um programa em C que solicita duas matrizes ao usuário. O usuário deve informar, também, a largura e a altura da matriz.

Em seguida, seu programa deverá gerar outras 11 matrizes dadas por
$$(1-t)\cdot A + t\cdot B$$
em que $t\in\{0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0\}$.