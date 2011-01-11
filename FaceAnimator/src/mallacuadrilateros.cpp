#include "mallacuadrilateros.h"
#include "triangulo.h"
#include "fabricaalgoritmosmallacuadrilateros.h"

MallaCuadrilateros::MallaCuadrilateros(Nodos *nds, Arcos *arcs, Caras *crs):Malla(nds,arcs,crs){
}

MallaTriangulos *MallaCuadrilateros::triangular() {
	Caras *nuevas_caras = new Caras();
	Nodos *nuevos_nodos = nodos->clone();
	Arcos *nuevos_arcos = arcos->clone();
	for(int i = 0; i < caras->getNumCaras(); ++i) {
		Cara *cara = caras->getCara(i);
		if(cara == 0)
			continue;
		cara->ordenar(this);
		vector<int> ind_arcos = cara->getArcos();
		vector<int> ind_nodos = cara->getNodos();

		// Encontrar mayor angulo y para dividirlo
		int n_ang_max = cara->getNodoAnguloMax(this);
		int n0 = -1;
		for(int j = 0; j < (int)ind_nodos.size(); ++j) {
		    if(n_ang_max == ind_nodos[j]) {
                n0 = j;
                break;
		    }
		}

		int n1 = int(fmod(n0+1,4));
		int n2 = int(fmod(n0+2,4));
		int n3 = int(fmod(n0+3,4));

		Arco *nuevo_arco = new Arco(ind_nodos[n0],ind_nodos[n2]);
		int ind_nuevo_arco = nuevos_arcos->addArco(nuevo_arco);
		Cara *nueva_cara_1 = new Triangulo(ind_nodos[n0],ind_nodos[n1],ind_nodos[n2],ind_arcos[n0],ind_arcos[n1],ind_nuevo_arco);
		Cara *nueva_cara_2 = new Triangulo(ind_nodos[n0],ind_nodos[n2],ind_nodos[n3],ind_nuevo_arco,ind_arcos[n2],ind_arcos[n3]);
		int ind_nueva_cara_1 = nuevas_caras->addCara(nueva_cara_1);
		int ind_nueva_cara_2 = nuevas_caras->addCara(nueva_cara_2);
		nuevo_arco->setCaras(ind_nueva_cara_1,ind_nueva_cara_2);
		for(int j = 0; j < (int)ind_nodos.size(); ++j) {
			Nodo *nodo = nuevos_nodos->getNodo(ind_nodos[j]);
			nodo->eraseCara(i);

			if(j != n3)
				nodo->addCaraConRepeticion(ind_nueva_cara_1);
			if(j != n1)
				nodo->addCaraConRepeticion(ind_nueva_cara_2);
			if(j == n0 || j == n2)
				nodo->addArco(ind_nuevo_arco);
		}
		nuevos_arcos->getArco(ind_arcos[n0])->changeCara(i,ind_nueva_cara_1);
		nuevos_arcos->getArco(ind_arcos[n1])->changeCara(i,ind_nueva_cara_1);
		nuevos_arcos->getArco(ind_arcos[n2])->changeCara(i,ind_nueva_cara_2);
		nuevos_arcos->getArco(ind_arcos[n3])->changeCara(i,ind_nueva_cara_2);
	}

	MallaTriangulos *malla = new MallaTriangulos(nuevos_nodos, nuevos_arcos, nuevas_caras);
    malla->setNormales();

	//Chequeamos consistencia topologica.
	int V=malla->getNumNodos();
	int E=malla->getNumArcos();
	int F=malla->getNumCaras();
	cout << "Numero de nodos=" << V << endl;
	cout << "Numero de arcos=" << E << endl;
	cout << "Numero de caras=" << F << endl;
	if (V-E+F==2 || V-E+F==0)
		cout << "La malla es consistente. Cumple la formula de Euler: V-E+F=2" << endl;
	else
		cout << "Atencion, la malla no es consistente. No cumple la formula de Euler: V-E+F=" << V-E+F << " y deberia ser V-E+F=2" << endl;

    assert(malla->checkMalla(true) >= 0);
    return malla;

}

FabricaAlgoritmos *MallaCuadrilateros::getFabricaAlgoritmos() {
    if(fabrica_algoritmos == NULL)
        fabrica_algoritmos = new FabricaAlgoritmosMallaCuadrilateros();
    return fabrica_algoritmos;
}

int MallaCuadrilateros::colapsarRegion(int indVerticeCentral) {
	// Respaldar estado actual de la malla
	Caras *caras_respaldo = caras->clone();
	Arcos *arcos_respaldo = arcos->clone();
	Nodos *nodos_respaldo = nodos->clone();

	bool colapso_ok = true;

	try {

        Nodo *nodo_central = nodos->getNodo(indVerticeCentral);
        vector<int> arcos_nodo_central = nodo_central->getArcos();

        for(int i = 0; i < (int)arcos_nodo_central.size(); ++i) {

            int indArcoAColapsar = arcos_nodo_central[i];
            Arco *arco_colapsar = arcos->getArco(indArcoAColapsar);
            int indVerticeABorrar = arco_colapsar->getNodoDistinto(indVerticeCentral);
            Nodo* verticeABorrar = getNodo(indVerticeABorrar);

            //Se omite si el vertice esta en el borde.
            if (esNodoBorde(indVerticeABorrar))
                return -1;

            //Obtenemos el vertice a mantener.
            int indVerticeAMantener = indVerticeCentral;
            Nodo* verticeAMantener = getNodo(indVerticeAMantener);

            //Obtenemos las caras que van a ser borradas.
            int indCaraABorrar1=arcos->getArco(indArcoAColapsar)->getCara1();
            int indCaraABorrar2=arcos->getArco(indArcoAColapsar)->getCara2();

            //Obtenemos las caras que deben ser modificadas.
            vector<int> indCarasAModificar;
            vector<int> indCarasVecinasAlNodo = nodos->getNodo(indVerticeABorrar)->getCaras();
            for (int i=0; i<(int)indCarasVecinasAlNodo.size(); i++)
                if (indCarasVecinasAlNodo[i]!=indCaraABorrar1 && indCarasVecinasAlNodo[i]!=indCaraABorrar2) {
                    indCarasAModificar.push_back(indCarasVecinasAlNodo[i]);
                }

            //Chequeamos si se puede hacer el vertexDeletion.
            //Vemos si alguna cara se voltearia al hacerlo.
            for (int i=0; i<(int)indCarasAModificar.size(); i++){
                int indCara=indCarasAModificar[i];
                Vect viejaNormal=caras->getCara(indCara)->getNormal(this);
                Punto viejoPunto=verticeABorrar->getPunto();
                Punto nuevoPunto=verticeAMantener->getPunto();
                verticeABorrar->setPunto(nuevoPunto);
                Vect nuevaNormal=caras->getCara(indCara)->getNormal(this);
                verticeABorrar->setPunto(viejoPunto);
                if (viejaNormal.inOrigen() || nuevaNormal.inOrigen()) //Por problema de precision no se puede calcular la normal.
                    return -1;
                double angulo=viejaNormal.getAngulo(nuevaNormal);
                if (angulo>PI/2) {
                    throw -1;
                }
            }

            //Obtenemos los arcos que se van a mantener.
            vector<int> posibles_arcos_a_mantener_1 = this->getArcosNoIncidentes(indCaraABorrar1,indVerticeABorrar);
            vector<int> posibles_arcos_a_mantener_2 = this->getArcosNoIncidentes(indCaraABorrar2,indVerticeABorrar);
            int indArcoAMantener1 = -1;
            int indArcoAMantener2 = -1;

            //Obtenemos los arcos que van a ser borrados.
            int indArcoABorrar1 = getArcoDiferente(indCaraABorrar1,indArcoAColapsar,indVerticeABorrar);
            int indArcoABorrar2 = getArcoDiferente(indCaraABorrar2,indArcoAColapsar,indVerticeABorrar);

            //Obtenemos las caras reemplazantes.
            vector<int> posibles_caras_reemplazantes_1 = this->getCarasVecinasSinNodo(indCaraABorrar1,indVerticeAMantener);
            vector<int> posibles_caras_reemplazantes_2 = this->getCarasVecinasSinNodo(indCaraABorrar2,indVerticeAMantener);
            int indCaraAReemplazar1 = -1;
            int indCaraAReemplazar2 = -1;

            Cara *nueva_cara_1 = caras->getCara(indCaraABorrar1)->colapsarArco(this,indArcoAColapsar,indVerticeABorrar);
            Cara *nueva_cara_2 = caras->getCara(indCaraABorrar2)->colapsarArco(this,indArcoAColapsar,indVerticeABorrar);
            caras->eraseCara(indCaraABorrar1);
            caras->eraseCara(indCaraABorrar2);

            if(nueva_cara_1 != NULL) {
                caras->addCaraIn(nueva_cara_1,indCaraABorrar1);
                indCaraABorrar1 = -1;
                indArcoABorrar1 = -1;
            }
            else {
                //Obtenemos el arco que se va a mantener.
                indArcoAMantener1 = posibles_arcos_a_mantener_1[0]; // Vector con un solo elemento
                indCaraAReemplazar1 = posibles_caras_reemplazantes_1[0]; // Vector con un solo elemento
            }
            if(nueva_cara_2 != NULL) {
                caras->addCaraIn(nueva_cara_2,indCaraABorrar2);
                indCaraABorrar2 = -1;
                indArcoABorrar2 = -1;
            }
            else {
                //Obtenemos el arco que se va a mantener.
                indArcoAMantener2 = posibles_arcos_a_mantener_2[0]; // Vector con un solo elemento
                indCaraAReemplazar2 = posibles_caras_reemplazantes_2[0]; // Vector con un solo elemento
            }

            //Modificamos las caras.
            for (int i=0; i<(int)indCarasAModificar.size(); i++){
                Cara* caraAModificar=caras->getCara(indCarasAModificar[i]);
                //Modificamos sus nodos.
                caraAModificar->changeNodo(indVerticeABorrar,indVerticeAMantener);
                for (int j=0; j<(int)caraAModificar->getNodos().size(); j++){
                    int indNodoAModificar=caraAModificar->getNodos()[j];
                    Nodo* nodoAModificar=nodos->getNodo(indNodoAModificar);
                    nodoAModificar->eraseCara(indCaraABorrar1);
                    nodoAModificar->eraseCara(indCaraABorrar2);
                    nodoAModificar->eraseArco(indArcoABorrar1);
                    nodoAModificar->eraseArco(indArcoABorrar2);
                }
                //Modificamos sus arcos.
                for (int j=0; j<(int)caraAModificar->getArcos().size(); j++){
                    int indArcoAModificar=caraAModificar->getArcos()[j];
                    Arco* arcoAModificar=arcos->getArco(indArcoAModificar);
                    if (indArcoAModificar==indArcoABorrar1)
                        caraAModificar->changeArco(indArcoAModificar,indArcoAMantener1);	//Cambiamos el arco.
                    else if (indArcoAModificar==indArcoABorrar2)
                        caraAModificar->changeArco(indArcoAModificar,indArcoAMantener2);	//Cambiamos el arco.
                    else
                    if (arcoAModificar->getNodo1()==indVerticeABorrar)
                        arcoAModificar->setNodo1(indVerticeAMantener);
                    else if (arcoAModificar->getNodo2()==indVerticeABorrar)
                        arcoAModificar->setNodo2(indVerticeAMantener);

                }
            }

            //Modificamos los nodos mantenidos.
            verticeAMantener->eraseCara(indCaraABorrar1);
            verticeAMantener->eraseCara(indCaraABorrar2);
            verticeAMantener->eraseArco(indArcoABorrar1);
            verticeAMantener->eraseArco(indArcoABorrar2);
            verticeAMantener->eraseArco(indArcoAColapsar);
            for (int i=0; i<(int)indCarasAModificar.size(); i++){
                verticeAMantener->addCara(indCarasAModificar[i]);
                Cara* cara=caras->getCara(indCarasAModificar[i]);
                for (int j=0; j<(int)cara->getArcos().size(); j++){
                    int indArco=cara->getArcos()[j];
                    Arco* arco=arcos->getArco(indArco);
                    if (indArco!=indArcoABorrar1 && indArco!=indArcoABorrar2 &&
                        (arco->getNodo1()==indVerticeAMantener || arco->getNodo2()==indVerticeAMantener))
                            verticeAMantener->addArco(indArco);
                    }
                }

            //Modificamos los arcos mantenidos.
            if(indArcoAMantener1 != -1) {
                Arco* arcoAMantener1=arcos->getArco(indArcoAMantener1);
                if (arcoAMantener1->getCara1()==indCaraABorrar1)
                    arcoAMantener1->setCara1(indCaraAReemplazar1);
                else if (arcoAMantener1->getCara2()==indCaraABorrar1)
                    arcoAMantener1->setCara2(indCaraAReemplazar1);
            }

            if(indArcoAMantener2 != -1) {
                Arco* arcoAMantener2=arcos->getArco(indArcoAMantener2);
                if (arcoAMantener2->getCara1()==indCaraABorrar2)
                    arcoAMantener2->setCara1(indCaraAReemplazar2);
                else if (arcoAMantener2->getCara2()==indCaraABorrar2)
                    arcoAMantener2->setCara2(indCaraAReemplazar2);
            }

            //Borramos
            nodos->eraseNodo(indVerticeABorrar);
            if(indArcoABorrar1 != -1)
                arcos->eraseArco(indArcoABorrar1);
            if(indArcoABorrar2 != -1)
                arcos->eraseArco(indArcoABorrar2);
            arcos->eraseArco(indArcoAColapsar);

            // Chequear que caras modificadas quedaron consistentes
            for (int i=0; i<(int)indCarasAModificar.size(); i++){
                if(!this->getCara(indCarasAModificar[i])->check(this)) {
                    throw -1;
                }
            }

        }
		delete caras_respaldo;
		delete arcos_respaldo;
        delete nodos_respaldo;

	}
	catch(int i) {
		// desechar los cambios hechos
		delete caras;
		delete arcos;
		delete nodos;
		caras = caras_respaldo;
		arcos = arcos_respaldo;
		nodos = nodos_respaldo;
		colapso_ok = false;
	}
    assert(this->checkMalla(false) >= 0);
	return colapso_ok? 0:-1;
}

