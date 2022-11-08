#include <iostream>
using namespace std;
//transporte cuidades y carreteras

struct Vertice{
    string nombre;

    struct Vertice * sigV;//para enlazar todos los vertices en una lista
    struct Arco *subListaArcos;//representa los arcos que salen de ese vertice

    bool visitado;
    Vertice (string nom){
            nombre = nom;
            sigV = NULL;
            subListaArcos = NULL;
            visitado = false;
    }
};

struct Arco{
    int distancia;
    string destino;
    struct Arco *sigA;//siguiente arco.
    Arco(int dis, string des){
            distancia = dis;
            destino = des;
            sigA = NULL;
    }
};

struct Vertice *grafo;// el apuntador inicial del grafo

//inserción al inicio de la lista de vertices.
void insertarVertice(string nom){
            struct Vertice *nuevoVertice = new Vertice(nom);

            nuevoVertice->sigV = grafo;
            grafo = nuevoVertice;
}

struct Vertice *   buscarVertice(string origen){
        struct Vertice *tempV = grafo;
        while(tempV != NULL){
            if(tempV->nombre == origen)
                return tempV;

            tempV = tempV->sigV;
        }
    return NULL;//no lo encontro
}

void insertarArco(string origen, int dis, string des){

        struct Vertice *vOrigen = buscarVertice(origen);
        struct Vertice *vDestino = buscarVertice(des);

        if(vOrigen == NULL){
            cout<<"\nNo se encuentra el origen.";
            return;
        }
        if(vDestino == NULL){
            cout<<"\nNo se encuentra el destino.";
            return;
        }
        struct Arco *nuevoArco = new Arco(dis,des);

        //se inserto al inicio de la sublista de Arcos
        nuevoArco->sigA = vOrigen->subListaArcos;
        vOrigen->subListaArcos = nuevoArco;

}

void cargarDatos(){
        insertarVertice("A");
        insertarVertice("B");
        insertarVertice("C");
        insertarVertice("D");
        insertarVertice("E");
        
        insertarArco("A",12,"B");
        insertarArco("B",12,"C");

        insertarArco("B",6,"C");
        insertarArco("C",6,"B");

        insertarArco("B",14,"F");
        insertarArco("F",14,"B");   

        insertarArco("C",8,"D");
        insertarArco("D",8,"C");

        insertarArco("D",10,"E");
        insertarArco("E",10,"D");
}



void amplitud(){
        struct Vertice *tempV = grafo;

        while(tempV != NULL){//RECORRE LA LISTA DE VERTICES
            cout<<"\nVertice:  "<<tempV->nombre<<"\t";
            struct Arco *tempA = tempV->subListaArcos;

            while(tempA != NULL){//RECORRE LOS ARCOS DE LA LISTA DE ARCOS DEL VERTICE
                    cout<<tempV->nombre<<tempA->destino<<tempA->distancia<<",  ";
                tempA = tempA->sigA;
            }
            tempV = tempV->sigV;
        }
}

void profundidad (struct Vertice *inicio){
        if((inicio == NULL) or (inicio->visitado== true)){
                cout<<endl;
            return;
        }

        inicio->visitado = true;

        struct Arco *tempA = inicio->subListaArcos;
        while(tempA != NULL){
            cout<<inicio->nombre<<tempA->destino<<tempA->distancia<<",  ";

            profundidad(buscarVertice(tempA->destino));

            tempA = tempA->sigA;
        }

}

void desmarcar(){
        struct Vertice *tempV = grafo;

        while(tempV != NULL){

            tempV->visitado = false;

            tempV = tempV->sigV;
        }
}

bool existeRuta = false;
bool buscarRuta( struct Vertice *origen, string destino){

    if((origen == NULL) or (origen->visitado== true))
        return existeRuta;

        if(origen->nombre == destino){
                existeRuta= true;
                 return existeRuta;
        }
        origen->visitado =true;

    struct Arco *tempA =origen->subListaArcos;
    while(tempA != NULL){

        buscarRuta(buscarVertice(tempA->destino), destino);
        tempA = tempA->sigA;
    }
}

bool imprimirRuta(struct Vertice *origen, string destino, string ruta){
    if((origen == NULL) or (origen->visitado== true))
            return existeRuta;

            if(origen->nombre == destino){
                    cout<<"\n\nRuta................  "<<ruta<<destino;
                    existeRuta= true;
                     return existeRuta;
            }
            origen->visitado =true;

        struct Arco *tempA =origen->subListaArcos;
        while(tempA != NULL){

            imprimirRuta(buscarVertice(tempA->destino), destino,ruta+origen->nombre);
            tempA = tempA->sigA;
        }
         origen->visitado =false;
}

bool imprimirRutaconDistancias(struct Vertice *origen, string destino, string ruta, int dis){
    if((origen == NULL) or (origen->visitado== true))
            return existeRuta;

            if(origen->nombre == destino){
                    cout<<"\nLa ruta es: "<<ruta<<destino<<" La distancia es: "<<dis;
                    existeRuta= true;
                     return existeRuta;
            }
            origen->visitado =true;

        struct Arco *tempA =origen->subListaArcos;
        while(tempA != NULL){
            imprimirRutaconDistancias(buscarVertice(tempA->destino), destino,
                                      ruta+origen->nombre, dis + tempA->distancia);
            tempA = tempA->sigA;
        }
        origen->visitado =false;
}
//variables globales
string rutaMenor = "";
int distanciaMenor = 0;
bool rutaCorta(struct Vertice *origen, string destino, string ruta, int dis){
    if((origen == NULL) or (origen->visitado== true))
        return existeRuta;

        if(origen->nombre == destino){
                if((distanciaMenor==0) || (dis < distanciaMenor)){
                        distanciaMenor =dis;
                        rutaMenor = ruta+destino;
                }
                existeRuta= true;
                 return existeRuta;
        }
        origen->visitado =true;

    struct Arco *tempA =origen->subListaArcos;
    while(tempA != NULL){

        rutaCorta(buscarVertice(tempA->destino), destino, ruta+origen->nombre, dis + tempA->distancia);
        tempA = tempA->sigA;
    }
    origen->visitado =false;
}
int main()
{
        cargarDatos();
        cout<<"\nRecorrido en Amplitud-----------------\n";
        amplitud();


        cout<<"\n\n---------------Recorrido en Profundidad a partir del vertice CQ----------------\n";
        profundidad(buscarVertice("CQ"));
        desmarcar();

        cout<<"\n\n---------------Averigurar si hay ruta de CQ a Fortuna:\n";

        buscarRuta(buscarVertice("CQ"), "Fortuna");
        if(existeRuta == true)
            cout<<"\n Si existe ruta";
        else
            cout<<"\nNo existe ruta";

        existeRuta= false;
        desmarcar();


        cout<<"\n\nRutas de CQ a Fortuna............\n\n";
        imprimirRuta(buscarVertice("Fortuna"), "CQ", "");
        existeRuta= false;
        desmarcar();

        cout<<"\n\n.................Rutas con distancia...................\n";
        imprimirRutaconDistancias(buscarVertice("Fortuna"), "Tanque", "",0);
        existeRuta= false;
        desmarcar();

        rutaCorta(buscarVertice("Fortuna"), "CQ", "",0);
        if(existeRuta == true){
                    cout<<"\n\nLa ruta más corta es: "<<rutaMenor
                    << "con una distancia de: "<<distanciaMenor;
        }
        else cout<<"\n\nNo existe ruta.................";
        rutaMenor = "";
        distanciaMenor= 0;
        existeRuta= false;
        desmarcar();


    return 0;
}
