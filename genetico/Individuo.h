#ifndef __INDIVIDUO_H__
#define __INDIVIDUO_H__
#include <vector>
#include "Peca.h"

class Individuo
{
private:
	std::vector<int> qte_pecas;
	int valor_objetivo;
	int limite_inferior;
	int limite_superior;
public:
	void addQuantidadePeca(int quantidade);
	void setPeca(int pos, int valor);
	void setFuncaoObjetivo(int valor);
	void setLimiteInferior(int limite_inferior);
	void setLimiteSuperior(int limite_superior);
	void limparVetor();
	int getLimiteInferior();
	int getLimiteSuperior();
	int getFuncaoObjetivo();
	std::vector<int> getVetorQuantidadePecas();
};
#endif