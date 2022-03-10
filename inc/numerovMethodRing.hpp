#ifndef NUMEROVMETHODRING_HPP
#define NUMEROVMETHODRING_HPP

#include "numerovMethodWaveFunction.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>

class NumerovMethodRing : public NumerovMethodWaveFunction {

    private: 
        double betaReal;

    public:

        NumerovMethodRing();
        NumerovMethodRing(
            double Yn_Anterior,
            double Yn, 
            double alpha,
            double beta,
            double valorH,
            double posicaoInicial
        );


        ~NumerovMethodRing();


        bool encontrarValoresE();

        bool gerarResultadoFinal();

        double procurarE(double E);

        // Gera resultado com valores definido metado convergindo
        bool gerarResultadoMeioConverge();
        

        bool gerarResultadoMetade();
        // Gera resultado com valores definidos

        bool gerarResultadoProvisorio();

        bool gerarTabela();
};

#endif