/*1. Implementati algoritmul lui Huffman:
Buduroes Elena Bianca - 143*/

#include <iostream> 
#include <queue> 
#include<vector>

using namespace std;

class ArboreHuffman 
{

public:
    
    char info;
    int frecventa;

    ArboreHuffman* stanga;
    ArboreHuffman* dreapta;

    ArboreHuffman(char litera, int frecv)
    {
        info = litera;
        frecventa = frecv;
        stanga = dreapta = NULL;
    }
};

// facem o clasa 'Comparator' pentru a putea stabili prioritatea in functie de frecventa
class Comparator 
{
public:
    bool operator() (ArboreHuffman* a, ArboreHuffman* b)
    {
        if (a->frecventa > b->frecventa)
            return 1;
        return 0;
    }
};

// metoda care sa genereze arborele Huffman
ArboreHuffman* GenerareArbore(priority_queue<ArboreHuffman*, vector<ArboreHuffman*>, Comparator> coada_de_prioritati)
{
    // iteram pana cand ramane un singur nod in coada de prioritati
    while (coada_de_prioritati.size() != 1) 
    {

        ArboreHuffman* stanga = coada_de_prioritati.top(); // nodul cu cea mai mica frecventa
        coada_de_prioritati.pop(); // stergem nodul din coada

        ArboreHuffman* dreapta = coada_de_prioritati.top(); // procedam la fel ca mai sus
        coada_de_prioritati.pop();

        // un nou nod e format din frecventa copilului stang + frecventa copilului drept
        ArboreHuffman* node = new ArboreHuffman('$', stanga->frecventa + dreapta->frecventa);
        node->stanga = stanga;
        node->dreapta = dreapta;

        // punem noul nod in coada de prioritati
        coada_de_prioritati.push(node);
    }

    return coada_de_prioritati.top();
}

// meotda pentru a afisa codul huffman pentru fiecare caracter in parte
void AfisareCoduri(ArboreHuffman* radacina,int cod[], int top)
{ 
    if (radacina->stanga) 
    {
        cod[top] = 0; // punem 0 pentru codul din stanga
        AfisareCoduri(radacina->stanga, cod, top + 1);
    }
 
    if (radacina->dreapta) 
    {
        cod[top] = 1; // punem 1 pentru codul din dreapta
        AfisareCoduri(radacina->dreapta, cod, top + 1);
    }

    if (!radacina->stanga && !radacina->dreapta) // daca este un nod frunza, afisam informatia din radacina
    {
        cout << "   " << radacina->info << " codat Huffman  ->  ";
        for (int i = 0; i < top; i++) // afisam si codul salvat in vector
        {
            cout << cod[i];
        }
        cout << endl;
    }
}

void CoduriHuffman(char info[], int frecventa[], int size)
{
    // declaram o coada de prioritati folosindu-ne si de comparatorul implementat
    priority_queue <ArboreHuffman*,vector<ArboreHuffman*>,Comparator> coada_de_prioritati;

    for (int i = 0; i < size; i++) 
    {
        ArboreHuffman* newNode = new ArboreHuffman(info[i], frecventa[i]);
        coada_de_prioritati.push(newNode);
    }

    // generam arborele Huffman 
    ArboreHuffman* radacina = GenerareArbore(coada_de_prioritati);

    int cod[100], top = 0;
    AfisareCoduri(radacina, cod, top); // afisam codurile
}

 
int main()
{
    cout << endl << "Caracterele si frecventele acestora sunt introduse mai jos (litera - frecventa)" << endl;

    cout << endl;

    cout << "   Litera: 'y'  Frecventa: 2" << endl;
    cout << "   Litera: 'x'  Frecventa: 10" << endl;
    cout << "   Litera: 'z'  Frecventa: 17" << endl;
    cout << "   Litera: 'f'  Frecventa: 20" << endl;
    cout << "   Litera: 'd'  Frecventa: 39" << endl;
    cout << "   Litera: 'b'  Frecventa: 63" << endl;
    cout << "   Litera: 'c'  Frecventa: 78" << endl;
    cout << "   Litera: 'e'  Frecventa: 79" << endl;
    cout << "   Litera: 'a'  Frecventa: 99" << endl;

    cout << endl;
    
    char info[] = { 'y', 'x', 'z', 'f', 'd', 'b','c','e','a' };
    int frecventa[] = { 2, 10, 17, 20, 39, 63, 78, 79, 99 };
    int size = sizeof(info) / sizeof(info[0]);

    CoduriHuffman(info, frecventa, size);
    return 0;
}