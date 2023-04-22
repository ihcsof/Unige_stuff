#include "avl.h"

using namespace avl;

struct avl::avlNode {
	Elem key;
	int h = 1;
	avlNode* sx = EmptyAvl;
	avlNode* dx = EmptyAvl;
};

int height(const AVL& a) {
	if(!a) return 0;
	return a->h;
}

int getBf(const AVL& a) {
	if(!a) return 0;
	return height(a->sx) - height(a->dx);
}

void avl::createEmpty(AVL& a) {
	a = EmptyAvl;
}

void avl::printAvl(const AVL& a, int n) {
	if(!a) return;
	printAvl(a->sx, n+1);
	std::cout << "Livello: " << n << " " << a->key << " Get: " << getBf(a) << std::endl;
	printAvl(a->dx, n+1);
}

Elem avl::search(const AVL& a, const Elem key) {
	if(!a) return emptyElem;
	if(key < a->key) return search(a->sx, key);
	if(key > a->key) return search(a->dx, key);
	return a->key;
}

AVL createNode(AVL& a, const Elem key) {
	a = new avlNode;
	a->key = key;
	return a;
}

// INSERT:

AVL rdx(AVL& a) {
	AVL left = a->sx;
	a->sx = left->dx;

	left->dx = a;
	a = left;

	a->dx->h = 1 + std::max(height(a->dx->sx), height(a->dx->dx));
	a->h = 1 + std::max(height(a->sx), height(a->dx));

	return a;
}

AVL rsx(AVL& a) {
	AVL right = a->dx;
	a->dx = right->sx;

	right->sx = a;
	a = right;

	a->sx->h = 1 + std::max(height(a->sx->sx), height(a->sx->dx));
	a->h = 1 + std::max(height(a->sx), height(a->dx));

	return a;
}

AVL avl::insert(AVL& a, const Elem k) {
	if(!a) return createNode(a, k);
	else if(k < a->key) insert(a->sx, k);
	else if(k > a->key) insert(a->dx, k);
	else return EmptyAvl;

	a->h = 1 + std::max(height(a->sx), height(a->dx));

	int bf = getBf(a);

	if(bf > 1)
		if(a->sx->key > k)
			rdx(a);
		else
			rsx(a->sx), rdx(a);
	else if(bf < -1)
		if(a->dx->key < k)
			rsx(a);
		else
			rdx(a->dx), rsx(a);

	return a;
}

Elem tergicristallo(AVL& a) {
	if(a->sx) return tergicristallo(a->sx);
	
	AVL aux = a;
	Elem toRet = a->key;
	a = a->dx;
	delete aux;
	return toRet;
}

AVL destroy(AVL& a) {
	if(a->sx && a->dx) {
		a->key = tergicristallo(a->dx);
		return a;
	}

	AVL aux = a;
	a = (a->sx) ? a->sx : a->dx;
	delete aux;
	return a;
}

void avl::deleteAvl(AVL& a, const Elem k) {
	AVL aux;
	if(!a) return;
	else if(k < a->key) deleteAvl(a->sx, k);
	else if(k > a->key) deleteAvl(a->dx, k);
	else { destroy(a); return; }

	//if(!aux) return EmptyAvl;

	a->h = 1 + std::max(height(a->sx), height(a->dx));

	int bf = getBf(a);

	if(bf > 1)
		if(getBf(a->sx) >= 0)
			rdx(a);
		else
			rsx(a->sx), rdx(a);
	else if(bf < -1)
		if(getBf(a->dx) <= 0)
			rsx(a);
		else
			rdx(a->dx), rsx(a);

	return;
}

