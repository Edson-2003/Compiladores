#include "../include/automoto.h"


// struct info_aux
// {
//   int id1, id2;
//   unsigned char label;
//   bool inicial, final;
// };

// struct transicao_info
// {
//     int estado1, estado2;
//     bool estado1inicial, estado1final, estado2inicial, estado2final;
//     char *validador;
// };

// struct linha
// {
//     char * orig, *dest, *val;
// };

struct estado *
criar_estado(int id, bool inicial, bool final)
{
  struct estado * new;
  new = (struct estado *) malloc(sizeof(struct estado));
  new->proximo = NULL;
  new->transicoes = NULL;
  new->id = id;
  new->inicial = inicial;
  new->final = final;
  return new;
}

struct transicao *
criar_transicao(struct transicao * proxima, struct estado * destino, char validador)
{
  struct transicao * new;
  new = ( struct transicao *) malloc(sizeof(struct transicao));
  new->destino = destino;
  new->proxima = proxima;
  new->validador = validador;
  return new;
}

void
inserir_estado(struct automoto * automoto, struct estado * estado)
{
  if(!automoto || !estado)
  {
    return;
  }
  if(!automoto->estados)
  {
    automoto->estados = (struct estado **) malloc(sizeof(struct automoto *));
    *automoto->estados = estado;
  }
  struct estado * temp = *automoto->estados;
  if(temp->id == estado->id)
  {
    return;
  }
  while (temp->proximo != NULL)
  {
    if(temp->proximo->id >= estado->id)
    {
      if(temp->proximo->id == estado->id)
      {
        return;
      }
      estado->proximo = temp->proximo;
      temp->proximo = estado;
      return;
    }
    temp = temp->proximo;
  }
  estado->proximo = temp->proximo;
  temp->proximo = estado;
  return;
}

struct estado *
procurar_estado(struct automoto * automoto, int estado)
{
  if(automoto->estados == NULL)
  {
    return NULL;
  }
  struct estado * temp =  *automoto->estados;
  if(temp->id == estado)
  {
    return temp;
  }
  temp = temp->proximo;
  while(temp != NULL)
  {
    if(temp->id == estado)
    {
      return temp;
    }
    temp = temp->proximo;
  }
  return NULL;
}

void
fecha_transicao(struct estado * origem, struct estado * destino, char label)
{
  if(!origem || !destino)
  {
    return;
  }

  if(!origem->transicoes)
  {
    origem->transicoes = criar_transicao(NULL, destino, label);
    return;
  }

  if((origem->transicoes->validador == label) && (origem->transicoes->destino == destino))
  {
    return;
  }

  struct transicao * temp;
  temp = origem->transicoes;
  while(temp->proxima != NULL)
  {
    if(temp->proxima->validador >= label)
    {
      if(temp->proxima->destino == destino)
      {
        return;
      }
      struct transicao * new = criar_transicao(temp->proxima, destino, label);
      temp->proxima = new;
      return;
    }
    temp = temp->proxima;  
  }
  temp->proxima = criar_transicao(NULL, destino, label);
  return;
}


void
insere_transicao(struct automoto * automoto, struct transicao_info * transicao)
{

  struct estado * estado1 = procurar_estado(automoto, transicao->estado1);
  // struct estado * temp

  if(estado1 == NULL)
  {
    estado1 = criar_estado(transicao->estado1, transicao->estado1inicial, transicao->estado1final);
    inserir_estado(automoto, estado1);
  }
  else
  {
    if(estado1->inicial != transicao->estado1inicial)
    {
      estado1->inicial = transicao->estado1inicial;
    }
    if(estado1->final != transicao->estado1final)
    {
      estado1->final = transicao->estado1final;
    }
  }

  if((transicao->estado2 == -1) && (*transicao->validador == '-'))
  {
    struct estado * estado1 = procurar_estado(automoto, transicao->estado1);
    estado1->inicial = transicao->estado1inicial;
    estado1->final = transicao->estado1final;
    return;
  }

  struct estado * estado2 = procurar_estado(automoto, transicao->estado2);
  if(estado2 == NULL)
  {
    estado2 = criar_estado(transicao->estado2,transicao->estado2inicial, transicao->estado2final);
    inserir_estado(automoto, estado2);
  }
    else
  {
    if(estado2->inicial != transicao->estado2inicial)
    {
      estado2->inicial = transicao->estado2inicial;
    }
    if(estado2->final != transicao->estado2final)
    {
      estado2->final = transicao->estado2final;
    }
  }

  fecha_transicao(estado1, estado2, *transicao->validador);
  return;
}


struct linha *
strip(unsigned char * str)
{
  if (!str) return NULL;
  char * value = str_clean(str);
  if (!value) return NULL;
  // printf("%s\n", value);
  struct linha *infos = malloc(sizeof(struct linha));
  if (!infos) { free(value); return NULL; }
  int i1 = -1, i2 = -1;
  int i = 0;
  int virgulas = 0;
  while (value[i] != '\0' && virgulas < 2)
  {
    // printf("value: %c i: %d Virgulas: %d\n", value[i], i, virgulas);
    if (value[i] == ',')
    {
      if (virgulas == 0) i1 = i;
      if (virgulas == 1) i2 = i;
      virgulas++;
    }
    i++;
  }
  while (value[i] != '\0' && virgulas < 2)
  {
    if (value[i] == ',')
    {
      if (virgulas == 0) i1 = i;
      if (virgulas == 1) i2 = i;
      virgulas++;
    }
    i++;
  }
 int len = u_len((unsigned char *)value);
  if (i1 <= 0 || i2 <= i1)
  {
    free(value);
    free(infos);
    return NULL;
  }
 infos->orig = cpyrange(value, 0, i1 - 1);
  infos->val  = cpyrange(value, i1 + 1, i2 - 1);
  infos->dest = cpyrange(value, i2 + 1, len - 1);
 // printf("%s\n", infos->val);
  // printf("posicao virgula 1: %d, posicao virgula 2: %d \n", i1, i2);
  // printf("origem %s destino %s validador %s\n", infos->orig, infos->dest, infos->val);
 if(!infos->orig || !infos->dest || !infos->val)
  {
    free(infos->orig); free(infos->dest); free(infos->val);
    free(infos);
    return NULL;
  }
  return infos;
}





struct transicao_info *
parse_line(struct linha *infos)
{
  if(!infos) return NULL;
  if(!infos->orig || !infos->dest || !infos->val) return NULL;
  struct transicao_info *new = malloc(sizeof(struct transicao_info));
  if(!new) return NULL;
  new->validador = infos->val;

  const char *s = infos->orig;
  new->estado1inicial = false;
  new->estado1final = false;
  new->estado1 = -1;
  int idx = 0;

  if (s[idx] == '-' && s[idx+1] == '>')
  {
    new->estado1inicial = true;
    idx += 2;
  }    
  if (s[idx] == '*')
  {
    new->estado1final = true;
    idx++;
  }
  if (s[idx] == 'q')
  {
    new->estado1 = atoi(&s[idx+1]);
  }
  else
  {
    free(new);
    return NULL;
  }

  if((*infos->val == '-') && (*infos->dest == '-'))
  {
    new->estado2 = -1;
    new->estado2final = false;
    new->estado2inicial = false;
    printf("linha: %s, %s, %s\n", infos->orig, infos->val, infos->dest);
    printf("estado 1: %d inicial:%d final: %d\nestado 2: %d inicial: %d final: %d\n", new->estado1, new->estado1inicial, new->estado1final, new->estado2, new->estado2inicial, new->estado2final);
    return new;
  }
  s = infos->dest;
  new->estado2inicial = false;
  new->estado2final = false;
  new->estado2 = -1;
  idx = 0;
  if (s[idx] == '-' && s[idx+1] == '>')
  {
    new->estado2inicial = true;
    idx += 2;
  }
  if (s[idx] == '*')
  {
    new->estado2final = true;
    idx++;
  }
  if (s[idx] == 'q')
  {
    new->estado2 = atoi(&s[idx+1]);
  }
  else
  {
    free(new);
    return NULL;
  }
  printf("linha: %s, %s, %s\n", infos->orig, infos->val, infos->dest);
  printf("estado 1: %d inicial:%d final: %d\nestado 2: %d inicial: %d final: %d\n", new->estado1, new->estado1inicial, new->estado1final, new->estado2, new->estado2inicial, new->estado2final);
  return new;
  
}


struct automoto *
criar_automoto(char * caminho)
{
  struct automoto * new;
  new = (struct automoto *) malloc(sizeof(struct automoto));
  struct file * arquivo;
  arquivo = criar_arquivo(caminho);
  unsigned char * entrada;
  entrada = ler_linha(arquivo);
  while(entrada)
  {
    if(entrada == NULL)
    {
      break;
    }
    struct linha * linha = strip(entrada);
    struct transicao_info * informacoes = parse_line(linha);
    insere_transicao(new, informacoes);
    free(linha);
    free(informacoes);
    entrada = ler_linha(arquivo);
  }
  
  return new;  
}


void 
limpar_automoto(struct automoto * automoto)
{
  if(!automoto)
  {
    return;
  }
  if(!automoto->estados)
  {
    free(automoto);
    return;
  }
  struct estado * estado_temporario;
  estado_temporario = *automoto->estados;
  while(estado_temporario != NULL)
  {
    struct transicao * transicao_temporaria;
    transicao_temporaria = estado_temporario->transicoes;
    while(transicao_temporaria != NULL)
    {
      estado_temporario->transicoes = transicao_temporaria->proxima;
      free(transicao_temporaria);
      transicao_temporaria = estado_temporario->transicoes;
    }
    *automoto->estados = estado_temporario->proximo;
    free(estado_temporario);
    estado_temporario = *automoto->estados;
  }

  free(*automoto->estados);
  free(automoto->estados);
  free(automoto);
  return;
}


void imprime_automoto(struct automoto * automoto)
{
  if(!automoto || !automoto->estados)
  {
    printf("O automoto esta vazio\n");
    return;
  }

  struct estado * estado = *automoto->estados;

  while (estado != NULL)
  {
    if(estado->transicoes)
    {
      struct transicao * transicao_temp = estado->transicoes  ;

      while (transicao_temp != NULL)  
      { 
        if (estado->inicial)  
        {
          printf("->");
        } 
        if (estado->final)  
        {
          printf("*");
        }  
        printf("q%d, %c, ", estado->id, transicao_temp->validador);

        if (transicao_temp->destino->inicial) 
        {
          printf("->");
        } 
        if (transicao_temp->destino->final) 
        {
          printf("*");
        }  

        printf("q%d\n", transicao_temp->destino->id); 

        transicao_temp = transicao_temp->proxima; 
      } 
    }
    else
    {
      if(estado->id)
      {
        printf("->");
      }
      if(estado->final)
      {
        printf("*");
      }
      printf("q%d,-,-\n", estado->id);
    }
    estado = estado->proximo;
  }
}








// void
// imprime_automoto(struct automoto * automoto)
// {
//   if(!automoto || !automoto->estados)
//   {
//     printf("O automoto esta vazio\n");
//     return;
//   }
//   struct estado * estado = *automoto->estados;
//   while(estado != NULL)
//   {
//     if(estado->transicoes)
//     {
//       struct transicao * trasnicao_temp;
//       trasnicao_temp = estado->transicoes;
//       while(trasnicao_temp != NULL)
//       {
//         if(estado->inicial)
//         {
//           printf("->");
//         }
//         if(estado->final)
//         {
//           printf("*");
//         }
//         printf("q%d, %c, ", estado->id, trasnicao_temp->validador);
//         if(trasnicao_temp->destino->inicial)
//         {
//           printf("->");
//         }
//         if(trasnicao_temp->destino->final)
//         { 
//           printf("*");
//         }
//         printf("q%d\n", trasnicao_temp->destino->id);
//         trasnicao_temp = trasnicao_temp->proxima;
//       }
//       estado = estado->proximo;
//     }
//   }


// }