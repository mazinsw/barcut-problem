#include "Individuo.h"

void Individuo::addQuantidadePeca(int quantidade)
{
	qte_pecas.push_back(quantidade);
}

std::vector<int> Individuo::getVetorQuantidadePecas()
{
	return qte_pecas;
}

void Individuo::setFuncaoObjetivo(int valor)
{
	valor_objetivo = valor;
}

int Individuo::getFuncaoObjetivo()
{
	return valor_objetivo;
}

void Individuo::setLimiteInferior(int limite_inferior)
{
	this->limite_inferior = limite_inferior;
}

void Individuo::setLimiteSuperior(int limite_superior)
{
	this->limite_superior = limite_superior;
}

int Individuo::getLimiteInferior()
{
	return limite_inferior;
}

int Individuo::getLimiteSuperior()
{
	return limite_superior;
}

void Individuo::limparVetor()
{
	qte_pecas.clear();
}

void Individuo::setPeca(int pos, int valor)
{
	qte_pecas[pos] = valor;
}