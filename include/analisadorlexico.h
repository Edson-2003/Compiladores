#ifndef ANALIZADOR_LEXICO_H_
#define ANALIZADOR_LEXICO_H_

#include <stdio.h>
#include <stdlib.h>

#include "Filehandler.h"
#include "automoto.h"
#include "untils.h"

struct palavra
{
  unsigned char * palavra;
  int col;
  struct palavra * proxima;
};

struct line 
{
  struct palavra * palavras;
};



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
  int qtd_lexemas;
  struct file * tokens_afd;
  struct lexemas * lexemas_encontrados;
  struct automoto_list * validadores;
};


void inserir_validadores(struct analizador * analizador, char * lexema, char * caminho);
struct analizador * criar_analizador(char *tokens_afd);


int inserir_lexema_encontrado(struct analizador * analizador, char * lexema);
int buscar_lexema_encontrado(struct analizador * analizador, char * lexema);

struct line * criar_line();
struct palavra * criar_palavra(unsigned char * palavra, int coluna);
int inserir_palavra(struct line * line, struct palavra * palavra);
void destruir_line(struct line * line);
struct line * line_strip(unsigned char * entrada);
void imprimir_line(struct line * line);


void valida_line(struct analizador * analizador, struct line * line);
void rodar_analizador_lexico(struct analizador * analizador, char * arquivo_entrada, char * arquivo_saida);



void imprimir_analizador(struct analizador * analizador);

#endif