#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct linha
{
    char * orig, *dest, *val;
};

struct transicao_info
{
    int estado1, estado2;
    bool estado1inicial, estado1final, estado2inicial, estado2final;
    char *validador;
    
};


char *
str_clean(char * str)
{
    char * clean;
    int i = 0;
    int c = 0;
    while(str[i] != '\0')
    {
        if((str[i] != '\0') || (str[i] != '\t') || (str[i] != ' ')) 
        {
            i++;
            continue;
        }
        i++;
        c++;
    }
    clean = malloc(sizeof(char) * (c + 1));
    i = 0;
    int j = 0;
    while(str[i] != '\0')
    {
        if((str[i] != '\t') && (str[i] != ' ')) 
        {
            clean[j] = str[i];
            j++;
            i++;
            continue;
        }
        i++;
    }
     clean[j] = '\0'; 
    return clean;
}


char *
cpyrange(const char *str, int ini, int fim)
{
    if (ini < 0 || fim < ini)
    {
        return NULL;
    }
        

    int len = fim - ini + 1; 
    char *value = malloc(len + 1);
    if (!value)
    {
        return NULL;
    }
        

    for (int i = 0; i < len - 1; i++)
    {
        value[i] = str[ini + i];
    }
    value[len] = '\0'; 

    return value;
}

struct linha * 
strip(char * str)
{
    char * value = str_clean(str);
    printf("%s\n", value);
    struct linha * infos;
    infos = malloc(sizeof(struct linha));
    int i1 = 0, i2 = 0;
    for(int virgulas, i = 0; virgulas < 2; i++)
    {
        printf("value: %c i: %d Virgulas: %d\n", value[i], i, virgulas);
        if((value[i] == ',') && virgulas == 0)
        {
            i1 = i;
            virgulas++;
            continue;
        }
        if((value[i] == ',') && virgulas == 1)
        {
            i2 = i;
            virgulas++;
            continue;
        }
        if(value[i] == '\0' || (value[i] == EOF) || (value[i] == '\n')) break;
    }
    int len = strlen(value);
    infos->orig = cpyrange(value, 0, i1);
    infos->dest = cpyrange(value, i2 + 1, len);
    printf("%s\n", infos->val = cpyrange(value, i1 + 1,i2));
    printf("posicao virgula 1: %d, posicao virgula 2: %d \n", i1, i2);
    printf("origem %s destino %s validador %s\n", infos->orig, infos->dest, infos->val);
    if(!infos) return NULL;
    if(!infos->orig || !infos->dest || !infos->val) return NULL;
    return infos;
}


struct transicao_info *
pars(struct linha *infos)
{
    if(!infos) return NULL;
    if(!infos->orig || !infos->dest || !infos->val) return NULL;
    struct transicao_info * new;
    new = malloc(sizeof(struct transicao_info));
    new->validador = infos->val;
    int i = 0;
    while(infos->orig[i] != '\0')
    {
        printf(" %c %d", infos->orig[i], i);
        i++;
    }
    printf("\n");
    if((infos->orig[0] == '-') && (infos->orig[1] == '>'))
    {
        if((infos->orig[3] == '*') && (infos->orig[4] == 'q'))
        {
            
            new->estado1 = atoi((const char *) &infos->orig[5]);
            new->estado1inicial = true;
            new->estado1final = true;
        }
        if(infos->orig[3] == 'q')
        {
            printf("%s", infos->orig[3]);
            new->estado1 = atoi((const char *) &infos->orig[4]);
            new->estado1inicial = true;
            new->estado1final = false;
        }
    }

    if((infos->dest[0] == '-') && (infos->dest[1] == '>'))
    {
        if((infos->dest[3] == '*') && (infos->dest[4] == 'q'))
        {
            new->estado2 = atoi((const char *) &infos->dest[5]);
            new->estado2inicial = true;
            new->estado2final = true;
        }
        if(infos->orig[3] == 'q')
        {
            new->estado2 = atoi((const char *) &infos->dest[4]);
            new->estado2inicial = true;
            new->estado2final = false;
        }
    }
    return new;

}

struct transicao_info *
parse(struct linha *infos)
{
    if(!infos) return NULL;
    if(!infos->orig || !infos->dest || !infos->val) return NULL;

    struct transicao_info *new = malloc(sizeof(struct transicao_info));
    if(!new) return NULL;

    new->validador = infos->val;

    // ======== PARSE DO ORIGEM ========
    // Formatos possíveis:
    // ->q1
    // ->*q1
    // q1
    // *q1

    char *s = infos->orig;

    new->estado1inicial = false;
    new->estado1final   = false;

    int i = 0;

    // verifica se começa com ->
    if(s[0] == '-' && s[1] == '>') i = 2;

    // verifica se é estado final
    if(s[i] == '*')
    {
        new->estado1final = true;
        i++;
    }

    // agora obrigatoriamente deve ser 'q'
    if(s[i] == 'q')
    {
        new->estado1 = atoi(&s[i+1]); 
        // estado inicial se houver ->
        if(s[0] == '-' && s[1] == '>') 
            new->estado1inicial = true;
    }
    else
        return NULL;


    // ======== PARSE DO DESTINO ========
    s = infos->dest;

    new->estado2inicial = false;
    new->estado2final   = false;

    i = 0;

    if(s[0] == '-' && s[1] == '>') i = 2;

    if(s[i] == '*')
    {
        new->estado2final = true;
        i++;
    }

    if(s[i] == 'q')
    {
        new->estado2 = atoi(&s[i+1]);
        if(s[0] == '-' && s[1] == '>') 
            new->estado2inicial = true;
    }
    else
        return NULL;

    return new;
}





int 
main()
{
    struct transicao_info * new = parse(strip("-   >q1,2,*q3"));
    printf("Origem: %d \nEstado inicial: %d Estado final: %d\n destino: %d \nEstado inicial: %d Estado final: %d\n Validador %c\n", new->estado1, new->estado1inicial, new->estado1final, new->estado2, new->estado2inicial, new->estado2inicial, new->validador);
    return 0;
}