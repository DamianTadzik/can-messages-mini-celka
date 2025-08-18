#include "mex.h"
#include "../src/cmmc.h"
#include <stdint.h>
#include <string.h>


int decode_frame(const uint32_t id, const uint8_t data[8],
                 const char ***signal_names_ptr,
                 double **signal_values_ptr,
                 size_t *nsignals_ptr,
                 const char **frame_name_ptr)
{
    /* Check if pointers are pointing to some data */
    if (!signal_names_ptr || !signal_values_ptr || !nsignals_ptr || !frame_name_ptr)
        return -1;

    switch(id)
    {
        case CMMC_TOF_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_tof_t tmp;   // temporary structure
                if (cmmc_tof_unpack(&tmp, data, CMMC_TOF_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[5]; 
                static const char *signal_names[5] = {
                    CMMC_TOF_RANGE_MM_NAME,
                    CMMC_TOF_SIGNAL_RATE_MCPS_NAME,
                    CMMC_TOF_ERROR_STATUS_NAME,
                    CMMC_TOF_RTN_AMBIENT_RATE_NAME,
                    CMMC_TOF_RTN_RATE_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_tof_range_mm_decode(tmp.range_mm);
                signal_values[1] = (double)cmmc_tof_signal_rate_mcps_decode(tmp.signal_rate_mcps);
                signal_values[2] = (double)cmmc_tof_error_status_decode(tmp.error_status);
                signal_values[3] = (double)cmmc_tof_rtn_ambient_rate_decode(tmp.rtn_ambient_rate);
                signal_values[4] = (double)cmmc_tof_rtn_rate_decode(tmp.rtn_rate);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 5;
                *frame_name_ptr = CMMC_TOF_NAME;
                return 0;
            }
        case CMMC_SERVO_POSITION_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_servo_position_t tmp;   // temporary structure
                if (cmmc_servo_position_unpack(&tmp, data, CMMC_SERVO_POSITION_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[3]; 
                static const char *signal_names[3] = {
                    CMMC_SERVO_POSITION_SETPOINT_NAME,
                    CMMC_SERVO_POSITION_ADC_RAW_NAME,
                    CMMC_SERVO_POSITION_ADC_VOLTAGE_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_servo_position_setpoint_decode(tmp.setpoint);
                signal_values[1] = (double)cmmc_servo_position_adc_raw_decode(tmp.adc_raw);
                signal_values[2] = (double)cmmc_servo_position_adc_voltage_decode(tmp.adc_voltage);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 3;
                *frame_name_ptr = CMMC_SERVO_POSITION_NAME;
                return 0;
            }
        case CMMC_DUMMY_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_dummy_t tmp;   // temporary structure
                if (cmmc_dummy_unpack(&tmp, data, CMMC_DUMMY_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[3]; 
                static const char *signal_names[3] = {
                    CMMC_DUMMY_DUMMY1_NAME,
                    CMMC_DUMMY_DUMMY2_NAME,
                    CMMC_DUMMY_DUMMYF_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_dummy_dummy1_decode(tmp.dummy1);
                signal_values[1] = (double)cmmc_dummy_dummy2_decode(tmp.dummy2);
                signal_values[2] = (double)cmmc_dummy_dummyf_decode(tmp.dummyf);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 3;
                *frame_name_ptr = CMMC_DUMMY_NAME;
                return 0;
            }

        default:
            return 1; // ID not known
    }
}


/* Main can_decoder MEX function */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    /* Check number of input arguments */
    if (nrhs != 2) 
    {
        mexErrMsgIdAndTxt("can_decoder:args:numberOfArgs",
                          "Usage: decode_can_mex(ID, Data[1x8])");
    }
    /* Check first input argument type and size */
    if (!mxIsUint32(prhs[0]) || mxGetNumberOfElements(prhs[0]) != 1) 
    {
        mexErrMsgIdAndTxt("can_decoder:args:typeOfArgs",
                          "First argument (ID) must be uint32[1x1] type and size!");
    }
    /* Check second input argument type and size */
    if (!mxIsUint8(prhs[1]) || mxGetNumberOfElements(prhs[1]) != 8 || 
        mxGetM(prhs[1]) != 1 || mxGetN(prhs[1]) != 8) 
    {
        mexErrMsgIdAndTxt("can_decoder:args:typeOfArgs",
                          "Second argument (Data) must be uint8[1x8] type and size!");
    }
   
    /* Check number of output arguments */
    if (nlhs > 1)
    {
        mexErrMsgIdAndTxt("can_decoder:args:numberOfArgs",
                          "Number of outputs must be 1!");
    }

    /* Get input arguments */
    uint32_t id = *(uint32_t *)mxGetData(prhs[0]);
    uint8_t data[8];
    memcpy(data, mxGetData(prhs[1]), 8);

    /* Call the C decoding function with pointers to receive output */
    const char **signal_names = NULL;
    double *signal_values = NULL;
    size_t nsignals = 0;
    const char *frame_name = NULL;

    /* Call the decoder */
    int decode_res = decode_frame(id, data, &signal_names, &signal_values, &nsignals, &frame_name);

    /* Check if decoding was successful (non-zero means failure) */
    if (decode_res > 0) 
    {
        mexErrMsgIdAndTxt("can_decoder:decoder:unsupported_id", "Decoding failed: unknown or unsupported CAN frame ID.");
    }

    /* Verify that all output pointers are valid and that at least one signal was decoded */
    if (!signal_names || !signal_values || !frame_name || nsignals == 0 || decode_res < 0)
    {
        mexErrMsgIdAndTxt("can_decoder:decoder:invalid_output", "Decoder returned invalid or incomplete data pointers.");
    }

    /* Create the signals_struct */
    mxArray *signals_struct = mxCreateStructMatrix(1, 1, (int)nsignals, signal_names);
    /* Populate the signals_struct with values corresponding to the names */
    for (size_t i = 0; i < nsignals; i++) 
    {
        mxArray *val = mxCreateDoubleScalar(signal_values[i]);
        mxSetField(signals_struct, 0, signal_names[i], val);
    }

    /* Create the out_struct with two fields */
    const char *field_names[] = {"frame", "signals"};
    mxArray *out_struct = mxCreateStructMatrix(1, 1, 2, field_names);

    /* Populate the out_struct with data */
    mxSetField(out_struct, 0, "frame", mxCreateString(frame_name));
    mxSetField(out_struct, 0, "signals", signals_struct);
    
    /* Assign structure to the output */
    plhs[0] = out_struct;
}
