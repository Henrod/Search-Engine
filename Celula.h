#include <iostream>

#ifndef CELULA_H
#define CELULA_H

typedef int TipoDoElemento;

class Celula
{
    private:
    protected:
        void setProx(Celula* p);
        Celula* getProx() const;
        void setInfo(TipoDoElemento t);
        TipoDoElemento getInfo() const;
    public:
        TipoDoElemento _info;
        Celula* _prox;
        Celula(TipoDoElemento t, Celula* prox);
        Celula* busca(TipoDoElemento t, Celula* inicio);
    friend class ListaLinear;
    friend class ArvoreBuscaBinaria;
    friend class No;
};

#endif // CELULA_H
