#ifndef NUMEROVMETHOD_HPP
#define NUMEROVMETHOD_HPP

class NumerovMethod {

    private: 
        double YnAnterior;
        double Yn;
        double YnPosterior;
        double valorE;
        double valorH;

    public:
        NumerovMethod();
        NumerovMethod(
            double Yn, 
            double valorE, 
            double valorH
        );
        NumerovMethod(double Yn, double valorH);
        ~NumerovMethod();

        // Geters and Setters
        double get_YnAnterior();
        void set_YnAnterior(double YnAnterior);

        double get_Yn();
        void set_Yn(double Yn);

        double get_YnPosterior();
        void set_YnPosterior(double YnPosterior);

        double get_valorE();
        void set_valorE(double valorE);

        double get_valorH();
        void set_valorH(double valorH);

        // Gera resultado com valores definidos
        bool gerarResultado();
        // Mostra valores possíveis de E com seus limites definidos
        bool gerarResultadoSemE(int valorInicial, int valorFinal);
        // Gera o resultado com o valor de E selecionado
        bool gerarResultadoComE( double e );
        // Cria a tabelo com GNU plot
        bool gerarTabela();

};

#endif 