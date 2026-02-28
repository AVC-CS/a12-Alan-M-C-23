#include <iostream>
#include <cstdlib>  // for malloc
using namespace std;

// T2: 2 initialized global variables (DATA segment)
int globalVar = 100;
int globalVar2 = 200;

// T2: 2 uninitialized global variables (BSS segment)
int uninitGlobal;
int uninitGlobal2;

void checkStack(int* parentAddr) {
    int childVar = 0;
    // T1 & T3: Label "STACK" and address comparison
    cout << "--- STACK SEGMENT (Cross-function comparison) ---" << endl;
    cout << "main local addr (parent frame): " << (void*)parentAddr << endl;
    cout << "param addr (child frame)      : " << (void*)&parentAddr << endl;
    cout << "child local addr (child frame): " << (void*)&childVar << endl;
    
    // T3: This logic proves stack grows down (higher address to lower)
    if (parentAddr > &childVar) {
        cout << "Stack grows: DOWN! (parent frame > child frame)" << endl;
    } else {
        cout << "Stack grows: UP" << endl;
    }
    cout << endl;
}

int main() {
    // T3: Local variable to pass to checkStack
    int mainVar = 10;

    // T4: Allocate 2 heap variables (large sizes ensure separation)
    char* heapVar1 = (char*)malloc(1024);
    char* heapVar2 = (char*)malloc(1024);

    cout << "=== MEMORY SEGMENT BOUNDARIES ===" << endl;
    cout << endl;

    // T2: Print TEXT segment (2 function addresses)
    cout << "--- TEXT SEGMENT (Code) ---" << endl;
    cout << "Address of main()       : " << (void*)&main << endl;
    cout << "Address of checkStack() : " << (void*)&checkStack << endl;
    cout << endl;

    // T2: Print DATA segment
    cout << "--- DATA SEGMENT (Initialized Globals) ---" << endl;
    cout << "globalVar addr  : " << (void*)&globalVar << " value: " << globalVar << endl;
    cout << "globalVar2 addr : " << (void*)&globalVar2 << " value: " << globalVar2 << endl;
    cout << endl;

    // T2: Print BSS segment
    cout << "--- BSS SEGMENT (Uninitialized Globals) ---" << endl;
    cout << "uninitGlobal addr : " << (void*)&uninitGlobal << endl;
    cout << "uninitGlobal2 addr: " << (void*)&uninitGlobal2 << endl;
    cout << endl;

    // T3: Trigger the stack check
    checkStack(&mainVar);

    // T4: Print HEAP segment (2 addresses + comparison)
    cout << "--- HEAP SEGMENT (Dynamic Allocation) ---" << endl;
    cout << "heapVar1 addr : " << (void*)heapVar1 << endl;
    cout << "heapVar2 addr : " << (void*)heapVar2 << endl;
    if (heapVar2 > heapVar1) {
        cout << "Heap grows: UP (lower to higher)" << endl;
    } else {
        cout << "Heap grows: DOWN" << endl;
    }
    cout << endl;

    cout << "=== RELATIVE POSITION SUMMARY ===" << endl;
    cout << "TEXT (lowest) : " << (void*)&main << endl;
    cout << "DATA          : " << (void*)&globalVar << endl;
    cout << "BSS           : " << (void*)&uninitGlobal << endl;
    cout << "HEAP          : " << (void*)heapVar1 << endl;
    cout << "STACK (highest): " << (void*)&mainVar << endl;

    free(heapVar1);
    free(heapVar2);
    return 0;
}