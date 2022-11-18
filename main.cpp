#include <iostream>
using namespace std;
//transporte cuidades y carreteras

struct Vertice
{
    string nombre;

    struct Vertice * sigV;//para enlazar todos los vertices en una lista
    struct Arco *subListaArcos;//representa los arcos que salen de ese vertice

    bool visitado;
    Vertice (string nom)
    {
        nombre = nom;
        sigV = NULL;
        subListaArcos = NULL;
        visitado = false;
    }
};

struct Arco
{
    int distancia;
    string destino;
    struct Arco *sigA;//siguiente arco.
    struct Arco *antA;//anterior arco.
    Arco(int dis, string des)
    {
        distancia = dis;
        destino = des;
        sigA = NULL;
        antA = NULL;
    }
};

struct Vertice *grafo;// el apuntador inicial del grafo

//inserción al inicio de la lista de vertices.
void insertarVertice(string nom)
{
    struct Vertice *nuevoVertice = new Vertice(nom);

    nuevoVertice->sigV = grafo;
    grafo = nuevoVertice;
}

struct Vertice *   buscarVertice(string origen)
{
    struct Vertice *tempV = grafo;
    while(tempV != NULL)
    {
        if(tempV->nombre == origen)
            return tempV;

        tempV = tempV->sigV;
    }
    return NULL;//no lo encontro
}

//Funcion para vertices, modifica el nombre
bool modificarVertice(string nombre, string nuevoNombre)
{
    Vertice * tempV = buscarVertice(nombre);

    if ( tempV == NULL)
    {
        cout<<"Persona no encontrada";
        return false;
    }
    else
    {
        tempV->nombre = nuevoNombre;
        cout<<"\nModificado con exito.";
        return true;
    }
}

//Funcion que permite eliminar un vertice
bool eliminarVertice(string nom, Vertice * sigV)
{
    if(sigV == NULL)
    {
        cout <<"\nLista vacia";
        return false;
    }
    else if(sigV->nombre== nom)
    {
        sigV = sigV->sigV;
        return true;
    }
    else
    {
        Vertice *temp = sigV;
        Vertice *tempAnt= sigV;
        while(temp != NULL)
        {

            if(temp->nombre == nom) //borrar
            {
                tempAnt->sigV  = temp->sigV;
                return true;
            }

            tempAnt= temp;
            temp = temp->sigV;
        }

        if(temp==NULL)
        {
            cout<<"El nombre no esta en la lista.";
            return false;
        }

    }
}

void insertarArco(string origen, int dis, string des)
{

    struct Vertice *vOrigen = buscarVertice(origen);
    struct Vertice *vDestino = buscarVertice(des);

    if(vOrigen == NULL)
    {
        cout<<"\nNo se encuentra el origen.";
        return;
    }
    if(vDestino == NULL)
    {
        cout<<"\nNo se encuentra el destino.";
        return;
    }
    struct Arco *nuevoArco = new Arco(dis,des);

    //se inserto al inicio de la sublista de Arcos
    nuevoArco->sigA = vOrigen->subListaArcos;
    nuevoArco->antA = NULL;
    vOrigen->subListaArcos = nuevoArco;
}

bool buscarArco(int dis, string des, Arco* subListaArcos)
{
    Arco*temp = subListaArcos;
    while(temp != NULL)
    {
        if(dis == temp->dis && des == temp-> des)
            return true;
            return temp;
        temp = temp->sig;
    }
    return false;
    return NULL;
}
void modificar(int x, int nuevoValor, nodo*lista)
{
    nodo* modif = buscarArco(x, lista);
    if(modif!= NULL)
        modif->num = nuevoValor;
}

bool eliminarArco(int id)
{
    if(lEfimeridad == NULL)
    {
        cout <<"\nLista vacia";
        return false;
    }
    else if(lEfimeridad->id == id)
    {
        lEfimeridad = lEfimeridad->sig;
        return true;
    }
    else //si esta en medio o al final de la lista
    {
        Efimeridad *temp = lEfimeridad;
        Efimeridad *tempAnt= lEfimeridad;
        while(temp != NULL)
        {

            if(temp->id == id) //borrar
            {
                tempAnt->sig  = temp->sig;
                return true;
            }

            tempAnt= temp;
            temp = temp->sig;
        }

        if(temp==NULL)
        {
            cout<<"La efimeridad no esta en la lista.";
            return false;
        }

    }
}

void cargarDatos()
{
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

void amplitud()
{
    struct Vertice *tempV = grafo;

    while(tempV != NULL) //RECORRE LA LISTA DE VERTICES
    {
        cout<<"\nVertice:  "<<tempV->nombre<<"\t";
        struct Arco *tempA = tempV->subListaArcos;

        while(tempA != NULL) //RECORRE LOS ARCOS DE LA LISTA DE ARCOS DEL VERTICE
        {
            cout<<tempV->nombre<<tempA->destino<<tempA->distancia<<",  ";
            tempA = tempA->sigA;
        }
        tempV = tempV->sigV;
    }
}

void profundidad (struct Vertice *inicio)
{
    if((inicio == NULL) or (inicio->visitado== true))
    {
        cout<<endl;
        return;
    }

    inicio->visitado = true;

    struct Arco *tempA = inicio->subListaArcos;
    while(tempA != NULL)
    {
        cout<<inicio->nombre<<tempA->destino<<tempA->distancia<<",  ";

        profundidad(buscarVertice(tempA->destino));

        tempA = tempA->sigA;
    }
}

void desmarcar()
{
    struct Vertice *tempV = grafo;

    while(tempV != NULL)
    {

        tempV->visitado = false;

        tempV = tempV->sigV;
    }
}

bool existeRuta = false;
bool buscarRuta( struct Vertice *origen, string destino)
{

    if((origen == NULL) or (origen->visitado== true))
        return existeRuta;

    if(origen->nombre == destino)
    {
        existeRuta= true;
        return existeRuta;
    }
    origen->visitado =true;

    struct Arco *tempA =origen->subListaArcos;
    while(tempA != NULL)
    {

        buscarRuta(buscarVertice(tempA->destino), destino);
        tempA = tempA->sigA;
    }
}

bool imprimirRuta(struct Vertice *origen, string destino, string ruta)
{
    if((origen == NULL) or (origen->visitado== true))
        return existeRuta;

    if(origen->nombre == destino)
    {
        cout<<"\n\nRuta................  "<<ruta<<destino;
        existeRuta= true;
        return existeRuta;
    }
    origen->visitado =true;

    struct Arco *tempA =origen->subListaArcos;
    while(tempA != NULL)
    {

        imprimirRuta(buscarVertice(tempA->destino), destino,ruta+origen->nombre);
        tempA = tempA->sigA;
    }
    origen->visitado =false;
}

bool imprimirRutaconDistancias(struct Vertice *origen, string destino, string ruta, int dis)
{
    if((origen == NULL) or (origen->visitado== true))
        return existeRuta;

    if(origen->nombre == destino)
    {
        cout<<"\nLa ruta es: "<<ruta<<destino<<" La distancia es: "<<dis;
        existeRuta= true;
        return existeRuta;
    }
    origen->visitado =true;

    struct Arco *tempA =origen->subListaArcos;
    while(tempA != NULL)
    {
        imprimirRutaconDistancias(buscarVertice(tempA->destino), destino,
                                  ruta+origen->nombre, dis + tempA->distancia);
        tempA = tempA->sigA;
    }
    origen->visitado =false;
}
//variables globales
string rutaMenor = "";
int distanciaMenor = 0;
bool rutaCorta(struct Vertice *origen, string destino, string ruta, int dis)
{
    if((origen == NULL) or (origen->visitado== true))
        return existeRuta;

    if(origen->nombre == destino)
    {
        if((distanciaMenor==0) || (dis < distanciaMenor))
        {
            distanciaMenor =dis;
            rutaMenor = ruta+destino;
        }
        existeRuta= true;
        return existeRuta;
    }
    origen->visitado =true;

    struct Arco *tempA =origen->subListaArcos;
    while(tempA != NULL)
    {

        rutaCorta(buscarVertice(tempA->destino), destino, ruta+origen->nombre, dis + tempA->distancia);
        tempA = tempA->sigA;
    }
    origen->visitado =false;
}
int main()
{
    cargarDatos();
    int op;
    op = -1;
    while(op != 0)
    {

        cout<<"\nBienvenido al simulador de caminatas"<<endl;

        cout<<"Ingrese 1 para crear, modificar o borrar un vertice"<<endl;

        cout<<"Ingrese 2 para crear, modificar o borrar un arco"<<endl;

        cout<<"Ingrese 3 para crear, modificar o borrar una persona"<<endl;

        cout<<"Ingrese 4 para imprimir los arcos, vertices o personas"<<endl;

        cout<<"Ingrese 5 para imprimir el estado de las personas en el avance"<<endl;

        cout<<"Ingrese 6 para saber cual es la persona que hizo mas amigos"<<endl;

        cout<<"Ingrese 7 para saber cual es la primera persona en terminar la caminata"<<endl;

        cout<<"Ingrese 8 para saber cual es la ultima persona en terminar la caminata"<<endl;

        cout<<"Ingrese 9 para imprimir el grafo en amplitud"<<endl;

        cout<<"Ingrese 10 para imprimir el arreglo"<<endl;

        cout<<"Ingrese 11 para imprimir las rutas cortas para las personas que avanzan de la forma 3 y 4."<<endl;

        cout<<"Ingrese 12 para 9 imprimir la cantidad y el nombre de los amigos que logro realizar una persona X"<<endl;

        cout<<"Ingrese 13 para imprimir cuales personas no encontraron algun amigo"<<endl;
        
        cout<<"Ingrese 14 para imprimir cuales no pudieron realizar la caminata al no existir ruta";

        cout<<"Ingrese 0 para salir"<<endl;

        cout<<"Ingrese la opcion que desea realizar: ";


        cin  >> op;
        cout<<endl;


        if(op == 1)
        {
            int ope;
            ope = -1;
            while(ope != 0){
                cout<<"Ingrese 1 si desea crear un vertice";
                
                cout<<"Ingrese 2 si desea modificar un vertice";
                
                cout<<"Ingrese 3 si desea borrar un vertice";

                cout<<"Ingrese 0 para salir"<<endl;

                cout<<"Ingrese la opcion que desea realizar: ";
                
                cin  >> ope;
                cout<<endl;
            }
        }
        if(op == 2)
        {
            int oper;
            oper = -1;
            while(oper != 0){
                cout<<"Ingrese 1 si desea crear un arco";
                
                cout<<"Ingrese 2 si desea modificar un arco";
                
                cout<<"Ingrese 3 si desea borrar un arco";

                cout<<"Ingrese 0 para salir"<<endl;

                cout<<"Ingrese la opcion que desea realizar: ";
                
                cin  >> oper;
                cout<<endl;
            }
        }
        if(op == 3)
        {
            int opera;
            opera = -1;
            while(opera != 0){
                cout<<"Ingrese 1 si desea crear una persona";
                
                cout<<"Ingrese 2 si desea modificar una persona";
                
                cout<<"Ingrese 3 si desea borrar una persona";

                cout<<"Ingrese 0 para salir"<<endl;

                cout<<"Ingrese la opcion que desea realizar: ";
                
                cin  >> opera;
                cout<<endl;
            }
        }
    return 0;
}


