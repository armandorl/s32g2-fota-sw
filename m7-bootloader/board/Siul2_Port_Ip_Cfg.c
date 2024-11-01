/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v8.0
processor: S32G274A_Rev2
package_id: S32G274A_Rev2_525bga
mcu_data: PlatformSDK_S32G_2020_12
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "Siul2_Port_Ip_Cfg.h"

/* clang-format off */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: M7_0}
- pin_list:
  - {pin_num: W12, peripheral: LINFlexD_1, signal: rxd, pin_signal: PB_00}
  - {pin_num: U12, peripheral: LINFlexD_1, signal: txd, pin_signal: PA_13}
  - {pin_num: J21, peripheral: QuadSPI, signal: ck_2a, pin_signal: PG_02}
  - {pin_num: H21, peripheral: QuadSPI, signal: ck_2a_b, pin_signal: PG_03}
  - {pin_num: K20, peripheral: QuadSPI, signal: ck_a, pin_signal: PG_00}
  - {pin_num: K21, peripheral: QuadSPI, signal: ck_a_b, pin_signal: PG_01}
  - {pin_num: G21, peripheral: QuadSPI, signal: 'cs_a, 0', pin_signal: PG_04}
  - {pin_num: H22, peripheral: QuadSPI, signal: 'cs_a, 1', pin_signal: PG_05}
  - {pin_num: L18, peripheral: QuadSPI, signal: 'data_a_in, 0', pin_signal: PF_05}
  - {pin_num: L19, peripheral: QuadSPI, signal: 'data_a_in, 1', pin_signal: PF_06}
  - {pin_num: L20, peripheral: QuadSPI, signal: 'data_a_in, 2', pin_signal: PF_07}
  - {pin_num: K22, peripheral: QuadSPI, signal: 'data_a_in, 3', pin_signal: PF_08}
  - {pin_num: K19, peripheral: QuadSPI, signal: 'data_a_in, 4', pin_signal: PF_09}
  - {pin_num: J23, peripheral: QuadSPI, signal: 'data_a_in, 5', pin_signal: PF_10}
  - {pin_num: H23, peripheral: QuadSPI, signal: 'data_a_in, 6', pin_signal: PF_11}
  - {pin_num: K18, peripheral: QuadSPI, signal: 'data_a_in, 7', pin_signal: PF_12}
  - {pin_num: L18, peripheral: QuadSPI, signal: 'data_a_out, 0', pin_signal: PF_05}
  - {pin_num: L19, peripheral: QuadSPI, signal: 'data_a_out, 1', pin_signal: PF_06}
  - {pin_num: L20, peripheral: QuadSPI, signal: 'data_a_out, 2', pin_signal: PF_07}
  - {pin_num: K22, peripheral: QuadSPI, signal: 'data_a_out, 3', pin_signal: PF_08}
  - {pin_num: K19, peripheral: QuadSPI, signal: 'data_a_out, 4', pin_signal: PF_09}
  - {pin_num: J23, peripheral: QuadSPI, signal: 'data_a_out, 5', pin_signal: PF_10}
  - {pin_num: H23, peripheral: QuadSPI, signal: 'data_a_out, 6', pin_signal: PF_11}
  - {pin_num: K18, peripheral: QuadSPI, signal: 'data_a_out, 7', pin_signal: PF_12}
  - {pin_num: K23, peripheral: QuadSPI, signal: dqs_a, pin_signal: PF_13, direction: OUTPUT}
  - {pin_num: J19, peripheral: QuadSPI, signal: inta_b, pin_signal: PF_14}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/*! @brief Array of pin configuration structures */
Siul2_Port_Ip_PinSettingsConfig g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0] =
{
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 16u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .inputMux[0]                 = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0]              = 736u,
        .inputMux[1]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7]                 = PORT_INPUT_MUX_NO_INIT,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 13u,
        .mux                         = PORT_MUX_ALT2,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 98u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 99u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 96u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 97u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 100u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 101u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 85u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .inputMux[0]                 = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0]              = 28u,
        .inputMux[1]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7]                 = PORT_INPUT_MUX_NO_INIT,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 86u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .inputMux[0]                 = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0]              = 29u,
        .inputMux[1]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7]                 = PORT_INPUT_MUX_NO_INIT,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 87u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .inputMux[0]                 = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0]              = 30u,
        .inputMux[1]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7]                 = PORT_INPUT_MUX_NO_INIT,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 88u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .inputMux[0]                 = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0]              = 31u,
        .inputMux[1]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7]                 = PORT_INPUT_MUX_NO_INIT,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 89u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .inputMux[0]                 = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0]              = 32u,
        .inputMux[1]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7]                 = PORT_INPUT_MUX_NO_INIT,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 90u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .inputMux[0]                 = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0]              = 33u,
        .inputMux[1]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7]                 = PORT_INPUT_MUX_NO_INIT,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 91u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .inputMux[0]                 = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0]              = 34u,
        .inputMux[1]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7]                 = PORT_INPUT_MUX_NO_INIT,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 92u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .inputMux[0]                 = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0]              = 35u,
        .inputMux[1]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7]                 = PORT_INPUT_MUX_NO_INIT,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 93u,
        .mux                         = PORT_MUX_ALT1,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
    },
    {
        .base                        = SIUL2_0,
        .pinPortIdx                  = 94u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .receiverSel                 = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel             = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .openDrain                   = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .inputMux[0]                 = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0]              = 37u,
        .inputMux[1]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6]                 = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7]                 = PORT_INPUT_MUX_NO_INIT,
    },
};

