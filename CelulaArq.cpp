#include <iostream>
#include "CelulaArq.h"

using namespace std;

typedef string Tipo;

CelulaArq::CelulaArq(Tipo x, CelulaArq* prox)
{
    _info = x;
    _prox = prox;
    nLinhas = NULL;
}

void CelulaArq::setProx(CelulaArq* p){
    _prox = p;
}

CelulaArq* CelulaArq::getProx() const {
    return _prox;
}

void CelulaArq::setInfo(Tipo t){
    _info = t;
}

Tipo CelulaArq::getInfo() const {
    return _info;
}

CelulaArq* CelulaArq::busca(Tipo t, CelulaArq* inicio)
{
    CelulaArq* temp = inicio;

    if(temp == NULL) return NULL;


    while(temp->getInfo() != t && temp != NULL){
        temp = temp->getProx();
    }

    return temp;
}
