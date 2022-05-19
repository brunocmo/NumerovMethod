#include "../inc/numerovMethodRing.hpp"

NumerovMethodRing::NumerovMethodRing() {
    set_YnAnterior(0);
    set_Yn(0);
    set_YnPosterior(0);
    set_valorE(0);
    set_valorH(0);
    set_alpha(0);
    set_beta(0);
    set_posicaoInicial(0);
}

NumerovMethodRing::~NumerovMethodRing() {}

NumerovMethodRing::NumerovMethodRing(
            double Yn_Anterior,
            double Yn, 
            double alpha,
            double beta,
            double valorH,
            double posicaoInicial
    ) {

    set_YnAnterior(Yn_Anterior);
    set_Yn(Yn);
    set_YnPosterior(0);
    set_valorH(valorH);
    set_alpha(alpha);
    set_beta(beta);
    set_posicaoInicial(posicaoInicial);
    this->betaReal = beta;
} 

bool NumerovMethodRing::gerarResultadoProvisorio() {

    double resultado{0};

    double An{0};
    double Bn{0};
    double g{0};
    int numeroIntervalo{0};

    std::vector<double> valoresAn;
    std::vector<double> valoresBn;
    std::vector<double> valoresX;

    FILE * pFile;
    pFile = fopen("doc/numerovValues5.txt", "w");

    if(!pFile) {
        perror("Erro ao abrir o arquivo!");
        return EXIT_FAILURE;
    }else {


        // printf("====> Alpha: %.2lf ||| Beta: %.6lf <==== \n", get_alpha(), get_beta());

        for( double i{get_posicaoInicial()}; i<(-(get_posicaoInicial())+get_valorH()); i=i+get_valorH()) {
            

            g = (get_beta() + ( get_alpha() / ( sqrt( 1+( (i*i) /100 ) ) ) ) );
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

bool NumerovMethodRing::encontrarValoresE() {

    double valorYfinal{0};
    double valorE{0};
    int iteradorE{0};
    double tempYnAnterior{get_YnAnterior()};
    double tempYn{get_Yn()};
    std::vector<double> valoresEnergia;

    for(double E{-13.95}; E<=(-13.93) ; E=E+0.00000001){
        
        set_YnAnterior(tempYnAnterior);
        set_Yn(tempYn);

        // printf("Para %.7lf ==> ", E);

        valorYfinal = procurarE(E);

        // printf("%lf -- to aqui2\n", valorYfinal);

        if( valorYfinal < 0.0012601 && valorYfinal >= 0.0012600 ){
            valoresEnergia.push_back(E);
        }
    }

    iteradorE = valoresEnergia.size();

    for( double e : valoresEnergia) {
        valorE += e;
        // printf("Valor possível de E: %.10lf\n", e);
    }



    valorE = valorE/iteradorE;

    printf(" O valor viável de E => %.10lf \n", valorE);
    printf("Foram encontrandos %lu valores de E\n", valoresEnergia.size());
    set_beta(betaReal*valorE);

    set_YnAnterior(tempYnAnterior);
    set_Yn(tempYn);

    gerarResultadoProvisorio();

    return EXIT_SUCCESS;
}



double NumerovMethodRing::procurarE(double E) {

    set_beta(betaReal * E);

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


        // printf("====> Alpha - %.2lf ||| Beta - %.2lf <==== \n",  get_alpha(), get_beta());

        for( double i{get_posicaoInicial()}; i<(-(get_posicaoInicial())+get_valorH()); i=i+get_valorH()) {
            
            g = (get_beta() + ( get_alpha() / ( sqrt( 1+( (i*i) /100 ) ) ) ) );
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