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
    int tiempo;
    string destino;
    struct Arco *sigA;//siguiente arco.
    struct Arco *antA;//anterior arco.
    Arco(int ti, string des)
    {
        tiempo = ti;
        destino = des;
        sigA = NULL;
        antA = NULL;
    }
};

struct Vertice *grafo;// el apuntador inicial del grafo

//Lista de objetos persona
struct Persona
{
    string verticeInicial;
    int id;
    string nombre;
    int formaDeAvance;
    int NumeroAmigos;
    Persona *sig;

    struct Amigos *sublista;

    Persona(string n, int FA, string VI, int ind,int num)
    {
        nombre = n;
        verticeInicial = VI;
        formaDeAvance = FA;
        id = ind;
        NumeroAmigos = num;
        sublista = NULL;
        sig = NULL;
    }
}*lPersonas;

//Funcion que busca una persona en la lista por su nombre
struct Persona*BuscarPersona(string Name)
{
    struct Persona*temp = lPersonas;
    if (temp == NULL)
    {
        return NULL;
    }
    else
    {
        while(temp != NULL)
        {
            if (Name == temp->nombre)
            {
                return temp;
            }
            temp = temp->sig;
        }
    }
    return NULL;
}

//Funcion que inserta una nueva persona a la lista
void insertarPersona(string name, int tipoAvanze, string verticeI,int id,int n)
{
    if(BuscarPersona(name) == NULL)
    {
        Persona*nn = new Persona(name,tipoAvanze,verticeI,id, n);
        nn->sig = lPersonas;
        lPersonas == nn;
    }
    else
    {
        cout<<"La persona ya se encuenta en la lista.";
    }
}

//Funcion que elimina una persona de la lista
bool eliminarPersona(string name)
{
    if (lPersonas == NULL)
    {
        cout<<"\nLa lista perosnas esta vacia";
        return false;
    }
    else if(lPersonas->nombre == name)
    {
        lPersonas = lPersonas->sig;
        return true;
    }
    else
    {
        Persona*temp = lPersonas;
        Persona*tempAnt = lPersonas;

        while (temp != NULL)
        {
            if(temp->nombre == name)
            {
                tempAnt->sig = temp->sig;
                return true;
            }
            tempAnt = temp;
            temp = temp->sig;

        }
        if (temp == NULL)
        {
            cout<<"La persona que quieres eliminar no esta en la lista.";
            return false;
        }
    }
}

//Funcion que imprime el nombre y id de las personas en la lista
void imprimirListaPersonas(Persona* lista)
{
    if(lista == NULL)
    {
        cout<<"\nNo hay personas en la lista.";
    }
    else
    {
        Persona*temp = lista;
        while (temp != NULL)
        {
            cout<<"Nombre:"<<temp->nombre<<", ";
            cout<<"Id:"<<temp->id<<".\n\n";
        }
    }
}

//Funcion para agregarle amigos a las personas
struct Amigos
{
    Amigos*sig;
    struct Persona*enlace;
    Amigos(struct Persona*A)
    {
        enlace=A;
        sig=NULL;
    }
};

//Funcion para que dos personas se hagan amiwis owo
void cienAmigos(string nameP1,string nameP2)
{
    Persona*persona1 = BuscarPersona(nameP1);
    Persona*persona2 = BuscarPersona(nameP2);

    Amigos*tem = persona1->sublista;

    struct Amigos*nuevo = new Amigos(persona1);
    struct Amigos*nuevo2 = new Amigos(persona2);

    if (persona1->sublista == NULL && persona2->sublista == NULL)
    {
        persona1->sublista = nuevo2;
        persona2->sublista = nuevo;

    }
    else
    {
        while (tem != NULL)
        {
            if (tem->enlace->nombre == persona2->nombre)
            {
                return;
            }
            else
            {
                tem = tem->sig;
            }
        }
        nuevo2->sig = persona1->sublista;
        persona1->sublista = nuevo2;
        persona1->NumeroAmigos+=1;

        nuevo->sig = persona2->sublista;
        persona2->sublista = nuevo;
        persona2->NumeroAmigos+=1;
    }
    return;
}

//Funcion que imprime quienes hicieron más amigos o quienes hicieron menos amigos
void masAmigos(Persona* lista, string tipo)
{
    Persona*tem = lista;
    int i = 0;


    //ver el mayor numero de amigos
    while (tem != NULL)
    {
        if (tem->NumeroAmigos > i)
        {
            i = tem->NumeroAmigos;
        }
        tem = tem->sig;
    }

    //ver el menor numero de amigos
    int min = i;
    tem = lista;
    while (tem != NULL)
    {
        if (tem->NumeroAmigos < min)
        {
            min = tem->NumeroAmigos;
        }
        tem = tem->sig;
    }

    if (tipo == "Amistad")
    {
        tem = lista;
        cout << "\nMayor numero de amigos :\n";
        while (tem != NULL)
        {
            if (tem->NumeroAmigos == i)
            {
                cout << "Nombre: " << tem->nombre << endl;
                cout << "Numero de amigos: " << tem->NumeroAmigos << endl << endl;
            }
            tem = tem->sig;
        }
    }
    else if(tipo == "La_bocchi")
    {
        tem = lista;
        cout << "\nMenor numero de amigos:\n";
        while (tem != NULL)
        {
            if (tem->NumeroAmigos == min)
            {
                cout << "Nombre: " << tem->nombre << endl;
                cout << "ID: " << tem->id << endl;
                cout << "Numero de amigos: " << tem->NumeroAmigos << endl << endl;
            }
            tem = tem->sig;
        }
    }
}

//Funcion para imprimir el numero de amigos que hizo una persona X

void amigosPersonaX(string name)
{
    Persona*personaX = BuscarPersona(name);
    cout<<"\n"<<personaX->nombre<<endl<<"Amigos: "<<personaX->NumeroAmigos;
    while (personaX->sublista != NULL)
    {
        cout<<personaX->sublista->enlace->nombre<<endl;
        personaX->sublista = personaX->sublista->sig;
    }
}

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
        cout<<"Vertice no encontrado";
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

void insertarArco(string origen, int ti, string des)
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
    struct Arco *nuevoArco = new Arco(ti,des);

    //se inserto al inicio de la sublista de Arcos
    nuevoArco->sigA = vOrigen->subListaArcos;
    nuevoArco->antA = NULL;
    vOrigen->subListaArcos = nuevoArco;
}

struct Arco* buscarArco(string origen, int ti, string des)
{
    struct Vertice *vOrigen = buscarVertice(origen);
    struct Vertice *vDestino = buscarVertice(des);
    struct Arco *temp = vOrigen->subListaArcos;
    while(temp != NULL)
    {
        if(vOrigen == NULL)
        {
            cout<<"\nNo se encuentra el origen.";
        }
        if(vDestino == NULL)
        {
            cout<<"\nNo se encuentra el destino.";

        }
        return temp;
        temp = temp->sigA;

    }
}
void modificar(int ti,int nuevoti, string nuevodes, string des, Arco*lista, string origen)
{

    Arco* modif = buscarArco(origen,ti,des);
    struct Vertice *vOrigen = buscarVertice(origen);
    if(modif!= NULL)
    {

        modif->tiempo = nuevoti;
        modif->destino = nuevodes;
    }
}

bool eliminarArco(int ti, string des, string origen)
{
    struct Vertice *vOrigen = buscarVertice(origen);
    struct Arco *arc = vOrigen->subListaArcos;
    struct Arco *arcAnt = vOrigen->subListaArcos;
    if( arc== NULL)
    {
        cout <<"\nLista vacia";
        return false;
    }
    else if(arc->tiempo == ti && arc->destino ==des)
    {
        arc = arc->sigA;
        return true;
    }
    else //si esta en medio o al final de la lista
    {
        while(arc != NULL)
        {

            if(arc->tiempo == ti && arc->destino ==des) //borrar
            {
                arcAnt->sigA  = arc->sigA;
                return true;
            }

            arcAnt= arc;
            arc = arc->sigA;
        }

        if(arc==NULL)
        {
            cout<<"La efimeridad no esta en la lista.";
            return false;
        }

    }
}

void cargarDatos()
{
    //Personas
    insertarPersona("Andrés",2,"B",2745,0);
    insertarPersona("Ana",4,"B",3298,0);
    insertarPersona("Eric",1,"B",4673,0);
    insertarPersona("María",2,"B",9001,0);
    insertarPersona("Evelyn",2,"B",9872,0);
    insertarPersona("José",3,"B",4587,0);
    insertarPersona("Iván",2,"B",9120,0);
    insertarPersona("Leo",1,"B",7581,0);
    insertarPersona("Sara",3,"B",1260,0);
    insertarPersona("Helena",4,"B",3965,0);

    insertarPersona("Emma",4,"B",6301,0);
    insertarPersona("Manuel",2,"B",6749,0);
    insertarPersona("Mariana",1,"B",2710,0);
    insertarPersona("Isabel",3,"B",2916,0);
    insertarPersona("Jorge",3,"B",4528,0);
    insertarPersona("Gabriel",1,"B",6471,0);
    insertarPersona("Eduardo",4,"B",9371,0);
    insertarPersona("Lucía",2,"B",1289,0);
    insertarPersona("Gerardo",1,"B",3283,0);
    insertarPersona("Johana",4,"B",8672,0);
    
    //Vertices
    insertarVertice("A");
    insertarVertice("B");
    insertarVertice("C");
    insertarVertice("D");
    insertarVertice("E");

    //Arcos
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
            cout<<tempV->nombre<<tempA->destino<<tempA->tiempo<<",  ";
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
        cout<<inicio->nombre<<tempA->destino<<tempA->tiempo<<",  ";

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
                                  ruta+origen->nombre, dis + tempA->tiempo);
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

        rutaCorta(buscarVertice(tempA->destino), destino, ruta+origen->nombre, dis + tempA->tiempo);
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
            while(ope != 0)
            {
                cout<<"Ingrese 1 si desea crear un vertice";

                cout<<"Ingrese 2 si desea modificar un vertice";

                cout<<"Ingrese 3 si desea borrar un vertice";

                cout<<"Ingrese 0 para salir"<<endl;

                cout<<"Ingrese la opcion que desea realizar: ";

                cin  >> ope;
                cout<<endl;

                if(op == 1)
                {

                }
            }
        }
        if(op == 2)
        {
            int oper;
            oper = -1;
            while(oper != 0)
            {
                cout<<"Ingrese 1 si desea crear un arco";

                cout<<"Ingrese 2 si desea modificar un arco";

                cout<<"Ingrese 3 si desea borrar un arco";

                cout<<"Ingrese 0 para salir"<<endl;

                cout<<"Ingrese la opcion que desea realizar: ";

                cin  >> oper;
                cout<<endl;

                if(op == 2)
                {

                }
            }
            if(op == 3)
            {
                int opera;
                opera = -1;
                while(opera != 0)
                {
                    cout<<"Ingrese 1 si desea crear una persona";

                    cout<<"Ingrese 2 si desea modificar una persona";

                    cout<<"Ingrese 3 si desea borrar una persona";

                    cout<<"Ingrese 0 para salir"<<endl;

                    cout<<"Ingrese la opcion que desea realizar: ";

                    cin  >> opera;
                    cout<<endl;
                }
            }

        }
    }
}
