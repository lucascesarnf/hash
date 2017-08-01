//
//  HASH.c
//  hash
//
//  Created by Lucas César  Nogueira Fonseca on 31/07/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

#include "HASH.h"
#include <math.h>
#include "Dados.h"

//##### V A R I Á V E I S   D E   C O N T R O L E :############

int N;//numero de bits que representam o hash
int profundidadeGlobal;// 2 ^ N, onde N é o numero de bits do hash
TabelaBinaria *tabelaBinaria;//Tabela binária que aponta para os bukets
Bucket *buckets;//Buckets reais
int numBuckets;
//#############################################################


//Inicia o HASH com o tamanho n;
void initHash(int n){
  
  //Seta a profundidade:
  N = n;
  profundidadeGlobal = pow(2, N);
  numBuckets = profundidadeGlobal;
  //Inicializa os bukets locais e a tabela binária:
  buckets = (Bucket*)calloc(profundidadeGlobal,sizeof(Bucket));
  
  tabelaBinaria = (TabelaBinaria*)calloc(profundidadeGlobal,sizeof(TabelaBinaria));
  
  for(int i = 0; i<profundidadeGlobal; i++){
    //Seta a profundidade local:
    buckets[i].profundidadeLocal = profundidadeGlobal;
    //Inicializa o bucket com zeros:
    for(int j = 0; j < TAMANHO_DO_BUCKET; j++){
      
      buckets[i].chaves[j] = 0;
      
    }
    //Vincula a tabela ao seu respectivo bucket:
    tabelaBinaria[i].bucket = &buckets[i];
    
  }
  
}

//Aloca Bucket:
void alocaBucket(int index, int rid){
  if(numBuckets == profundidadeGlobal){
    recalculaProfundidade(index, rid);
  }else{
    //Adiciona mais 1 bucket:
    numBuckets ++;
    buckets = realloc(buckets, numBuckets);
    buckets[numBuckets - 1].profundidadeLocal = profundidadeGlobal;
    for (int i = 0; i<TAMANHO_DO_BUCKET; i++) {
      buckets[numBuckets - 1].chaves[i] = 0;
    }
    tabelaBinaria[numBuckets -1].bucket = &buckets[numBuckets - 1];
    //Recoloca as chaves do bucket:
    int aux[TAMANHO_DO_BUCKET];
    
    for(int i = 0; i < TAMANHO_DO_BUCKET; i ++){
      aux[i] = buckets[index].chaves[i];
      buckets[index].chaves[i] = 0;
    }
    for(int i = 0; i < TAMANHO_DO_BUCKET; i ++){
      insereRegistro(aux[i]);
    }
    insereRegistro(rid);
    //printHash();
  }
}


//Recalcula a profundidade do hash binário:
void recalculaProfundidade(int index, int rid){
  
  int n2 = N + 1;
  int prof2 = pow(2,n2);
  
  //Duplica a tabela:
  TabelaBinaria *t2 = (TabelaBinaria*)calloc(prof2,sizeof(TabelaBinaria));
  
  for(int i = 0; i< profundidadeGlobal; i++){
    t2[i].bucket = tabelaBinaria[i].bucket;
    t2[i + profundidadeGlobal].bucket = tabelaBinaria[i].bucket;
  }
  
  free(tabelaBinaria);
  tabelaBinaria = t2;
  
  //Altera as profundidades de acordo com o número de Bits
  N = n2;
  profundidadeGlobal = prof2;
  
  //Adiciona mais 1 bucket:
  numBuckets ++;
  buckets = realloc(buckets, numBuckets);
  buckets[numBuckets - 1].profundidadeLocal = profundidadeGlobal;
  for (int i = 0; i<TAMANHO_DO_BUCKET; i++) {
    buckets[numBuckets - 1].chaves[i] = 0;
  }
 
  printBuckets();
  
  //Adiciona o novo Bucket ao centro da tabela multiplicada:
  tabelaBinaria[profundidadeGlobal/2].bucket = &buckets[numBuckets - 1];
  
  //printHash();
  //Recoloca as chaves do bucket:
  int aux[TAMANHO_DO_BUCKET];
  
  for(int i = 0; i < TAMANHO_DO_BUCKET; i ++){
    aux[i] = buckets[index].chaves[i];
    buckets[index].chaves[i] = 0;
  }
  for(int i = 0; i < TAMANHO_DO_BUCKET; i ++){
    insereRegistro(aux[i]);
  }
  insereRegistro(rid);
  //printHash();
}

int insereRegistro(int rid){
  
  int index = funcaoHash(rid);//Calculo o index na tabela
  
  
  //procuro espaço no bukket
  for(int i = 0; i < TAMANHO_DO_BUCKET; i++){
    if(tabelaBinaria[index].bucket->chaves[i] == 0){
      //Se tiver espaço guardo nele
      tabelaBinaria[index].bucket->chaves[i] = rid;
      tabelaBinaria[index].bucket->profundidadeLocal = profundidadeGlobal;
      return 1;
    }
  }
  //Se não encontrar espaço no bucket dobra o diretório:
  alocaBucket(index,rid);
  //recalculaProfundidade(index,rid);
  return 0;
}

int buscaRegistro(int rid){
  int index = funcaoHash(rid);
  for(int i = 0; i< TAMANHO_DO_BUCKET;i++){
    if(tabelaBinaria[index].bucket->chaves[i] == rid){
      return tabelaBinaria[index].bucket->chaves[i];
    }
  }
  return 0;
}



//##### C A L C U L A   F U N Ç Ã O   H A S H #######
int funcaoHash(int id){
  
  return id % profundidadeGlobal;
  
}

//########## A U X I L I A R E S #############
void printHash(){
  printf("\n##### H A S H ######");
  for(int i = 0; i < profundidadeGlobal; i ++){
    
    printf("\n[%d] - > [%d] ",i,tabelaBinaria[i].bucket->profundidadeLocal);
    for(int j = 0; j < TAMANHO_DO_BUCKET; j ++){
      printf("|%d|",tabelaBinaria[i].bucket->chaves[j]);
      
    }
  }
  printf("\n###################\n");
}

void printBuckets(){
  printf("\n##### B U K E T ######");
  for(int i = 0; i < numBuckets; i ++){
    
    printf("\n[%d] - > [%d] ",i, buckets[i].profundidadeLocal);
    for(int j = 0; j < TAMANHO_DO_BUCKET; j ++){
      printf("|%d|",buckets[i].chaves[j]);
      
    }
  }
  printf("\n#####################\n");
}


