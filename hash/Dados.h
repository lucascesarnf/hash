//
//  Dados.h
//  hash
//
//  Created by Lucas César  Nogueira Fonseca on 31/07/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

#ifndef Dados_h
#define Dados_h
//### D E F I N I Ç Õ E S   D E  C O N S T A N T E S ########
#define TM_MAX_REGISTROS 50
#define TAMANHO_DO_BUCKET 4
//##########################################################
#include <stdio.h>

typedef struct registro_pessoa
{
  int rid;
  char nome[100];
  int idade;
} RegistroPessoa;


typedef struct bucket
{
  int profundidadeLocal;
  int chaves[TAMANHO_DO_BUCKET];
} Bucket;

typedef struct tabela_binaria
{
  Bucket *bucket;
  
} TabelaBinaria;





#endif /* Dados_h */
