#ifndef UNTILS_H_
#define UNTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <limits.h>

char * cpy(char * origem);
char *cct(char *str1, char *str2);
bool cmp(char * str1, char * str2);
bool valida(char * str);
int u_atoi(unsigned char *str);
unsigned char * str_clean(unsigned char * str);
char * cpyrange(unsigned char *str, int ini, int fim);
int u_len(unsigned char * str);
int p_char(unsigned char * str, char * val);



#endif
