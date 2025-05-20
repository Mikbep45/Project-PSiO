#include "historia_walk.h"
#include <fstream>
#include <iostream>

HistoriaWalk::HistoriaWalk(const string& aktualnyPlikWalk_z, const string& HistoriaWalk_z) : aktualnyPlikWalk_z(aktualnyPlikWalk_z), HistoriaWalk_z(HistoriaWalk_z) {}

void HistoriaWalk::ZapiszWalkeDoHistori() const
{

    ifstream currentFight(aktualnyPlikWalk_z);
    if (!currentFight)
    {
        cerr << "Error: Nie da sie otworzyc " << aktualnyPlikWalk_z << " do odczytu." << endl;
        return;
    }


    ofstream history(HistoriaWalk_z, ios::app);
    if (!history)
    {
        cerr << "Error: Nie da sie otworzyc pliku " << HistoriaWalk_z << " do zpisania." << endl;
        return;
    }


    string line;
    while (getline(currentFight, line))
    {
        history << line << endl;
    }


    currentFight.close();
    history.close();

}
