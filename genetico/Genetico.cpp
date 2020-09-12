#include "Genetico.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <sstream>

Genetico::Genetico(int qte_pecas, Barra* barra, int iteracoes)
{
	this->qte_pecas = qte_pecas;
	this->barra = barra;
	this->iteracoes = iteracoes;
	str_pecas = "";
	str_solucao = "";
	total_comprimento = 0;
}

void Genetico::execute()
{
	srand(time(NULL));
	gerarPecas();
	gerarPopulacaoInicial();
	calcularFuncaoObjetivo();
	montarRoletaViciada();
	//gravarPopulacaoInicial();
	selecionarPais();
	crossOver();

	for(int i = 0; i < iteracoes; i++)
	{
		calcularFuncaoObjetivo();
		montarRoletaViciada();
		selecionarPais();
		crossOver();
	}
	gravarSolucao();
	botao_executar->setEnabled(true);
	memo_pecas_geradas->setText(getStringPecas().c_str());
	memo_solucao->setText(getStringSolucao().c_str());
	if(getComprimentoSolucao() <= 100)
		MessageBox(handle, "A execução do algoritmo terminou.\nFoi obtida uma solução que respeita o comprimento da barra.", "Trabalho PO2", MB_ICONINFORMATION);
	else
		MessageBox(handle, "A execução do algoritmo terminou.\nFoi obtida uma solução que NÃO respeita o comprimento da barra.\nSugestão: aumentar a quantidade de gerações.", "Trabalho PO2", MB_ICONINFORMATION);
}

void Genetico::gerarPecas()
{
	//FILE * arq;
	//arq = fopen("Pecas.txt", "w+");
	//if(arq == NULL)
	//	exit(1);
	for(int i = 0; i < qte_pecas; i++)
	{

		int limite_inferior = 0.25 * barra->getComprimento();
		int limite_superior = 0.75 * barra->getComprimento();
		int v = rand() % (limite_superior - limite_inferior + 1) + limite_inferior;
		int c = rand() % (limite_superior - limite_inferior + 1) + limite_inferior;
		Peca * peca = new Peca(v, c);
		//	fprintf(arq, "%s %d, %s %d\n", "Valor:", v, "Comprimento:", c);
		str_pecas += "Peca " + int_to_str(i + 1) + " - " + "Valor: " + int_to_str(v) + ", Comprimento: " + int_to_str(c);
		str_pecas += "\r\n";
		vet_pecas.push_back(peca);
	}
	//fclose(arq);
}

void Genetico::gerarPopulacaoInicial()
{
	vet_individuos.clear();
	// utilizada população de 65 individuos de acordo com o artigo
	int i = 0;
	while(i < 65)
	{
		Individuo individuo;
		for(int j = 0; j < (int)vet_pecas.size(); j++)
		{
			int qte = rand() % (int)(barra->getComprimento() / vet_pecas[j]->getComprimento());
			individuo.addQuantidadePeca(qte);

		}
		vet_individuos.push_back(individuo);
		i++;
	}
}

// cálculo da função objetivo
void Genetico::calcularFuncaoObjetivo()
{
	bool tem_negativo = false;
	// percorro todos os indivíduos
	for(int i = 0; i < (int)vet_individuos.size(); i++)
	{
		std::vector<int> vet_individuo = vet_individuos[i].getVetorQuantidadePecas();
		int total_comprimento = 0;
		double e = 0;
		// saber o comprimento total de cada individuo
		// de acordo com a quantidade de peças e comprimento de cada peça
		for(int j = 0; j < (int)vet_individuo.size(); j++)
			total_comprimento += vet_individuo[j] * vet_pecas[j]->getComprimento();
		if(total_comprimento > barra->getComprimento())
			e = total_comprimento - barra->getComprimento();
		double aux_penalidade = pow(e / barra->getComprimento(), 1.0 / 3);
		int total_valor = 0;
		for(int j = 0; j < (int)vet_individuo.size(); j++)
			total_valor += vet_individuo[j] * vet_pecas[j]->getValor();
		double penalidade = aux_penalidade * total_valor;
		int avaliacao = total_valor - penalidade;
		if(avaliacao <= 0)
			tem_negativo = true;
		vet_individuos[i].setFuncaoObjetivo(avaliacao);
	}
	if(tem_negativo)
	{
		int menor = vet_individuos[0].getFuncaoObjetivo();
		for(int i = 1; i < (int)vet_individuos.size(); i++)
		{
			if(vet_individuos[i].getFuncaoObjetivo() < menor)
				menor = vet_individuos[i].getFuncaoObjetivo();
		}
		/*
		se tem avaliação negativa, então a função de avaliação
		tem que ser calculada de modo que seja somada a uma constante
		maior que o maior valor negativo
		*/
		int constante = (-1) * menor + 1;
		for(int i = 0; i < (int)vet_individuos.size(); i++)
		{
			int valor_objetivo = vet_individuos[i].getFuncaoObjetivo();
			vet_individuos[i].setFuncaoObjetivo(valor_objetivo + constante);
		}
	}
}

// monta a roleta viciada
void Genetico::montarRoletaViciada()
{
	// ordena crescentemente pelo valor da função objetivo
	std::sort(vet_individuos.begin(), vet_individuos.end(), CompFuncaoObjetivo());
	int soma_total = 0;
	// obtém a soma dos valores da funcao objetivo de todos os individuos
	for(int i = 0; i < (int)vet_individuos.size(); i++)
		soma_total += vet_individuos[i].getFuncaoObjetivo();
	soma_avaliacao = soma_total;
	int anterior = 0;
	for(int i = 0; i < (int)vet_individuos.size(); i++)
	{
		int valor = vet_individuos[i].getFuncaoObjetivo();
		vet_individuos[i].setLimiteInferior(anterior);
		vet_individuos[i].setLimiteSuperior(anterior + valor);
		anterior = anterior + valor + 1;
	}
}

// funcao que seleciona os individuos que irão participar do processo reprodutório
void Genetico::selecionarPais()
{
	vet_pais.clear();
	int k = 0;
	while(k < 65)
	{
		int num = rand() % (soma_avaliacao + 1);
		for(int i = 0; i < (int)vet_individuos.size(); i++)
		{
			if(num >= vet_individuos[i].getLimiteInferior() && num <= vet_individuos[i].getLimiteSuperior())
			{
				vet_pais.push_back(vet_individuos[i]);
				k++;
				break;
			}
		}
	}
}

// função que aplica crossover de único ponto
void Genetico::crossOver()
{
	// reprodução elitista, os 15% passam inalteráveis
	int limite = 65 * 0.1;
	// aplica recombinação e mutação somente para 85% dos individuos
	for(int i = 0; i < (65 - limite); i += 2)
	{
		if(i == 64)
			break;
		// aplica a recombinação (crossover de um ponto)
		// sorteia um ponto de corte
		int corte = rand() % qte_pecas + 1;
		std::vector<int> individuo1 = vet_pais[i].getVetorQuantidadePecas();
		std::vector<int> individuo2 = vet_pais[i + 1].getVetorQuantidadePecas();
		std::vector<int> filho1, filho2;
		// gerando o primeiro filho
		for(int j = 0; j < corte; j++)
			filho1.push_back(individuo1[j]);
		for(int j = corte; j < qte_pecas; j++)
			filho1.push_back(individuo2[j]);
		// gerando o segundo filho
		for(int j = 0; j < corte; j++)
			filho2.push_back(individuo2[j]);
		for(int j = corte; j < qte_pecas; j++)
			filho2.push_back(individuo1[j]);

		// aplica a mutação por gene no filho1
		for(int j = 0; j < (int)filho1.size(); j++)
		{
			int mut = rand() % 1000 + 1;
			if(mut == 10)
			{
				int gene = rand() % (int)(barra->getComprimento() / vet_pecas[j]->getComprimento());
				filho1[j] = gene;
			}
		}

		// aplica a mutação por gene no filho2
		for(int j = 0; j < (int)filho2.size(); j++)
		{
			int mut = rand() % 1000 + 1;
			if(mut == 10)
			{
				int gene = rand() % (int)(barra->getComprimento() / vet_pecas[j]->getComprimento());
				filho2[j] = gene;
			}
		}

		for(int j = 0; j < qte_pecas; j++)
			vet_individuos[i].setPeca(j, filho1[j]);
		for(int j = 0; j < qte_pecas; j++)
			vet_individuos[i + 1].setPeca(j, filho2[j]);
	}
}

std::vector<Individuo> Genetico::getIndividuos()
{
	return vet_individuos;
}

void Genetico::gravarPopulacaoInicial()
{
	FILE * arq;
	arq = fopen("Populacao_Inicial.txt", "w+");
	if(arq == NULL)
		exit(1);
	for(int i = 0; i < (int)vet_individuos.size(); i++)
	{
		std::vector<int> vet_individuo = vet_individuos[i].getVetorQuantidadePecas();
		fprintf(arq, "%s %d%s", "Individuo", i + 1, ": ");
		for(int j = 0; j < (int)vet_individuo.size(); j++)
			fprintf(arq, "%d ", vet_individuo[j]);
		fprintf(arq, "%s %d ", "Valor de avaliacao:", vet_individuos[i].getFuncaoObjetivo());
		fprintf(arq, "%s %s%d%s%d%s", "Roleta:", "[", vet_individuos[i].getLimiteInferior(), ",", vet_individuos[i].getLimiteSuperior(), "]");
		fprintf(arq, "%s", "\n");
	}
	fclose(arq);
}

void Genetico::gravarSolucao()
{
	//FILE * arq;
	//arq = fopen("Solucao.txt", "w+");
	//if(arq == NULL)
	//	exit(1);
	std::vector<int> vet_individuo = vet_individuos[64].getVetorQuantidadePecas();
	for(int i = 0; i < (int)vet_individuo.size(); i++)
	{
		if(vet_individuo[i] != 0)
		{
			//fprintf(arq, "%s %d %s %s %d %s %d %s %d", "Peca ", i + 1, " - ", "Quantidade:", vet_individuo[i], "Valor:", vet_pecas[i]->getValor(), "Comprimento:", vet_pecas[i]->getComprimento());
			//fprintf(arq, "%s", "\n");
			total_comprimento += vet_pecas[i]->getComprimento();
			str_solucao += "Peca " + int_to_str(i + 1) + " - " + "Quantidade: " + int_to_str(vet_individuo[i]) + ", Valor: " + int_to_str(vet_pecas[i]->getValor()) + ", Comprimento: " + int_to_str(vet_pecas[i]->getComprimento());
			str_solucao += "\r\n";
		}
	}
	//fclose(arq);
}

std::string Genetico::getStringPecas()
{
	return str_pecas;
}

std::string Genetico::getStringSolucao()
{
	return str_solucao;
}

std::string Genetico::int_to_str(int num)
{
	std::ostringstream ss;
	ss << num;
	return ss.str();
}

int Genetico::getComprimentoSolucao()
{
	return total_comprimento;
}

void Genetico::setComponents(HWND handle, Memo* memo_pecas_geradas, Memo* memo_solucao, Button* botao_executar)
{
	this->handle = handle;
	this->memo_pecas_geradas = memo_pecas_geradas;
	this->memo_solucao = memo_solucao;
	this->botao_executar = botao_executar;
}


