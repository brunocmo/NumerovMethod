#include "numerovMethod.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>

NumerovMethod::NumerovMethod() {
    YnAnterior = 0;
    Yn = 0;
    YnPosterior = 0;
    valorE = 0;
}

NumerovMethod::NumerovMethod(
        double Yn, 
        double valorE, 
        double valorH
    ) {
    this->Yn = Yn;
    this->valorE = valorE;
    this->valorH = valorH;
    Yn = 0;
    YnPosterior = 0;
}

NumerovMethod::NumerovMethod(
        double Yn, 
        double valorH
    ) {
    this->Yn = Yn;
    this->valorH = valorH;
    Yn = 0;
    YnPosterior = 0;
    valorE = 0;
}

NumerovMethod::~NumerovMethod() { 
}

double NumerovMethod::get_YnAnterior() {
    return YnAnterior;
}

void NumerovMethod::set_YnAnterior(double YnAnterior) {
    this->YnAnterior = YnAnterior;
}

double NumerovMethod::get_Yn() {
    return Yn;
}

void NumerovMethod::set_Yn(double Yn) {
    this->Yn = Yn;
}

double NumerovMethod::get_YnPosterior() {
    return YnPosterior;
}

void NumerovMethod::set_YnPosterior(double YnPosterior) {
    this->YnPosterior = YnPosterior;
}

double NumerovMethod::get_valorE() {
    return valorE;
}

void NumerovMethod::set_valorE(double valorE) {
    this->valorE = valorE;
}

double NumerovMethod::get_valorH() {
    return valorH;
}

void NumerovMethod::set_valorH(double valorH) {
    this->valorH = valorH;
}

bool NumerovMethod::gerarResultado() {
  /*
    Numerov - isolate Y(n+1)

              ( 2 - (5h²/6) * g(k) ) * Y(n) - ( 1 + (h²/12) * g(k-1) ) Y(n-1)
    Y(n+1) = -----------------------------------------------------------
                            ( 1 + (h²/12) * g(k+1) )

  */

    double resultado{0};

    FILE * pFile;
    pFile = fopen("doc/valor.txt", "w");

    if(!pFile) {
        perror("Erro ao abrir o arquivo!");
        return EXIT_FAILURE;
    }else {

        fprintf (pFile , "0.00 %lf\n", YnAnterior);
        fprintf (pFile , "0.01 %lf\n", Yn);

        for (int i{2}; i<=(1/valorH); i++) {
            resultado = ((1 - ((5*(valorH*valorH)/12)*valorE)) * 2 *Yn);
            resultado -= (1+(((valorH*valorH)/12)*valorE)) * YnAnterior;
            resultado /= (1 + (((valorH*valorH)/12) * valorE));
            set_YnPosterior(resultado);

            fprintf (pFile , "%.2f %lf\n", float(i)/100 , YnPosterior);
            set_YnAnterior(Yn);
            set_Yn(YnPosterior);           
        }

        fclose(pFile);
        return EXIT_SUCCESS;
    }
}

bool NumerovMethod::gerarResultadoSemE(int valorInicial, int valorFinal){
     /*
    Numerov - isolate Y(n+1)

              ( 2 - (5h²/6) * g(k) ) * Y(n) - ( 1 + (h²/12) * g(k-1) ) Y(n-1)
    Y(n+1) = -----------------------------------------------------------
                            ( 1 + (h²/12) * g(k+1) )

  */

    double inicialYnAnterior{YnAnterior};
    double inicialYn{Yn};

    double resultado{0};
    double resultadoSimulado[101];

    double erroAproximado{0.0000005};

    resultadoSimulado[0] = YnAnterior;
    resultadoSimulado[1] = Yn;

    std::vector<double> valoresE;

    int iterador{0};

    for(double e{double(valorInicial)}; e<double(valorFinal); e+=0.000005) {
        
        set_YnAnterior(inicialYnAnterior);
        set_Yn(inicialYn);  
        
        for (int i{2}; i<=100; i++) {
            resultado = ((1 - ((5*(valorH*valorH)/12)*e)) * 2 *Yn);
            resultado -= (1+(((valorH*valorH)/12)*e)) * YnAnterior;
            resultado /= (1 + (((valorH*valorH)/12) * e));
            set_YnPosterior(resultado);

            resultadoSimulado[i] = resultado;

            set_YnAnterior(Yn);
            set_Yn(YnPosterior);           
        }

        if( resultadoSimulado[100] < erroAproximado && resultadoSimulado[100] > -erroAproximado) {
            valoresE.push_back(e);
            // printf("Simulado = %lf\n", resultadoSimulado[100]);
            // printf("Entrei, o valor E = %f \n", e);
            iterador++;
        };

    }

    for( double valor : valoresE) {
        printf("Valor possivel de E: %lf\n", valor);
    }

    // set_YnAnterior(inicialYnAnterior);
    // set_Yn(inicialYn);

    // gerarResultado();

    return EXIT_SUCCESS;

}

bool NumerovMethod::gerarResultadoComE( double e ) {

    set_valorE(e);
    set_Yn( sqrt(2)*sin(sqrt(e)*valorH) );
    set_YnAnterior(0);

    std::cout << "Plotando para Yn em "<< get_Yn() << '\n';

    gerarResultado();
    gerarTabela();

    return EXIT_SUCCESS;
}

bool NumerovMethod::gerarTabela() {
    FILE * gnuplotPipe = popen("gnuplot -persistent", "w");

    if(!gnuplotPipe){
        perror("Erro ao executar tabela");
        return EXIT_FAILURE;
    }else {

        char tituloTabela[30] = "set title \"Numerov\"";
        char executarPlot[100] = "plot 'doc/valor.txt' with lines";

        fprintf (gnuplotPipe, "%s \n", tituloTabela);
        fprintf (gnuplotPipe, "%s \n", executarPlot);

        pclose(gnuplotPipe);

        return EXIT_SUCCESS;
    }
}