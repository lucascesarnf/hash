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
  
  initHash(2);
  //00
  insereRegistro(4);
  insereRegistro(12);
  insereRegistro(32);
  insereRegistro(16);
  //01
  insereRegistro(1);
  insereRegistro(5);
  insereRegistro(21);
  insereRegistro(13);
  //10
  insereRegistro(10);
  //11
  insereRegistro(15);
  insereRegistro(7);
  insereRegistro(19);
  printHash();
  
  insereRegistro(20);
  printHash();
  insereRegistro(25);
  printHash();
  return 0;
}
