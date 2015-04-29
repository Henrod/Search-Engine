#include <iostream>
#include <string>
#include <fstream>
#include "No.h"

using namespace std;

No::No(Tipo chave, No* esq, No* dir)
{
    arquivos = NULL;
    _chave = chave;
    _esq = esq;
    _dir = dir;

    int e = (_esq==NULL)? 0 : _esq->_nElems;
    int d = (_esq==NULL)? 0 : _dir->_nElems;
    _nElems = e+d+1;
    _bal = 0;
}

No::~No()
{
	delete _esq;
	delete _dir;
}

No* No::getEsq() const {
    return _esq;
}

No* No::getDir() const {
    return _dir;
}

Tipo No::getChave() const {
    return _chave;
}

void No::insere( Tipo t, TipoDoElemento linha ) {

    if( t.size() <= _chave.size() ) {
        if( _esq ) _esq -> insere(t, linha);
        else _esq = new No(t);
    }
    else if ( t.size() > _chave.size() ) {
        if( _dir ) _dir -> insere(t, linha);
        else _dir = new No(t);
    }
}

void No::pre_ordem() const {
    P();
    if( _esq ) _esq->pre_ordem();
    if( _dir ) _dir->pre_ordem();
}

void No::in_ordem() const {
    if( _esq ) _esq->in_ordem();
    P();
    if( _dir ) _dir->in_ordem();
}

void No::pos_ordem() const {
    if( _esq ) _esq->pos_ordem();
    if( _dir ) _dir->pos_ordem();
    P();
}


void No::insereLinhaNo(int linha, string arquivo)
{
    if(arquivos == NULL)
    arquivos = new CelulaArq(arquivo, NULL);

    CelulaArq* temp = arquivos;

    while(temp->getInfo() != arquivo && temp->getProx() != NULL)
    temp = temp->getProx();

    if(temp->getInfo() != arquivo && temp->getProx() == NULL){
    CelulaArq* temp1 = new CelulaArq(arquivo, NULL);
    temp->setProx(temp1);
    temp = temp1;
    }

    if(temp->nLinhas != NULL){
    Celula* aux = temp->nLinhas;

    while(aux->getProx() != NULL){
        aux = aux->getProx();
    }

    Celula* aux2 = new Celula(linha, NULL);
    aux->setProx(aux2);
    }

    else if(temp->nLinhas == NULL)
    temp->nLinhas = new Celula(linha, NULL);


}

void No::getLinhas()
{
    string frase;
    CelulaArq* aux = arquivos;
    while(aux != NULL){
        cout << aux->getInfo() << ":----------------------------\n";
        Celula* temp = aux->nLinhas;
        while(temp != NULL){

          fstream arq;
          arq.open((aux->getInfo()).c_str(), fstream::in);
          getline(arq,frase);

          for(int i = 0; i<temp->getInfo()-1; i++)
          getline(arq,frase);

          cout << temp->getInfo() << ": " << frase << endl;

          temp = temp->getProx();
        }

        aux = aux->getProx();
    }
}
