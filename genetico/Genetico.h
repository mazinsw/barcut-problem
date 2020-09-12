#ifndef __GENETICO_H__
#define __GENETICO_H__
#include <vector>
#include <string>
#include <windows.h>
#include "Barra.h"
#include "Peca.h"
#include "Individuo.h"
#include "../gui/thread.h"
#include "../gui/button.h"
#include "../gui/memo.h"

class Genetico: public Thread
{
private:
	Barra * barra;
	int qte_pecas;
	int soma_avaliacao;
	int iteracoes;
	int total_comprimento;
	std::vector<Peca*> vet_pecas;
	std::vector<Individuo> vet_individuos;
	std::vector<Individuo> vet_pais;
	std::string str_pecas;
	std::string str_solucao;
	Memo * memo_pecas_geradas;
	Memo * memo_solucao;
	Button * botao_executar;
	HWND handle;
public:
	Genetico(int qte_pecas, Barra * barra, int iteracoes);
	void gerarPecas();
	void gerarPopulacaoInicial();
	void gravarPopulacaoInicial();
	void gravarSolucao();
	void calcularFuncaoObjetivo();
	void montarRoletaViciada();
	void selecionarPais();
	void crossOver();
	void execute();
	void setComponents(HWND handle, Memo * memo_pecas_geradas, Memo * memo_solucao, Button * botao_executar);
	std::vector<Individuo> getIndividuos();
	std::string getStringPecas();
	std::string getStringSolucao();
	std::string int_to_str(int num);
	int getComprimentoSolucao();
protected:
	void run()
	{
		execute();
	}
};

class CompFuncaoObjetivo
{
public:
	bool operator()(Individuo a, Individuo b)
	{
		return a.getFuncaoObjetivo() < b.getFuncaoObjetivo();
	}
};

#endif
