#ifndef ANALIZADOR_LEXICO_H_
#define ANALIZADOR_LEXICO_H_

#include <stdio.h>
#include <stdlib.h>

#include "Filehandler.h"
#include "automoto.h"
#include "untils.h"


struct lexemas
{
  int id;
  char * lexema;
  struct lexemas * proximo;
};

struct automoto_list
{
  char * lexema;
  struct automoto * automoto;
  struct automoto_list * proximo;
};

struct analizador
{
  struct file * tokens_afd;
  struct lexemas * lexemas_encontrados;
  struct automoto_list * validadores;
};


void inserir_validadores(struct analizador * analizador, char * lexema, char * caminho);
struct analizador * criar_analizador(char *tokens_afd);


int inserir_lexema_encontrado(struct analizador * analizador, char * lexema);
int buscar_lexema_encontrado(struct analizador * analizador);







void inserir_automoto(struct analizador * analizador, char * lexema, char * path);
void rodar_analizador_lexico(struct analizador * analizador, char * arquivo_saida);





#endif