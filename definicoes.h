#ifndef DEFINICOES_H
#define DEFINICOES_H

#define MAXSTR 50

typedef struct arvore {
    int valor;
    double salario;
    char nome[MAXSTR+1];
    struct arvore *esq;
    struct arvore *dir;
} ARVORE;

// Prototypes das funções do grupo
ARVORE* busca_valor(ARVORE *r, int chave);
ARVORE* busca_nome(ARVORE *r, char *nome);
double contabiliza(ARVORE *r);
void desaloca(ARVORE *r);

// Funções do professor (já existentes)
ARVORE* insere(ARVORE *no, ARVORE *r);
ARVORE* ledados(FILE *arq);
void imprimeNO(ARVORE *no);
void pre(ARVORE *r);
void em(ARVORE *r);
void pos(ARVORE *r);
void lestringARQ(char *s, int max, FILE *arq);

#endif
