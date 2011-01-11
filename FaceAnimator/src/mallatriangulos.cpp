#include "mallatriangulos.h"
#include "cuadrilatero.h"
#include "fabricaalgoritmosmallatriangulos.h"

MallaTriangulos::MallaTriangulos(Nodos *nds, Arcos *arcs, Caras *crs):Malla(nds,arcs,crs) {
}

MallaTriangulos::MallaTriangulos(Punto p0, Punto p1, Punto p2):Malla(new Nodos(),new Arcos(),new Caras()) {
	//Nodos
	int ind_n0 = nodos->addNodo(new Nodo(p0));
	int ind_n1 = nodos->addNodo(new Nodo(p1));
	int ind_n2 = nodos->addNodo(new Nodo(p2));

	//Arcos
	int ind_a0 = arcos->addArco(new Arco(ind_n0,ind_n1,0,-1));
	int ind_a1 = arcos->addArco(new Arco(ind_n1,ind_n2,0,-1));
	int ind_a2 = arcos->addArco(new Arco(ind_n2,ind_n0,0,-1));

	//Cara
	int ind_cara = caras->addCara(new Triangulo(ind_n0,ind_n1,ind_n2,ind_a0,ind_a1,ind_a2));

	//Indices de los nodos a la cara y los arcos.
	nodos->getNodo(ind_n0)->addCara(ind_cara);
	nodos->getNodo(ind_n1)->addCara(ind_cara);
	nodos->getNodo(ind_n2)->addCara(ind_cara);

	nodos->getNodo(ind_n0)->addArco(ind_a0);
	nodos->getNodo(ind_n0)->addArco(ind_a2);
	nodos->getNodo(ind_n1)->addArco(ind_a0);
	nodos->getNodo(ind_n1)->addArco(ind_a1);
	nodos->getNodo(ind_n2)->addArco(ind_a1);
	nodos->getNodo(ind_n2)->addArco(ind_a2);

	show_nodos_destacados=true;
	concentracion_max = 1;
	concentracion_min = 0;
}

MallaTriangulos::MallaTriangulos(Punto p0, Punto p1, Punto pc0, Punto pc1):Malla(new Nodos(),new Arcos(),new Caras()) {
	//Nodos
	int ind_n0 = nodos->addNodo(new Nodo(p0));
	int ind_n1 = nodos->addNodo(new Nodo(p1));
	int ind_nc0 = nodos->addNodo(new Nodo(pc0));
	int ind_nc1 = nodos->addNodo(new Nodo(pc1));

	//Arcos
	int ind_a0 = arcos->addArco(new Arco(ind_n0,ind_n1,0,1));
	int ind_a1 = arcos->addArco(new Arco(ind_n0,ind_nc0,0,-1));
	int ind_a2 = arcos->addArco(new Arco(ind_n1,ind_nc0,0,-1));
	int ind_a3 = arcos->addArco(new Arco(ind_n0,ind_nc1,1,-1));
	int ind_a4 = arcos->addArco(new Arco(ind_n1,ind_nc1,1,-1));

	//Caras
	int ind_c0 = caras->addCara(new Triangulo(ind_n0,ind_n1,ind_nc0,ind_a0,ind_a2,ind_a1));
	int ind_c1 = caras->addCara(new Triangulo(ind_n1,ind_n0,ind_nc1,ind_a0,ind_a3,ind_a4));

	//Indices de los nodos a la cara y los arcos.
	nodos->getNodo(ind_n0)->addCara(ind_c0);
	nodos->getNodo(ind_n0)->addCara(ind_c1);
	nodos->getNodo(ind_n1)->addCara(ind_c0);
	nodos->getNodo(ind_n1)->addCara(ind_c1);
	nodos->getNodo(ind_nc0)->addCara(ind_c0);
	nodos->getNodo(ind_nc1)->addCara(ind_c1);

	nodos->getNodo(ind_n0)->addArco(ind_a0);
	nodos->getNodo(ind_n0)->addArco(ind_a1);
	nodos->getNodo(ind_n0)->addArco(ind_a3);
	nodos->getNodo(ind_n1)->addArco(ind_a0);
	nodos->getNodo(ind_n1)->addArco(ind_a2);
	nodos->getNodo(ind_n1)->addArco(ind_a4);
	nodos->getNodo(ind_nc0)->addArco(ind_a1);
	nodos->getNodo(ind_nc0)->addArco(ind_a2);
	nodos->getNodo(ind_nc1)->addArco(ind_a3);
	nodos->getNodo(ind_nc1)->addArco(ind_a4);

	show_nodos_destacados=true;
	concentracion_max = 1;
	concentracion_min = 0;
}

int MallaTriangulos::vertexDeletion(int indArcoAColapsar, int indVerticeABorrar){
	assert(arcos->getArco(indArcoAColapsar) != NULL);
	assert(nodos->getNodo(indVerticeABorrar) != NULL);

	//Se omite si el vertice esta en el borde.
	if (esNodoBorde(indVerticeABorrar))
		return -1;

	//Obtenemos el vertice a mantener.
	int indVerticeAMantener;
	if(arcos->getArco(indArcoAColapsar)->getNodo1()!=indVerticeABorrar)
		indVerticeAMantener=arcos->getArco(indArcoAColapsar)->getNodo1();
	else
		indVerticeAMantener=arcos->getArco(indArcoAColapsar)->getNodo2();

	//Obtenemos las caras que van a ser borradas.
	int indCaraABorrar1=arcos->getArco(indArcoAColapsar)->getCara1();
	int indCaraABorrar2=arcos->getArco(indArcoAColapsar)->getCara2();

	//Obtenemos las caras reemplazantes.
	int indCaraAReemplazar1=getCaraOpuestaNodo(indCaraABorrar1,indVerticeAMantener);
	int indCaraAReemplazar2=getCaraOpuestaNodo(indCaraABorrar2,indVerticeAMantener);

	//Obtenemos los arcos que van a ser borrados.
	int indArcoABorrar1=getArcoOpuestoNodo(indCaraABorrar1,indVerticeAMantener);
	int indArcoABorrar2=getArcoOpuestoNodo(indCaraABorrar2,indVerticeAMantener);

	//Obtenemos los arcos que se van a mantener.
	int indArcoAMantener1=getArcoOpuestoNodo(indCaraABorrar1,indVerticeABorrar);
	int indArcoAMantener2=getArcoOpuestoNodo(indCaraABorrar2,indVerticeABorrar);

	//Obtenemos las caras que deben ser modificadas.
	vector<int> indCarasAModificar;
	vector<int> indCarasVecinasAlNodo=nodos->getNodo(indVerticeABorrar)->getCaras();
	for (int i=0; i<(int)indCarasVecinasAlNodo.size(); i++)
		if (indCarasVecinasAlNodo[i]!=indCaraABorrar1 && indCarasVecinasAlNodo[i]!=indCaraABorrar2)
			indCarasAModificar.push_back(indCarasVecinasAlNodo[i]);

	//Chequeamos si se puede hacer el vertexDeletion.
	//Vemos si alguna cara se voltearia al hacerlo.
	for (int i=0; i<(int)indCarasAModificar.size(); i++){
		int indCara=indCarasAModificar[i];
		Nodo* verticeABorrar=getNodo(indVerticeABorrar);
		Nodo* verticeAMantener=getNodo(indVerticeAMantener);
		Vect viejaNormal=caras->getCara(indCara)->getNormal(this);
		Punto viejoPunto=verticeABorrar->getPunto();
		Punto nuevoPunto=verticeAMantener->getPunto();
		verticeABorrar->setPunto(nuevoPunto);
		Vect nuevaNormal=caras->getCara(indCara)->getNormal(this);
		verticeABorrar->setPunto(viejoPunto);
		if (viejaNormal.inOrigen() || nuevaNormal.inOrigen()) //Por problema de precision no se puede calcular la normal.
			return -1;
		double angulo=viejaNormal.getAngulo(nuevaNormal);
		if (angulo>PI/2)
			return -1;
		}

	//Chequeamos si se puede hacer el vertexDeletion.
	//Vemos si hay caras vecinas a las caras a borrar que son vecinas entre ellas.
	int ind_p1=indVerticeABorrar;
	int ind_p2=indVerticeAMantener;
	int ind_c1=indCaraABorrar1;
	int ind_c2=indCaraABorrar2;
	int ind_c1_vecina1 = getCaraOpuestaNodo(ind_c1, ind_p1);
	int ind_c1_vecina2 = getCaraOpuestaNodo(ind_c1, ind_p2);
	int ind_c2_vecina1 = getCaraOpuestaNodo(ind_c2, ind_p1);
	int ind_c2_vecina2 = getCaraOpuestaNodo(ind_c2, ind_p2);
	if(this->sonCarasVecinas(ind_c1_vecina1,ind_c1_vecina2) || this->sonCarasVecinas(ind_c2_vecina1,ind_c2_vecina2))
		return -1;

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
			else if (arcoAModificar->getNodo1()==indVerticeABorrar)
				arcoAModificar->setNodo1(indVerticeAMantener);
			else if (arcoAModificar->getNodo2()==indVerticeABorrar)
				arcoAModificar->setNodo2(indVerticeAMantener);

			}
		}

	//Modificamos los nodos mantenido.
	Nodo* verticeAMantener=nodos->getNodo(indVerticeAMantener);
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
			if (indArco!=indArcoAMantener1 && indArco!=indArcoAMantener2 &&
				(arco->getNodo1()==indVerticeAMantener || arco->getNodo2()==indVerticeAMantener))
					verticeAMantener->addArco(indArco);
			}
		}

	//Modificamos los arcos mantenidos.
	Arco* arcoAMantener1=arcos->getArco(indArcoAMantener1);
	if (arcoAMantener1->getCara1()==indCaraABorrar1)
		arcoAMantener1->setCara1(indCaraAReemplazar1);
	else if (arcoAMantener1->getCara2()==indCaraABorrar1)
		arcoAMantener1->setCara2(indCaraAReemplazar1);

	Arco* arcoAMantener2=arcos->getArco(indArcoAMantener2);
	if (arcoAMantener2->getCara1()==indCaraABorrar2)
		arcoAMantener2->setCara1(indCaraAReemplazar2);
	else if (arcoAMantener2->getCara2()==indCaraABorrar2)
		arcoAMantener2->setCara2(indCaraAReemplazar2);

	//Borramos
	nodos->eraseNodo(indVerticeABorrar);
	caras->eraseCara(indCaraABorrar1);
	caras->eraseCara(indCaraABorrar2);
	arcos->eraseArco(indArcoABorrar1);
	arcos->eraseArco(indArcoABorrar2);
	arcos->eraseArco(indArcoAColapsar);

	return 0;
	}

int MallaTriangulos::edgeCollapse2(int ind_arco, double dist) {
	int indNodo1=arcos->getArco(ind_arco)->getNodo1();
	int indNodo2=arcos->getArco(ind_arco)->getNodo2();

	//Si el nodo que vamos a hacerle el deletion esta en el borde, le hacemos el deletion al
	//nodo opuesto.
	if(esNodoBorde(indNodo1)){
		int aux=indNodo2;
		indNodo2=indNodo1;
		indNodo1=aux;
		}

	Nodo* nodo1=nodos->getNodo(indNodo1);
	Nodo* nodo2=nodos->getNodo(indNodo2);
	Punto A = nodo1->getPunto();
	Punto B = nodo2->getPunto();
	Vect vectA(A);
	Vect vectB(B);
	Vect AMenosB= vectA-vectB;
	Vect distAMenosB=AMenosB*dist;
	Vect P=vectB+distAMenosB;
	int resultado=vertexDeletion(ind_arco,indNodo1);
	if (resultado!=-1){
		nodo2->setPunto(P.getPunto());
		}

	return resultado;
}

MallaCuadrilateros *MallaTriangulos::cuadrangular(AlgCentroTriangulo *alg_centro_triangulo) {
	Nodos *nuevos_nodos = nodos->clone();
	Caras *nuevas_caras = new Caras();
	Arcos *nuevos_arcos = arcos->clone();

	vector<int> nuevos_nodos_arcos; // para cada arco, indica el índice del nodo
	map <int,vector<int> > nuevos_arcos_arcos; // para cada arco, indica los índices de los nuevos arcos que lo reemplazaran
	nuevos_nodos_arcos.assign(nuevos_arcos->getNumArcos(),-1); // inicializamos con -1

	for(int i = 0; i < caras->getNumCaras(); ++i) {
		Triangulo *cara = (Triangulo *)caras->getCara(i);
		if(cara == 0)
			continue;
		cara->ordenar(this);

		vector<int> ind_arcos = cara->getArcos();
		vector<int> ind_nodos = cara->getNodos();
		vector<int> ind_nuevos_nodos;
		vector<int> ind_nuevos_arcos;
		ind_nuevos_arcos.reserve(6);
		map<int,bool> arco_actualizado; // Indica si el arco fue reemplazado por otros dos en esta iteración

		//Recuperar los nodos intermedios y los nuevos arcos, crearlos si no existen
		for(int j = 0; j < (int)ind_arcos.size(); ++j) {
			if(nuevos_nodos_arcos[ind_arcos[j]] == -1) {
				Arco *arco = nuevos_arcos->getArco(ind_arcos[j]);
				Nodo *nodo = new Nodo(arco->getPuntoMedio(this));
				int ind_nuevo_nodo = nuevos_nodos->addNodo(nodo);
				nuevos_nodos_arcos[ind_arcos[j]] = ind_nuevo_nodo;
				int n1 = arco->getNodo1();
				int n2 = arco->getNodo2();
				double c1 = nuevos_nodos->getNodo(n1)->getConcentracion();
				double c2 = nuevos_nodos->getNodo(n2)->getConcentracion();
				nodo->setConcentracion((c1+c2)/2);
				nuevos_arcos->eraseArco(ind_arcos[j]);
				Arco *nuevo_arco_1 = new Arco(n1,ind_nuevo_nodo);
				Arco *nuevo_arco_2 = new Arco(ind_nuevo_nodo,n2);
				vector<int> ind_nuevos_dos_arcos;
				ind_nuevos_dos_arcos.push_back(nuevos_arcos->addArco(nuevo_arco_1));
				ind_nuevos_dos_arcos.push_back(nuevos_arcos->addArco(nuevo_arco_2));
				nuevos_arcos_arcos[ind_arcos[j]] = ind_nuevos_dos_arcos;
				arco_actualizado[ind_arcos[j]] = true;
			}
			else
                arco_actualizado[ind_arcos[j]] = false;
			ind_nuevos_nodos.push_back(nuevos_nodos_arcos[ind_arcos[j]]);
		}

		Punto p_centro = alg_centro_triangulo->getCentro(cara);
		double concentracion = alg_centro_triangulo->getConcentracionCentro(cara);
		Nodo *centro = new Nodo(p_centro);
		centro->setConcentracion(concentracion);
		int ind_centro = nuevos_nodos->addNodo(centro);

		vector<Arco*> arcos_centrales;
		vector<int> ind_arcos_centrales;
		for(int j = 0; j < (int)ind_nuevos_nodos.size(); ++j) {
			arcos_centrales.push_back(new Arco(ind_nuevos_nodos[j],ind_centro));
			ind_arcos_centrales.push_back(nuevos_arcos->addArco(arcos_centrales[j]));
		}

		// Obtener los nuevos arcos que reemplazan a los antiguos, ordenado
		// (debo hacer dos ciclos pues los nodos y arcos no necesariamente están en el mismo orden)
		for(int j = 0; j < (int)ind_arcos.size(); ++j) {
			vector<int> ind_nuevos_dos_arcos = nuevos_arcos_arcos[ind_arcos[j]];
			if(nuevos_arcos->getArco(ind_nuevos_dos_arcos[0])->perteneceNodo(ind_nodos[j])) {
				ind_nuevos_arcos[j] = ind_nuevos_dos_arcos[0];
				ind_nuevos_arcos[j+ind_nodos.size()] = ind_nuevos_dos_arcos[1];
			}
			else {
				ind_nuevos_arcos[j] = ind_nuevos_dos_arcos[1];
				ind_nuevos_arcos[j+ind_nodos.size()] = ind_nuevos_dos_arcos[0];
			}
		}

		vector<int> ind_nuevas_caras;
		vector<int> aux;
		aux.push_back(5);
		aux.push_back(3);
		aux.push_back(4);

		for(int j = 0; j < (int)ind_nodos.size(); ++j) {
			Cara *nueva_cara = new Cuadrilatero(
				ind_nuevos_nodos[int(fmod(j+2,ind_nodos.size()))],
				ind_nodos[j],
				ind_nuevos_nodos[j],
				ind_centro,
				ind_nuevos_arcos[aux[j]],
				ind_nuevos_arcos[j],
				ind_arcos_centrales[j],
				ind_arcos_centrales[int(fmod(j+2,ind_nodos.size()))]);
				ind_nuevas_caras.push_back(nuevas_caras->addCara(nueva_cara));
		}

		// Actualizar referencias
		for(int j = 0; j < (int)arcos_centrales.size(); ++j) {
			// Actualizar arcos
			arcos_centrales[j]->setCaras(ind_nuevas_caras[j],ind_nuevas_caras[int(fmod(j+1,arcos_centrales.size()))]);
			nuevos_arcos->getArco(ind_nuevos_arcos[j])->setCara(ind_nuevas_caras[j]);
			nuevos_arcos->getArco(ind_nuevos_arcos[aux[j]])->setCara(ind_nuevas_caras[j]);

			// Actualizar nodos
			//Nodos antiguos
			Nodo *nodo = nuevos_nodos->getNodo(ind_nodos[j]);
			nodo->changeCara(i,ind_nuevas_caras[j]);
			if(arco_actualizado[ind_arcos[j]])
                nodo->changeArco(ind_arcos[j],ind_nuevos_arcos[j]);
			if(arco_actualizado[ind_arcos[int(fmod(j+2,arcos_centrales.size()))]])
                nodo->changeArco(ind_arcos[int(fmod(j+2,arcos_centrales.size()))],ind_nuevos_arcos[aux[j]]);
			//Nodos nuevos intermedios
			nodo = nuevos_nodos->getNodo(ind_nuevos_nodos[j]);
			nodo->addCara(ind_nuevas_caras[j]);
			nodo->addCara(ind_nuevas_caras[int(fmod(j+1,arcos_centrales.size()))]);
			nodo->addArco(ind_arcos_centrales[j]);
			nodo->addArco(ind_nuevos_arcos[j]);
			nodo->addArco(ind_nuevos_arcos[j+arcos_centrales.size()]);
			//Nuevo nodo central
			centro->addCara(ind_nuevas_caras[j]);
			centro->addArco(ind_arcos_centrales[j]);
		}
	}

	MallaCuadrilateros *malla = new MallaCuadrilateros(nuevos_nodos, nuevos_arcos, nuevas_caras);
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

int MallaTriangulos::isDelaunay(int ind_arco){
	assert(ind_arco >= 0 && ind_arco <= getMaxIndiceArcos());
	assert(getArco(ind_arco) != NULL);

   if (this->esArcoFijo(ind_arco))
		return -1;	//no se puede hacer el flip

	// Obtenemos los indices que necesitamos.
	// Indices de las caras
	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	//Indices de los nodos
	int ind_p1 = arcos->getArco(ind_arco)->getNodo1();
	int ind_p2 = arcos->getArco(ind_arco)->getNodo2();
	int ind_p_c1 = this->getNodoOpuestoArco(ind_c1,ind_arco);
	int ind_p_c2 = this->getNodoOpuestoArco(ind_c2,ind_arco);

   	if (ind_p_c1 == ind_p_c2){
	   	cerr << "No se puede chequar Delaunay en arco " << ind_arco << " ya que sus caras vecinas estan superpuestas" << endl;
		return -1;
   		}

	//Obtenemos el angulo minimo de cada cara que separa el arco, y el minimo entre ellos.
	double angulo_min_c1 = caras->getCara(ind_c1)->getAnguloMin(this);
	double angulo_min_c2 = caras->getCara(ind_c2)->getAnguloMin(this);
	double angulo_min = angulo_min_c1;
	if(angulo_min_c2 < angulo_min) {
		angulo_min = angulo_min_c2;
	}

	Punto punto1, punto2, punto3;

	punto1=nodos->getNodo(ind_p1)->getPunto();
	punto2=nodos->getNodo(ind_p_c2)->getPunto();
	punto3=nodos->getNodo(ind_p_c1)->getPunto();

	Malla *m1= new MallaTriangulos(punto1, punto2, punto3);

	punto1=nodos->getNodo(ind_p2)->getPunto();
	punto2=nodos->getNodo(ind_p_c1)->getPunto();
	punto3=nodos->getNodo(ind_p_c2)->getPunto();

	Malla *m2= new MallaTriangulos(punto1, punto2, punto3);

    if(ind_arco == 10736) {
        cout << "************" << endl;
        cout << punto1 << endl;
        cout << punto2 << endl;
        cout << punto3 << endl;
    }
	double nuevo_angulo_min_c1 = m1->getCara(0)->getAnguloMin(m1);
	double nuevo_angulo_min_c2 = m2->getCara(0)->getAnguloMin(m2);

	delete m1;
	delete m2;

	double nuevo_angulo_min = nuevo_angulo_min_c1;
	if(nuevo_angulo_min_c2 < nuevo_angulo_min) {
		nuevo_angulo_min = nuevo_angulo_min_c2;
	}
	//si mejoramos el angulo minimo hacemos el flip ya que no es delaunay.
	if(nuevo_angulo_min > angulo_min)
		return 0;	//No cumple Delaunay
	else
		return 1;	//Si cumple Delaunay
	}

void MallaTriangulos::makeDelaunay(int ind_arco){
	assert(ind_arco >= 0 && ind_arco <= getMaxIndiceArcos());

	if (isDelaunay(ind_arco)!=0) //Si es que ya es Delaunay o si es que no se puede determinar.
		return;

	int nuevo_arco = edgeFlip(ind_arco);
	if (nuevo_arco==-1) return;

	int nueva_c1 = getArco(nuevo_arco)->getCara1();
	int nueva_c2 = getArco(nuevo_arco)->getCara2();

	//revisamos los arcos vecinos, por si ahora se puede realizar el flip.
	vector<int> arcos_nueva_c1 = getCara(nueva_c1)->getArcos();
	for(int i=0; i<(int)arcos_nueva_c1.size(); i++) {
		if(arcos_nueva_c1[i] != nuevo_arco)
			makeDelaunay(arcos_nueva_c1[i]);
		}
	vector<int> arcos_nueva_c2 = getCara(nueva_c2)->getArcos();
	for(int i=0; i<(int)arcos_nueva_c2.size(); i++) {
		if(arcos_nueva_c2[i] != nuevo_arco)
			makeDelaunay(arcos_nueva_c2[i]);
		}
	}

FabricaAlgoritmos *MallaTriangulos::getFabricaAlgoritmos() {
        if(fabrica_algoritmos == NULL)
            fabrica_algoritmos = new FabricaAlgoritmosMallaTriangulos();
        return fabrica_algoritmos;
    }

int MallaTriangulos::colapsarRegion(int indVerticeCentral) {
        Nodo *nodo_central = nodos->getNodo(indVerticeCentral);
        vector<int> arcos_nodo_central = nodo_central->getArcos();
        for(int i = 0; i < (int)arcos_nodo_central.size(); ++i) {
            Arco *arco_colapsar = arcos->getArco(arcos_nodo_central[i]);
            int nodo = arco_colapsar->getNodoDistinto(indVerticeCentral);
            this->vertexDeletion(arcos_nodo_central[i],nodo);
        }
        return 0;
}

int MallaTriangulos::edgeFlip(int ind_arco) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));
	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();
	if(ind_c1 < 0 || ind_c2 < 0) {
		cout << "Arco " << ind_arco << " es region borde. No se hace el flip." << endl;
		return -1; // este arco no define 2 caras --> region borde (No se puede realizar el flip).
	}
	//obtenemos los indices de los 4 puntos
	int ind_p1 = arcos->getArco(ind_arco)->getNodo1();
	int ind_p2 = arcos->getArco(ind_arco)->getNodo2();
	int ind_p_c1 = this->getNodoOpuestoArco(ind_c1,ind_arco);
	int ind_p_c2 = this->getNodoOpuestoArco(ind_c2,ind_arco);

	// 	Se comenta estas lineas para permitir que los algoritmos de deformacion puedan
	//	funcionar. Estas verificaciones se caen si se llaman durante la deformacion ya
	//	que durante la deformacion la malla esta en un estado inconsistente.
    //
	//	Update: Al final mejor dejarlas descomentadas ya que sino no funciona edgeCollapse.

	Cara *c1 = caras->getCara(ind_c1);
	Cara *c2 = caras->getCara(ind_c2);

	double angulo1 = c1->getAnguloVertice(ind_p1,this) + c2->getAnguloVertice(ind_p1,this);
	double angulo2 = c1->getAnguloVertice(ind_p2,this) + c2->getAnguloVertice(ind_p2,this);

	//si se forma un angulo mayor o igual a 180º no se puede realizar el flip
	if(angulo1 >= PI || angulo2 >= PI) {
		cout << "Arco " << ind_arco << " forma angulo mayor a 180º. No se hace el flip." << endl;
		return -1;
	}

	Vect normal_c1 = caras->getCara(ind_c1)->getNormal(this);
	Vect normal_puntos = this->getNormalNodos(ind_p1,ind_p2,ind_p_c1);
	double prod_punto = normal_puntos.prodPunto(normal_c1);
	if(prod_punto < 0) {
		// Cambiamos los indices de p1 y p2
		int aux = ind_p1;
		ind_p1 = ind_p2;
		ind_p2 = aux;
	}

	//obtenemos los indices de los arcos
	int ind_a1_c1 = this->getArcoOpuestoNodo(ind_c1,ind_p1);
	int ind_a2_c1 = this->getArcoOpuestoNodo(ind_c1,ind_p2);
	int ind_a1_c2 = this->getArcoOpuestoNodo(ind_c2,ind_p1);
	int ind_a2_c2 = this->getArcoOpuestoNodo(ind_c2,ind_p2);

	//obtenemos los indices de las caras vecinas
	int ind_c1_vecina1 = getCaraOpuestaNodo(ind_c1, ind_p1);
	int ind_c1_vecina2 = getCaraOpuestaNodo(ind_c1, ind_p2);
	int ind_c2_vecina1 = getCaraOpuestaNodo(ind_c2, ind_p1);
	int ind_c2_vecina2 = getCaraOpuestaNodo(ind_c2, ind_p2);

	//borramos el arco en ind_arco y agregamos el nuevo arco. Esto se hace en un paso con la funcion addArcoIn(Arco *a, int indice), es decir, agrega el arco "a" en la posicion de indice. Con esto el nuevo arco quedara en la misma posicion en en que estaba el arco borrado.
	int ind_nuevo_arco = arcos->addArcoIn(new Arco(ind_p_c1,ind_p_c2),ind_arco);

	vector<int> indice_puntos;
	vector<int> indice_arcos;
	vector<int> indice_caras;

	indice_puntos.push_back(ind_p_c2);
	indice_puntos.push_back(ind_p_c1);
	indice_puntos.push_back(ind_p1);

	indice_arcos.push_back(ind_nuevo_arco);
	indice_arcos.push_back(ind_a2_c1);
	indice_arcos.push_back(ind_a2_c2);

	//borramos la cara en ind_c1 y agregamos la nueva cara
	int ind_nueva_cara1 = caras->addCaraIn(new Triangulo(indice_puntos,indice_arcos),ind_c1);
	arcos->setCaraArco(ind_nuevo_arco,ind_nueva_cara1);

	indice_puntos[0] = ind_p_c1;
	indice_puntos[1] = ind_p_c2;
	indice_puntos[2] = ind_p2;
	indice_arcos[0] = ind_nuevo_arco;
	indice_arcos[1] = ind_a1_c2;
	indice_arcos[2] = ind_a1_c1;

	//borramos la cara en ind_c1 y agregamos la nueva cara
	int ind_nueva_cara2 = caras->addCaraIn(new Triangulo(indice_puntos,indice_arcos),ind_c2);
	arcos->setCaraArco(ind_nuevo_arco,ind_nueva_cara2);

	//actualizamos los indices del nodo p1 hacia sus arcos y caras
	nodos->getNodo(ind_p1)->eraseCara(ind_c1);
	nodos->getNodo(ind_p1)->eraseCara(ind_c2);
	nodos->getNodo(ind_p1)->addCara(ind_nueva_cara1);
	nodos->getNodo(ind_p1)->eraseArco(ind_arco);

	//actualizamos los indices del nodo p2 hacia sus arcos y caras
	nodos->getNodo(ind_p2)->eraseCara(ind_c1);
	nodos->getNodo(ind_p2)->eraseCara(ind_c2);
	nodos->getNodo(ind_p2)->addCara(ind_nueva_cara2);
	nodos->getNodo(ind_p2)->eraseArco(ind_arco);

	//actualizamos los indices del nodo p_cara1 hacia sus arcos y caras
	nodos->getNodo(ind_p_c1)->eraseCara(ind_c1);
	nodos->getNodo(ind_p_c1)->addCara(ind_nueva_cara1);
	nodos->getNodo(ind_p_c1)->addCara(ind_nueva_cara2);
	nodos->getNodo(ind_p_c1)->addArco(ind_nuevo_arco);

	//actualizamos los indices del nodo p_cara2 hacia sus arcos y caras
	nodos->getNodo(ind_p_c2)->eraseCara(ind_c2);
	nodos->getNodo(ind_p_c2)->addCara(ind_nueva_cara1);
	nodos->getNodo(ind_p_c2)->addCara(ind_nueva_cara2);
	nodos->getNodo(ind_p_c2)->addArco(ind_nuevo_arco);

	//actualizamos los indices de los arcos que apuntan hacia las nuevas caras
	arcos->getArco(ind_a1_c1)->setCaras(ind_nueva_cara2,ind_c1_vecina1);
	arcos->getArco(ind_a2_c1)->setCaras(ind_nueva_cara1,ind_c1_vecina2);
	arcos->getArco(ind_a1_c2)->setCaras(ind_nueva_cara2,ind_c2_vecina1);
	arcos->getArco(ind_a2_c2)->setCaras(ind_nueva_cara1,ind_c2_vecina2);

	return ind_nuevo_arco;
}

vector<int> MallaTriangulos::edgeSplit(int ind_arco, double dist, int retorna) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));
	assert(dist>0 && dist<1);

	vector<int> nuevos_arcos;
	vector<int> nuevas_caras;

	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	//obtenemos los indices de los 4 puntos
	int ind_p1 = arcos->getArco(ind_arco)->getNodo1();
	int ind_p2 = arcos->getArco(ind_arco)->getNodo2();
	int ind_p_c1 = this->getNodoOpuestoArco(ind_c1,ind_arco);
	int ind_p_c2 = this->getNodoOpuestoArco(ind_c2,ind_arco);

	Vect normal_c1 = caras->getCara(ind_c1)->getNormal(this);
	Vect normal_puntos = this->getNormalNodos(ind_p1,ind_p2,ind_p_c1);
	double prod_punto = normal_puntos.prodPunto(normal_c1);
	if(prod_punto < 0) {
		// Cambiamos los indices de p1 y p2
		int aux = ind_p1;
		ind_p1 = ind_p2;
		ind_p2 = aux;
	}

	//obtenemos los indices de los arcos
	int ind_a1_c1 = this->getArcoOpuestoNodo(ind_c1,ind_p1);
	int ind_a2_c1 = this->getArcoOpuestoNodo(ind_c1,ind_p2);
	int ind_a1_c2 = this->getArcoOpuestoNodo(ind_c2,ind_p1);
	int ind_a2_c2 = this->getArcoOpuestoNodo(ind_c2,ind_p2);

	//obtenemos los indices de las caras vecinas
	int ind_c1_vecina1 = getCaraOpuestaNodo(ind_c1, ind_p1);
	int ind_c1_vecina2 = getCaraOpuestaNodo(ind_c1, ind_p2);
	int ind_c2_vecina1 = getCaraOpuestaNodo(ind_c2, ind_p1);
	int ind_c2_vecina2 = getCaraOpuestaNodo(ind_c2, ind_p2);

	//borramos las 2 caras
	if(ind_c1 != -1) {
		caras->eraseCara(ind_c1);
	}
	if(ind_c2 != -1) {
		caras->eraseCara(ind_c2);
	}

	//borramos el arco
	arcos->eraseArco(ind_arco);

	//agregamos el nuevo nodo y le seteamos su normal y concentracion.
	Punto p1 = nodos->getNodo(ind_p1)->getPunto();
	Punto p2 = nodos->getNodo(ind_p2)->getPunto();
	Vect vp1(p1);
	Vect vp2(p2);
	Vect v_p1_p2 = vp2 - vp1;
	v_p1_p2 = v_p1_p2 * dist;
	Vect vp = vp1 + v_p1_p2;
	Punto p=vp.getPunto();
	Nodo *nuevo_nodo = new Nodo(p);
	int ind_nuevo_nodo = nodos->addNodo(nuevo_nodo);
	//le seteamos su normal como el promedio de las normales de sus nodos vecinos
	//le seteamos la concentracion como el promedio de la concentracion de nodos vecinos.
	Vect normal_p1 = nodos->getNodo(ind_p1)->getNormal();
	Vect normal_p2 = nodos->getNodo(ind_p2)->getNormal();
	Vect normal_prom = normal_p1 + normal_p2;
	double concentracion_p1=nodos->getNodo(ind_p1)->getConcentracion();
	double concentracion_p2=nodos->getNodo(ind_p2)->getConcentracion();
	double sumaConcentracion=concentracion_p1+concentracion_p2;
	double divisorConcentracion=2;

	if(ind_p_c1 != -1) {
		Vect normal_p_c1 = nodos->getNodo(ind_p_c1)->getNormal();
		normal_prom = normal_prom + normal_p_c1;
		sumaConcentracion=sumaConcentracion+nodos->getNodo(ind_p_c1)->getConcentracion();
		divisorConcentracion++;
	}
	if(ind_p_c2 != -1) {
		Vect normal_p_c2 = nodos->getNodo(ind_p_c2)->getNormal();
		normal_prom = normal_prom + normal_p_c2;
		sumaConcentracion=sumaConcentracion+nodos->getNodo(ind_p_c2)->getConcentracion();
		divisorConcentracion++;
	}
	if(normal_prom.largo() != 0) {
		normal_prom = normal_prom * (1/normal_prom.largo()); // se normaliza
	}
	nodos->getNodo(ind_nuevo_nodo)->setNormal(normal_prom);
	nodos->getNodo(ind_nuevo_nodo)->setConcentracion(sumaConcentracion/divisorConcentracion);

	//agregamos los 4 nuevos arcos
	int ind_nuevo_arco_p1 = arcos->addArco(new Arco(ind_p1,ind_nuevo_nodo));
	nuevos_arcos.push_back(ind_nuevo_arco_p1);
	int ind_nuevo_arco_p2 = arcos->addArco(new Arco(ind_p2,ind_nuevo_nodo));
	nuevos_arcos.push_back(ind_nuevo_arco_p2);
	//Le seteamos estos arcos al nodo insertado
	nodos->addArcoNodo(ind_nuevo_nodo,ind_nuevo_arco_p1);
	nodos->addArcoNodo(ind_nuevo_nodo,ind_nuevo_arco_p2);
	int ind_nuevo_arco_p_c1 = -1;
	int ind_nuevo_arco_p_c2 = -1;
	if(ind_p_c1 != -1) {
		ind_nuevo_arco_p_c1 = arcos->addArco(new Arco(ind_p_c1,ind_nuevo_nodo));
		nuevos_arcos.push_back(ind_nuevo_arco_p_c1);
		//Le seteamos este arco al nodo insertado
		nodos->addArcoNodo(ind_nuevo_nodo,ind_nuevo_arco_p_c1);
	}
	if(ind_p_c2 != -1) {
		ind_nuevo_arco_p_c2 = arcos->addArco(new Arco(ind_p_c2,ind_nuevo_nodo));
		nuevos_arcos.push_back(ind_nuevo_arco_p_c2);
		//Le seteamos este arco al nodo insertado
		nodos->addArcoNodo(ind_nuevo_nodo,ind_nuevo_arco_p_c2);
	}

	vector<int> indice_puntos;
	vector<int> indice_arcos;
	vector<int> indice_caras;

	//agregamos las nuevas caras
	int ind_nueva_cara1 = -1;
	int ind_nueva_cara2 = -1;
	int ind_nueva_cara3 = -1;
	int ind_nueva_cara4 = -1;
	if(ind_p_c1 != -1) {
		indice_puntos.push_back(ind_p1);
		indice_puntos.push_back(ind_nuevo_nodo);
		indice_puntos.push_back(ind_p_c1);

		indice_arcos.push_back(ind_nuevo_arco_p1);
		indice_arcos.push_back(ind_nuevo_arco_p_c1);
		indice_arcos.push_back(ind_a2_c1);

		ind_nueva_cara1 = caras->addCara(new Triangulo(indice_puntos,indice_arcos));
		nuevas_caras.push_back(ind_nueva_cara1);
		arcos->setCaraArco(ind_nuevo_arco_p_c1,ind_nueva_cara1);
		arcos->setCaraArco(ind_nuevo_arco_p1,ind_nueva_cara1);
		//Le seteamos esta cara al nodo insertado
		nodos->addCaraNodo(ind_nuevo_nodo,ind_nueva_cara1);

		indice_puntos[0] = ind_p2;
		indice_puntos[1] = ind_p_c1;
		indice_puntos[2] = ind_nuevo_nodo;
		indice_arcos[0] = ind_a1_c1;
		indice_arcos[1] = ind_nuevo_arco_p_c1;
		indice_arcos[2] = ind_nuevo_arco_p2;

		ind_nueva_cara2 = caras->addCara(new Triangulo(indice_puntos,indice_arcos));
		nuevas_caras.push_back(ind_nueva_cara2);
		arcos->setCaraArco(ind_nuevo_arco_p_c1,ind_nueva_cara2);
		arcos->setCaraArco(ind_nuevo_arco_p2,ind_nueva_cara2);
		//Le seteamos esta cara al nodo insertado
		nodos->addCaraNodo(ind_nuevo_nodo,ind_nueva_cara2);

		indice_puntos.clear();
		indice_arcos.clear();

		//actualizamos los indices del nodo p_cara1 hacia sus arcos y caras
		nodos->getNodo(ind_p_c1)->eraseCara(ind_c1);
		nodos->getNodo(ind_p_c1)->addCara(ind_nueva_cara1);
		nodos->getNodo(ind_p_c1)->addCara(ind_nueva_cara2);
		nodos->getNodo(ind_p_c1)->addArco(ind_nuevo_arco_p_c1);

		//actualizamos los indices de los arcos que apuntan hacia las nuevas caras
		arcos->getArco(ind_a1_c1)->setCaras(ind_nueva_cara2,ind_c1_vecina1);
		arcos->getArco(ind_a2_c1)->setCaras(ind_nueva_cara1,ind_c1_vecina2);
	}
	if(ind_p_c2 != -1) {

		indice_puntos.push_back(ind_p2);
		indice_puntos.push_back(ind_nuevo_nodo);
		indice_puntos.push_back(ind_p_c2);

		indice_arcos.push_back(ind_nuevo_arco_p2);
		indice_arcos.push_back(ind_nuevo_arco_p_c2);
		indice_arcos.push_back(ind_a1_c2);

		ind_nueva_cara3 = caras->addCara(new Triangulo(indice_puntos,indice_arcos));
		nuevas_caras.push_back(ind_nueva_cara3);
		arcos->setCaraArco(ind_nuevo_arco_p_c2,ind_nueva_cara3);
		arcos->setCaraArco(ind_nuevo_arco_p2,ind_nueva_cara3);
		//Le seteamos esta cara al nodo insertado
		nodos->addCaraNodo(ind_nuevo_nodo,ind_nueva_cara3);

		indice_puntos[0] = ind_p1;
		indice_puntos[1] = ind_p_c2;
		indice_puntos[2] = ind_nuevo_nodo;
		indice_arcos[0] = ind_a2_c2;
		indice_arcos[1] = ind_nuevo_arco_p_c2;
		indice_arcos[2] = ind_nuevo_arco_p1;

		ind_nueva_cara4 = caras->addCara(new Triangulo(indice_puntos,indice_arcos));
		nuevas_caras.push_back(ind_nueva_cara4);
		arcos->setCaraArco(ind_nuevo_arco_p_c2,ind_nueva_cara4);
		arcos->setCaraArco(ind_nuevo_arco_p1,ind_nueva_cara4);
		//Le seteamos esta cara al nodo insertado
		nodos->addCaraNodo(ind_nuevo_nodo,ind_nueva_cara4);

		indice_puntos.clear();
		indice_arcos.clear();

		//actualizamos los indices del nodo p_cara2 hacia sus arcos y caras
		nodos->getNodo(ind_p_c2)->eraseCara(ind_c2);
		nodos->getNodo(ind_p_c2)->addCara(ind_nueva_cara3);
		nodos->getNodo(ind_p_c2)->addCara(ind_nueva_cara4);
		nodos->getNodo(ind_p_c2)->addArco(ind_nuevo_arco_p_c2);

		//actualizamos los indices de los arcos que apuntan hacia las nuevas caras
		arcos->getArco(ind_a1_c2)->setCaras(ind_nueva_cara3,ind_c2_vecina1);
		arcos->getArco(ind_a2_c2)->setCaras(ind_nueva_cara4,ind_c2_vecina2);
	}

	//actualizamos los indices del nodo p1 hacia sus arcos y caras
	nodos->getNodo(ind_p1)->eraseCara(ind_c1);
	nodos->getNodo(ind_p1)->eraseCara(ind_c2);
	nodos->getNodo(ind_p1)->addCara(ind_nueva_cara1);
	nodos->getNodo(ind_p1)->addCara(ind_nueva_cara4);
	nodos->getNodo(ind_p1)->eraseArco(ind_arco);
	nodos->getNodo(ind_p1)->addArco(ind_nuevo_arco_p1);

	//actualizamos los indices del nodo p2 hacia sus arcos y caras
	nodos->getNodo(ind_p2)->eraseCara(ind_c1);
	nodos->getNodo(ind_p2)->eraseCara(ind_c2);
	nodos->getNodo(ind_p2)->addCara(ind_nueva_cara2);
	nodos->getNodo(ind_p2)->addCara(ind_nueva_cara3);
	nodos->getNodo(ind_p2)->eraseArco(ind_arco);
	nodos->getNodo(ind_p2)->addArco(ind_nuevo_arco_p2);

	if(retorna == 1) {
		return nuevas_caras;
	}
	else {
		return nuevos_arcos;
	}
}

int MallaTriangulos::edgeCollapse(int ind_arco, double dist) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));
	assert(dist>=0 && dist<=1);
	assert(arcos->getArco(ind_arco) != NULL);


	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	//obtenemos los indices de los 4 puntos
	int ind_p1 = arcos->getArco(ind_arco)->getNodo1();
	int ind_p2 = arcos->getArco(ind_arco)->getNodo2();
	int ind_p_c1 = this->getNodoOpuestoArco(ind_c1,ind_arco);
	int ind_p_c2 = this->getNodoOpuestoArco(ind_c2,ind_arco);

	//obtenemos los indices de los arcos
	int ind_a1_c1 = this->getArcoOpuestoNodo(ind_c1,ind_p1);
	int ind_a2_c1 = this->getArcoOpuestoNodo(ind_c1,ind_p2);
	int ind_a1_c2 = this->getArcoOpuestoNodo(ind_c2,ind_p1);
	int ind_a2_c2 = this->getArcoOpuestoNodo(ind_c2,ind_p2);

	//obtenemos los indices de las caras vecinas, pueden ser -1 si no hay cara vecina
	int ind_c1_vecina1 = getCaraOpuestaNodo(ind_c1, ind_p1);
	int ind_c1_vecina2 = getCaraOpuestaNodo(ind_c1, ind_p2);
	int ind_c2_vecina1 = getCaraOpuestaNodo(ind_c2, ind_p1);
	int ind_c2_vecina2 = getCaraOpuestaNodo(ind_c2, ind_p2);

	if(ind_c1 != -1 && ind_c1_vecina1 == -1 && ind_c1_vecina2 == -1) {
		//No se puede reducir el arco
		return -1;
	}
	if(ind_c2 != -1 && ind_c2_vecina1 == -1 && ind_c2_vecina2 == -1) {
		//No se puede reducir el arco
		return -1;
	}

	if(this->sonCarasVecinas(ind_c1_vecina1,ind_c1_vecina2) || this->sonCarasVecinas(ind_c2_vecina1,ind_c2_vecina2)) {
		int nuevo_arco = this->edgeFlip(ind_arco);
		cerr << "Hago edge-flip sobre arco " << ind_arco << " con resultado nuevo_arco = " << nuevo_arco << endl;
		if(nuevo_arco != -1) {
			this->edgeCollapse(nuevo_arco,dist);
		}
		return -1;
	}

	vector<int> ind_arcos_p1 = nodos->getNodo(ind_p1)->getArcos();
	vector<int> ind_arcos_p2 = nodos->getNodo(ind_p2)->getArcos();
	vector<int> ind_caras_p1 = nodos->getNodo(ind_p1)->getCaras();
	vector<int> ind_caras_p2 = nodos->getNodo(ind_p2)->getCaras();

	//borramos las 2 caras
	if(ind_c1 != -1) {
		caras->eraseCara(ind_c1);
	}
	if(ind_c2 != -1) {
		caras->eraseCara(ind_c2);
	}

	//borramos el arco dado como parametro
	arcos->eraseArco(ind_arco);
	//borramos los 4 otros arcos que formaban las caras
	if(ind_a1_c1 != -1) {
		arcos->eraseArco(ind_a1_c1);
	}
	if(ind_a1_c2 != -1) {
		arcos->eraseArco(ind_a1_c2);
	}
	if(ind_a2_c1 != -1) {
		arcos->eraseArco(ind_a2_c1);
	}
	if(ind_a2_c2 != -1) {
		arcos->eraseArco(ind_a2_c2);
	}

	// obtenemos la informacion que necesitamos de los nodos p1 y p2 antes de borrarlos
	Punto p1 = nodos->getNodo(ind_p1)->getPunto();
	Punto p2 = nodos->getNodo(ind_p2)->getPunto();
	Vect vp1(p1);
	Vect vp2(p2);

	Vect normal_p1 = nodos->getNodo(ind_p1)->getNormal();
	Vect normal_p2 = nodos->getNodo(ind_p2)->getNormal();

	//agregamos el nuevo nodo y le seteamos su normal
	Vect v_p1_p2 = vp2 - vp1;
	v_p1_p2 = v_p1_p2 * dist;
	Vect vp = vp1 + v_p1_p2;

	//le seteamos su normal como el promedio de las normales de sus nodos vecinos
	Vect normal_prom = normal_p1 + normal_p2;
	if(normal_prom.largo() != 0) {
		normal_prom = normal_prom * (1/normal_prom.largo()); // se normaliza
	}

	//borramos los 2 nodos
	nodos->eraseNodo(ind_p1);
	nodos->eraseNodo(ind_p2);

	//creamos el nuevo nodo
	Punto p=vp.getPunto();
	Nodo *nuevo_nodo = new Nodo(p);
	int ind_nuevo_nodo = nodos->addNodo(nuevo_nodo);
	nodos->getNodo(ind_nuevo_nodo)->setNormal(normal_prom);

	//agregamos los nuevos arcos, seteandole sus caras. Ademas al nuevo nodo le seteamos estos arcos y actualizamos p_c1 y p_c2
	int ind_nuevo_arco_p_c1 = -1;
	int ind_nuevo_arco_p_c2 = -1;
	if(ind_p_c1 != -1) {
		//agregamos el nuevo arco
		assert(nodos->getNodo(ind_p_c1) != 0 && nodos->getNodo(ind_nuevo_nodo) != 0);
		ind_nuevo_arco_p_c1 = arcos->addArco(new Arco(ind_p_c1,ind_nuevo_nodo));
		//le seteamos sus caras
		cout << "Nuevo arco = " << ind_nuevo_arco_p_c1 << endl;
		arcos->getArco(ind_nuevo_arco_p_c1)->setCaras(ind_c1_vecina1,ind_c1_vecina2);
		//seteamos este arco al nuevo nodo
		nodos->getNodo(ind_nuevo_nodo)->addArco(ind_nuevo_arco_p_c1);
		//actualizamos el nodo p_c1
		nodos->getNodo(ind_p_c1)->eraseCara(ind_c1);
		nodos->getNodo(ind_p_c1)->eraseArco(ind_a1_c1);
		nodos->getNodo(ind_p_c1)->eraseArco(ind_a2_c1);
		nodos->getNodo(ind_p_c1)->addArco(ind_nuevo_arco_p_c1);
	}
	if(ind_p_c2 != -1) {
		//agregamos el nuevo arco
		assert(nodos->getNodo(ind_p_c2) != 0 && nodos->getNodo(ind_nuevo_nodo) != 0);
		ind_nuevo_arco_p_c2 = arcos->addArco(new Arco(ind_p_c2,ind_nuevo_nodo));
		//le seteamos sus caras
		cout << "Nuevo arco = " << ind_nuevo_arco_p_c2 << endl;
		assert(ind_c2_vecina1 != ind_c2_vecina2);
		arcos->getArco(ind_nuevo_arco_p_c2)->setCaras(ind_c2_vecina1,ind_c2_vecina2);
		//seteamos este arco al nuevo nodo
		nodos->getNodo(ind_nuevo_nodo)->addArco(ind_nuevo_arco_p_c2);
		//actualizamos el nodo p_c2
		nodos->getNodo(ind_p_c2)->eraseCara(ind_c2);
		nodos->getNodo(ind_p_c2)->eraseArco(ind_a1_c2);
		nodos->getNodo(ind_p_c2)->eraseArco(ind_a2_c2);
		nodos->getNodo(ind_p_c2)->addArco(ind_nuevo_arco_p_c2);
	}

	//actualizamos los arcos de las caras vecinas.
	if(ind_c1_vecina2 != -1) {
		caras->getCara(ind_c1_vecina2)->eraseArco(ind_a2_c1);
		caras->getCara(ind_c1_vecina2)->addArco(ind_nuevo_arco_p_c1);
	}
	if(ind_c1_vecina1 != -1) {
		caras->getCara(ind_c1_vecina1)->eraseArco(ind_a1_c1);
		caras->getCara(ind_c1_vecina1)->addArco(ind_nuevo_arco_p_c1);
	}
	if(ind_c2_vecina2 != -1) {
		caras->getCara(ind_c2_vecina2)->eraseArco(ind_a2_c2);
		caras->getCara(ind_c2_vecina2)->addArco(ind_nuevo_arco_p_c2);
	}
	if(ind_c2_vecina1 != -1) {
		caras->getCara(ind_c2_vecina1)->eraseArco(ind_a1_c2);
		caras->getCara(ind_c2_vecina1)->addArco(ind_nuevo_arco_p_c2);
	}

	//Le seteamos los arcos y caras al nodo insertado (las que tenian p1 y p2)
	//seteo de arcos que tenia p1 menos los que ya no estan:
	for(int i=0; i<(int)ind_arcos_p1.size(); i++) {
		if(ind_arcos_p1[i] != ind_arco && ind_arcos_p1[i] != ind_a2_c1 && ind_arcos_p1[i] != ind_a2_c2) {
			nodos->getNodo(ind_nuevo_nodo)->addArco(ind_arcos_p1[i]);
		}
	}
	//seteo de arcos que tenia p2 menos los que ya no estan:
	for(int i=0; i<(int)ind_arcos_p2.size(); i++) {
		if(ind_arcos_p2[i] != ind_arco && ind_arcos_p2[i] != ind_a1_c1 && ind_arcos_p2[i] != ind_a1_c2) {
			nodos->getNodo(ind_nuevo_nodo)->addArco(ind_arcos_p2[i]);
		}
	}

	//seteo de caras que tenia p1 menos las que ya no estan:
	for(int i=0; i<(int)ind_caras_p1.size(); i++) {
		if(ind_caras_p1[i] != ind_c1 && ind_caras_p1[i] != ind_c2) {
			nodos->getNodo(ind_nuevo_nodo)->addCara(ind_caras_p1[i]);
		}
	}
	//seteo de caras que tenia p2 menos las que ya no estan:
	for(int i=0; i<(int)ind_caras_p2.size(); i++) {
		if(ind_caras_p2[i] != ind_c1 && ind_caras_p2[i] != ind_c2) {
			nodos->getNodo(ind_nuevo_nodo)->addCara(ind_caras_p2[i]);
		}
	}

	//actualizamos los nodos de los arcos que tenian como nodo los que ya no estan
	vector<int> arcos_nuevo_nodo = nodos->getNodo(ind_nuevo_nodo)->getArcos();
	for(int i=0; i<(int)arcos_nuevo_nodo.size(); i++) {
		if(arcos_nuevo_nodo[i] != ind_nuevo_arco_p_c1 && arcos_nuevo_nodo[i] != ind_nuevo_arco_p_c2) {
			if(arcos->getArco(arcos_nuevo_nodo[i])->getNodo1() == ind_p1 || arcos->getArco(arcos_nuevo_nodo[i])->getNodo1() == ind_p2) {
				arcos->getArco(arcos_nuevo_nodo[i])->setNodo1(ind_nuevo_nodo);
			}
			else {
				arcos->getArco(arcos_nuevo_nodo[i])->setNodo2(ind_nuevo_nodo);
			}
		}
	}

	//actualizamos los nodos de las caras que tenian como nodo los que ya no estan
	vector<int> caras_nuevo_nodo = nodos->getNodo(ind_nuevo_nodo)->getCaras();
	for(int i=0; i<(int)caras_nuevo_nodo.size(); i++) {
		if(caras_nuevo_nodo[i] != ind_c1 && caras_nuevo_nodo[i] != ind_c2) {
			caras->getCara(caras_nuevo_nodo[i])->changeNodo(ind_p1,ind_nuevo_nodo);
			caras->getCara(caras_nuevo_nodo[i])->changeNodo(ind_p2,ind_nuevo_nodo);
		}
	}
	return 0;
}

void MallaTriangulos::manejaInconsitenciaArco(int ind_arco) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	cout << "ind_c1 = " << ind_c1 << endl;
	cout << "ind_c2 = " << ind_c2 << endl;

	if(ind_c1 < 0 || ind_c2 < 0) {
		return;
	}

	//obtenemos los indices de los 4 puntos
	int ind_p1 = arcos->getArco(ind_arco)->getNodo1();
	int ind_p2 = arcos->getArco(ind_arco)->getNodo2();
	int ind_p_c1 = this->getNodoOpuestoArco(ind_c1,ind_arco);
	int ind_p_c2 = this->getNodoOpuestoArco(ind_c2,ind_arco);

	//obtenemos los 4 puntos
	Punto p_c1 = nodos->getNodo(ind_p_c1)->getPunto();
	Punto p_c2 = nodos->getNodo(ind_p_c2)->getPunto();
	Punto p1 = nodos->getNodo(ind_p1)->getPunto();
	Punto p2 = nodos->getNodo(ind_p2)->getPunto();

	//obtenemos los indices de los arcos
	int ind_a1_c1 = this->getArcoOpuestoNodo(ind_c1,ind_p1);
	int ind_a2_c1 = this->getArcoOpuestoNodo(ind_c1,ind_p2);
	int ind_a1_c2 = this->getArcoOpuestoNodo(ind_c2,ind_p1);
	int ind_a2_c2 = this->getArcoOpuestoNodo(ind_c2,ind_p2);

	cout << "ind_a1_c1 = " << ind_a1_c1 << endl;
	cout << "ind_a2_c1 = " << ind_a2_c1 << endl;
	cout << "ind_a1_c2 = " << ind_a1_c2 << endl;
	cout << "ind_a2_c2 = " << ind_a2_c2 << endl;

	int tip_arco = this->tipArco(ind_arco);
	cout << "tip_arco = " << tip_arco << endl;

	if(tip_arco == TIP_INSIDE) {
		cout << "TIP_INSIDE en arco(" << ind_arco << ")" << endl;
		cout << "Realizado flip en arco(" << ind_arco << ")" << endl;
		edgeFlip(ind_arco);
	}
	else if(tip_arco == TIP_ON_EDGE) {
		cout << "TIP_ON_EDGE en arco(" << ind_arco << ")" << endl;
	}
	else if(tip_arco == TIP_OUTSIDE_B) {
		//no hacemos nada porque no se producen inconsistencias.
		cout << "TIP_OUTSIDE_B en arco(" << ind_arco << ")" << endl;
	}
	else if(tip_arco == TIP_OUTSIDE_A) {
		cout << "TIP_OUTSIDE_A en arco(" << ind_arco << ")" << endl;
		//tengo que ver que arcos se cruzan y en que punto
		if(seCruzan(p1,p_c2,p2,p_c1) == 1) {
			cout << "Se cruzan en: p1,p_c2,p2,p_c1" << endl;
			double alfa = valorInterseccion(p1,p_c2,p2,p_c1);
			double beta = valorInterseccion(p2,p_c1,p1,p_c2);
			cout << "alfa = " << alfa << endl;
			cout << "beta = " << beta << endl;

			if(arcos->getArco(ind_a1_c1) == 0) {
				cout << "ind_a1_c1 = " << ind_a1_c1 << " es nulo"<< endl;
			}
			if(arcos->getArco(ind_a2_c2) == 0) {
				cout << "ind_a2_c2 = " << ind_a2_c2 << " es nulo"<< endl;
			}

			//dividimos los arcos en su punto de intersecioon
			if(arcos->getArco(ind_a2_c2)->getNodo1() == ind_p1) {
				cout << "refinando en alfa" << endl;
				edgeSplit(ind_a2_c2,alfa);
			}
			else {
				edgeSplit(ind_a2_c2,1-alfa);
				cout << "refinando en 1-alfa" << endl;
			}
			if(arcos->getArco(ind_a1_c1)->getNodo1() == ind_p2) {
				cout << "refinando en beta" << endl;
				edgeSplit(ind_a1_c1,beta);
			}
			else {
				cout << "refinando en 1-beta" << endl;
				edgeSplit(ind_a1_c1,1-beta);
			}
			//hacemos un flip en el arco
			cout << "Flip ind_arco = " << ind_arco << endl;
			int nuevo_arco = edgeFlip(ind_arco);
			cout << "Nuevo nuevo_arco = " << nuevo_arco << endl;
			cout << "Largo nuevo_arco = " << arcos->getArco(nuevo_arco)->getLargo(this) << endl;
			//ahora hacemos un reduce arco
			edgeCollapse(nuevo_arco,0);

		}
		else if(seCruzan(p1,p_c1,p2,p_c2) == 1) {
			cout << "Se cruzan en: p1,p_c1,p2,p_c2" << endl;
			double alfa = valorInterseccion(p1,p_c1,p2,p_c2);
			double beta = valorInterseccion(p2,p_c2,p1,p_c1);
			cout << "alfa = " << alfa << endl;
			cout << "beta = " << beta << endl;

			if(arcos->getArco(ind_a2_c1) == 0) {
				cout << "ind_a2_c1 = " << ind_a2_c1 << " es nulo"<< endl;
			}
			if(arcos->getArco(ind_a1_c2) == 0) {
				cout << "ind_a1_c2 = " << ind_a1_c2 << " es nulo"<< endl;
			}

			//dividimos los arcos en su punto de intersecioon
			if(arcos->getArco(ind_a2_c1)->getNodo1() == ind_p1) {
				cout << "refinando en alfa" << endl;
				edgeSplit(ind_a2_c1,alfa);
			}
			else {
				cout << "refinando en 1-alfa" << endl;
				edgeSplit(ind_a2_c1,1-alfa);
			}
			if(arcos->getArco(ind_a1_c2)->getNodo1() == ind_p2) {
				cout << "refinando en beta" << endl;
				edgeSplit(ind_a1_c2,beta);
			}
			else {
				cout << "refinando en 1-beta" << endl;
				edgeSplit(ind_a1_c2,1-beta);
			}
			//hacemos un flip en el arco
			int nuevo_arco = edgeFlip(ind_arco);
			//ahora hacemos un reduce arco
			edgeCollapse(nuevo_arco,0);
		}
		else {

		}
	}
	cout << "retornamos de manejaInconsitenciaArco" << endl;
	return;

}

void MallaTriangulos::manejaInconsistenciaArcoAntes(int ind_arco, double val) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	if(ind_c1 < 0 || ind_c2 < 0) {
		return; // region borde
	}

	//obtenemos los indices de los 4 puntos
	int ind_p1 = arcos->getArco(ind_arco)->getNodo1();
	int ind_p2 = arcos->getArco(ind_arco)->getNodo2();
	int ind_p_c1 = this->getNodoOpuestoArco(ind_c1,ind_arco);
	int ind_p_c2 = this->getNodoOpuestoArco(ind_c2,ind_arco);

	//movemos los 4 nodos.
	nodos->moverNodoSegunConcentracion(ind_p1,val);
	nodos->moverNodoSegunConcentracion(ind_p2,val);
	nodos->moverNodoSegunConcentracion(ind_p_c1,val);
	nodos->moverNodoSegunConcentracion(ind_p_c2,val);

	this->manejaInconsitenciaArco(ind_arco);

	//regresamos los 4 nodos.
	nodos->regresarNodoSegunConcentracion(ind_p1,val);
	nodos->regresarNodoSegunConcentracion(ind_p2,val);
	nodos->regresarNodoSegunConcentracion(ind_p_c1,val);
	nodos->regresarNodoSegunConcentracion(ind_p_c2,val);
}
