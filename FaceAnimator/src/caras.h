#ifndef CARAS_H
#define CARAS_H

#include "nodo.h"
#include "nodos.h"
#include "cara.h"

class Cara;
/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase es un contenedor de caras, es decir, representa un conjunto de caras
 */
class Caras {
    private:
        vector<Cara*> caras; // lista de caras.
        vector<int> borrados; // lista de índices a caras que han sido borradas.
        int num_caras; // número de caras almacenadas.
        int num_caras_validas; // número de caras almacenadas que no han sido borradas, debe ser igual a caras.size() - borrados.size().
	protected:
        Caras(Caras *c); // constructor de copia
    public:
        Caras(); // crea un contenedor de caras con 0 caras.
        Caras(Cara *c); // crea un contenedor de caras con 1 cara.
        Caras(vector<Cara*> crs); // crea un contenedor con un conjunto de caras.
        Caras *clone();
        int addCara(Cara *c); // agrega una cara al contenedor.
        int addCaraIn(Cara *c, int indice); // agrega la cara "c" al contenedor en la posicion "indice". Si habia otra cara en indice se borra.
        void eraseCara(int indice); // borra la cara en ese indice si no estaba borrada.
        Cara* getCara(int indice); // get de la cara en ese inidice.
        Cara* operator[](int indice); // get de la cara en ese inidice.
        int getNumCaras(); // número de caras totales.
        int getNumCarasValidas(); // número de caras válidas.
        friend ostream& operator<<(ostream &os, Caras *c);
		~Caras();
};

#endif
