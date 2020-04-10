#include "global.h"
#include "dummyvector.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	DummyVector<int> *dv = new DummyVector<int>(5);
	delete dv;
	return 0;
}