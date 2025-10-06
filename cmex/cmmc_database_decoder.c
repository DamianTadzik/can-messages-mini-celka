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
        case CMMC_ODRIVE_HEARTBEAT_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_odrive_heartbeat_t tmp;   // temporary structure
                if (cmmc_odrive_heartbeat_unpack(&tmp, data, CMMC_ODRIVE_HEARTBEAT_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[3]; 
                static const char *signal_names[3] = {
                    CMMC_ODRIVE_HEARTBEAT_AXIS_ERROR_NAME,
                    CMMC_ODRIVE_HEARTBEAT_AXIS_CURRENT_STATE_NAME,
                    CMMC_ODRIVE_HEARTBEAT_CONTROLLER_STATUS_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_odrive_heartbeat_axis_error_decode(tmp.axis_error);
                signal_values[1] = (double)cmmc_odrive_heartbeat_axis_current_state_decode(tmp.axis_current_state);
                signal_values[2] = (double)cmmc_odrive_heartbeat_controller_status_decode(tmp.controller_status);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 3;
                *frame_name_ptr = CMMC_ODRIVE_HEARTBEAT_NAME;
                return 0;
            }
        case CMMC_ODRIVE_SET_REQUESTED_STATE_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_odrive_set_requested_state_t tmp;   // temporary structure
                if (cmmc_odrive_set_requested_state_unpack(&tmp, data, CMMC_ODRIVE_SET_REQUESTED_STATE_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[1]; 
                static const char *signal_names[1] = {
                    CMMC_ODRIVE_SET_REQUESTED_STATE_AXIS_REQUESTED_STATE_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_odrive_set_requested_state_axis_requested_state_decode(tmp.axis_requested_state);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 1;
                *frame_name_ptr = CMMC_ODRIVE_SET_REQUESTED_STATE_NAME;
                return 0;
            }
        case CMMC_ODRIVE_ENCODER_ESTIMATES_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_odrive_encoder_estimates_t tmp;   // temporary structure
                if (cmmc_odrive_encoder_estimates_unpack(&tmp, data, CMMC_ODRIVE_ENCODER_ESTIMATES_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[2]; 
                static const char *signal_names[2] = {
                    CMMC_ODRIVE_ENCODER_ESTIMATES_ENCODER_POS_ESTIMATE_NAME,
                    CMMC_ODRIVE_ENCODER_ESTIMATES_ENCODER_VEL_ESTIMATE_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_odrive_encoder_estimates_encoder_pos_estimate_decode(tmp.encoder_pos_estimate);
                signal_values[1] = (double)cmmc_odrive_encoder_estimates_encoder_vel_estimate_decode(tmp.encoder_vel_estimate);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 2;
                *frame_name_ptr = CMMC_ODRIVE_ENCODER_ESTIMATES_NAME;
                return 0;
            }
        case CMMC_ODRIVE_SET_INPUT_VEL_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_odrive_set_input_vel_t tmp;   // temporary structure
                if (cmmc_odrive_set_input_vel_unpack(&tmp, data, CMMC_ODRIVE_SET_INPUT_VEL_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[2]; 
                static const char *signal_names[2] = {
                    CMMC_ODRIVE_SET_INPUT_VEL_INPUT_VEL_NAME,
                    CMMC_ODRIVE_SET_INPUT_VEL_TORQUE_FF_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_odrive_set_input_vel_input_vel_decode(tmp.input_vel);
                signal_values[1] = (double)cmmc_odrive_set_input_vel_torque_ff_decode(tmp.torque_ff);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 2;
                *frame_name_ptr = CMMC_ODRIVE_SET_INPUT_VEL_NAME;
                return 0;
            }
        case CMMC_ODRIVE_GET_SENSORLESS_ESTIMATES_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_odrive_get_sensorless_estimates_t tmp;   // temporary structure
                if (cmmc_odrive_get_sensorless_estimates_unpack(&tmp, data, CMMC_ODRIVE_GET_SENSORLESS_ESTIMATES_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[2]; 
                static const char *signal_names[2] = {
                    CMMC_ODRIVE_GET_SENSORLESS_ESTIMATES_SENSORLESS_POS_ESTIMATE_NAME,
                    CMMC_ODRIVE_GET_SENSORLESS_ESTIMATES_SENSORLESS_VEL_ESTIMATE_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_odrive_get_sensorless_estimates_sensorless_pos_estimate_decode(tmp.sensorless_pos_estimate);
                signal_values[1] = (double)cmmc_odrive_get_sensorless_estimates_sensorless_vel_estimate_decode(tmp.sensorless_vel_estimate);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 2;
                *frame_name_ptr = CMMC_ODRIVE_GET_SENSORLESS_ESTIMATES_NAME;
                return 0;
            }
        case CMMC_ODRIVE_GET_VBUS_VOLTAGE_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_odrive_get_vbus_voltage_t tmp;   // temporary structure
                if (cmmc_odrive_get_vbus_voltage_unpack(&tmp, data, CMMC_ODRIVE_GET_VBUS_VOLTAGE_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[1]; 
                static const char *signal_names[1] = {
                    CMMC_ODRIVE_GET_VBUS_VOLTAGE_VBUS_VOLTAGE_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_odrive_get_vbus_voltage_vbus_voltage_decode(tmp.vbus_voltage);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 1;
                *frame_name_ptr = CMMC_ODRIVE_GET_VBUS_VOLTAGE_NAME;
                return 0;
            }
        case CMMC_ODRIVE_CLEAR_ERRORS_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_odrive_clear_errors_t tmp;   // temporary structure
                if (cmmc_odrive_clear_errors_unpack(&tmp, data, CMMC_ODRIVE_CLEAR_ERRORS_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[0]; 
                static const char *signal_names[0] = {
        
                };
        
                /* Decode all single signals */
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 0;
                *frame_name_ptr = CMMC_ODRIVE_CLEAR_ERRORS_NAME;
                return 0;
            }
        case CMMC_RADIO_CONTROL_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_radio_control_t tmp;   // temporary structure
                if (cmmc_radio_control_unpack(&tmp, data, CMMC_RADIO_CONTROL_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[8]; 
                static const char *signal_names[8] = {
                    CMMC_RADIO_CONTROL_THROTTLE_NAME,
                    CMMC_RADIO_CONTROL_STEERING_NAME,
                    CMMC_RADIO_CONTROL_FRONT_PITCH_NAME,
                    CMMC_RADIO_CONTROL_FRONT_ROLL_NAME,
                    CMMC_RADIO_CONTROL_REAR_PITCH_NAME,
                    CMMC_RADIO_CONTROL_FREE_BITS_NAME,
                    CMMC_RADIO_CONTROL_ARM_SWITCH_NAME,
                    CMMC_RADIO_CONTROL_MODE_SWITCH_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_radio_control_throttle_decode(tmp.throttle);
                signal_values[1] = (double)cmmc_radio_control_steering_decode(tmp.steering);
                signal_values[2] = (double)cmmc_radio_control_front_pitch_decode(tmp.front_pitch);
                signal_values[3] = (double)cmmc_radio_control_front_roll_decode(tmp.front_roll);
                signal_values[4] = (double)cmmc_radio_control_rear_pitch_decode(tmp.rear_pitch);
                signal_values[5] = (double)cmmc_radio_control_free_bits_decode(tmp.free_bits);
                signal_values[6] = (double)cmmc_radio_control_arm_switch_decode(tmp.arm_switch);
                signal_values[7] = (double)cmmc_radio_control_mode_switch_decode(tmp.mode_switch);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 8;
                *frame_name_ptr = CMMC_RADIO_CONTROL_NAME;
                return 0;
            }
        case CMMC_ACTUATOR_CONFIGURATION_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_actuator_configuration_t tmp;   // temporary structure
                if (cmmc_actuator_configuration_unpack(&tmp, data, CMMC_ACTUATOR_CONFIGURATION_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[2]; 
                static const char *signal_names[2] = {
                    CMMC_ACTUATOR_CONFIGURATION_REQUEST_NAME,
                    CMMC_ACTUATOR_CONFIGURATION_ACTUATOR_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_actuator_configuration_request_decode(tmp.request);
                signal_values[1] = (double)cmmc_actuator_configuration_actuator_decode(tmp.actuator);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 2;
                *frame_name_ptr = CMMC_ACTUATOR_CONFIGURATION_NAME;
                return 0;
            }
        case CMMC_ACTUATOR_RIGHT_FOIL_FEEDBACK_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_actuator_right_foil_feedback_t tmp;   // temporary structure
                if (cmmc_actuator_right_foil_feedback_unpack(&tmp, data, CMMC_ACTUATOR_RIGHT_FOIL_FEEDBACK_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[7]; 
                static const char *signal_names[7] = {
                    CMMC_ACTUATOR_RIGHT_FOIL_FEEDBACK_CURRENT_NAME,
                    CMMC_ACTUATOR_RIGHT_FOIL_FEEDBACK_VOLTAGE_NAME,
                    CMMC_ACTUATOR_RIGHT_FOIL_FEEDBACK_POWER_NAME,
                    CMMC_ACTUATOR_RIGHT_FOIL_FEEDBACK_SETPOINT_US_NAME,
                    CMMC_ACTUATOR_RIGHT_FOIL_FEEDBACK_POSITION_RAW_NAME,
                    CMMC_ACTUATOR_RIGHT_FOIL_FEEDBACK_FREE_BITS_NAME,
                    CMMC_ACTUATOR_RIGHT_FOIL_FEEDBACK_MODE_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_actuator_right_foil_feedback_current_decode(tmp.current);
                signal_values[1] = (double)cmmc_actuator_right_foil_feedback_voltage_decode(tmp.voltage);
                signal_values[2] = (double)cmmc_actuator_right_foil_feedback_power_decode(tmp.power);
                signal_values[3] = (double)cmmc_actuator_right_foil_feedback_setpoint_us_decode(tmp.setpoint_us);
                signal_values[4] = (double)cmmc_actuator_right_foil_feedback_position_raw_decode(tmp.position_raw);
                signal_values[5] = (double)cmmc_actuator_right_foil_feedback_free_bits_decode(tmp.free_bits);
                signal_values[6] = (double)cmmc_actuator_right_foil_feedback_mode_decode(tmp.mode);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 7;
                *frame_name_ptr = CMMC_ACTUATOR_RIGHT_FOIL_FEEDBACK_NAME;
                return 0;
            }
        case CMMC_ACTUATOR_LEFT_FOIL_FEEDBACK_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_actuator_left_foil_feedback_t tmp;   // temporary structure
                if (cmmc_actuator_left_foil_feedback_unpack(&tmp, data, CMMC_ACTUATOR_LEFT_FOIL_FEEDBACK_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[7]; 
                static const char *signal_names[7] = {
                    CMMC_ACTUATOR_LEFT_FOIL_FEEDBACK_CURRENT_NAME,
                    CMMC_ACTUATOR_LEFT_FOIL_FEEDBACK_VOLTAGE_NAME,
                    CMMC_ACTUATOR_LEFT_FOIL_FEEDBACK_POWER_NAME,
                    CMMC_ACTUATOR_LEFT_FOIL_FEEDBACK_SETPOINT_US_NAME,
                    CMMC_ACTUATOR_LEFT_FOIL_FEEDBACK_POSITION_RAW_NAME,
                    CMMC_ACTUATOR_LEFT_FOIL_FEEDBACK_FREE_BITS_NAME,
                    CMMC_ACTUATOR_LEFT_FOIL_FEEDBACK_MODE_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_actuator_left_foil_feedback_current_decode(tmp.current);
                signal_values[1] = (double)cmmc_actuator_left_foil_feedback_voltage_decode(tmp.voltage);
                signal_values[2] = (double)cmmc_actuator_left_foil_feedback_power_decode(tmp.power);
                signal_values[3] = (double)cmmc_actuator_left_foil_feedback_setpoint_us_decode(tmp.setpoint_us);
                signal_values[4] = (double)cmmc_actuator_left_foil_feedback_position_raw_decode(tmp.position_raw);
                signal_values[5] = (double)cmmc_actuator_left_foil_feedback_free_bits_decode(tmp.free_bits);
                signal_values[6] = (double)cmmc_actuator_left_foil_feedback_mode_decode(tmp.mode);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 7;
                *frame_name_ptr = CMMC_ACTUATOR_LEFT_FOIL_FEEDBACK_NAME;
                return 0;
            }
        case CMMC_ACTUATOR_REAR_FOIL_FEEDBACK_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_actuator_rear_foil_feedback_t tmp;   // temporary structure
                if (cmmc_actuator_rear_foil_feedback_unpack(&tmp, data, CMMC_ACTUATOR_REAR_FOIL_FEEDBACK_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[7]; 
                static const char *signal_names[7] = {
                    CMMC_ACTUATOR_REAR_FOIL_FEEDBACK_CURRENT_NAME,
                    CMMC_ACTUATOR_REAR_FOIL_FEEDBACK_VOLTAGE_NAME,
                    CMMC_ACTUATOR_REAR_FOIL_FEEDBACK_POWER_NAME,
                    CMMC_ACTUATOR_REAR_FOIL_FEEDBACK_SETPOINT_US_NAME,
                    CMMC_ACTUATOR_REAR_FOIL_FEEDBACK_POSITION_RAW_NAME,
                    CMMC_ACTUATOR_REAR_FOIL_FEEDBACK_FREE_BITS_NAME,
                    CMMC_ACTUATOR_REAR_FOIL_FEEDBACK_MODE_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_actuator_rear_foil_feedback_current_decode(tmp.current);
                signal_values[1] = (double)cmmc_actuator_rear_foil_feedback_voltage_decode(tmp.voltage);
                signal_values[2] = (double)cmmc_actuator_rear_foil_feedback_power_decode(tmp.power);
                signal_values[3] = (double)cmmc_actuator_rear_foil_feedback_setpoint_us_decode(tmp.setpoint_us);
                signal_values[4] = (double)cmmc_actuator_rear_foil_feedback_position_raw_decode(tmp.position_raw);
                signal_values[5] = (double)cmmc_actuator_rear_foil_feedback_free_bits_decode(tmp.free_bits);
                signal_values[6] = (double)cmmc_actuator_rear_foil_feedback_mode_decode(tmp.mode);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 7;
                *frame_name_ptr = CMMC_ACTUATOR_REAR_FOIL_FEEDBACK_NAME;
                return 0;
            }
        case CMMC_ACTUATOR_STEERING_FEEDBACK_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_actuator_steering_feedback_t tmp;   // temporary structure
                if (cmmc_actuator_steering_feedback_unpack(&tmp, data, CMMC_ACTUATOR_STEERING_FEEDBACK_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[7]; 
                static const char *signal_names[7] = {
                    CMMC_ACTUATOR_STEERING_FEEDBACK_CURRENT_NAME,
                    CMMC_ACTUATOR_STEERING_FEEDBACK_VOLTAGE_NAME,
                    CMMC_ACTUATOR_STEERING_FEEDBACK_POWER_NAME,
                    CMMC_ACTUATOR_STEERING_FEEDBACK_SETPOINT_US_NAME,
                    CMMC_ACTUATOR_STEERING_FEEDBACK_POSITION_RAW_NAME,
                    CMMC_ACTUATOR_STEERING_FEEDBACK_FREE_BITS_NAME,
                    CMMC_ACTUATOR_STEERING_FEEDBACK_MODE_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_actuator_steering_feedback_current_decode(tmp.current);
                signal_values[1] = (double)cmmc_actuator_steering_feedback_voltage_decode(tmp.voltage);
                signal_values[2] = (double)cmmc_actuator_steering_feedback_power_decode(tmp.power);
                signal_values[3] = (double)cmmc_actuator_steering_feedback_setpoint_us_decode(tmp.setpoint_us);
                signal_values[4] = (double)cmmc_actuator_steering_feedback_position_raw_decode(tmp.position_raw);
                signal_values[5] = (double)cmmc_actuator_steering_feedback_free_bits_decode(tmp.free_bits);
                signal_values[6] = (double)cmmc_actuator_steering_feedback_mode_decode(tmp.mode);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 7;
                *frame_name_ptr = CMMC_ACTUATOR_STEERING_FEEDBACK_NAME;
                return 0;
            }
        case CMMC_DISTANCE_FORE_FEEDBACK_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_distance_fore_feedback_t tmp;   // temporary structure
                if (cmmc_distance_fore_feedback_unpack(&tmp, data, CMMC_DISTANCE_FORE_FEEDBACK_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[6]; 
                static const char *signal_names[6] = {
                    CMMC_DISTANCE_FORE_FEEDBACK_RANGE_MM_L_NAME,
                    CMMC_DISTANCE_FORE_FEEDBACK_ERROR_STATUS_L_NAME,
                    CMMC_DISTANCE_FORE_FEEDBACK_SIGNAL_RATE_MCPS_L_NAME,
                    CMMC_DISTANCE_FORE_FEEDBACK_RANGE_MM_R_NAME,
                    CMMC_DISTANCE_FORE_FEEDBACK_ERROR_STATUS_R_NAME,
                    CMMC_DISTANCE_FORE_FEEDBACK_SIGNAL_RATE_MCPS_R_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_distance_fore_feedback_range_mm_l_decode(tmp.range_mm_l);
                signal_values[1] = (double)cmmc_distance_fore_feedback_error_status_l_decode(tmp.error_status_l);
                signal_values[2] = (double)cmmc_distance_fore_feedback_signal_rate_mcps_l_decode(tmp.signal_rate_mcps_l);
                signal_values[3] = (double)cmmc_distance_fore_feedback_range_mm_r_decode(tmp.range_mm_r);
                signal_values[4] = (double)cmmc_distance_fore_feedback_error_status_r_decode(tmp.error_status_r);
                signal_values[5] = (double)cmmc_distance_fore_feedback_signal_rate_mcps_r_decode(tmp.signal_rate_mcps_r);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 6;
                *frame_name_ptr = CMMC_DISTANCE_FORE_FEEDBACK_NAME;
                return 0;
            }
        case CMMC_DISTANCE_ACHTER_FEEDBACK_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_distance_achter_feedback_t tmp;   // temporary structure
                if (cmmc_distance_achter_feedback_unpack(&tmp, data, CMMC_DISTANCE_ACHTER_FEEDBACK_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[6]; 
                static const char *signal_names[6] = {
                    CMMC_DISTANCE_ACHTER_FEEDBACK_RANGE_MM_L_NAME,
                    CMMC_DISTANCE_ACHTER_FEEDBACK_ERROR_STATUS_L_NAME,
                    CMMC_DISTANCE_ACHTER_FEEDBACK_SIGNAL_RATE_MCPS_L_NAME,
                    CMMC_DISTANCE_ACHTER_FEEDBACK_RANGE_MM_R_NAME,
                    CMMC_DISTANCE_ACHTER_FEEDBACK_ERROR_STATUS_R_NAME,
                    CMMC_DISTANCE_ACHTER_FEEDBACK_SIGNAL_RATE_MCPS_R_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_distance_achter_feedback_range_mm_l_decode(tmp.range_mm_l);
                signal_values[1] = (double)cmmc_distance_achter_feedback_error_status_l_decode(tmp.error_status_l);
                signal_values[2] = (double)cmmc_distance_achter_feedback_signal_rate_mcps_l_decode(tmp.signal_rate_mcps_l);
                signal_values[3] = (double)cmmc_distance_achter_feedback_range_mm_r_decode(tmp.range_mm_r);
                signal_values[4] = (double)cmmc_distance_achter_feedback_error_status_r_decode(tmp.error_status_r);
                signal_values[5] = (double)cmmc_distance_achter_feedback_signal_rate_mcps_r_decode(tmp.signal_rate_mcps_r);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 6;
                *frame_name_ptr = CMMC_DISTANCE_ACHTER_FEEDBACK_NAME;
                return 0;
            }
        case CMMC_DISTANCE_BOW_FEEDBACK_FRAME_ID:
            {
                /* Unpack data into temporary structure */
                struct cmmc_distance_bow_feedback_t tmp;   // temporary structure
                if (cmmc_distance_bow_feedback_unpack(&tmp, data, CMMC_DISTANCE_BOW_FEEDBACK_LENGTH))
                    return 2;
        
                /* Local static arrays so that the pointers remain valid after return */
                static double signal_values[3]; 
                static const char *signal_names[3] = {
                    CMMC_DISTANCE_BOW_FEEDBACK_RANGE_MM_NAME,
                    CMMC_DISTANCE_BOW_FEEDBACK_ERROR_STATUS_NAME,
                    CMMC_DISTANCE_BOW_FEEDBACK_SIGNAL_RATE_MCPS_NAME
                };
        
                /* Decode all single signals */
                signal_values[0] = (double)cmmc_distance_bow_feedback_range_mm_decode(tmp.range_mm);
                signal_values[1] = (double)cmmc_distance_bow_feedback_error_status_decode(tmp.error_status);
                signal_values[2] = (double)cmmc_distance_bow_feedback_signal_rate_mcps_decode(tmp.signal_rate_mcps);
                
        
                /* Assign to outputs */
                *signal_names_ptr = signal_names;
                *signal_values_ptr = signal_values;
                *nsignals_ptr = 3;
                *frame_name_ptr = CMMC_DISTANCE_BOW_FEEDBACK_NAME;
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
