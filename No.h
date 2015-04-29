#ifndef NO_H
#define NO_H
#include <iostream>
#include "CelulaArq.h"

using namespace std;

typedef string Tipo;
typedef int TipoDoElemento;

class No
{
    private:
		Tipo _chave;
		No* _esq;
		No* _dir;
		int _nElems;
		int _bal;
    protected:
        void P() const {cout << _chave << " ";}
        void insere( Tipo t, TipoDoElemento linha );
        CelulaArq* arquivos;
        void insereLinhaNo(int linha, string arquivo);

        // Funções para impressão ordenada
        void pre_ordem() const;
        void pos_ordem() const;
        void in_ordem() const;

    public:
        No(Tipo chave, No* esq = NULL, No* dir = NULL);
		~No();
        No* getEsq() const;
        No* getDir() const;
        Tipo getChave() const;
        int getNElems() const { return _nElems; }
        int getBal() const { return _bal; }
        void getLinhas();

        friend class ArvoreBuscaBinaria;
};

#endif // NO_H
