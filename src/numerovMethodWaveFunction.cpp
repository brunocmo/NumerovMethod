#include "numerovMethodWaveFunction.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>

NumerovMethodWaveFunction::NumerovMethodWaveFunction() {
    set_YnAnterior(0);
    set_Yn(0);
    set_YnPosterior(0);
    set_valorE(0);
}

NumerovMethodWaveFunction::NumerovMethodWaveFunction(
            double Yn_Anterior,
            double Yn, 
            double massa,
            double velocidadeAngular,
            double valorH,
            double posicaoInicial
    ) {

    set_YnAnterior(Yn_Anterior);
    set_Yn(Yn);
    set_YnPosterior(0);
    set_valorH(valorH);

    this->massa = massa;
    this->velocidadeAngular = velocidadeAngular;
    this->posicaoInicial = posicaoInicial;

    this->alpha = (((massa * velocidadeAngular)/(velocidadeLuz*velocidadeLuz) )/ (planck_eV) ) * 1e-18 ;
    this->beta = ((2*massa) / (planck_eV*planck_eV*velocidadeLuz*velocidadeLuz*1e+18)) * 0.18;
} 


bool NumerovMethodWaveFunction::gerarResultadoFinal() {

    double valorYfinal{0};
    double valorE{0};
    double tempYnAnterior{get_YnAnterior()};
    double tempYn{get_Yn()};

    for(double E{0.1700}; E<=0.2000 ; E=E+0.0000001){
        
        set_YnAnterior(tempYnAnterior);
        set_Yn(tempYn);

        printf("Para %.7lf ==> ", E);

        valorYfinal = procurarE(E);

        // printf("%lf -- to aqui2\n", valorYfinal);

        if( valorYfinal < 0.01 && valorYfinal >= -0.01 ){
            valorE = E;
            break;
        }
    }

    printf(" O valor viável de E => %lf \n O valor de Yn final => %lf\n", valorE, valorYfinal);

    this->beta = ((2*massa) / (planck_eV*planck_eV*velocidadeLuz*velocidadeLuz*1e+18)) * valorE;

    gerarResultadoProvisorio();

    return EXIT_SUCCESS;
}

double NumerovMethodWaveFunction::procurarE(double E) {

    this->beta = ((2*massa) / (planck_eV*planck_eV*velocidadeLuz*velocidadeLuz*1e+18)) * E;

    double resultado{0};

    double An{0};
    double Bn{0};
    double g{0};
    int numeroIntervalo{0};

    std::vector<double> valoresAn;
    std::vector<double> valoresBn;
    std::vector<double> valoresX;

    FILE * pFile;
    pFile = fopen("doc/numerovValues.txt", "w");

    if(!pFile) {
        perror("Erro ao abrir o arquivo!");
        return EXIT_FAILURE;
    }else {


        printf("====> Alpha - %.2lf ||| Beta - %.2lf <==== \n", alpha, beta);

        for( double i{posicaoInicial}; i<(-posicaoInicial+get_valorH()); i=i+get_valorH()) {
            
            g = (beta - (alpha*alpha)*(i*i));
            An = 1 + (( ( get_valorH()*get_valorH() )/12 ) * g);
            Bn = 1 - (( ( 5*get_valorH()*get_valorH() )/12 ) * g);

            // printf("Para x = %.3lf \n    An - %.4lf | Bn - %.4lf\n", i, An, Bn);

            valoresAn.push_back(An);
            valoresBn.push_back(Bn);
            valoresX.push_back(i);
            numeroIntervalo++;
        }

            

        // std::cout << numeroIntervalo << '\n';

        for( int k{2}; k<numeroIntervalo; k++) {
            


            // printf("Bk - %lf ; Ak+1 - %lf ; Yn - %lf \n", valoresBn.at(k), valoresAn.at(k+1), get_Yn());
            resultado = 2*(valoresBn.at(k-1)/valoresAn.at(k)) * get_Yn();
            // printf("valor Primario: %lf \n ------------------------\n ", resultado);
            resultado = resultado-(valoresAn.at(k-2)/valoresAn.at(k))*get_YnAnterior();
            set_YnPosterior(resultado);

            set_YnAnterior(get_Yn());
            set_Yn(get_YnPosterior());

        }

        fclose(pFile);


    }

    

    return get_YnPosterior();


}

bool NumerovMethodWaveFunction::gerarResultadoMeioConverge() {


    double resultado{0};

    double An{0};
    double Bn{0};
    double g{0};
    int numeroIntervalo{0};

    double valorAnleft{get_YnAnterior()};
    double valorAnmiddle{get_Yn()};



    std::vector<double> valoresAn;
    std::vector<double> valoresBn;
    std::vector<double> valoresX;

    FILE * pFile;
    pFile = fopen("doc/numerovValuesleft.txt", "w");

    if(!pFile) {
        perror("Erro ao abrir o arquivo!");
        return EXIT_FAILURE;
    }else {


        //printf("====> Alpha - %.2lf ||| Beta - %.2lf <==== \n", alpha, beta);

        for( double i{-posicaoInicial}; i>=0; i=i-get_valorH()) {
            
            g = (beta - (alpha*alpha)*(i*i));
            An = 1 + (( ( get_valorH()*get_valorH() )/12 ) * g);
            Bn = 1 - (( ( 5*get_valorH()*get_valorH() )/12 ) * g);

            //printf("Para x = %.3lf \n    An - %.4lf | Bn - %.4lf\n", i, An, Bn);

            valoresAn.push_back(An);
            valoresBn.push_back(Bn);
            valoresX.push_back(i);
            numeroIntervalo++;
        }

        
        // std::cout << numeroIntervalo << '\n';

        fprintf (pFile , "%.5f %lf\n", float(valoresX.at(0)) , get_YnAnterior());
        fprintf (pFile , "%.5f %lf\n", float(valoresX.at(1)) , get_Yn());

        for( int k{2}; k<3950; k++) {
            
            //printf("Bk - %lf ; Ak+1 - %lf ; Yn - %lf \n", valoresBn.at(k), valoresAn.at(k+1), get_Yn());
            resultado = 2*(valoresBn.at(k-1)/valoresAn.at(k)) * get_Yn();

            //printf("valor Primario: %lf \n ------------------------\n ", resultado);
            resultado = resultado-(valoresAn.at(k-2)/valoresAn.at(k))*get_YnAnterior();
            set_YnPosterior(resultado);

            fprintf (pFile , "%.5f %lf\n", float(valoresX.at(k)) , get_YnPosterior());
            set_YnAnterior(get_Yn());
            set_Yn(get_YnPosterior());

        }



    }

    fclose(pFile);

    numeroIntervalo = 0;
    g = 0;
    An = 0;
    Bn = 0;

    std::vector<double> valoresAn2;
    std::vector<double> valoresBn2;
    std::vector<double> valoresX2;


    FILE * p2File;
    p2File = fopen("doc/numerovValuesright.txt", "w");

    if(!p2File) {
        perror("Erro ao abrir o arquivo!");
        return EXIT_FAILURE;
    }else {
    
        for( double j{posicaoInicial}; j<=0; j=j+get_valorH()) {
            
            g = (beta - (alpha*alpha)*(j*j));
            An = 1 + (( ( get_valorH()*get_valorH() )/12 ) * g);
            Bn = 1 - (( ( 5*get_valorH()*get_valorH() )/12 ) * g);

            // printf("Para x = %.3lf \n    An - %.4lf | Bn - %.4lf\n", j, An, Bn);

            valoresAn2.push_back(An);
            valoresBn2.push_back(Bn);
            valoresX2.push_back(j);
            numeroIntervalo++;
        }

        
        std::cout << numeroIntervalo << '\n';

        set_YnAnterior(valorAnleft);
        set_Yn(valorAnmiddle);

        fprintf (p2File , "%.5f %lf\n", float(valoresX2.at(0)) , get_YnAnterior());
        fprintf (p2File , "%.5f %lf\n", float(valoresX2.at(1)) , get_Yn());

        for( int l{2}; l<3950; l++) {
            
            // printf("Bk - %lf ; Ak+1 - %lf ; Yn - %lf \n", valoresBn2.at(l), valoresAn2.at(l+1), get_Yn());
            resultado = 2*(valoresBn2.at(l-1)/valoresAn2.at(l)) * get_Yn();

            // printf("valor Primario: %lf \n ------------------------\n ", resultado);
            resultado = resultado-(valoresAn2.at(l-2)/valoresAn2.at(l))*get_YnAnterior();
            set_YnPosterior(resultado);

            fprintf (p2File , "%.5f %lf\n", float(valoresX2.at(l)) , get_YnPosterior());
            set_YnAnterior(get_Yn());
            set_Yn(get_YnPosterior());

        }
    }

    fclose(p2File);
    return EXIT_SUCCESS;




}

bool NumerovMethodWaveFunction::gerarResultadoMetade() {

    double resultado{0};

    double An{0};
    double Bn{0};
    double g{0};
    int numeroIntervalo{0};

    double valorAnleft{get_YnAnterior()};
    double valorAnmiddle{get_Yn()};


    std::vector<double> valoresAn;
    std::vector<double> valoresBn;
    std::vector<double> valoresX;

    FILE * pFile;
    pFile = fopen("doc/numerovValuesleft.txt", "w");

    if(!pFile) {
        perror("Erro ao abrir o arquivo!");
        return EXIT_FAILURE;
    }else {


        //printf("====> Alpha - %.2lf ||| Beta - %.2lf <==== \n", alpha, beta);

        for( double i{posicaoInicial}; i>-0.06; i=i-get_valorH()) {
            
            g = (beta - (alpha*alpha)*(i*i));
            An = 1 + (( ( get_valorH()*get_valorH() )/12 ) * g);
            Bn = 1 - (( ( 5*get_valorH()*get_valorH() )/12 ) * g);

            //printf("Para x = %.3lf \n    An - %.4lf | Bn - %.4lf\n", i, An, Bn);

            valoresAn.push_back(An);
            valoresBn.push_back(Bn);
            valoresX.push_back(i);
            numeroIntervalo++;
        }

        
        // std::cout << numeroIntervalo << '\n';

        fprintf (pFile , "%.5f %lf\n", float(valoresX.at(0)) , get_YnAnterior());
        fprintf (pFile , "%.5f %lf\n", float(valoresX.at(1)) , get_Yn());

        for( int k{2}; k<3950; k++) {
            
            //printf("Bk - %lf ; Ak+1 - %lf ; Yn - %lf \n", valoresBn.at(k), valoresAn.at(k+1), get_Yn());
            resultado = 2*(valoresBn.at(k-1)/valoresAn.at(k)) * get_Yn();

            //printf("valor Primario: %lf \n ------------------------\n ", resultado);
            resultado = resultado-(valoresAn.at(k-2)/valoresAn.at(k))*get_YnAnterior();
            set_YnPosterior(resultado);

            fprintf (pFile , "%.5f %lf\n", float(valoresX.at(k)) , get_YnPosterior());
            set_YnAnterior(get_Yn());
            set_Yn(get_YnPosterior());

        }



    }

    fclose(pFile);

    numeroIntervalo = 0;
    g = 0;
    An = 0;
    Bn = 0;

    std::vector<double> valoresAn2;
    std::vector<double> valoresBn2;
    std::vector<double> valoresX2;


    FILE * p2File;
    p2File = fopen("doc/numerovValuesright.txt", "w");

    if(!p2File) {
        perror("Erro ao abrir o arquivo!");
        return EXIT_FAILURE;
    }else {
    
        for( double j{posicaoInicial}; j<0.06; j=j+get_valorH()) {
            
            g = (beta - (alpha*alpha)*(j*j));
            An = 1 + (( ( get_valorH()*get_valorH() )/12 ) * g);
            Bn = 1 - (( ( 5*get_valorH()*get_valorH() )/12 ) * g);

            // printf("Para x = %.3lf \n    An - %.4lf | Bn - %.4lf\n", j, An, Bn);

            valoresAn2.push_back(An);
            valoresBn2.push_back(Bn);
            valoresX2.push_back(j);
            numeroIntervalo++;
        }

        
        std::cout << numeroIntervalo << '\n';

        set_YnAnterior(valorAnleft);
        set_Yn(valorAnmiddle);

        fprintf (p2File , "%.5f %lf\n", float(valoresX2.at(0)) , get_YnAnterior());
        fprintf (p2File , "%.5f %lf\n", float(valoresX2.at(1)) , get_Yn());

        for( int l{2}; l<3950; l++) {
            
            // printf("Bk - %lf ; Ak+1 - %lf ; Yn - %lf \n", valoresBn2.at(l), valoresAn2.at(l+1), get_Yn());
            resultado = 2*(valoresBn2.at(l-1)/valoresAn2.at(l)) * get_Yn();

            // printf("valor Primario: %lf \n ------------------------\n ", resultado);
            resultado = resultado-(valoresAn2.at(l-2)/valoresAn2.at(l))*get_YnAnterior();
            set_YnPosterior(resultado);

            fprintf (p2File , "%.5f %lf\n", float(valoresX2.at(l)) , get_YnPosterior());
            set_YnAnterior(get_Yn());
            set_Yn(get_YnPosterior());

        }
    }

    fclose(p2File);
    return EXIT_SUCCESS;




}

bool NumerovMethodWaveFunction::gerarResultadoProvisorio() {

    double resultado{0};

    double An{0};
    double Bn{0};
    double g{0};
    int numeroIntervalo{0};

    std::vector<double> valoresAn;
    std::vector<double> valoresBn;
    std::vector<double> valoresX;

    FILE * pFile;
    pFile = fopen("doc/numerovValues.txt", "w");

    if(!pFile) {
        perror("Erro ao abrir o arquivo!");
        return EXIT_FAILURE;
    }else {


        printf("====> Alpha - %.2lf ||| Beta - %.2lf <==== \n", alpha, beta);

        for( double i{posicaoInicial}; i<(-posicaoInicial+get_valorH()); i=i+get_valorH()) {
            
            g = (beta - (alpha*alpha)*(i*i));
            An = 1 + (( ( get_valorH()*get_valorH() )/12 ) * g);
            Bn = 1 - (( ( 5*get_valorH()*get_valorH() )/12 ) * g);

            // printf("Para x = %.3lf \n    An - %.4lf | Bn - %.4lf\n", i, An, Bn);

            valoresAn.push_back(An);
            valoresBn.push_back(Bn);
            valoresX.push_back(i);
            numeroIntervalo++;
        }

            

        std::cout << numeroIntervalo << '\n';

        fprintf (pFile , "%.5f %lf\n", float(valoresX.at(0)) , get_YnAnterior());
        fprintf (pFile , "%.5f %lf\n", float(valoresX.at(1)) , get_Yn());

        for( int k{2}; k<numeroIntervalo; k++) {
            


            // printf("Bk - %lf ; Ak+1 - %lf ; Yn - %lf \n", valoresBn.at(k), valoresAn.at(k+1), get_Yn());
            resultado = 2*(valoresBn.at(k-1)/valoresAn.at(k)) * get_Yn();

            // printf("valor Primario: %lf \n ------------------------\n ", resultado);
            resultado = resultado-(valoresAn.at(k-2)/valoresAn.at(k))*get_YnAnterior();
            set_YnPosterior(resultado);

            fprintf (pFile , "%.5f %lf\n", float(valoresX.at(k)) , get_YnPosterior());
            set_YnAnterior(get_Yn());
            set_Yn(get_YnPosterior());

        }

        fclose(pFile);
        return EXIT_SUCCESS;

    }



}

bool NumerovMethodWaveFunction::gerarResultado() {
  /*
    Numerov - isolate Y(n+1)

              ( 2 - (5h²/6) * g(k) ) * Y(n) - ( 1 + (h²/12) * g(k-1) ) Y(n-1)
    Y(n+1) = -----------------------------------------------------------
                            ( 1 + (h²/12) * g(k+1) )

  */

    double resultado{0};

    FILE * pFile;
    pFile = fopen("doc/numerovValues.txt", "w");

    if(!pFile) {
        perror("Erro ao abrir o arquivo!");
        return EXIT_FAILURE;
    }else {

        fprintf (pFile , "0.00 %lf\n", get_YnAnterior() );
        fprintf (pFile , "0.01 %lf\n", get_Yn() );

        for (int i{2}; i<=(1/get_valorH()); i++) {
            resultado = ((1 - ((5*(get_valorH()*get_valorH())/12)*get_valorE())) * 2 *get_Yn());
            resultado -= (1+(((get_valorH()*get_valorH())/12)*get_valorE())) * get_YnAnterior();
            resultado /= (1 + (((get_valorH()*get_valorH())/12) * get_valorE()));
            set_YnPosterior(resultado);

            fprintf (pFile , "%.2f %lf\n", float(i)/100 , get_YnPosterior());
            set_YnAnterior(get_Yn());
            set_Yn(get_YnPosterior());           
        }

        fclose(pFile);
        return EXIT_SUCCESS;
    }
}

bool NumerovMethodWaveFunction::gerarResultadoSemE(int valorInicial, int valorFinal){
     /*
    Numerov - isolate Y(n+1)

              ( 2 - (5h²/6) * g(k) ) * Y(n) - ( 1 + (h²/12) * g(k-1) ) Y(n-1)
    Y(n+1) = -----------------------------------------------------------
                            ( 1 + (h²/12) * g(k+1) )

  */

    double inicialYnAnterior{get_YnAnterior()};
    double inicialYn{get_Yn()};

    double resultado{0};
    double resultadoSimulado[101];

    double erroAproximado{0.0000005};

    resultadoSimulado[0] = get_YnAnterior();
    resultadoSimulado[1] = get_Yn();

    std::vector<double> valoresE;

    int iterador{0};

    for(double e{double(valorInicial)}; e<double(valorFinal); e+=0.000005) {
        
        set_YnAnterior(inicialYnAnterior);
        set_Yn(inicialYn);  
        
        for (int i{2}; i<=100; i++) {
            resultado = ((1 - ((5*(get_valorH()*get_valorH())/12)*e)) * 2 *get_Yn());
            resultado -= (1+(((get_valorH()*get_valorH())/12)*e)) * get_YnAnterior();
            resultado /= (1 + (((get_valorH()*get_valorH())/12) * e));
            set_YnPosterior(resultado);

            resultadoSimulado[i] = resultado;

            set_YnAnterior(get_Yn());
            set_Yn(get_YnPosterior());           
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

bool NumerovMethodWaveFunction::gerarResultadoComE( double e ) {

    set_valorE(e);
    set_Yn( sqrt(2)*sin(sqrt(e)*get_valorH()) );
    set_YnAnterior(0);

    std::cout << "Plotando para Yn em "<< get_Yn() << '\n';

    gerarResultado();
    gerarTabela();

    return EXIT_SUCCESS;
}

bool NumerovMethodWaveFunction::gerarTabela() {
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