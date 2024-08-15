
#define CATCH_CONFIG_MAIN // O Catch fornece uma main()
#include "catch_amalgamated.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <functional>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>


/**
 * A struct abaixo define uma ABB. Complete a estrutura
 */
template<typename T>
struct Arvore {
  // complete os dados aqui

  // recebe uma lista de valores em pre-ordem
  // precisa converter para uma arvore
  void inicia(std::list<T>& entrada){
    for (auto &e : entrada)
      insere_entrada(e);
  }

  // testa se a arvore esta vazia
  bool vazio(){
    return !raiz_;
  }

  // recebe uma lista (vazia) onde insere os elementos da arvore
  // em pos-ordem
  bool posOrdem(std::list<T>& saida){
    posOrdem(raiz_, saida);
    return true;
  }

  // libera a memoria da arvore
  void destroi(void){
    liberaArvore(raiz_);
  }
private:
  struct No_arvore {
    T dado;
    No_arvore *esq, *dir;
  };

  void insere_entrada(T dado) {
    No_arvore *no{ new No_arvore{dado, nullptr, nullptr} };
    raiz_ = insere_no(raiz_, no);
  }

  No_arvore *insere_no(No_arvore *raiz, No_arvore *no) {
    if (!raiz) return no;
    if (no->dado < raiz->dado) raiz->esq = insere_no(raiz->esq, no);
    else if (no->dado > raiz->dado) raiz->dir = insere_no(raiz->dir, no);
    else delete no; // Nós repetidos não são permitidos.
    return raiz;
  }

  void posOrdem(No_arvore *raiz, std::list<T>& saida) {
    if (raiz->esq) posOrdem(raiz->esq, saida);
    if (raiz->dir) posOrdem(raiz->dir, saida);
    if (raiz) saida.push_back(raiz->dado);
  }

  void liberaArvore(No_arvore *raiz) {
    if (raiz) {// Libera os nós da arvore em pós-ordem.
      liberaArvore(raiz->esq);
      liberaArvore(raiz->dir);
      delete raiz;
    }
  }

  No_arvore *raiz_{ nullptr };
};


TEST_CASE("Teste vazio") {
    Arvore<int> a;
    std::list<int> entrada {};
    a.inicia(entrada);
    REQUIRE(a.vazio() == true);
    a.destroi();
}

TEST_CASE("Teste nao vazio") {
    Arvore<int> a;
    std::list<int> entrada {1};
    a.inicia(entrada);
    REQUIRE(a.vazio() == false);
    a.destroi();
}

TEST_CASE("Caso 1") {
    Arvore<int> a;
    std::list<int> entrada {5, 3, 7};
    std::list<int> saida;
    std::list<int> resultado {3, 7, 5};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}

TEST_CASE("Caso 3") {
    Arvore<char> a;
    std::list<char> entrada {'F', 'C', 'A', 'D', 'J', 'H', 'I', 'K'};
    std::list<char> saida;
    std::list<char> resultado {'A', 'D', 'C', 'I', 'H', 'K', 'J', 'F'};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}

TEST_CASE("Caso N") {
    Arvore<int> a;
    std::list<int> entrada {50, 30, 24, 5, 28, 45, 98, 52, 60};
    std::list<int> saida;
    std::list<int> resultado {5, 28, 24, 45, 30, 60, 52, 98, 50};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}
