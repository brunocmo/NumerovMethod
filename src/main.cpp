#include <iostream>
#include <cmath>
#include <stdio.h>

// Fix values
double valorG(double x);

int main() {

  FILE * pFile;

  pFile = fopen("valor.txt", "w");

  /*
    Numerov - isolate Y(n+1)

              ( 2 - (5h²/6) * g(k) ) * Y(n) - ( 1 + (h²/12) * g(k-1) ) Y(n-1)
    Y(n+1) = -----------------------------------------------------------
                            ( 1 + (h²/12) * g(k+1) )


              leftIteration - rightIteration
    Y(n+1) = -----------------------------------
                         divider

  */

  double Yn_ant{0};
  double Yn{0.0888};
  double Yn_pos{0};

  // Problema definição de h
  double h = 0.01;

  // Problema ao resolver valor de G
  // double gk_ant{valorG(-M_2_PI)};
  // double gk{gk_ant+h};
  // double gk_pos{gk+h};

  // double PlankConst{1.055e-34};

  double divider{0};
  double leftIteration{0};
  double rightIteration{0};

  // VALOR DO E
  double e{2*M_PI};
  e = e*e;
  
  std::cout << "n | Y(n+1) |  Y(n)  | Y(n-1)" << '\n';


  for (int i{0}; i<100 ; i++) {

    leftIteration =  (1 - ((5*(h*h)/12)*e)) * 2 *Yn;
    rightIteration = (1+(((h*h)/12)*e)) * Yn_ant;


    divider =  1 + (((h*h)/12) * e);

    Yn_pos = ( leftIteration - rightIteration ) / divider;


    std::cout << i << " | " << Yn_pos << " | " << Yn << " | " << Yn_ant << "\n";

    // gk_ant = gk;
    // gk = gk_pos;
    // gk_pos = gk+h;

    fprintf (pFile , "%lf\n", Yn_pos);

    Yn_ant = Yn;
    Yn = Yn_pos;

  }

  fclose(pFile);

  return 0;

}
