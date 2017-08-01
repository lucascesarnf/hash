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
void initHash(int n);

void recalculaProfundidade(int index, int rid);

int insereRegistro(int rid);

int funcaoHash(int id);

void printHash();

void printBuckets();

void alocaBucket(int index, int rid);

int buscaRegistro(int rid);
#endif /* HASH_h */
