#ifndef ANALIZADOR_LEXICO_H_
#define ANALIZADOR_LEXICO_H_

#include <stdio.h>
#include <stdlib.h>

#include "Filehandler.h"
#include "automoto.h"
#include "untils.h"

struct palavra
{
  char * palavra;
  int col;
  struct palavra * proxima;
};

struct linha 
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

struct linha * criar_linha();
struct palavra * criar_palavra(char * palavra, int coluna);
int inserir_palavra(struct linha * linha, struct palavra * palavra);
void destruir_linha(struct linha * linha);
struct linha * linha_strip(char * entrada);

void rodar_analizador_lexico(struct analizador * analizador, char * arquivo_entrada, char * arquivo_saida);



void imprimir_analizador(struct analizador * analizador);

#endif