#include <string>
using namespace std;

class QuizMrowki {
private:
    const string rozowy = "\033[35m";
    const string reset = "\033[0m";
    const string jasny_zielen = "\033[92m";
    static const int MAX_PYTAN = 10;
    string pytania[MAX_PYTAN];
    string odpowiedzi[MAX_PYTAN];
    int liczba_pytan;

    void wczytajPytaniaZPliku(const string& nazwaPliku);

public:
    QuizMrowki(const string& nazwaPliku);
    void uruchomQuiz();
};


