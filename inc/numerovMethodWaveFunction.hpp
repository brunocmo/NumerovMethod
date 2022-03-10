#ifndef NUMEROVMETHODWAVEFUNCTION_HPP
#define NUMEROVMETHODWAVEFUNCTION_HPP
#include "numerovMethod.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>

    // planck_eV -- (em eV * segundo) 
    const double planck_eV = 6.58211915e-16;

    // velocidadeLuz -- (em m/s) 
    const double velocidadeLuz = 3e+8;

class NumerovMethodWaveFunction: public NumerovMethod {
    private: 
        
        double alpha;
        double beta;
        double massa;
        double velocidadeAngular;
        double posicaoInicial;

    public:

        NumerovMethodWaveFunction();
        NumerovMethodWaveFunction(
            double Yn_Anterior,
            double Yn, 
            double massa,
            double velocidadeAngular,
            double valorH,
            double posicaoInicial
        );


        bool encontrarValoresE();

        bool gerarResultadoFinal();

        double procurarE(double E);

        // Gera resultado com valores definido metado convergindo
        bool gerarResultadoMeioConverge();
        

        bool gerarResultadoMetade();
        // Gera resultado com valores definidos

        bool gerarResultadoProvisorio();
        // Gera resultado com valores definidos
        bool gerarResultado();
        // Mostra valores possíveis de E com seus limites definidos
        bool gerarResultadoSemE(int valorInicial, int valorFinal);
        // Gera o resultado com o valor de E selecionado
        bool gerarResultadoComE( double e );
        // Cria a tabelo com GNU plot
        bool gerarTabela();

        void set_alpha( double alpha );
        double get_alpha();

        void set_beta( double beta );
        double get_beta();

        void set_posicaoInicial( double posicaoInicial );
        double get_posicaoInicial();

};

#endif 