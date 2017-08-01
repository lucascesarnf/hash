//
//  main.c
//  hash
//
//  Created by Lucas César  Nogueira Fonseca on 31/07/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

#include <stdio.h>
#include "HASH.h"

int main(int argc, const char * argv[]) {
  
  //########### CARREGA ARQUIVO ###############
  RegistroPessoa registros[15];
  FILE *f = fopen("arquivo.txt", "r");
  if(f == NULL){
    exit(1);
  }
  int count = 0;
  while (!feof(f)){
    fscanf(f, "%d %s %d", &registros[count].rid,registros[count].nome,&registros[count].idade);
    count ++;
  }
  
  
  for(int i = 0; i < TM_MAX_REGISTROS; i++){
    printf("\n[%d][%d,%s,%d]\n",i,registros[i].rid,registros[i].nome,registros[i].idade);
  }
  //###########################################
  
  //Cria um hash na chave primária de registros:
  hash(registros);
  //Imprime o Hash criado:
   printf("\n! ! HASH FINAL  ! !");
  printHash();
  
  //Pesquisa por índice rid:
  RegistroPessoa *p = buscaRegistro(registros[6].rid);
  printf("\n\nRegistro buscado:\n[6][%d %s %d]\n\n",p->rid,p->nome,p->idade);
  
  
  RegistroPessoa p2;
  p2.rid = 100;
  p2.idade = 100;
  strcpy(p2.nome,"Inserido");
  Registro reg;
  reg.rid = p2.rid;
  reg.registro = &p2;
  
  //Insere registro:
  insereRegistro(reg);
  printf("\n! ! HASH INSERÇÃO  ! !");
  printHash();
  //Remove registro que acabamos de adicionar:
  removeRegistro(reg.rid);
  
  printf("\n\nRegistro deletado:\n[%d %s %d]\n\n",reg.rid,reg.registro->nome,reg.registro->idade);
  
  printf("\n! ! HASH REMOÇÃO  ! !");
  printHash();
   return 0;
}
