#ifndef DIRHANDLER_H_
#define DIRHANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "Filehandler.h"
#include "untils.h"


struct item
{
  struct file * fd;
  struct item * next;
};

struct dir
{
  struct item * arquivos;
  int qtd_arquivos;
  
  char *caminho;
};


struct item * criar_item(char * caminho);

struct dir * criar_dir(char *caminho);
int inserir_item(struct dir * dir, struct item * item);
int remover_item(struct dir * dir, struct item * item);


int finalizar_dir(struct dir *dir);
int finalizar_item(struct item * item);


#endif