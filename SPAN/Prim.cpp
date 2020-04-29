#include "Prim.h"

using namespace std;

Prim::Prim()
{

}

Prim::~Prim()
{

}

Prim::node* Prim::minimum()
{
	return &heap[1];
}