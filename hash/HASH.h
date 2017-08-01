//
//  HASH.h
//  hash
//
//  Created by Lucas César  Nogueira Fonseca on 31/07/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

#ifndef HASH_h
#define HASH_h

#include <stdio.h>
#include <stdlib.h>
#include "Dados.h"

void hash(RegistroPessoa *regs);

void initHash(int n);//

void alocaBucket(int index, Registro reg);//

int removeRegistro(int rid);//

void recalculaProfundidade(int index, Registro reg);//

int insereRegistro(Registro reg);//

int funcaoHash(int id);

void printHash();

void printBuckets();

RegistroPessoa *buscaRegistro(int rid);
#endif /* HASH_h */
