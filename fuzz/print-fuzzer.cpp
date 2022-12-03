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
        int caseTarget = Data[0] % 8;
        switch (caseTarget) {
            case 0:
            {
                char* input = (char*) malloc(Size - 1);
                memcpy(input, Data + 1, Size - 1);
                input[Size - 2] = 0;
                pretty::Print(file) * input;
                free(input);
                break;
            }
            case 1:
            {
                if (Size > 1 + sizeof(int)) {
                    int* input = (int*) malloc((Size - 1));
                    memcpy(input, Data + 1, Size - 1);
                    pretty::Print(file) * input;
                    free(input);
                }
                break;
            }
            case 2: 
            {
                if (Size > 1 + sizeof(float)) {
                    float* input = (float*) malloc((Size - 1));
                    memcpy(input, Data + 1, Size - 1);
                    pretty::Print(file) * input[0];
                    free(input);
                }
                break;
            }
            case 3: 
            {
                if (Size > 1 + sizeof(double)) {
                    double* input = (double*) malloc((Size - 1));
                    memcpy(input, Data + 1, Size - 1);
                    pretty::Print(file) * input[0];
                    free(input);
                }
                break;
            }
            case 4: 
            {
                if (Size > 1 + sizeof(void*)) {
                    void* input = (void*) malloc((Size - 1));
                    memcpy(input, Data + 1, Size - 1);
                    pretty::Print(file) * input;
                    free(input);
                }
                break;
            }
            case 5: 
            {
                if (Size > 1 + sizeof(bool*)) {
                    bool* input = (bool*) malloc((Size - 1));
                    memcpy(input, Data + 1, Size - 1);
                    pretty::Print(file) * input[0];
                    free(input);
                }
                break;
            }
            case 6: 
            {
                if (Size > 1 + 2 * sizeof(char*)) {
                    char* input1 = (char*) malloc((Size - 1));
                    memcpy(input1, Data + 1, (Size - 1) / 2);
                    char* input2 = (char*) malloc((Size - 1));
                    memcpy(input2, Data + 1 + ((Size - 1) / 2), (Size - 1) / 2);
                    pretty::Print(file) * input1, input2;
                    free(input1);
                    free(input2);
                }
                break;
            }
            case 7: 
            {
                if (Size > 1 + sizeof(char*) + 4 * sizeof(int)) {
                    int* input1_a = (int*) malloc(4 * sizeof(int));
                    int input1[4];
                    memcpy(input1, input1_a, sizeof(input1));
                    char* input2 = (char*) malloc((Size - 1 - 4 * sizeof(int)));
                    memcpy(input2, Data + 1 + 4 * sizeof(int), (Size - 1 - 4 * sizeof(int)));
                    pretty::Print(file) * input1, input2;
                    free(input1_a);
                    free(input2);
                }
                break;
            }
        }
        
    }

    return 0;
}