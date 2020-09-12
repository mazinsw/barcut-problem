#include "Barra.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Barra::Barra(int comprimento)
{
	this->comprimento = comprimento;
}

int Barra::getComprimento()
{
	return comprimento;
}


