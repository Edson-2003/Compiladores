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
str_clean(const char * str)
{
    int i = 0;
    int c = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ' && str[i] != '\t')
            c++;
        i++;
    }
    char *clean = malloc(c + 1);
    if (!clean) return NULL;
    i = 0;
    int j = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ' && str[i] != '\t')
            clean[j++] = str[i];
        i++;
    }
    clean[j] = '\0';
    return clean;
}


char *
cpyrange(const char *str, int ini, int fim)
{
    if (!str || ini < 0 || fim < ini) return NULL;
    int len = fim - ini + 1;
    char *value = malloc(len + 1);
    if (!value) return NULL;
    for (int i = 0; i < len; i++)
        value[i] = str[ini + i];
    value[len] = '\0';
    return value;
}


struct linha *
strip(char * str)
{
    if (!str) return NULL;
    char *value = str_clean(str);
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

    int len = strlen(value);
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
parse(struct linha *infos)
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

    return new;
}

int 
main()
{
    struct linha *l = strip("-   > *        q1,              2, -        > *q3");
    if (!l)
    {
        printf("Erro no strip()\n");
        return 1;
    }

    struct transicao_info * new = parse(l);
    if (!new)
    {
        printf("Erro no parse()\n");
        free(l->orig); free(l->dest); free(l->val); free(l);
        return 1;
    }

    printf("Origem: %d \nEstado inicial: %d Estado final: %d\n", new->estado1, new->estado1inicial, new->estado1final);
    printf("Destino: %d \nEstado inicial: %d Estado final: %d\n", new->estado2, new->estado2inicial, new->estado2final);
    printf("Validador: %s\n", new->validador);

    free(l->orig); free(l->dest); free(l->val); free(l);
    free(new);

    return 0;
}
