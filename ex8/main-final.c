#include <stdlib.h>
#include <stdio.h>
#define MAX 1000

typedef struct node {
    int chave;
    struct node *esquerda;
    struct node *direita;
};

struct node * inicia_arvore()
{
    return NULL;
}

void print_posordem(struct node * no)
{   
    if(no != NULL)
    {
        print_posordem(no->esquerda);
        print_posordem(no->direita);
        printf("%d\n", no->chave);
    }
}
struct node * cria_node(int key)
{
    struct node * novo_no = (struct node *)malloc(sizeof(struct node));
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    novo_no->chave = key;

    return novo_no;
}

struct node * insere_no(struct node * raiz,struct node * node)
{
    if(raiz == NULL){
        return node;
    }
    if(node->chave < raiz->chave){
        raiz->esquerda = insere_no(raiz->esquerda, node);
    }
    else{
        raiz->direita = insere_no(raiz->direita, node);
    }
    
    return raiz;
}

int main()
{   
    int n, pre_ordem[MAX], em_ordem[MAX], i;
    scanf("%d", &n);
    struct node * arvore = inicia_arvore(); //pre_ordem, em_ordem

		for(i=0; i<n; i++){
			scanf("%d", &pre_ordem[i]);
            struct node * no = cria_node(pre_ordem[i]);
            arvore = insere_no(arvore, no);
		}

    for(i = 0; i < n; i++)
    {
        scanf("%d", &em_ordem[i]);
    }
    print_posordem(arvore);
    return 0;
}