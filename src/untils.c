#include "../include/untils.h"



char *cpy( char *origem)
{
  int len = 0;


  while (origem[len] != '\0') 
  {
    len++;
  }

  char *destino = (char *) malloc((len + 1) * sizeof(char));
  if (destino == NULL) return NULL;

  for (int i = 0; i <= len; i++) 
  {
    destino[i] = origem[i];
  }

  return destino;
}



char *cct( char *str1,  char *str2)
{

  if (str1 == NULL) str1 = "";
  if (str2 == NULL) str2 = "";


  size_t len1 = 0;
  while (str1[len1] != '\0') len1++;

  size_t len2 = 0;
  while (str2[len2] != '\0') len2++;

  char *str = (char *)malloc((len1 + len2 + 1) * sizeof(char));

  size_t i = 0;
  for (; i < len1; i++) 
  {
    str[i] = str1[i];
  }

  for (size_t j = 0; j < len2; j++, i++) 
  {
    str[i] = str2[j];
  }

  str[i] = '\0';

  return str;
}


bool 
cmp(char * str1, char * str2)
{
  int i = 0;
  while((str1[i] == str2[i]))
  {
    if(str1[i] == '\0')
    {
      return true;
    }
    i++;
  }

  return false;

}

bool 
valida(char * str)
{
  int i = 0;
  while(str[i] != '.')
  {
    if(str[i] == '\0') 
    {
      return false;
    }
    i++;
  }
  return cmp(&str[i], ".afd");
}



int u_atoi(unsigned char *str)
{
  int i = 0;
  int sign = 1;
  long result = 0;

  while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r') 
  {
    i++;
  }

  if(str[i] == '-') 
  {
    sign = -1;
    i++;
  }

  if(str[i] == '+') 
  {
    i++;
  }

  while(str[i] >= '0' && str[i] <= '9') 
  {
    result = result * 10 + (str[i] - '0');

    if (sign == 1 && result > INT_MAX)
    {
      return INT_MAX;
    }  
    if (sign == -1 && -result < INT_MIN)
    {
      return INT_MIN;
    }
    i++;
  }
  return(int)(result * sign);
}

unsigned char *
str_clean(unsigned char * str)
{
  int i = 0;
  int c = 0;
  while (str[i] != '\0')
  {
    if (str[i] != ' ' && str[i] != '\t')
    {
      c++;
    }
    i++;
  }
  unsigned char * clean = malloc(c + 1);
  if (!clean) return NULL;
  i = 0;
  int j = 0;
  while (str[i] != '\0')
  {
    if (str[i] != ' ' && str[i] != '\t')
    {
      clean[j++] = str[i];
    }
    i++;
  }
  clean[j] = '\0';
  return clean;
}

char *
cpyrange(unsigned char *str, int ini, int fim)
{
  if (!str || ini < 0 || fim < ini) return NULL;
  int len = fim - ini + 1;
  char *value = malloc(len + 1);
  if (!value) return NULL;
  for (int i = 0; i < len; i++)
  {    
    value[i] = str[ini + i];
  }
  value[len] = '\0';
  return value;
}

int
u_len(unsigned char * str)
{
  int i = 0;
  while(str[i] != '\0')
  {
    i++;
  }
  return i;
}


int 
p_char(unsigned char * str, char * val)
{
  int i = 0;
  while(str[i] != '\0' )
  {
    if(str[i] == *val)
    {
      return i;
    }
    i++;
  }
  return -1;
}