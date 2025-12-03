#include <stdio.h>
#include "dirhandler.h"
#include "automoto.h"

int
main()
{
  struct automoto * automoto;
  automoto = criar_automoto("../automotos/teste.afd");
  printf("Leu o automoto\n");
  struct estado * estado = procurar_estado(automoto, 3);
  printf("%d\n", estado->id);


  imprime_automoto(automoto);
  printf("imprimiu op automoto\n");
  limpar_automoto(automoto);
  return 0;
}