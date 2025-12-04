#include "../include/analisadorlexico.h"



void 
inserir_validadores(struct analizador * analizador, char * lexema, char * caminho)
{
  if(!analizador || !lexema || !caminho)
  {
    return;
  }
  printf("%s\n", caminho);
  struct automoto_list * validador;
  validador = (struct automoto_list *) malloc(sizeof(struct automoto_list));
  validador->automoto = criar_automoto(caminho);
  validador->lexema = cpy(lexema);
  // validador->proximo = analizador->validadores;
  // analizador->validadores = validador;

  if(!analizador->validadores)
  {
    analizador->validadores = validador;
    return;
  }
  if(analizador->validadores->lexema[0] > lexema[0])
  {
    validador->proximo = analizador->validadores;
    analizador->validadores = validador;
    return;
  }
  
  struct automoto_list * temp;
  temp = analizador->validadores;
  while (temp->proximo != NULL)
  {
    if(temp->proximo->lexema[0] >= lexema[0])
    {
      validador->proximo = temp->proximo;
      temp->proximo = validador;
      return;
    }
    temp = temp->proximo;
  }
  temp->proximo = validador;
  
  
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
  new = (struct analizador *) malloc(sizeof(struct analizador));
  new->tokens_afd = criar_arquivo(tokens_afd, true);
  new->qtd_lexemas = 0;
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
    lexema = cpyrange(entrada, 0, v - 1);
    char * caminho;
    caminho = cpyrange(entrada, v + 1, u_len(entrada));

    inserir_validadores(new, lexema, caminho);

    entrada = ler_linha(new->tokens_afd);
  }
  return new;
}



int 
inserir_lexema_encontrado(struct analizador * analizador, char * lexema)
{
  struct lexemas * new;
  new  = (struct lexemas *) malloc(sizeof(struct lexemas));
  new->lexema = cpy(lexema);
  new->id = analizador->qtd_lexemas++;
  if(!analizador->lexemas_encontrados)
  {
    analizador->lexemas_encontrados = new;
    new->id = 0;
    return new->id;
  }
  if(analizador->lexemas_encontrados->lexema[0] > lexema[0])
  {
    
    new->proximo = analizador->lexemas_encontrados;
    return new->id;
  }
  struct lexemas * temp;
  temp = analizador->lexemas_encontrados;
  while(temp->proximo == NULL)
  {
    if(temp->proximo->lexema[0] > lexema[0])
    {
      new->proximo = temp->proximo;
      temp->proximo = new;
      return new->id;
    }
  }
  new->proximo = temp->proximo;
  temp->proximo = new;
  return new->id;
}

int 
buscar_lexema_encontrado(struct analizador * analizador, char * lexema)
{
  if(!analizador)
  {
    return -1;
  }
  if(!analizador->lexemas_encontrados)
  {
    return -1;
  }
  if(analizador->qtd_lexemas <= 0)
  {
    return -1;
  }

  if(cmp(analizador->lexemas_encontrados->lexema, lexema))
  {
    return analizador->lexemas_encontrados->id;
  }
  struct lexemas * tk;
  tk = analizador->lexemas_encontrados;
  while(tk != NULL)
  {
    if(cmp(tk->lexema, lexema))
    {
      return tk->id;
    }
    tk = tk->proximo;
  }
  return -1;
}

struct linha  * 
criar_linha()
{
  struct linha * new;
  new = (struct linha *) malloc(sizeof(struct linha *));
  new->palavras = NULL;
  return new;
}

struct palavra * 
criar_palavra(char * palavra, int coluna)
{
  struct palavra * new;
  new = (struct palavra *) malloc(sizeof(struct palavra));
  new->palavra = palavra;
  new->col = coluna;
  new->proxima = NULL;
  return new;
}

int 
inserir_palavra(struct linha * linha, struct palavra * palavra)
{
  if(!linha || !palavra)
  {
    return;
  }
  if(!linha->palavras)
  {
    linha->palavras = palavra;
    return palavra->col;
  }
  struct palavra * p;
  p = linha->palavras;
  while (p->proxima)
  {
    p = p->proxima;
  }
  p->proxima = palavra;
  return palavra->col;
}


void
destruir_linha(struct linha * linha)
{
  if(!linha)
  {
    return;
  }
  if(!linha->palavras)
  {
    free(linha);
    return;
  }
  struct palavra * p;
  p = linha->palavras;
  while(p)
  {
    linha->palavras = p->proxima;
    free(p->palavra);
    free(p->col);
    free(p);
    p = linha->palavras;
  }
  free(linha);
}

struct linha * 
linha_strip(char * entrada)
{
  if(!entrada)
  {
    return NULL;
  }
  struct linha * linha = criar_linha();
  int col = 0;
  int inicio = 0;

  while(entrada[col] != '\0')
  {
    if((entrada[col] == '\n') || (entrada[col] == '\t'))
    {
      inicio ++;
      col ++;
      continue;
    }
    while((entrada[col] == '\n') || (entrada[col] == '\t'))
    {
      col ++;
    }
    char *nova_palavra = cpyrange(entrada, inicio, col);
    struct palavra * new;
    new = criar_palavra(nova_palavra, inicio);
    if(inicio == inserir_palavra(linha, nova_palavra))
    {
      inicio = col;
      continue;
    }
    inicio = 0;
    col = 0;
  }

}



void 
rodar_analizador_lexico(struct analizador * analizador, char * arquivo_entrada, char * arquivo_saida)
{
  struct file * fentrada, * fsaida;
  fentrada = criar_arquivo(arquivo_entrada, true);
  fsaida = criar_arquivo(arquivo_saida, false);
  int linhas = 0;
  int colunas = 0;
  unsigned char * entrada = ler_linha(fentrada);
  while(entrada)
  {
    
  }

  return;
}



void 
imprimir_analizador(struct analizador * analizador)
{
  if(!analizador)
  {
    printf("O analizador está vazio\n");
  }
  printf("Iniciando a impressão do analizador\n");
  if(!analizador->lexemas_encontrados)
  {
    printf("O analizador ainda não encontrou nenhum token\n");
  }
  else
  {
    struct lexemas * tk;
    tk = analizador->lexemas_encontrados;
    while(tk != NULL)
    {
      printf("%s, %d\n", tk->lexema, tk->id);
      tk = tk->proximo;
    }
  }

  if(!analizador->validadores)
  {
    printf("O analizador não possui nenhum lexema para validar\n");
  }
  else
  {
    struct automoto_list * at;
    at = analizador->validadores;
    while(at != NULL)
    {
      printf("%s\n", at->lexema);
      imprime_automoto(at->automoto);
      at = at->proximo;
    } 
  }

}
