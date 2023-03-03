/*!
稀疏矩阵测试Demo演示
 */

#include "test.h"


using namespace std;


int main(int argc, char** argv) {

    TestSparseMatrixConstructor();

    TestSparseMatrixCopyConstructor();

    // TestSparseMatrixInput();

    TestSparseMatrixTranspose();

    TestSparseMatrixFastTranspose();

    return 0;
}