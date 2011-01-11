#ifndef DISTRIBUIRHORMONA_H
#define DISTRIBUIRHORMONA_H

#include "comando.h"
#include "SimpleGLScene.hh"

class NodoProb{
    public:
    int indnodo;
    double probabilidad;
    double distancia;
    double ponderacionubicacion;
    NodoProb(){
        this->indnodo=-1;
        this->distancia=0;
        this->probabilidad=0;
        this->ponderacionubicacion=1;
        }
    NodoProb(int indnodo, double distancia){
        this->indnodo=indnodo;
        this->distancia=distancia;
        this->probabilidad=0;
        this->ponderacionubicacion=1;
        }
    bool operator<(const NodoProb &n)const{
        return distancia<n.distancia;
        }
    };

class DistribuirHormona : public Comando
{
    public:
        DistribuirHormona(  Malla* malla,
                            SimpleGLScene* simpleglscene,
                            double factorgravitacional,
                            double factorlongitudinal,
                            double factortangencial
                            );
        void execute();
        ~DistribuirHormona();
    protected:
    private:
        SimpleGLScene* simpleglscene;
        double factorgravitacional;
        double factorlongitudinal;
        double factortangencial;
        vector<NodoProb> *nodosprob;

        Vect getVectorLongitudinal(double altura);
        double calcularProbabilidad(int indNodo, int indNodoDestino, double ponderacion);  //Calcula la probabilidad de que indNodo vaya a indNodoDestino.
        void paseoHormonas(); //Realiza el paseo al hazar de las hormonas y actualiza las concentraciones de acuerdo a eso.
        int paseoAlAzar(int indNodo);   //Retorna el indice al nodo donde continua el paseo.
        vector<NodoProb> getNodosCercanos(int indNodo);
        void normalizarProbabilidades(int indNodo);
};



#endif // DISTRIBUIRHORMONA_H
