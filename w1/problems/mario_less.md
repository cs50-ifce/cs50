
/*
MATRÍCULA: 20201045050201
NOME: VICTOR GUILHERME DA SILVEIRA CASTRO
USUÁRIO: 1-LEI-DE-NEWTON
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = get_int("Height: ");
    
//Captura a altura desejada pelo usuário

    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");

//Caso a altura seja menor que 1 ou maior que 8, o programa pede novamente a altura
    }
    for (int i = 0; i < height; i++)
    {
//Cria uma linha
        
        for (int j = 0; j < height; j++)
        {
//Cria um loop para imprimir a altura desejada pelo usuário
            
            if (j < height - i - 1)
            
//Caso o valor de j seja menor que a altura desejada pelo usuário menos o valor de i menos 1, imprime um espaço
            
            {
                printf(" ");
            } 
            else 
        
//Caso contrário, imprime um #
        
            {
                printf("#");
            }
        }
        printf("\n");
        
//Pula uma linha

    }
    
}
