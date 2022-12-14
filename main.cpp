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
struct Vertice *grafo2;
//Lista de objetos persona
struct Persona
{
    string verticeInicial;
    int id;
    string nombre;
    int formaDeAvance;
    int NumeroAmigos;
    int minCaminata;//duracion caminata
    string Dedondesoy;
    string Adondevoy;
    string Actual;
    Persona *sig;

    struct Amigos *sublista;

    Persona(string n, int FA, string VI, int ind,int num, int minC, string soy, string voy, string actual)
    {
        nombre = n;
        verticeInicial = VI;
        formaDeAvance = FA;
        id = ind;
        minCaminata = minC;
        Dedondesoy = soy;
        NumeroAmigos = num;
        Adondevoy= voy;
        Actual = actual;
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
void insertarPersona(string name, int tipoAvanze, string verticeI,int id,int n, int minC, string soy, string voy,string actual)
{
    if(BuscarPersona(name) == NULL)
    {
        Persona*nn = new Persona(name,tipoAvanze,verticeI,id, n, minC, soy, voy, actual);
        nn->sig = lPersonas;
        lPersonas = nn;
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
            temp = temp->sig;
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

//Funcion que imprime quienes hicieron m??s amigos o quienes hicieron 0 amigos
void masAmigos(Persona* lista, string tipo)
{
    Persona*tem = lista;
    int i = 0;
    int asociales = 0;


    //ver el mayor numero de amigos
    while (tem != NULL)
    {
        if (tem->NumeroAmigos > i)
        {
            i = tem->NumeroAmigos;
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
        cout << "\nPersonas con 0 amigos:\n";
        while (tem != NULL)
        {
            if (tem->NumeroAmigos == 0)
            {
                cout << "Nombre: " << tem->nombre << endl;
                cout << "ID: " << tem->id << endl;
                cout << "Numero de amigos: " << tem->NumeroAmigos << endl << endl;
                asociales+=1;
            }
            tem = tem->sig;
        }
        if (asociales == 0)
        {
            cout<<"Las personas que realizaron la caminata eran muy sociales y todos hicieron algun amigo ???(?????`)/ \n";
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

//inserci??n al inicio de la lista de vertices.
void insertarVertice(string nom)
{
    struct Vertice *nuevoVertice = new Vertice(nom);

    nuevoVertice->sigV = grafo;
    grafo = nuevoVertice;
}

void insertarVertice2(string nom)
{
    struct Vertice *nuevoVertice = new Vertice(nom);

    nuevoVertice->sigV = grafo2;
    grafo2 = nuevoVertice;
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
struct Vertice *   buscarVertice2(string origen)
{
    struct Vertice *tempV = grafo2;
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

void imprimirVertce(Vertice* lista)
{
    if(lista== NULL)
        cout<<"\nLa lista esta vacia.";
    else
    {
        Vertice* temp = lista;
        while(temp != NULL)
        {

            cout<<temp->nombre<<endl;
            temp = temp->sigV;
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

void insertarArco2(string origen, int ti, string des)
{
    struct Vertice *vOrigen = buscarVertice2(origen);
    struct Vertice *vDestino = buscarVertice2(des);

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

struct Arco* buscarArco2(string origen, int ti, string des)
{
    struct Vertice *vOrigen = buscarVertice2(origen);
    struct Vertice *vDestino = buscarVertice2(des);
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

void modificarArco(int ti,int nuevoti, string nuevodes, string des, Arco*lista, string origen)
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

void imprimirArco(int ti, string des, string origen)
{
    struct Vertice *vOrigen = buscarVertice(origen);
    struct Arco *arc = vOrigen->subListaArcos;
    if(vOrigen== NULL)
        cout<<"\nNo existe el vertice.";
    else
    {
        if(arc== NULL)
        {
            cout<<"No se encontro arcos";
        }
        else
        {
            cout<<"Los arcos del vertice son: "<<endl;
            while(arc != NULL)
            {
                cout<<arc->tiempo<<arc->destino<<endl;
                arc = arc->sigA;
            }
        }
    }
}

void cargarDatos()
{
    //Personas

    insertarPersona("Andr??s",2,"B",2745,0,0,"","A","");
    insertarPersona("Ana",4,"B",3298,0,0,"","E","");
    insertarPersona("Eric",1,"A",4673,0,0,"","D","");
    insertarPersona("Mar??a",2,"D",9001,0,0,"","C","");
    insertarPersona("Evelyn",2,"B",9872,0,0,"", "D","");
    insertarPersona("Jos??",3,"C",4587,0,0,"","A","");
    insertarPersona("Iv??n",2,"D",9120,0,0,"", "B","");
    insertarPersona("Leo",1,"B",7581,0,0,"", "C","");
    insertarPersona("Sara",3,"D",1260,0,0,"", "E","");
    insertarPersona("Helena",4,"A",3965,0,0,"", "E","");

    insertarPersona("Emma",4,"B",6301,0,0,"", "A","");
    insertarPersona("Manuel",2,"C",6749,0,0,"", "E","");
    insertarPersona("Mariana",1,"C",2710,0,0,"", "D","");
    insertarPersona("Isabel",3,"A",2916,0,0,"", "C","");
    insertarPersona("Jorge",3,"D",4528,0,0,"", "A","");
    insertarPersona("Gabriel",1,"A",6471,0,0,"", "D","");
    insertarPersona("Eduardo",4,"C",9371,0,0,"","B","");
    insertarPersona("Luc??a",2,"B",1289,0,0,"","C","");
    insertarPersona("Gerardo",1,"A",3283,0,0,"", "E","");
    insertarPersona("Johana",4,"D",8672,0,0,"", "E","");


    //Vertices
    insertarVertice("A");
    insertarVertice("B");
    insertarVertice("C");
    insertarVertice("D");
    insertarVertice("E");

    insertarVertice2("A");
    insertarVertice2("B");
    insertarVertice2("C");
    insertarVertice2("D");
    insertarVertice2("E");
    insertarVertice2("F");
    insertarVertice2("G");

    //Arcos
    insertarArco("A",12,"B");
    insertarArco("B",12,"A");

    insertarArco("B",6,"C");
    insertarArco("C",6,"B");

    insertarArco("B",14,"E");
    insertarArco("E",14,"B");

    insertarArco("C",8,"D");
    insertarArco("D",8,"C");

    insertarArco("D",10,"E");
    insertarArco("E",10,"D");



    insertarArco2("A",12,"B");
    insertarArco2("B",12,"A");

    insertarArco2("B",6,"C");
    insertarArco2("C",6,"B");

    insertarArco2("B",14,"F");
    insertarArco2("F",14,"B");

    insertarArco2("C",8,"D");
    insertarArco2("D",8,"C");

    insertarArco2("D",10,"E");
    insertarArco2("E",10,"D");

    insertarArco2("F",12,"G");
    insertarArco2("G",12,"F");

    insertarArco2("C",0,"C");
    insertarArco2("C",0,"C");

    insertarArco2("A",14,"F");
    insertarArco2("F",14,"A");

    insertarArco2("C",8,"E");
    insertarArco2("E",8,"C");

    insertarArco2("B",10,"E");
    insertarArco2("E",10,"B");
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
    struct Arco *tempA =origen->subListaArcos;
    if((origen == NULL) || (origen->visitado== true))
        return existeRuta;

    if(origen->nombre == destino)
    {
        existeRuta = true;
        return existeRuta;
    }
    origen->visitado =true;


    while(tempA != NULL)
    {

        buscarRuta(buscarVertice(tempA->destino), destino);
        tempA = tempA->sigA;
    }
    return existeRuta;

}

bool buscarRuta2( struct Vertice *origen, string destino)
{
    struct Arco *tempA =origen->subListaArcos;
    if((origen == NULL) || (origen->visitado== true))
        return existeRuta;

    if(origen->nombre == destino)
    {
        existeRuta = true;
        return existeRuta;
    }
    origen->visitado =true;


    while(tempA != NULL)
    {

        buscarRuta2(buscarVertice2(tempA->destino), destino);
        tempA = tempA->sigA;
    }
    return existeRuta;

}

bool imprimirRuta(struct Vertice *origen, string destino, string ruta)
{
    if((origen == NULL) || (origen->visitado== true))
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


bool imprimirRutaconTiempo(struct Vertice *origen, string destino,string ruta, int ti)
{
    if((origen == NULL) or (origen->visitado== true))
        return existeRuta;

    if(origen->nombre == destino)
    {
        cout<<" El tiempo de llegada es: "<<ti<<endl;
        existeRuta= true;
        return existeRuta;
    }
    origen->visitado =true;

    struct Arco *tempA =origen->subListaArcos;
    while(tempA != NULL)
    {
        imprimirRutaconTiempo(buscarVertice(tempA->destino), destino,
                              ruta+origen->nombre,ti + tempA->tiempo);
        tempA = tempA->sigA;
    }
    origen->visitado =false;
}



void imprimirinicio(Persona*lista)
{
    if(lista == NULL)
    {
        cout<<"\nNo hay personas en la lista.";
    }
    else
    {
        Persona*temp = lista;
        string origen;
        origen = temp->verticeInicial;
        cout<<"Inicio"<<endl;
        while (temp != NULL)
        {
            cout<<temp->nombre<<" inicia en "<<temp->verticeInicial<<" tipo de avance "<<temp->formaDeAvance<<endl;
            temp = temp->sig;
        }
    }
}

int cont = 0;
void AvancePersonasGrafo(Persona* lista)
{
    int num1 = 12;
    int num2 = 6;
    int num3 = 8;
    int num4 = 10;
    int num5 = 14;
    Persona*temp = lista;
    string origen;
    string donde;
    string destino;
    cout<<endl;
    if(lista == NULL)
    {
        cout<<"\nNo hay personas en la lista.";
    }
    else
    {
        while (temp != NULL)
        {
            if(temp->formaDeAvance==1)
            {
                struct Vertice *vOrigen = buscarVertice(temp->verticeInicial);
                struct Arco *arc = vOrigen->subListaArcos;
                if (imprimirRutaconTiempo(vOrigen, temp->Adondevoy,"",0)==true)
                {
                    if (arc->tiempo == num1||arc->tiempo == num2||arc->tiempo == num3||
                            arc->tiempo == num4||arc->tiempo == num5)
                    {
                        if (temp->Dedondesoy != arc->destino)
                        {
                            cout<<"Avance aleatorio grafo 1 "<<temp->nombre<<endl;
                            cout<<"Vertice inicial "<<temp->verticeInicial<<endl;
                            cout<<temp->nombre<<"  se dirige a "<<temp->Adondevoy<<endl;
                            cout<<"Vertice actual "<<arc->destino<<endl;
                            bool caminar = imprimirRutaconTiempo(vOrigen, temp->Adondevoy,"",0);
                            temp->Dedondesoy = temp->verticeInicial;
                            temp->verticeInicial = arc->destino;
                        }

                    }
                }
            }
            temp = temp->sig;
        }
    }
}


void AvancePersonasGrafo2(Persona* lista)
{
    int num1 = 12;
    int num2 = 6;
    int num3 = 8;
    int num4 = 10;
    int num5 = 14;
    Persona*temp = lista;
    string origen;
    string donde;
    string destino;
    cout<<endl;
    if(lista == NULL)
    {
        cout<<"\nNo hay personas en la lista.";
    }
     else
    {
        while (temp != NULL)
        {
            if(temp->formaDeAvance==1)
            {
                struct Vertice *vOrigen = buscarVertice2(temp->verticeInicial);
                struct Arco *arc = vOrigen->subListaArcos;
                if (imprimirRutaconTiempo(vOrigen, temp->Adondevoy,"",0)==true)
                {
                    if (arc->tiempo == num1||arc->tiempo == num2||arc->tiempo == num3||
                            arc->tiempo == num4||arc->tiempo == num5)
                    {
                        if (temp->Dedondesoy != arc->destino)
                        {
                            cout<<"Avance aleatorio grafo 2 "<<temp->nombre<<endl;
                            cout<<"Vertice inicial "<<temp->verticeInicial<<endl;
                            cout<<temp->nombre<<"  se dirige a "<<temp->Adondevoy<<endl;
                            cout<<"Vertice actual "<<arc->destino<<endl;
                            bool caminar = imprimirRutaconTiempo(vOrigen, temp->Adondevoy,"",0);
                            temp->Dedondesoy = temp->verticeInicial;
                            temp->verticeInicial = arc->destino;
                        }

                    }
                }
            }
            temp = temp->sig;
        }
    }
}

//Funcion que imprime quien fue mas rapido en completar su ruta  o quien fue el mas lento
void primerPuesto(Persona* lista, string Quchao)  //el string sirve para ver si retorna el mas rapido o el mas lento
{
    Persona*tem = lista;
    int franshescoVirgolini = 0;
    int flashZootopia = 0;


    //comprueba quien tardo mas minutos
    while (tem != NULL)
    {
        if (tem->minCaminata > franshescoVirgolini)
        {
            franshescoVirgolini = tem->minCaminata;
        }
        tem = tem->sig;
    }
    //comprueba quien tardo menos minutos
    tem = lista;
    flashZootopia = franshescoVirgolini;
    while (tem != NULL)
    {
        if (tem->minCaminata < flashZootopia)
        {
            flashZootopia = tem->minCaminata;
        }
        tem = tem->sig;
    }

    //si quieres al mas rapido
    if (Quchao == "Rapidez")
    {
        tem = lista;
        cout << "\nPrimero o primeros en terminar la caminata :\n";
        while (tem != NULL)
        {
            if (tem->minCaminata == franshescoVirgolini)
            {
                cout << "Nombre: " << tem->nombre << endl;
                cout << "Minutos de caminata: " << tem->minCaminata << endl;
                cout << "id: " << tem->id << endl << endl;
            }
            tem = tem->sig;
        }
    }

    //si quieres al mas lento
    if (Quchao == "Lento")
    {
        tem = lista;
        cout << "\nEl o los ultimos en terminar la caminata :\n";
        while (tem != NULL)
        {
            if (tem->minCaminata == flashZootopia)
            {
                cout << "Nombre: " << tem->nombre << endl;
                cout << "Minutos de caminata: " << tem->minCaminata << endl;
                cout << "id: " << tem->id << endl << endl;
            }
            tem = tem->sig;
        }
    }
}



//Funcion que imprime toda la informacion que hay en la lista de personas
void Doxeados(Persona*lista)
{
    Persona*tem = lista;

    cout<<"Lista de personas con toda la informacion que contiene:"<<endl<<endl;
    while (tem != NULL)
    {
        cout<<"Nombre: "<<tem->nombre<<endl;
        cout<<"ID: "<<tem->id<<endl;
        cout<<"Tiempo de su caminata: "<<tem->minCaminata<<endl;
        cout<<"Vertice inicial: "<<tem->verticeInicial<<endl;
        cout<<"Su forma de avance durante la caminata: "<<tem->formaDeAvance<<endl;
        cout<<"Numero de amigos que hizo en su caminata: "<<tem->NumeroAmigos<<endl;
        if (tem->NumeroAmigos > 0)
        {
            cout<<"Amigos que hizo (Nombre y ID): "<<endl;
            Amigos*sublistatem = tem->sublista;
            while (tem->sublista != NULL)
            {
                cout<<"Nombre: "<<sublistatem->enlace->nombre<<endl;
                cout<<"ID: "<<sublistatem->enlace->id<<endl<<endl;
                sublistatem = sublistatem->sig;
            }
        }
        tem = tem->sig;
    }
}

//MENU
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

        cout<<"Ingrese 4 para imprimir los arcos de un vertice, vertices o personas"<<endl;

        cout<<"Ingrese 5 para imprimir el estado de las personas en el avance"<<endl;

        cout<<"Ingrese 6 para saber cual es la persona que hizo mas amigos"<<endl;

        cout<<"Ingrese 7 para saber cual es la primera persona en terminar la caminata"<<endl;

        cout<<"Ingrese 8 para saber cual es la ultima persona en terminar la caminata"<<endl;

        cout<<"Ingrese 9 para imprimir el grafo en amplitud"<<endl;

        cout<<"Ingrese 10 para imprimir el arreglo"<<endl;

        cout<<"Ingrese 11 para imprimir las rutas cortas para las personas que avanzan de la forma 3 y 4."<<endl;

        cout<<"Ingrese 12 para 9 imprimir la cantidad y el nombre de los amigos que logro realizar una persona X"<<endl;

        cout<<"Ingrese 13 para imprimir cuales personas no encontraron algun amigo"<<endl;

        cout<<"Ingrese 14 para imprimir cuales no pudieron realizar la caminata al no existir ruta"<<endl;

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
                cout<<"Ingrese 1 si desea crear un vertice"<<endl;

                cout<<"Ingrese 2 si desea modificar un vertice"<<endl;

                cout<<"Ingrese 3 si desea borrar un vertice"<<endl;

                cout<<"Ingrese 0 para salir"<<endl;

                cout<<"Ingrese la opcion que desea realizar: ";

                cin  >> ope;
                cout<<endl;

                if(ope == 1)
                {
                    string no;
                    cout<<"Ingrese el nombre del vertice que desea incertar: ";
                    cin>>no;
                    insertarVertice(no);
                }
                if(ope == 2)
                {
                    string n;
                    string no;
                    cout<<"Ingrese el nombre del vertice:";
                    cout<<"Ingrese el nuevo nombre del vertice:";
                    cin>>no;
                    cin>>n;
                    modificarVertice(n,no);
                }
                if(ope == 3)
                {
                    string no;
                    cout<<"Ingrese el nombre del vertice:";
                    cin>>no;

                }
            }
        }
        if(op == 2)
        {
            int oper;
            oper = -1;
            while(oper != 0)
            {
                cout<<"Ingrese 1 si desea crear un arco"<<endl;

                cout<<"Ingrese 2 si desea modificar un arco"<<endl;

                cout<<"Ingrese 3 si desea borrar un arco"<<endl;

                cout<<"Ingrese 0 para salir"<<endl;

                cout<<"Ingrese la opcion que desea realizar: ";

                cin  >> oper;
                cout<<endl;

                if(op == 2)
                {

                }
            }
        }

        if(op == 3)
        {
            int opera;
            opera = -1;
            while(opera != 0)
            {
                cout<<"Ingrese 1 si desea crear una persona"<<endl;

                cout<<"Ingrese 2 si desea modificar una persona"<<endl;

                cout<<"Ingrese 3 si desea borrar una persona"<<endl;

                cout<<"Ingrese 0 para salir"<<endl;

                cout<<"Ingrese la opcion que desea realizar: ";

                cin  >> opera;
                cout<<endl;
            }
        }

        if (op == 5)
        {
            int cont = 0;

            imprimirinicio(lPersonas);
            AvancePersonasGrafo(lPersonas);
            AvancePersonasGrafo2(lPersonas);

            int operacio;
            operacio = -1;
            while(operacio != 0)
            {
                cout<<endl;
                cout<<endl;
                cout<<"Ingrese 1 si desea ver el siguiente avance"<<endl;

                cout<<"Ingrese 0 para salir"<<endl;

                cout<<"Ingrese la opcion que desea realizar: ";

                cin  >> operacio;
                cout<<endl;
                if(operacio == 1)
                {
                    AvancePersonasGrafo(lPersonas);
                    cout<<endl;
                    cout<<endl;
                    AvancePersonasGrafo2(lPersonas);
                }
            }

        }

        if (op == 6)
        {
            masAmigos(lPersonas,"Amistad");
            cout<<endl;
        }

        if (op == 7)
        {
            primerPuesto(lPersonas,"Rapidez");
            cout<<endl;
        }

        if (op == 8)
        {
            primerPuesto(lPersonas,"Lento");
            cout<<endl;
        }

        if (op == 10)
        {
            Doxeados(lPersonas);
            cout<<endl;
        }

        if (op == 12)
        {
            cout<<"Lista de personas registradas: "<<endl;
            imprimirListaPersonas(lPersonas);
            string PersonaX;
            cout<<"Ingrese el nombre de la persona: ";
            cin >> PersonaX;
            amigosPersonaX(PersonaX);
            cout<<endl;
        }

        if (op == 13)
        {
            masAmigos(lPersonas,"La_bocchi");
            cout<<endl;
        }

    }

}

