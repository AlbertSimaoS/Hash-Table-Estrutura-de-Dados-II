#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

//====================== Estrutura da Hash ======================
struct hash{
    int qtd;
    int TABLE_SIZE;
    struct aluno **itens;
};

//=========== Menu =============
int menu() {
    int escolha = 0;

    while (1) {
        printf("\n----------------------------------------------------------------\n");
        printf("\tTabela Hash\n");
        printf("----------------------------------------------------------------\n");
        printf("1 - Insercao sem tratamento de colisoes\n");
        printf("2 - Insercao com tratamento de colisoes\n");
        printf("3 - Encerrar o Programa\n\n");

        printf("Escolha: ");
        // Verifica se a entrada é inválida
        if (scanf("%d", &escolha) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {} // limpa o buffer
            fprintf(stderr, "Entrada invalida! Digite apenas numeros de 1 a 3.\n");
            system("pause");
            system("cls");
            continue; // volta pro menu
        }

        system("cls");

        switch (escolha) {
            case 1:
                 break;
            case 2:
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                system("cls");
                printf("Numero fora do intervalo permitido (1-3)!\n");
                system("pause");
                system("cls");
                continue; // volta pro menu
        }

        return escolha;
    }
}

//===========Submenu=============
int subMenu()
{
    int esc;
    system("cls");
    printf("\n----------------------------------------------------------------\n");
    printf("\tOperacao a ser feita\n");
    printf("----------------------------------------------------------------\n");
    printf("1 - Inserir Elemento\n");
    printf("2 - Buscar Elemento\n");
    printf("3 - Encerrar o Programa\n");

    printf("Escolha: ");
    if (scanf("%d", &esc) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        fprintf(stderr, "Entrada invalida! Digite apenas numeros de 1 a 3.\n");//imprimir a saída no stderr: que é o stream de saída de erro padrão(standard error)
        system("pause");
        system("cls");
        return 0;
    }

    system("cls");

    return esc;
}
// ===== Controle de Hash=====
//precisa ser inicializada no main pela variavel tamanho
Hash *criaHash(int TABLE_SIZE) {
    Hash *ha = (Hash*) malloc(sizeof(Hash));
    if(ha != NULL) {
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->itens = (struct aluno**) malloc(TABLE_SIZE * sizeof(struct aluno*));

        if(ha->itens == NULL) {
            free(ha);
            return NULL;
        }

        ha->qtd = 0;
        for(i = 0; i < ha->TABLE_SIZE; i++) {
            ha->itens[i] = NULL;
        }
    }
    return ha;
}

//chamada sempre que encerrar o programa
void liberaHash(Hash *ha) {
    if(ha != NULL) {
        int i;
        for(i = 0; i < ha->TABLE_SIZE; i++) {
            if(ha->itens[i] != NULL) {
                free(ha->itens[i]);
            }
        }
        free(ha->itens);
        free(ha);
    }
}

//====================== Funções Hashing ======================
//usar um numero primo para o TABLE_SIZE
//1º Gerar chave aleatoria
int chaveDobra(int chave, int TABLE_SIZE) {
    int num_bits = 10;
    int parte1 = chave >> num_bits;
    int parte2 = chave & (TABLE_SIZE - 1);
    return (parte1 ^ parte2);
}

//2º será usada para gerar outra chave caso haja colisão
int chaveDivisao(int chave, int TABLE_SIZE) {
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

//será usada nas colisões
int duploHash(int H1, int chave, int i, int TABLE_SIZE) {
    int H2 = chaveDivisao(chave, TABLE_SIZE - 1) + 1;
    return ((H1 + i * H2) & 0x7FFFFFFF) % TABLE_SIZE;
}

//====================== Operações sem Tratamento ======================
int insereHash_semColisao(Hash *ha, struct aluno al) {
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }
    int chave = al.matricula;

    int pos = chaveDobra(chave, ha->TABLE_SIZE);//o metodo que tiver escolhido
    struct aluno *novo;
    novo = (struct aluno*) malloc(sizeof(struct aluno));
    if(novo == NULL) {
        return 0;
    }
    *novo = al;
    ha->itens[pos] = novo;
    ha->qtd++;
    return 1;
}

int buscaHash_semColisao(Hash *ha, int mat, struct aluno *al) {
    if(ha == NULL) { //lista vazia
        return 0;
    }
    int pos = chaveDobra(mat, ha->TABLE_SIZE);//o metodo que tiver escolhido
    if(ha->itens[pos] == NULL) {
        return 0;
    }
    *al = *(ha->itens[pos]);
    return 1;
}

//====================== Operações com Tratamento ======================
int insereHash_enderecoAberto(Hash *ha, struct aluno al) {
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }
    int chave = al.matricula;

    int i, pos, newPos;
    pos = chaveDobra(chave, ha->TABLE_SIZE);

    for(i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if(ha->itens[newPos] == NULL) {
            struct aluno *novo;
            novo = (struct aluno*) malloc(sizeof(struct aluno));
            if(novo == NULL) {
                return 0;
            }
            *novo = al;
            ha->itens[newPos] = novo;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

int buscaHash_enderecoAberto(Hash *ha, int mat, struct aluno *al) {
    if(ha == NULL) {
        return 0;
    }
    int i, pos, newPos;
    pos = chaveDobra(mat, ha->TABLE_SIZE);
    for(i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = duploHash(pos, mat, i, ha->TABLE_SIZE);
        if(ha->itens[newPos] == NULL) {
            return 0;
        }
        if(ha->itens[newPos]->matricula == mat) {
            *al = *(ha->itens[newPos]);
            return 1;
        }
    }
    return 0;
}
