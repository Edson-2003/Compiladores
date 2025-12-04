#include "../include/Filehandler.h"

struct file *
criar_arquivo(char * path, bool read)
{
  struct file * file;
  file = (struct file *) malloc(sizeof(struct file));
  if(read)
  {
    file->file_ptr = fopen(path, "r");
  }
  else
  {
    file->file_ptr = fopen(path, "w");
  }
    
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


int 
finalizar_arquivo(struct file * arquivo)
{
  free(arquivo->path);
  int retorno = fclose(arquivo->file_ptr);
  free(arquivo);
  return retorno;
}