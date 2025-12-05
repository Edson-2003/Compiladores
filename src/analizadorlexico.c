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

struct line  * 
criar_line()
{
  struct line * new;
  new = (struct line *) malloc(sizeof(struct line *));
  new->palavras = NULL;
  return new;
}

struct palavra * 
criar_palavra(unsigned char * palavra, int coluna)
{
  struct palavra * new;
  new = (struct palavra *) malloc(sizeof(struct palavra));
  new->palavra = palavra;
  new->col = coluna;
  new->proxima = NULL;
  return new;
}

int 
inserir_palavra(struct line * line, struct palavra * palavra)
{
  if(!line || !palavra)
  {
    return -1;
  }
  if(!line->palavras)
  {
    line->palavras = palavra;
    return palavra->col;
  }
  struct palavra * p;
  p = line->palavras;
  while (p->proxima)
  {
    p = p->proxima;
  }
  p->proxima = palavra;
  return palavra->col;
}


void
destruir_line(struct line * line)
{
  if(!line)
  {
    return;
  }
  if(!line->palavras)
  {
    free(line);
    return;
  }
  struct palavra * p;
  p = line->palavras;
  while(p)
  {
    line->palavras = p->proxima;
    free(p->palavra);
    free(p);
    p = line->palavras;
  }
  free(line);
}

// struct line * 
// line_strip(unsigned char * entrada)
// {
//   if(!entrada)
//   {
//     return NULL;
//   }
//   struct line * line = criar_line();
//   int col = 0;
//   int inicio = 0;

//   while(entrada[col] != '\0')
//   {
//     if((entrada[col] == '\n') || (entrada[col] == '\t'))
//     {
//       inicio ++;
//       col ++;
//       continue;
//     }
//     while((entrada[col] != '\n') && (entrada[col] != '\t') && (entrada[col] != ' ') && (entrada[col] != '\0'))
//     {
//       col ++;
//     }
//     unsigned char *nova_palavra = (unsigned char *) cpyrange(entrada, inicio, col);
//     struct palavra * new;
//     new = criar_palavra(nova_palavra, inicio);
//     if(inicio == inserir_palavra(line, new))
//     {
//       inicio = col;
//       continue;
//     }
//     inicio = 0;
//     col = 0;
//   }
//   return line;
// }

struct line * 
line_strip(unsigned char * entrada)
{
  if(!entrada)
  {
    return NULL;
  }
  struct line * line = criar_line();
  int col = 0;
  int inicio = 0;

  while (entrada[col] != '\0')
  {
    while (entrada[col] == ' ' || entrada[col] == '\n' || entrada[col] == '\t')
    {
      col++;
    }

    inicio = col; 

    while (entrada[col] != ' ' && entrada[col] != '\n' && entrada[col] != '\t' && entrada[col] != '\0')
    {
      col++;
    }

    if (inicio == col)
    break;

    unsigned char *nova_palavra = (unsigned char *) cpyrange(entrada, inicio, col);

    struct palavra * new = criar_palavra(nova_palavra, inicio);

    inserir_palavra(line, new);

    if (entrada[col] != '\0')
    col++;
  }

  return line;
}




void 
imprimir_line(struct line * line)
{
  if(!line)
  {
    printf("esta line esta vazia\n");
  }
  if(!line->palavras)
  {
    printf("esta line esta vazia\n");
  }
  struct palavra * p;
  p = line->palavras;
  while(p)
  {
    printf("col: %d, %s\n", p->col, p->palavra);
    p = p->proxima;
  }
  return;

}


void 
valida_line(struct analizador * analizador, struct line * line)
{
  if(!analizador) return;
  if(!analizador->validadores) return;
  if(!line) return;
  if(!line->palavras) return;
  struct palavra * p;
  p = line->palavras;
  while(p)
  {
    struct automoto_list *validador = analizador->validadores;
    while(validador)
    {
      if(rodar_automoto(validador->automoto, p->palavra))
      {
        int id = buscar_lexema_encontrado(analizador, validador->lexema);
        if(id < 0)
        {
          id = inserir_lexema_encontrado(analizador, validador->lexema);
        }
        printf("id: %d, lexema: %s, token: %s, col: %d", id, p->palavra, validador->lexema, p->col);
        break;
      }
      validador = validador->proximo;
    }
    p = p->proxima;
  }
}




void 
rodar_analizador_lexico(struct analizador * analizador, char * arquivo_entrada, char * arquivo_saida)
{
  struct file * fentrada;
  // struct file * fsaida;
  fentrada = criar_arquivo(arquivo_entrada, true);
  // fsaida = criar_arquivo(arquivo_saida, false);
  int linhas = 0;
  // int colunas = 0;
  unsigned char * entrada = ler_linha(fentrada);
  while(entrada)
  {
    linhas++;
    struct line * nova_line = criar_line();
    nova_line = line_strip(entrada);
    printf("Imprimindo palavras encontrads na linha: %d\n", linhas);

    valida_line(analizador, nova_line);

    destruir_line(nova_line);
    entrada = ler_linha(fentrada);
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
