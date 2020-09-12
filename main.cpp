#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gui/win.h"
#include "genetico/Barra.h"
#include "genetico/Genetico.h"

class MyWindow: public Window, ClickEvent
{
private:
	Label label_titulo;
	Label label_algoritmo;
	Label label_pecas;
	Label label_solucao;
	Label label_qte_pecas;
	Label label_iteracoes;
	Memo memo_pecas_geradas;
	Memo memo_solucao;
	Edit edit_qte_pecas;
	Edit edit_iteracoes;
	Panel * painel_principal;
	Button botao_executar;
	Font * fonte_titulo;
	Font * fonte_media;
	Font * fonte_botao;
public:
	MyWindow()
	{
		//srand(time(NULL));

		create("MinhaClasse", 800, 600, "Trabalho PO2 - Problema do Corte de Barras", NULL);
		setButtonEnabled(BUTTON_MAXIMIZE, false);
		setResizable(false);

		painel_principal = new Panel();
		painel_principal->create(0, 0, getClientWidth(), getClientHeight(), this);

		fonte_titulo = new Font(this, "Times New Roman", 22);
		fonte_media = new Font(this, "Times New Roman", 14);
		fonte_botao = new Font(this, "Arial", 13);

		label_titulo.create(240, 20, 100, 21,
							"Problema do Corte de Barras", painel_principal);
		label_titulo.setFont(fonte_titulo);
		label_titulo.show();

		label_algoritmo.create(235, 65, 100, 21,
							   "Algoritmo Genético - Tamanho da barra: 100", painel_principal);
		label_algoritmo.setFont(fonte_media);
		label_algoritmo.show();

		label_qte_pecas.create(270, 100, 100, 21,
							   "Quantidade de Peças:", painel_principal);
		label_qte_pecas.setFont(fonte_botao);
		label_qte_pecas.show();

		edit_qte_pecas.create(440, 100,
							  50, 21, "", painel_principal);
		edit_qte_pecas.setFocus();

		label_iteracoes.create(250, 130, 100, 21,
							   "Quantidade de gerações:", painel_principal);
		label_iteracoes.setFont(fonte_botao);
		label_iteracoes.show();

		edit_iteracoes.create(440, 130,
							  50, 21, "", painel_principal);

		botao_executar.create(345, 160,
							  100, 30, "Executar", painel_principal);
		botao_executar.setFont(fonte_botao);
		botao_executar.addClickEvent(this);

		label_pecas.create(340, 205, 100, 21,
						   "Peças Geradas:", painel_principal);
		label_pecas.setFont(fonte_media);
		label_pecas.show();

		memo_pecas_geradas.create(260, 240, 280, 125,
								  "", painel_principal);
		memo_pecas_geradas.getFont().setSize(10);
		memo_pecas_geradas.setReadOnly(true);

		label_solucao.create(320, 380, 100, 21,
							 "Solução Encontrada:", painel_principal);
		label_solucao.setFont(fonte_media);
		label_solucao.show();

		memo_solucao.create(220, 420, 350, 125,
							"", painel_principal);
		memo_solucao.getFont().setSize(10);
		memo_solucao.setReadOnly(true);

		show();
	}
	~MyWindow()
	{
		delete fonte_botao;
		delete fonte_media;
		delete fonte_titulo;
		delete painel_principal;
	}

	void click(Object & sender)
	{
		String str_pecas = edit_qte_pecas.getText();
		if(str_pecas == "")
		{
			memo_pecas_geradas.clear();
			memo_solucao.clear();
			messageBox("Digite a quantidade de peças!", "Trabalho PO2", MB_ICONINFORMATION);
			edit_qte_pecas.setFocus();
			return;
		}
		bool somente_numeros = true;
		for(int i = 0; i < (int)str_pecas.size(); i++)
		{
			if(!(str_pecas[i] >= '0' && str_pecas[i] <= '9'))
			{
				somente_numeros = false;
				break;
			}
		}
		if(somente_numeros == false)
		{
			memo_pecas_geradas.clear();
			memo_solucao.clear();
			messageBox("Digite somente números na quantidade de peças!", "Trabalho PO2", MB_ICONINFORMATION);
			edit_qte_pecas.setFocus();
			return;
		}
		String str_iteracoes = edit_iteracoes.getText();
		if(str_iteracoes == "")
		{
			memo_pecas_geradas.clear();
			memo_solucao.clear();
			messageBox("Digite a quantidade de gerações!", "Trabalho PO2", MB_ICONINFORMATION);
			edit_iteracoes.setFocus();
			return;
		}
		somente_numeros = true;
		for(int i = 0; i < (int)str_iteracoes.size(); i++)
		{
			if(!(str_iteracoes[i] >= '0' && str_iteracoes[i] <= '9'))
			{
				somente_numeros = false;
				break;
			}
		}
		if(somente_numeros == false)
		{
			memo_pecas_geradas.clear();
			memo_solucao.clear();
			messageBox("Digite somente números na quantidade de gerações!", "Trabalho PO2", MB_ICONINFORMATION);
			edit_iteracoes.setFocus();
			return;
		}

		// transformando para int a string str_pecas
		int tam = str_pecas.size();
		int qte_pecas = 0;
		for(int i = 0; i < tam; i++)
			qte_pecas = (qte_pecas * 10 + str_pecas[i] - '0');

		// transformando para int a string str_iteracoes
		tam = str_iteracoes.size();
		int qte_iteracoes = 0;
		for(int i = 0; i < tam; i++)
			qte_iteracoes = (qte_iteracoes * 10 + str_iteracoes[i] - '0');
		
		Genetico * genetico = new Genetico(qte_pecas, new Barra(100), qte_iteracoes);
		genetico->setComponents(getHandle(), &memo_pecas_geradas, &memo_solucao, &botao_executar);
		botao_executar.setEnabled(false);
		messageBox("Essa operação pode demorar algum tempo...\nO botão Executar ficará desabilitado até o término da operação.", "Trabalho PO2", MB_ICONINFORMATION);
		genetico->start();
	}

	void dblClick(Object & sender)
	{

	}
};

int main(int argc, char *argv[])
{
	MyWindow my;

	return my.run();
}
