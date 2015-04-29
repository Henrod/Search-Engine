#ifndef CELULAARQ_H
#define CELULAARQ_H

#include <iostream>
#include "Celula.h"

using namespace std;

typedef string Tipo;

class CelulaArq
{
    private:
       Tipo _info;
       CelulaArq* _prox;
    protected:
        void setProx(CelulaArq* p);
        CelulaArq* getProx() const;
        void setInfo(Tipo t);
        Tipo getInfo() const;
        CelulaArq* busca(Tipo t, CelulaArq* inicio);
    public:
        CelulaArq(Tipo t, CelulaArq* prox);
        Celula* nLinhas;

        friend class ArvoreBuscaBinaria;
        friend class No;
};

#endif // CELULAARQ_H
