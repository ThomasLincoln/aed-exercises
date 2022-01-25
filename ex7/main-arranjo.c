#include <stdio.h>
#include <stdlib.h>
 
//estruturas
#define true 1
#define false 0
 
 
typedef int bool;
typedef int Tipo_Chave;
 
// ------------------------------------
//| esse é o objeto nó, cada nó vai ter essas variaveis, é possivel
//| adcionar outras caso seja necessário, como nome de usuario, id, ?
//| etc...
// ------------------------------------
 
typedef struct no{
  Tipo_Chave chave;
  struct no * filhos[500];
    int totalFilhos;
}node;//node é nó em ingles, usei pq ja tinha no
 
 
 
// ------------------------------------
//|  TAD árvore
//|  Precisamos de: Iniciar a árvore
//| (alocar a memória e os primeiros valores)
//| Inserir Filho (inserir um nó filho para um nó pai)
//| Imprimir (mostrar a lista de filhos em ordem)
//| Busca chave
// ------------------------------------
 
// ------------------------------------
//| ***Inicializar***
// ------------------------------------
 
// ---------------------------
//| essa função cria um novo nó
// ---------------------------
node* criar_novo_no(Tipo_Chave chave_aux){
  int i;
  node * novo_no = (node*)malloc(sizeof(node));
  novo_no->chave = chave_aux;
  for(i =0; i < 500; i++){
    novo_no->filhos[i] = NULL;
  }
    novo_no->totalFilhos = 0;
  return(novo_no);
}
 
// ---------------------------
//| essa função inicializa
// ---------------------------
 
node * inicializa_arvore(Tipo_Chave chave_aux){
  return(criar_novo_no(chave_aux));
}
 
 
// ------------------------------------
//| ***Busca_Chave***
// ------------------------------------
node * busca_Chaves(Tipo_Chave chave_aux, node * raiz){
  //se a raiz for nula, nao existe, ai ele retorna null
  if(raiz == NULL){
    return(NULL);
  }
  //se a chave da raiz for = a chave aux q inserimos na função,
  if(raiz->chave == chave_aux){
      return(raiz);
  }
  int i = 0;
  //pego o primeiro filho pra ter um inicio
 
 
  while(raiz->filhos[i] != NULL){
      node * resp = busca_Chaves(chave_aux, raiz->filhos[i]);
      if(resp != NULL){
        return(resp);
      }
            i++;
  }
  return(NULL);
}
 
 
// ------------------------------------
//| ***Inserir***
// ------------------------------------
 
bool insere(node * raiz, Tipo_Chave nova_chave, Tipo_Chave chave_pai){
  int i = 0;
  //verificar se o pai existe
  node * pai = busca_Chaves(chave_pai, raiz);
 
  if(pai == NULL){
    return(false);
  }
 
  node * filho = criar_novo_no(nova_chave);//cria novo no pro filhos
  node * p = pai->filhos[0];//pega o primeiro filho do pai
  if(p == NULL){//se o pai não tiver primeiro filho ele ganha o primeiro
    pai->filhos[0] = filho;
        pai->totalFilhos++;
  }else{
        i++;
    while(pai->filhos[i] != NULL){
      i++;
    }
    pai->filhos[i] = filho;
        pai->totalFilhos++;
  }
  return(true);
}
 
// ------------------------------------
//| ***Imprimir***
// ------------------------------------
 
void exibirArvore(node * raiz){
  int i=0;
  if(raiz == NULL) return;
 
  printf("(%d", raiz->chave);
  //node * p = raiz->filhos[0];
  while(raiz->filhos[i] != NULL){
    exibirArvore(raiz->filhos[i]);
    i++;
  }
 
  printf(")");
}
 
 
int main(){
  int numero_de_membros, numero_de_filiacoes, i = 0;
  int filho, pai;
 
  // printf("Insira a quantidade de membros da familia: ");
  scanf("%i", &numero_de_membros);
  if(numero_de_membros < 1){
    return 0;
  }
  // printf("Insira a quantidade de filiacoes: ");
  scanf("%i", &numero_de_filiacoes);
 
  node * arvore = inicializa_arvore(1);
  for(i = 2; i<= numero_de_membros; i++){
    criar_novo_no(i);
  }
  for(i = 0; i< numero_de_filiacoes; i++){
    scanf("%i %i", &pai,  &filho);
    insere(arvore, filho, pai);
    filho = 0;
    pai = 0;
  }
    
 
  //printf("%p\n", busca_Chaves(1, arvore));
  //printf("%d %p %p %p\n", arvore->chave, arvore, arvore->primeiro_filho, arvore->proxIrmao);
 
  exibirArvore(arvore);
 
  return 0;
}