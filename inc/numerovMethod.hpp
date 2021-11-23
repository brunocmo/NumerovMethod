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
            double YnAnterior, 
            double Yn, 
            double valorE, 
            double valorH
        );
        NumerovMethod(double YnAnterior, double Yn, double valorH);
        ~NumerovMethod();

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

        bool gerarResultado();

        bool gerarResultadoSemE(int valorInicial, int valorFinal);

        bool gerarTabela();

};

#endif 