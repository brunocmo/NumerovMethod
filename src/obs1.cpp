// #include <iostream>
// #include <cmath>

// // Fix values
// double valorG(double x);

// int main() {

//   /*
//     Numerov - isolate Y(n+1)

    
//               ( 2 - (5h²/6) * g(k) ) * Y(n) - ( 1 + (h²/12) * g(k-1) ) Y(n-1)
//     Y(n+1) = -----------------------------------------------------------
//                             ( 1 + (h²/12) * g(k+1) )


//               leftIteration - rightIteration
//     Y(n+1) = -----------------------------------
//                          divider


//   */


//   double Yn_ant{0};
//   double Yn{0.0001};
//   double Yn_pos{0};

//   // Problema definição de h
//   double h = (2*M_2_PI/1);

//   // Problema ao resolver valor de G
//   double gk_ant{valorG(-M_2_PI)};
//   double gk{gk_ant+h};
//   double gk_pos{gk+h};

//   double PlankConst{1.055e-34};

//   double divider{0};
//   double leftIteration{0};
//   double rightIteration{0};

  
  
//   std::cout << "n | Y(n+1) |  Y(n)  | Y(n-1)" << '\n';


//   for (int i{0}; i<6 ; i++) {

//     leftIteration =  (2-((5*(PlankConst*PlankConst)/6)*gk)) * Yn;
//     rightIteration = (1+(((PlankConst*PlankConst)/12)*gk_ant)) * Yn_ant;
//     divider =  1 + (((PlankConst*PlankConst)/12) * gk_pos);

//     Yn_pos = ( leftIteration - rightIteration ) / divider;

//     gk_ant = gk;
//     gk = gk_pos;
//     gk_pos = gk+h;

//     Yn_ant = Yn;
//     Yn = Yn_pos;

//     std::cout << i << " | " << Yn_pos << " | " << Yn << " | " << Yn_ant << "\n";

//   }


// }

// double valorG(double x) {

//   double result{0};
//   double Vo{1};
//   double expressao{0};
//   float E{0.5};

//   result = (1 - x * (1/tan(x)))/(x*x);
//   result = Vo*result;

//   result = 2 * (E - result);

//   return result;

// }
