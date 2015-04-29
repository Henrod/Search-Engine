#include <iostream>
#include "Celula.h"

typedef int TipoDoElemento;

using namespace std;

Celula::Celula(TipoDoElemento x, Celula* prox)
{
    _info = x;
    _prox = prox;
}

void Celula::setProx(Celula* p){
    _prox = p;
}

Celula* Celula::getProx() const {
    return _prox;
}

void Celula::setInfo(TipoDoElemento t){
    _info = t;
}

TipoDoElemento Celula::getInfo() const {
    return _info;
}

Celula* Celula::busca(TipoDoElemento t, Celula* inicio){
    Celula* temp = inicio;

    if(temp == NULL) return NULL;

    while(temp->getInfo() != t && temp != NULL){
        temp = temp->getProx();
    }

    return temp;
}
