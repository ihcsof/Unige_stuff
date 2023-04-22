#include "labo2_aux.h"


vector<int> leggiVettoreDaFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    vector<int> v;        // vettore di dati (numeri interi diversi da -1000000
    int dato;
    ifs>>dato;
    if (!ifs) throw runtime_error("Errore inserimento dati\n");
    while (dato!=-1000000)  // assumiamo che il segnale di fine input nel file sia il numero "meno un milione", -1000000
        {          
        v.push_back(dato);   // put into vector
        ifs>>dato;
        if (!ifs) throw runtime_error("Errore inserimento dati\n");
        }
return v;
}

void stampaVettoreEDurataSuStream(const vector<int>& v, string info, double duration, ofstream& ofs) // notare passaggio per "const reference" di v
{
    ofs << info;
    cout << info;
    for (unsigned int i=0; i<v.size(); ++i)
       {
       ofs << v[i] << "\n";
       cout << v[i] << "\n";
       }
    ofs << info << "\nDurata dell'esecuzione in microsecondi: " << duration << endl;
    cout << info << "\nDurata dell'esecuzione in microsecondi: " << duration << endl;
    cout << "\nPremere un carattere qualunque per andare avanti: ";
    char ch;
    cin >> ch;
}
