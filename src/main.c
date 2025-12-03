#include <stdio.h>
#include "dirhandler.h"
#include "automoto.h"

int
main()
{
  struct automoto * automoto;
  automoto = criar_automoto("../automotos/teste.afd");
  imprime_automoto(automoto);
  limpar_automoto(automoto);
  return 0;
}