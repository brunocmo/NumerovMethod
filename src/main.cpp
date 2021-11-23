#include "numerovMethod.hpp"
#include <cmath>

int main() {

  // NumerovMethod * teste1 = new NumerovMethod(0.437, 9.872125685 , 0.1);
  // NumerovMethod * teste2 = new NumerovMethod(0.0888, pow(2*M_PI, 2), 0.01);
  NumerovMethod * teste3 = new NumerovMethod(0.0888, 0.01);
  // NumerovMethod * teste4 = new NumerovMethod(0.133089, pow(3*M_PI, 2), 0.01);


  // teste1->gerarResultado();
  // teste1->gerarTabela();

  // teste2->gerarResultado();
  // teste2->gerarTabela();

  // teste3->gerarResultadoSemE(0, 300);

  teste3->gerarResultadoComE(9.869605);
  teste3->gerarResultadoComE(39.478415);
  teste3->gerarResultadoComE(88.826410);
  teste3->gerarResultadoComE(157.913505);
  teste3->gerarResultadoComE(246.739465);

  
  // teste4->gerarResultado();
  // teste4->gerarTabela();

  delete teste3;

  return 0;

}
