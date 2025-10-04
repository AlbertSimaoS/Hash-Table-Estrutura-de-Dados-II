struct aluno{
    int matricula;
    char nome[31];
    float n1, n2, n3;
};

typedef struct hash Hash;

// ===== Menus =====
int menu();
int subMenu();

// ===== Controle de Hash=====
Hash *criaHash(int tamanho);
void liberaHash(Hash *ha);

// ===== Hashing =====
int duploHash(int H1, int chave, int i, int TABLE_SIZE);
int chaveDivisao(int chave, int TABLE_SIZE);
int chaveDobra(int chave, int TABLE_SIZE);

// ===== Inserção/Busca =====
int insereHash_semColisao(Hash *ha,
                                struct aluno al);
int buscaHash_semColisao(Hash *ha, int mat,
                                struct aluno *al);
int insereHash_enderecoAberto(Hash *ha,
                                struct aluno al);
int buscaHash_enderecoAberto(Hash *ha, int mat,
                                struct aluno *al);
