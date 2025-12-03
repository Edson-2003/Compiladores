#include "../include/Filehandler.h"

struct file *
criar_arquivo(char * path)
{
  struct file * file;
  file = (struct file *) malloc(sizeof(struct file));
  file->file_ptr = fopen(path, "r");
  // if(file->file_ptr == NULL)
  // {
  //   return NULL;
  // }
  file->path = (path);
  file->isopen = true;
  return file;
}


unsigned char 
ler_char( struct file * arquivo)
{
  if(!arquivo->isopen)
  {
    return '\0';
  }
  return fgetc(arquivo->file_ptr);
}

unsigned char * 
ler_linha(struct file *file)
{
    if (!file || !file->file_ptr)
        return NULL;

    int capacidade = 16;
    int tamanho = 0;

    unsigned char *linha = malloc(capacidade);
    if (!linha)
        return NULL;

    int c = fgetc(file->file_ptr);

    // Se EOF logo no início → fim do arquivo
    if (c == EOF)
    {
        free(linha);
        return NULL;
    }

    // Primeiro caractere lido
    linha[tamanho++] = (unsigned char)c;

    // Lê até newline ou EOF
    while (c != '\n' && c != EOF)
    {
        c = fgetc(file->file_ptr);

        if (c == EOF || c == '\n')
            break;

        // Expande buffer se necessário
        if (tamanho + 1 >= capacidade)
        {
            capacidade *= 2;
            unsigned char *tmp = realloc(linha, capacidade);
            if (!tmp)
            {
                free(linha);
                return NULL;
            }
            linha = tmp;
        }

        linha[tamanho++] = (unsigned char)c;
    }

    linha[tamanho] = '\0';
    return linha;
}



// unsigned char *
// ler_linha(struct file * file)
// {
//   if(!file || !file->file_ptr)
//   {
//     return NULL;
//   }
//   unsigned char * linha;
//   linha = calloc(1, sizeof(char));
//   linha = ler_char(file);
//   if(linha [0] == EOF)
//   {
//     free(linha);
//     return NULL;
//   }
//   int i = 1;
//   while((linha[i - 1] != EOF) || (linha[i - 1] != '\n'))
//   {
//     i++;
//     realloc(linha, i * sizeof(unsigned char));
//     linha[i - 1] = ler_char(file);
//   }
//   i++;
//   realloc(linha, i * sizeof(unsigned char));
//   linha[i - 1] = '\0';
//   return linha;
// }

// unsigned char * ler_linha(struct file *file)
// {
//     if (!file || !file->file_ptr)
//         return NULL;

//     int capacidade = 32;   // tamanho inicial
//     int tamanho = 0;

//     unsigned char *linha = malloc(capacidade);
//     if (!linha)
//         return NULL;

//     int c;

//     while ((c = fgetc(file->file_ptr)) != EOF)
//     {
//         // se chegar no fim da linha, finaliza
//         if (c == '\n')
//             break;

//         // verifica se precisa expandir o buffer
//         if (tamanho + 1 >= capacidade)
//         {
//             capacidade *= 2;
//             unsigned char *temp = realloc(linha, capacidade);
//             if (!temp)
//             {
//                 free(linha);
//                 return NULL;
//             }
//             linha = temp;
//         }

//         linha[tamanho++] = (unsigned char)c;
//     }

//     // se não leu nada e chegou no EOF → fim do arquivo
//     if (tamanho == 0 && c == EOF)
//     {
//         free(linha);
//         return NULL;
//     }

//     linha[tamanho] = '\0'; // finaliza string

//     return linha;
// }





int 
finalizar_arquivo(struct file * arquivo)
{
  free(arquivo->path);
  int retorno = fclose(arquivo->file_ptr);
  free(arquivo);
  return retorno;
}