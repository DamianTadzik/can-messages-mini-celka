#include "mex.h"
#include "cmmc.h"
#include <stdint.h>
#include <string.h>


int decode_frame(const uint32_t id, const uint8_t *data, void *ret)
{
    switch (id)
    {
        case example_id:
            
            
            return 0;
        default: // nieznany ID
            // todo
            return -1; 
    }
}


// Główna funkcja MEX
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    // Sprawdzenie argumentów wejściowych
    if (nrhs != 2) {
        mexErrMsgIdAndTxt("decode_can_mex:args",
                          "Użycie: decode_can_mex(ID, Data[1x8])");
    }
    if (!mxIsUint32(prhs[0]) || mxGetNumberOfElements(prhs[0]) != 1) {
        mexErrMsgIdAndTxt("decode_can_mex:type",
                          "Pierwszy argument musi być uint32 (ID)");
    }
    if (!mxIsUint8(prhs[1]) || mxGetNumberOfElements(prhs[1]) != 8) {
        mexErrMsgIdAndTxt("decode_can_mex:type",
                          "Drugi argument musi być uint8[1x8]");
    }
    
    // Sprawdzenie argumentów wyjściowych
    

    // Pobranie argumentów wejściowych
    uint32_t id = *(uint32_t *)mxGetData(prhs[0]);
    uint8_t data[8];
    memcpy(data, mxGetData(prhs[1]), 8);
    
}