#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "untils.h"

struct file
{
  
  FILE * file_ptr;
  char * path;
  bool isopen;
};


struct file * criar_arquivo(char * path);
unsigned char ler_char(struct file * arquivo);
int ler_int(struct file * arquivo);
unsigned char * ler_linha(struct file * file);



int finalizar_arquivo(struct file * self);




#endif