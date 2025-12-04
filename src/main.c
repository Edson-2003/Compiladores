#include <stdio.h>
#include "dirhandler.h"
#include "automoto.h"

int
main()
{
  struct automoto * automoto;
  automoto = criar_automoto("../automotos/teste.afd");
  printf("Leu o automoto\n");
  printf("validado: %d\n", rodar_automoto(automoto, (unsigned char *) "oi"));
  // imprime_automoto(automoto);
  printf("imprimiu op automoto\n");
  limpar_automoto(automoto);
  return 0;
}