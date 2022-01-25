/* Andre Eiki Hiratsuka RA: 156263 turma IB - prof Regina */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 1000 
//bibliotecas


//estrutura da arvore
typedef struct arv {
  char info;
  struct arv* esq;
  struct arv* dir;
} TArv;
typedef TArv *PArv;



//cria um no de cada vez, a diferença para o "cria" do slide eh que cria_um aponta para NULL na esquerda e direita
PArv cria_um(char c){
    PArv p = (PArv) malloc(sizeof(TArv));
    p->info = c;
    p->esq = NULL;
    p->dir = NULL;
    return p;
}

//as funcoes compara_pre e compara_in sao identicas as imprimepre e imprimein dos slides. porem, ao inves de printf, apenas cria-se uma string da sequencia prefixa e infixa para comparar com a sequencia que o usuario digitou.
void compara_pre(char string_aux[max], PArv a){
  static int auxiliar = 0;

  if(a == NULL){
    string_aux[auxiliar] = '\n';
  	string_aux[auxiliar+1] = '\0';
		
		return;
  }

  string_aux[auxiliar] = a->info;
  auxiliar++;
  compara_pre(string_aux, a->esq);
  compara_pre(string_aux, a->dir); 
		
  //o \n e \0 servem para nao dar erro na hora de executar o strcmp
  string_aux[auxiliar] = '\n';
  string_aux[auxiliar+1] = '\0';
	
}

void compara_in(char string_aux[max], PArv a){
  static int auxiliar2 = 0;

  if(a == NULL){
		string_aux[auxiliar2] = '\n';
  	string_aux[auxiliar2+1] = '\0';
    return;
  }

  compara_in(string_aux, a->esq);
  string_aux[auxiliar2] = a->info;
  auxiliar2++;
  compara_in(string_aux, a->dir); 


  string_aux[auxiliar2] = '\n';
  string_aux[auxiliar2+1] = '\0';
}


//funcao de liberar a memoria alocada
PArv libera(PArv a){
  if(a!= NULL){
    libera(a->esq);
    libera(a->dir);
    free(a);
  }
  return NULL;
}

//aqui, cria-se a arvore. da main, pede-se as duas strings prefixa e infixa, a posicao inicial (no caso s1[0] ou 0), a posição final (s1[n-1]) e o numero de nos.

//usa-se a raiz da arvore na forma infixa para dividir a sequencia em 2 partes: o que esta na esquerda e o que esta a direita da raiz. por isso, posicao_ini e posicao_fim irao mudar constantemente
PArv arvore (char s1[], char s2[], int posicao_ini, int posicao_fim, int n){

  int  posicao_raiz, i;
  static int passo = 0;
  char aux;

  //casos que nao podem acontecer. posicao inicial nao pode ser maior que a posicao final. 'passo = n' quer dizer que ja chegou ao final da string
  if ((posicao_ini > posicao_fim) || (passo == n)){
    return NULL;
  }

  //cria a raiz, ja que s1[0] (primeiro elemento da forma prefixa) eh sempre a raiz da arvore
  PArv tree = cria_um(s1[passo]);

  //durante a criacao dos nosm foi separado entre esquerda e direita. se pos_ini = pos_fim, quer dizer que todos os elementos de um lado ja foram alocados num no
  if(posicao_ini == posicao_fim){
    passo++;
    return tree;
  }

  aux = s1[passo++];

  //para achar a posicao da raiz na string infixa. a 'raiz' da arvore tambem ira mudar constantemente, ja que tambem pode ser a raiz de uma subarvore
  for(i = 1; i < n; i++){
    if(aux == s2[i]){
      posicao_raiz = i;
     }
  }
  //criando os nos na esquerda e na direita, mudando posicao_ini e posicao_fim de acordo com cada um
  tree->esq = arvore(s1, s2, posicao_ini, posicao_raiz - 1, n);
  tree->dir = arvore(s1, s2, posicao_raiz + 1, posicao_fim, n);

  //ao final, retorna a arvore para a funcao main
  return tree;

}

//calcula-se a altura da arvore para que de para saber quantos \t o caractere ira precisar. Quanto maior a altura, mais \t ia digitar. Para isso, ira fazer a impressao da esquerda da arvore, chegando na raiz, e imprimindo todo o canto direito.
void imprime_exercicio(PArv tree, int altura){
    int i;

    //se o no for vazio
    if(tree == NULL)
        return;

    //vai para a esquerda da arvore, aumentando a altura em 1 sempre que acontece isso
    imprime_exercicio(tree->esq, altura+1);

    for(i=0; i<altura; i++)
        printf("\t");

    printf("%3c\n", tree->info);

    imprime_exercicio(tree->dir, altura+1); 
}


int main(void) {
  char num[max];
  int n=0, i;

  //pedindo e verificando o numero de nos
  printf("Digite o numero de nos (ate 100) que a arvore tera: ");
  if(fgets(num, sizeof(num), stdin)){
    sscanf(num, "%d", &n);
    if (n==0 || n>100) {
      while(1 != sscanf(num, "%d", &n) || n>100){
        printf("Digite o numero corretamente: ");
        fgets(num, sizeof(num), stdin);
        sscanf(num, "%d", &n);
      }
    }
  //a verificacao tem 2 passos: checar se o que o usuario digitou realmente eh um numero, e se o numero digitado eh menor ou igual a 100

  }
  
  //pedindo para que o usuario digite as sequencias prefixa e infixa
  char s1[max], s2[max];
  printf("Digite a sequencia dos nos em ordem pre-fixa: ");
  fgets(s1, 1000, stdin);
  if(strlen(s1) - 1 != n){ //primeira verificacao de erro, em que checa se o numero de caracteres das strings sao iguais ao numero de nos
    while(strlen(s1) - 1 != n){
      printf("Digite a sequencia 1 de acordo com o numero de nos que escolheu: ");
      fgets(s1, 1000, stdin);
    }
  }
  printf("Digite a sequencia dos nos em ordem infixa: ");
  fgets(s2, 1000, stdin);
  if(strlen(s2) != strlen(s1)){
    while(strlen(s2) != strlen(s1)){
      printf("Digite a sequencia 2 de acordo com o numero de nos que escolheu: ");
      fgets(s1, 1000, stdin);
    }
  }
  printf("\n\nValores digitados: \n\n");
  printf("Numero de nos: %d\n", n);
  printf("Sequencia prefixa: %s", s1);
  printf("Sequencia infixa: %s\n", s2);
  PArv tree = arvore(s1, s2, 0, n-1, n);



  //verificar se o prefixo e infixo da arvore feita eh a msm do que o usuario digitou
  char string_aux[max], string2_aux[max];
  compara_pre(string_aux, tree);
  compara_in(string2_aux, tree);

  if(strcmp(s1, string_aux) != 0){
    printf("\n\nErro na criacao da arvore. Por favor digite as sequencias prefixas e infixas corretamente e revise-as na proxima vez.");
    libera(tree);
    return 0;
  }

  if(strcmp(s2, string2_aux) != 0){
    printf("\n\nErro na criacao da arvore. Por favor digite as sequencias prefixas e infixas corretamente e revise-as na proxima vez.");
    libera(tree);
    return 0;
  }


  printf("\nA arvore digitada sera desse formato: \n\n");
  imprime_exercicio(tree, 0);

  libera(tree); //libera a memoria aloada
  return 0;
}