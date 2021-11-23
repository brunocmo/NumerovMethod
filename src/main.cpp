#include "numerovMethod.hpp"
#include <cmath>

int main() {

  // NumerovMethod * teste1 = new NumerovMethod(0, 0.437, 9.872125685 , 0.1);
  // NumerovMethod * teste2 = new NumerovMethod(0, 0.0888, pow(2*M_PI, 2), 0.01);
  NumerovMethod * teste3 = new NumerovMethod(0, 0.0888, 0.01);

  // teste1->gerarResultado();
  // teste1->gerarTabela();

  // teste2->gerarResultado();
  // teste2->gerarTabela();

  if( teste3->gerarResultadoSemE(0, 100) == 0 ) {
    teste3->gerarTabela();
  }
  
  return 0;

}
