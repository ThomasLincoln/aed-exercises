#include <stdlib.h>
#include <stdio.h>

//  --------------------
// | Struct
//  --------------------
struct node{
    int chave; //id do nó
    struct node * esquerda;//filho da esquerda
    struct node * direita;//filho da direita
};

//  ----------------------
// | Função para criar nó
//  ----------------------

struct node * novo_node(int chave)
{       
    struct node * node_aux = (struct node *)malloc(sizeof(struct node));
    node_aux->chave = chave;
    node_aux->direita = node_aux->esquerda = NULL;
}

// ---------------------
//| Construir 
// ---------------------
struct node * construir(int inorder[], int start, int end, int preorder[], int *p_index){
    if (start > end){
        return NULL;
    }

    struct node * no = novo_node(preorder[(*p_index)++]);

    int i;
    for(i = start; i <= end; i++){
        if(inorder[i]== no->chave){
            break;
        }
    }
    no->esquerda = construct(inorder, start, i - 1, preorder, p_index);
    no->direita = construct(inorder, start, i-1, preorder, p_index);

    return no;
}
// ---------------------
//| Construir árvore
// ---------------------
struct node * construir_arvore(int inorder[], int preorder[], int n){
    int p_index =0;
    return construct(inorder, 0, n-1, preorder, &p_index);
}


// -------------
// Recursive function to perform preorder traversal on a given binary tree
void preorderTraversal(struct node* root)
{
    if (root == NULL) {
        return;
    }
 
    printf("%d ", root->chave);
    preorderTraversal(root->esquerda);
    preorderTraversal(root->direita);
}

int main (){
    int tamanho_da_sequencia = 0, sequencia_inordem[1000] = {0}, sequencia_preordem[1000] = {0}, i;

    printf("Insira o tamanho das sequencias: ");
    scanf("%i", &tamanho_da_sequencia);

    int inordem[] = { 4, 2, 1, 7, 5, 8, 3, 6 };
    int preordem[] = { 1, 2, 4, 3, 5, 7, 8, 6 };
    int n = sizeof(inordem)/sizeof(inordem[0]);
    struct node* root = constructTree(inordem, preordem, n);
        
    printf("\nThe preorder traversal is "); preorderTraversal(root);

    // printf("O numero inserido foi: %i\n", tamanho_da_sequencia);
    // for(i = 0; i< tamanho_da_sequencia; i++){
    //     scanf("%i", &sequencia_inordem[i]); 
    // }
    // for (i = 0; i < tamanho_da_sequencia; i++)
    // {
    //     printf("%i ", sequencia_preordem[i]);
    // }

    // printf("\n");
    //     for(i = 0; i< tamanho_da_sequencia; i++){
    //     scanf("%i", &sequencia_preordem[i]); 
    // }
    // for (i = 0; i < tamanho_da_sequencia; i++)
    // {
    //     printf("%i ", sequencia_posordem[i]);
    // }
}