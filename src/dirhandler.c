#include "../include/dirhandler.h"

int 
finalizar_item(struct item * item)
{
  int retorno = 0;
  if(item->fd)
  {
    retorno = finalizar_arquivo(item->fd);
  }
  free(item);
  return retorno;
}

int 
finalizar_dir(struct dir *dir)
{
  int retorno = 0;
  while(dir->arquivos)
  {
    struct item * temp;
    temp = dir->arquivos;
    dir->arquivos = temp->next;
    retorno = finalizar_item(temp);
  }
  free(dir->caminho);
  free(dir);
  return retorno;
}

struct item * 
criar_item(char * caminho)
{
  struct item * item;
  item = (struct item *) malloc(sizeof(struct item));
  item->fd = criar_arquivo(caminho);
  item->next =  NULL;
  return item;
}

int 
inserir_item(struct dir * dir, struct item * item)
{
  if(!dir || !item)
  {
    return -1;
  }
  item->next =  dir->arquivos;
  dir->arquivos = item;
  dir->qtd_arquivos++;
  return 0;
}
int 
remover_item(struct dir * dir, struct item * item)
{
  if(!dir || !item)
  {
    return -1;
  }

  if(dir->arquivos == item)
  {
    dir->arquivos = item->next;
    finalizar_item(item);
    dir->qtd_arquivos--;
    return 0;
  }

  struct item * temp;
  temp = dir->arquivos;
  while(temp->next != NULL)
  {
    if(temp->next == item)
    {
      temp->next = item->next;
      dir->qtd_arquivos--;
      finalizar_item(item);
      return 0;
    }
  }

  finalizar_item(item);
  return 0;
}


struct dir * 
criar_dir(char *caminho)
{
  struct dir * dir;
  dir = (struct dir *) malloc(sizeof(struct dir));
  
  DIR *fd = opendir(caminho);

  if (fd == NULL) 
  {

    return NULL;
  }

  struct dirent *entry;
  while ((entry = readdir(fd)) != NULL) 
  {
    if(!valida(entry->d_name))
    {
      continue;
    }
    char * path = cct(caminho,cct("/", entry->d_name));
    struct item * temp = criar_item(path);
    inserir_item(dir,temp);
  }

  closedir(fd);

  return dir;
}
