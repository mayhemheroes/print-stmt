#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// #define PRETTYPRINT_NO_KEYWORD 1
#include "../print.h"

using namespace pretty;

FILE *file;
char buf[1024 * 8 * 4096];

void open_file() {
    file = fmemopen(buf, sizeof buf, "w");
    
    if (!file) {
        perror("fmemopen failed");
        exit(1);
    }
}

void clear_file() {
    rewind(file);
}

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv) {
    open_file();
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    clear_file();
    if (Size > 1) {
        int caseTarget = Data[0] % 4;
        switch (caseTarget) {
            case 0:
            {
                char* charInput = (char*) malloc(Size - 1);
                memcpy(charInput, Data + 1, Size - 1);
                charInput[Size - 2] = 0;
                pretty::Print(file) * charInput;
                free(charInput);
                break;
            }
            case 1:
            {
                if (Size > 1 + sizeof(int)) {
                    int* intArrayInput = (int*) malloc((Size - 1));
                    memcpy(intArrayInput, Data + 1, Size - 1);
                    pretty::Print(file) * intArrayInput;
                    free(intArrayInput);
                }
                break;
            }
            case 2: 
            {
                if (Size > 1 + sizeof(float)) {
                    float* floatInput = (float*) malloc((Size - 1));
                    memcpy(floatInput, Data + 1, Size - 1);
                    pretty::Print(file) * floatInput[0];
                    free(floatInput);
                }
                break;
            }
            case 3: 
            {
                if (Size > 1 + sizeof(double)) {
                    double* doubleInput = (double*) malloc((Size - 1));
                    memcpy(doubleInput, Data + 1, Size - 1);
                    pretty::Print(file) * doubleInput[0];
                    free(doubleInput);
                }
                break;
            }
            case 4: 
            {
                if (Size > 1 + sizeof(void*)) {
                    void* doubleInput = (void*) malloc((Size - 1));
                    memcpy(doubleInput, Data + 1, Size - 1);
                    pretty::Print(file) * doubleInput;
                    free(doubleInput);
                }
                break;
            }
        }
        
    }

    return 0;
}