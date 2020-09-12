#ifndef __PECA_H__
#define __PECA_H__
#include <string>

class Peca
{
private:
	int comprimento;
	int valor;
	double densidade;
	double penalidade;
public:
	Peca(int valor, int comprimento);
	void setValor(int valor);
	int getValor();
	void setComprimento(int comprimento);
	int getComprimento();
	double getDensidade();
};

#endif
