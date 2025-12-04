#include "../include/analisadorlexico.h"



void 
inserir_validadores(struct analizador * analizador, char * lexema, char * caminho)
{
  if(!analizador || !lexema || !caminho)
  {
    return;
  }
  struct automoto_list * validador;
  validador = (struct automoto_list *) malloc(sizeof(struct automoto_list));
  validador->automoto = criar_automoto(caminho);
  validador->lexema = cpy(lexema);
  validador->proximo = analizador->validadores;
  analizador->validadores = validador;
  return;
}



struct analizador *
criar_analizador(char *tokens_afd)
{
  if(!tokens_afd)
  {
    return NULL;
  }
  struct analizador * new;
  new->tokens_afd = criar_arquivo(tokens_afd);
  unsigned char * entrada;
  entrada = ler_linha(new->tokens_afd);
  while(entrada != NULL)
  {
    int v;
    v = p_char(entrada, ",");
    if(v == -1)
    {
      entrada = ler_linha(new->tokens_afd);
      continue;
    }
    char * lexema;
    lexema = cpyrange(entrada, 0, v);
    char * caminho;
    caminho = cpyrange(entrada, v, u_len(entrada));

    inserir_validadores(new, lexema, caminho);

    entrada = ler_linha(new->tokens_afd);
  }
}



int 
inserir_lexema_encontrado(struct analizador * analizador, char * lexema)
{

  return 0;
}

int 
buscar_lexema_encontrado(struct analizador * analizador)
{
  return 0;
}

void 
inserir_automoto(struct analizador * analizador, char * lexema, char * path)
{

  return;
}

void 
rodar_analizador_lexico(struct analizador * analizador, char * arquivo_saida)
{
  return;
}
