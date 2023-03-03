

#include "huffman_tree.h"

int main() {
	double w[] = { 2,4,6,1,10 };
	int n = sizeof(w) / sizeof(w[0]);

	HuffmanTree<int> htree(w, n);

	htree.showTree();

	return 0;
}
