#include "Peca.h"

Peca::Peca(int valor, int comprimento)
{
	this->valor = valor;
	this->comprimento = comprimento;
	densidade = (double)valor / comprimento;
}

void Peca::setValor(int valor)
{
	this->valor = valor;
}

int Peca::getValor()
{
	return valor;
}

void Peca::setComprimento(int comprimento)
{
	this->comprimento = comprimento;
}

int Peca::getComprimento()
{
	return comprimento;
}

double Peca::getDensidade()
{
	return densidade;
}