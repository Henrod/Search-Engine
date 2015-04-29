#include "No.h"
#include <string>

#ifndef ARVOREBUSCABINARIA_H
#define ARVOREBUSCABINARIA_H


class ArvoreBuscaBinaria
{
    private:
        No* _raiz;
    protected:
        void imprimeRecursivo(No* no, int nivel);

        // Rotações etc.
        void insereTopo( Tipo t, No **ppNo );
        No* selecao( int k, No* r );
        void sobeMenor( No **ppNo );
        No* uneDirEsq(No *e, No **d);
		void removeNo(Tipo x, No **ppNo);
		int insereAVL(Tipo t, No **ppNo);
		string geraSaida(string arquivo, No* pNo);

    public:
        ArvoreBuscaBinaria();
        ~ArvoreBuscaBinaria();
        No* busca(Tipo t);
        bool vazia() const;
        void insere(Tipo t, TipoDoElemento linha);
        void insereAVL(Tipo t);
        void imprime();
        No* getRaiz() const {return _raiz;}
        bool verificaAVL(No** ppNo);
        int altura(No *raiz);
        int maximo(int x, int y);
        bool verificaBalanceamento(No** ppNo);
        void insereLinha(int linha, string palavra, string arquivo);
        string geraSaida(string arquivo);
        void imprimeWords(string comando, CelulaArq* nomesDosArquivos);

        //Rotacoes (está aqui por causa da GUI)
        void rotDir( No **ppNo );
        void rotEsq( No **ppNo );

        //Impressão em diversas ordens
        void pre_ordem() const { if(_raiz) _raiz->pre_ordem(); }
        void pos_ordem() const { if(_raiz) _raiz->pos_ordem(); }
        void in_ordem()  const { if(_raiz) _raiz->in_ordem(); }

        // Inserção no Topo e remoção
        void insereNoTopo( Tipo t );
        void removeNo( Tipo x ) { removeNo( x, &_raiz ); }

        friend class ListaArq;
        friend class CelArq;
};

#endif // ARVOREBUSCABINARIA_H
