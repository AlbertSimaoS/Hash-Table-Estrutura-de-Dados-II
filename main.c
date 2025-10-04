#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"

int main()
{
    int comOuSem, operacao, mat;
    char continuar;
    struct aluno al;
    Hash *ha = criaHash(19); //definir tamanho com um número primo

    comOuSem = menu(); //retorna se é com ou sem tratamento
    if (comOuSem == 3) {
        liberaHash(ha);
        return 0;
    }

    do {
        operacao = subMenu(); //retorna a operação que o usuario deseja fazer
         switch(operacao) {
            case 1: // Inserir
                printf("\n----------------------------------------------------------------\n");
                printf("\tInserir\n");
                printf("----------------------------------------------------------------\n");
                printf("Digite matricula: ");
                scanf("%d", &al.matricula);
                printf("Digite nome: ");
                scanf(" %30[^\n]", al.nome);
                printf("Digite a Nota[1]: ");
                scanf("%f", &al.n1);
                printf("Digite a Nota[2]: ");
                scanf("%f", &al.n2);
                printf("Digite a Nota[3]: ");
                scanf("%f", &al.n3);

                if (comOuSem == 1) {
                    if (insereHash_semColisao(ha, al))
                        printf("Inserido com sucesso!\n");
                    else
                        printf("Erro ao inserir!\n");
                } else {
                    if (insereHash_enderecoAberto(ha, al))
                        printf("Inserido com sucesso!\n");
                    else
                        printf("Erro ao inserir!\n");
                }
                break;

            case 2: // Buscar
                printf("\n----------------------------------------------------------------\n");
                printf("\tBuscar\n");
                printf("----------------------------------------------------------------\n");
                printf("Digite a matricula para buscar: ");
                scanf("%d", &mat);

                if (comOuSem == 1) {
                    if (buscaHash_semColisao(ha, mat, &al))
                        printf("Encontrado: %s (Nota 1: %.2f, Nota 2: %.2f, Nota 3: %.2f)\n", al.nome, al.n1, al.n2, al.n3);
                    else
                        printf("Nao encontrado!\n");
                } else {
                    if (buscaHash_enderecoAberto(ha, mat, &al))
                        printf("Encontrado: %s (Nota 1: %.2f, Nota 2: %.2f, Nota 3: %.2f)\n", al.nome, al.n1, al.n2, al.n3);
                    else
                        printf("Nao encontrado!\n");
                }
                break;

            case 3:
                liberaHash(ha);
                printf("Encerrando...\n");
                return 0;
        }

        printf("Deseja Continuar (S/N)? ");
        scanf(" %c", &continuar);

    } while (continuar == 'S' || continuar == 's');

    liberaHash(ha);
    return 0;
}
