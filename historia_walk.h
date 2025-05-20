#include <string>
using namespace std;

class HistoriaWalk
{
public:
    HistoriaWalk(const string& aktualnyPlikWalk_z = "zapis_wyniku.txt", const string& HistoriaWalk_z = "historia_walk.txt");

    void ZapiszWalkeDoHistori() const;

private:
    string aktualnyPlikWalk_z;
    string HistoriaWalk_z;
};
