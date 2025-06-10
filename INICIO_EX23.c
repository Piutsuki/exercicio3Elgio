#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Nomes do grupo:
 * - Igor: implementação das funções busca_valor e busca_nome
 * - Camila: implementação de contabiliza e desaloca
 * - Todos: testes e revisão do código
 */

#include "definicoes.h"
#include "funcoesProf.c"

// === Implementação das funções do grupo ===

ARVORE* busca_valor(ARVORE *r, int chave) {
    if (r == NULL) return NULL;
    if (r->valor == chave) return r;
    if (chave < r->valor) return busca_valor(r->esq, chave);
    return busca_valor(r->dir, chave);
}

ARVORE* busca_nome(ARVORE *r, char *nome) {
    if (r == NULL) return NULL;
    if (strcmp(r->nome, nome) == 0) return r;

    ARVORE *esq = busca_nome(r->esq, nome);
    if (esq != NULL) return esq;

    return busca_nome(r->dir, nome);
}

double contabiliza(ARVORE *r) {
    if (r == NULL) return 0.0;
    return r->salario + contabiliza(r->esq) + contabiliza(r->dir);
}

void desaloca(ARVORE *r) {
    if (r == NULL) return;
    desaloca(r->esq);
    desaloca(r->dir);
    free(r);
}

// === Função principal ===

int main(int argc, char *argv[]) {
    ARVORE *r = NULL, *no = NULL, *resp = NULL;
    double totsal = 0.0;
    int total = 0, valor;
    char nome[MAXSTR + 1];
    FILE *arq;

    if (argc < 2) {
        fprintf(stderr, "ERRO. Você precisa fornecer o nome do arquivo com os dados\n");
        fprintf(stderr, "Sintaxe: %s arquivo.txt\n", argv[0]);
        return 1;
    }

    arq = fopen(argv[1], "r");
    if (arq == NULL) {
        fprintf(stderr, "ERRO. Não pude abrir o arquivo \"%s\" para leitura\n", argv[1]);
        return 2;
    }

    while (!feof(arq)) {
        no = ledados(arq);
        if (no == NULL) break;

        if (r == NULL) {
            r = no;
            total = 1;
        } else {
            if (insere(no, r) == NULL) {
                free(no);
            } else {
                total++;
            }
        }
    }
    fclose(arq);

    printf("\n==================================\n");
    printf("Lido %d nos do arquivo \"%s\"\n", total, argv[1]);
    printf("==================================\n\n");

    printf("Depuração: percurso pré-ordem\n");
    pre(r);
    printf("\n\n");

    printf("Depuração: percurso em ordem\n");
    em(r);
    printf("\n\n");

    printf("Depuração: percurso pós-ordem\n");
    pos(r);
    printf("\n\n");

    printf("Digite um valor a ser buscado:\n");
    scanf("%d", &valor);
    resp = busca_valor(r, valor);
    if (resp == NULL) {
        printf("%d não encontrado na árvore\n", valor);
    } else {
        printf("Achei %d\n", valor);
        imprimeNO(resp);
    }

    printf("Digite um nome a ser encontrado:\n");
    getchar(); // limpa o buffer
    lestringARQ(nome, MAXSTR, stdin);
    resp = busca_nome(r, nome);
    if (resp == NULL) {
        printf("%s não encontrado na árvore\n", nome);
    } else {
        printf("Achei %s\n", nome);
        imprimeNO(resp);
    }

    totsal = contabiliza(r);
    printf("Total de salários = R$ %.2lf\n", totsal);

    desaloca(r);
    return 0;
}
