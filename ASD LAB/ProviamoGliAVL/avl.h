#include <iostream>
#include <climits>

#ifndef AVL_H
#define AVL_H

namespace avl {

	struct avlNode;
	typedef avlNode* AVL;

	typedef int Elem;
	const AVL EmptyAvl = nullptr;
	const Elem emptyElem =  INT_MIN;

	void createEmpty(AVL&);
	void printAvl(const AVL&, int = 0);
	Elem search(const AVL&, const Elem);
	AVL insert(AVL&, const Elem);
	void deleteAvl(AVL&, const Elem);
};

#endif
