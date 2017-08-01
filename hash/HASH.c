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

void hash(RegistroPessoa *regs){
  initHash(2);
  Registro r;
  for(int i = 0; i< TM_MAX_REGISTROS;i++){
    r.rid = regs[i].rid;
    r.registro = &regs[i];
    if(r.rid == 20){
      printf("\n! ! HASH ANTES DA DUPLICAÇÃO ! !");
      printHash();
    }
    insereRegistro(r);
  }
}
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
      
      buckets[i].chaves[i].rid = 0;
      buckets[i].chaves[i].registro = NULL;
      
    }
    //Vincula a tabela ao seu respectivo bucket:
    tabelaBinaria[i].bucket = &buckets[i];
    
  }
  
}

//Aloca Bucket:
void alocaBucket(int index, Registro reg){
  if(numBuckets == profundidadeGlobal){
    recalculaProfundidade(index, reg);
  }else{
    //Adiciona mais 1 bucket:
    numBuckets ++;
    buckets = realloc(buckets, numBuckets);
    buckets[numBuckets - 1].profundidadeLocal = profundidadeGlobal;
    for (int i = 0; i<TAMANHO_DO_BUCKET; i++) {
      buckets[numBuckets - 1].chaves[i].rid = 0;
      buckets[numBuckets - 1].chaves[i].registro = NULL;
    }
    tabelaBinaria[numBuckets -1].bucket = &buckets[numBuckets - 1];
    //Recoloca as chaves do bucket:
    Registro aux[TAMANHO_DO_BUCKET];
    
    for(int i = 0; i < TAMANHO_DO_BUCKET; i ++){
      aux[i] = buckets[index].chaves[i];
      buckets[index].chaves[i].rid = 0;
      buckets[index].chaves[i].registro = NULL;
    }
    for(int i = 0; i < TAMANHO_DO_BUCKET; i ++){
      insereRegistro(aux[i]);
    }
    insereRegistro(reg);
    //printHash();
  }
}


//Recalcula a profundidade do hash binário:
void recalculaProfundidade(int index, Registro reg){
  
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
    buckets[numBuckets - 1].chaves[i].rid = 0;
    buckets[numBuckets - 1].chaves[i].registro = NULL;
  }
  
  //printBuckets();
  
  //Adiciona o novo Bucket ao centro da tabela multiplicada:
  tabelaBinaria[profundidadeGlobal/2].bucket = &buckets[numBuckets - 1];
  
  //printHash();
  
  //Recoloca as chaves do bucket:
  Registro aux[TAMANHO_DO_BUCKET];
  
  for(int i = 0; i < TAMANHO_DO_BUCKET; i ++){
    aux[i] = buckets[index].chaves[i];
    buckets[index].chaves[i].rid = 0;
    buckets[index].chaves[i].registro = NULL;
  }
  for(int i = 0; i < TAMANHO_DO_BUCKET; i ++){
    insereRegistro(aux[i]);
  }
  insereRegistro(reg);
  printf("\n! ! HASH APÓS DA DUPLICAÇÃO ! !");
  printHash();
}

int insereRegistro(Registro reg){
  
  int index = funcaoHash(reg.rid);//Calculo o index na tabela
  
  //procuro espaço no bukket
  for(int i = 0; i < TAMANHO_DO_BUCKET; i++){
    if(tabelaBinaria[index].bucket->chaves[i].rid == 0){
      //Se tiver espaço guardo nele
      tabelaBinaria[index].bucket->chaves[i] = reg;
      tabelaBinaria[index].bucket->profundidadeLocal = profundidadeGlobal;
      return 1;
    }
  }
  //Se não encontrar espaço no bucket adiciona bucket/ dobra diretório:
  alocaBucket(index,reg);
  //recalculaProfundidade(index,rid);
  return 0;
}

RegistroPessoa *buscaRegistro(int rid){
  int index = funcaoHash(rid);
  for(int i = 0; i< TAMANHO_DO_BUCKET;i++){
    if(tabelaBinaria[index].bucket->chaves[i].rid == rid){
      return tabelaBinaria[index].bucket->chaves[i].registro;
    }
  }
  return NULL;
}

int removeRegistro(int rid){
  int index = funcaoHash(rid);
  for(int i = 0; i< TAMANHO_DO_BUCKET;i++){
    if(tabelaBinaria[index].bucket->chaves[i].rid == rid){
      //ZERA A VARIÁVEL:
      tabelaBinaria[index].bucket->chaves[i].registro->idade = 0;
      strcpy(tabelaBinaria[index].bucket->chaves[i].registro->nome,"");
      tabelaBinaria[index].bucket->chaves[i].registro->rid = 0;
      
      //Remove do Hash:
      tabelaBinaria[index].bucket->chaves[i].rid = 0;
      tabelaBinaria[index].bucket->chaves[i].registro = NULL;
      return 1;
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
      printf("|%d|",tabelaBinaria[i].bucket->chaves[j].rid);
      
    }
  }
  printf("\n###################\n");
}

void printBuckets(){
  printf("\n##### B U K E T ######");
  for(int i = 0; i < numBuckets; i ++){
    
    printf("\n[%d] - > [%d] ",i, buckets[i].profundidadeLocal);
    for(int j = 0; j < TAMANHO_DO_BUCKET; j ++){
      printf("|%d|",buckets[i].chaves[j].rid);
      
    }
  }
  printf("\n#####################\n");
}


