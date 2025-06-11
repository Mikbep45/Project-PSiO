#include <string>
#include <iostream>
#include "vcpkg\installed\x64-windows\include\hpdf.h"
using namespace std;

class Pdf_handler
{
public:
    void tworzeniePdf(const string& nazwa_pliku_pdf, const string& tresc);
private:
   HPDF_Doc pdf;
};
