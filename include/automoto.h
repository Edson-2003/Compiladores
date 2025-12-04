#ifndef AUTOMOTO_H_
#define AUTOMOTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/Filehandler.h"


struct automoto
{
  struct estado ** estados; 
};

struct estado
{
  struct estado * proximo;
  struct transicao * transicoes;
  int id;
  bool inicial, final;
};


struct transicao
{
  struct transicao * proxima;
  struct estado * destino;
  char validador;
};

struct transicao_info
{
  int estado1, estado2;
  bool estado1inicial, estado1final, estado2inicial, estado2final;
  char *validador;
};

struct linha
{
  char * orig, *dest, *val;
};






struct automoto * criar_automoto(char * path);
struct estado * criar_estado(int id, bool inicial, bool final);
struct transicao * criar_transicao(struct transicao * proxima, struct estado * destino, char validador);
void insere_transicao(struct automoto * automoto, struct transicao_info * transicao);
void inserir_estado(struct automoto * automoto, struct estado * estado);
struct estado * procurar_estado(struct automoto * automoto, int estado);
void fecha_transicao(struct estado * origem, struct estado * destino, char label);
void imprime_automoto(struct automoto * automoto);


struct linha * strip(unsigned char * str);
struct transicao_info * parse_line(struct linha *infos);




bool rodar_automoto(struct automoto * automoto, unsigned char * cadeia);


void limpar_automoto(struct automoto * automoto);



#endif