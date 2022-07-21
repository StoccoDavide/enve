/**
 * ENVEsfun_Simulator4.c
 *
 *    ABSTRACT:
 *      The purpose of this sfunction is to call a simple legacy
 *      function during simulation:
 *
 *         void sfun_out(shellsRF      u1[1], groundContact y1[1], double        p14[1], double        p15[1]) 
 *
 *    Simulink version           : 10.4 (R2021b) 14-May-2021
 *    C source code generated on : 21-Jul-2022 17:52:26
 *
 * THIS S-FUNCTION IS GENERATED BY THE LEGACY CODE TOOL AND MAY NOT WORK IF MODIFIED
 */

/**
     %%%-MATLAB_Construction_Commands_Start
     def = legacy_code('initialize');
     def.SFunctionName = 'ENVEsfun_Simulator4';
     def.OutputFcnSpec = 'void sfun_out(shellsRF      u1[1], groundContact y1[1], double        p14[1], double        p15[1]) ';
     def.StartFcnSpec = 'void sfun_init(double p1[1], double p2[1], double p3[1], double p4[1], double p5[1], double p6[1], double p7[1], double p8[1], double p9[1], double p10[1], double p11[1], double p12[1], double p13[1])';
     def.TerminateFcnSpec = 'void sfun_end()';
     def.HeaderFiles = {'sfun_types.h', 'sfun_interface.h'};
     def.HostLibFiles = {'../../lib/dll/libenve_osx.dylib'};
     def.IncPaths = {'../../lib/include'};
     def.LibPaths = {'/usr/local/lib'};
     legacy_code('sfcn_cmex_generate', def);
     legacy_code('compile', def);
     %%%-MATLAB_Construction_Commands_End
 */

/* Must specify the S_FUNCTION_NAME as the name of the S-function */
#define S_FUNCTION_NAME  ENVEsfun_Simulator4
#define S_FUNCTION_LEVEL 2

/**
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"

#include <string.h>
#include <stdlib.h>

/* Specific header file(s) required by the legacy code function */
#include "sfun_types.h"
#include "sfun_interface.h"

#define EDIT_OK(S, P_IDX) \
       (!((ssGetSimMode(S)==SS_SIMMODE_SIZES_CALL_ONLY) && mxIsEmpty(ssGetSFcnParam(S, P_IDX))))

#define IS_SIMULATION_TARGET(S) (ssRTWGenIsAccelerator(S) || ssIsRapidAcceleratorActive(S) || ssRTWGenIsModelReferenceSimTarget(S) || (ssGetSimMode(S)==SS_SIMMODE_NORMAL) || (ssGetSimMode(S)==SS_SIMMODE_SIZES_CALL_ONLY) || !((ssRTWGenIsCodeGen(S) || ssGetSimMode(S)==SS_SIMMODE_EXTERNAL) && GetRTWEnvironmentMode(S)==0))


/* Utility function prototypes */
static void CheckDataTypes(SimStruct *S);
static int_T GetRTWEnvironmentMode(SimStruct *S);

#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
/* Function: mdlCheckParameters ===========================================
 * Abstract:
 *   mdlCheckParameters verifies new parameter settings whenever parameter
 *   change or are re-evaluated during a simulation. When a simulation is
 *   running, changes to S-function parameters can occur at any time during
 *   the simulation loop.
 */
static void mdlCheckParameters(SimStruct *S)
{
    /* Check the parameter 1 */
    if (EDIT_OK(S, 0)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 0, "P1", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 2 */
    if (EDIT_OK(S, 1)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 1, "P2", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 3 */
    if (EDIT_OK(S, 2)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 2, "P3", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 4 */
    if (EDIT_OK(S, 3)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 3, "P4", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 5 */
    if (EDIT_OK(S, 4)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 4, "P5", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 6 */
    if (EDIT_OK(S, 5)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 5, "P6", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 7 */
    if (EDIT_OK(S, 6)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 6, "P7", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 8 */
    if (EDIT_OK(S, 7)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 7, "P8", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 9 */
    if (EDIT_OK(S, 8)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 8, "P9", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 10 */
    if (EDIT_OK(S, 9)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 9, "P10", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 11 */
    if (EDIT_OK(S, 10)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 10, "P11", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 12 */
    if (EDIT_OK(S, 11)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 11, "P12", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 13 */
    if (EDIT_OK(S, 12)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 12, "P13", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 14 */
    if (EDIT_OK(S, 13)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 13, "P14", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

    /* Check the parameter 15 */
    if (EDIT_OK(S, 14)) {
        int_T dimsArray[2] = {1, 1};

        /* Check the parameter attributes */
        ssCheckSFcnParamValueAttribs(S, 14, "P15", DYNAMICALLY_TYPED, 2, dimsArray, 0);
    } /* if */

}
#endif

#define MDL_PROCESS_PARAMETERS
#if defined(MDL_PROCESS_PARAMETERS) && defined(MATLAB_MEX_FILE)
/* Function: mdlProcessParameters =========================================
 * Abstract:
 *   Update run-time parameters.
 */
static void mdlProcessParameters(SimStruct *S)
{
    ssUpdateAllTunableParamsAsRunTimeParams(S);
}
#endif

/* Function: mdlInitializeSizes ===========================================
 * Abstract:
 *   The sizes information is used by Simulink to determine the S-function
 *   block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    /* Flag for detecting standalone or simulation target mode */
    boolean_T isSimulationTarget = IS_SIMULATION_TARGET(S);

    /* Number of expected parameters */
    ssSetNumSFcnParams(S, 15);

    #if defined(MATLAB_MEX_FILE) 
    if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {
        /**
         * If the number of expected input parameters is not equal
         * to the number of parameters entered in the dialog box return.
         * Simulink will generate an error indicating that there is a
         * parameter mismatch.
         */
        mdlCheckParameters(S);
        if (ssGetErrorStatus(S) != NULL) return;
    } else {
        /* Return if number of expected != number of actual parameters */
        return;
    } /* if */
    #endif 

    /* Set the parameter's tunability */
    ssSetSFcnParamTunable(S, 0, 1);
    ssSetSFcnParamTunable(S, 1, 1);
    ssSetSFcnParamTunable(S, 2, 1);
    ssSetSFcnParamTunable(S, 3, 1);
    ssSetSFcnParamTunable(S, 4, 1);
    ssSetSFcnParamTunable(S, 5, 1);
    ssSetSFcnParamTunable(S, 6, 1);
    ssSetSFcnParamTunable(S, 7, 1);
    ssSetSFcnParamTunable(S, 8, 1);
    ssSetSFcnParamTunable(S, 9, 1);
    ssSetSFcnParamTunable(S, 10, 1);
    ssSetSFcnParamTunable(S, 11, 1);
    ssSetSFcnParamTunable(S, 12, 1);
    ssSetSFcnParamTunable(S, 13, 1);
    ssSetSFcnParamTunable(S, 14, 1);

    /* Set the number of work vectors */
    if (!IS_SIMULATION_TARGET(S)) {
        ssSetNumPWork(S, 0);
        if (!ssSetNumDWork(S, 0)) return;
    } else {
        ssSetNumPWork(S, 2);
        if (!ssSetNumDWork(S, 2)) return;

        /* Configure the dwork 1 (__dtSizeInfo) */
        ssSetDWorkDataType(S, 0, SS_INT32);
        ssSetDWorkUsageType(S, 0, SS_DWORK_USED_AS_DWORK);
        ssSetDWorkName(S, 0, "dtSizeInfo");
        ssSetDWorkWidth(S, 0, 3);
        ssSetDWorkComplexSignal(S, 0, COMPLEX_NO);

        /* Configure the dwork 2 (__dtBusInfo) */
        ssSetDWorkDataType(S, 1, SS_INT32);
        ssSetDWorkUsageType(S, 1, SS_DWORK_USED_AS_DWORK);
        ssSetDWorkName(S, 1, "dtBusInfo");
        ssSetDWorkWidth(S, 1, 34);
        ssSetDWorkComplexSignal(S, 1, COMPLEX_NO);
    } /* if */

    /* Set the number of input ports */
    if (!ssSetNumInputPorts(S, 1)) return;

    /* Configure the input port 1 */
    #if defined(MATLAB_MEX_FILE) 
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
        DTypeId dataTypeIdReg;

        ssRegisterTypeFromNamedObject(S, "shellsRF", &dataTypeIdReg);
        if(dataTypeIdReg == INVALID_DTYPE_ID) return;

        ssSetInputPortDataType(S, 0, dataTypeIdReg);
    } /* if */
    #endif
    ssSetBusInputAsStruct(S, 0, 1);
    {
        int_T u1Width = 1;
        ssSetInputPortWidth(S, 0, u1Width);
    }
    ssSetInputPortComplexSignal(S, 0, COMPLEX_NO);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortAcceptExprInRTW(S, 0, 0);
    ssSetInputPortOverWritable(S, 0, 0);
    ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
    ssSetInputPortRequiredContiguous(S, 0, 1);

    /* Set the number of output ports */
    if (!ssSetNumOutputPorts(S, 1)) return;

    /* Configure the output port 1 */
    #if defined(MATLAB_MEX_FILE) 
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
        DTypeId dataTypeIdReg;

        ssRegisterTypeFromNamedObject(S, "groundContact", &dataTypeIdReg);
        if(dataTypeIdReg == INVALID_DTYPE_ID) return;

        ssSetOutputPortDataType(S, 0, dataTypeIdReg);
    } /* if */
    #endif
    ssSetBusOutputObjectName(S, 0, (void *)"groundContact");
    ssSetBusOutputAsStruct(S, 0, 1);
    {
        int_T y1Width = 1;
        ssSetOutputPortWidth(S, 0, y1Width);
    }
    ssSetOutputPortComplexSignal(S, 0, COMPLEX_NO);
    ssSetOutputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
    ssSetOutputPortOutputExprInRTW(S, 0, 0);

    /* Register reserved identifiers to avoid name conflict */
    if (ssRTWGenIsCodeGen(S) || ssGetSimMode(S)==SS_SIMMODE_EXTERNAL) {

        /* Register reserved identifier for  */
        ssRegMdlInfo(S, "sfun_init", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

        /* Register reserved identifier for  */
        ssRegMdlInfo(S, "sfun_out", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

        /* Register reserved identifier for  */
        ssRegMdlInfo(S, "sfun_end", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

        /* Register reserved identifier for wrappers */
        if (isSimulationTarget) {

            /* Register reserved identifier for  */
            ssRegMdlInfo(S, "sfun_init_wrapper_Start", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

            /* Register reserved identifier for  */
            ssRegMdlInfo(S, "sfun_out_wrapper_Output", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

            /* Register reserved identifier for  */
            ssRegMdlInfo(S, "sfun_end_wrapper_Terminate", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

            /* Register reserved identifier for allocating PWork for SimulationTarget */
            ssRegMdlInfo(S, "ENVEsfun_Simulator4_wrapper_allocmem", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));

            /* Register reserved identifier for freeing PWork for SimulationTarget */
            ssRegMdlInfo(S, "ENVEsfun_Simulator4_wrapper_freemem", MDL_INFO_ID_RESERVED, 0, 0, ssGetPath(S));
        } /* if */
    } /* if */

    /* This S-function can be used in referenced model simulating in normal mode */
    ssSetModelReferenceNormalModeSupport(S, MDL_START_AND_MDL_PROCESS_PARAMS_OK);

    /* Set the number of sample time */
    ssSetNumSampleTimes(S, 1);

    /* Set the compliance for the operating point save/restore. */
    ssSetOperatingPointCompliance(S, USE_DEFAULT_OPERATING_POINT);

    ssSetArrayLayoutForCodeGen(S, SS_ALL);

    /* Set the Simulink version this S-Function has been generated in */
    ssSetSimulinkVersionGeneratedIn(S, "10.4");

    /**
     * All options have the form SS_OPTION_<name> and are documented in
     * matlabroot/simulink/include/simstruc.h. The options should be
     * bitwise or'd together as in
     *    ssSetOptions(S, (SS_OPTION_name1 | SS_OPTION_name2))
     */
    ssSetOptions(S,
        SS_OPTION_USE_TLC_WITH_ACCELERATOR |
        SS_OPTION_CAN_BE_CALLED_CONDITIONALLY |
        SS_OPTION_EXCEPTION_FREE_CODE |
        SS_OPTION_WORKS_WITH_CODE_REUSE |
        SS_OPTION_SFUNCTION_INLINED_FOR_RTW |
        SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME
    );

    /* Verify Data Type consistency with specification */
    #if defined(MATLAB_MEX_FILE)
    if ((ssGetSimMode(S)!=SS_SIMMODE_SIZES_CALL_ONLY)) {
        CheckDataTypes(S);
    } /* if */
    #endif
}

/* Function: mdlInitializeSampleTimes =====================================
 * Abstract:
 *   This function is used to specify the sample time(s) for your
 *   S-function. You must register the same number of sample times as
 *   specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);

    #if defined(ssSetModelReferenceSampleTimeDefaultInheritance)
    ssSetModelReferenceSampleTimeDefaultInheritance(S);
    #endif
}

#define MDL_SET_WORK_WIDTHS
#if defined(MDL_SET_WORK_WIDTHS) && defined(MATLAB_MEX_FILE)
/* Function: mdlSetWorkWidths =============================================
 * Abstract:
 *   The optional method, mdlSetWorkWidths is called after input port
 *   width, output port width, and sample times of the S-function have
 *   been determined to set any state and work vector sizes which are
 *   a function of the input, output, and/or sample times. 
 *   Run-time parameters are registered in this method using methods 
 *   ssSetNumRunTimeParams, ssSetRunTimeParamInfo, and related methods.
 */
static void mdlSetWorkWidths(SimStruct *S)
{
    /* Set number of run-time parameters */
    if (!ssSetNumRunTimeParams(S, 15)) return;

    /* Register the run-time parameter 1 */
    ssRegDlgParamAsRunTimeParam(S, 0, 0, "p1", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 2 */
    ssRegDlgParamAsRunTimeParam(S, 1, 1, "p2", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 3 */
    ssRegDlgParamAsRunTimeParam(S, 2, 2, "p3", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 4 */
    ssRegDlgParamAsRunTimeParam(S, 3, 3, "p4", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 5 */
    ssRegDlgParamAsRunTimeParam(S, 4, 4, "p5", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 6 */
    ssRegDlgParamAsRunTimeParam(S, 5, 5, "p6", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 7 */
    ssRegDlgParamAsRunTimeParam(S, 6, 6, "p7", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 8 */
    ssRegDlgParamAsRunTimeParam(S, 7, 7, "p8", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 9 */
    ssRegDlgParamAsRunTimeParam(S, 8, 8, "p9", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 10 */
    ssRegDlgParamAsRunTimeParam(S, 9, 9, "p10", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 11 */
    ssRegDlgParamAsRunTimeParam(S, 10, 10, "p11", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 12 */
    ssRegDlgParamAsRunTimeParam(S, 11, 11, "p12", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 13 */
    ssRegDlgParamAsRunTimeParam(S, 12, 12, "p13", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 14 */
    ssRegDlgParamAsRunTimeParam(S, 13, 13, "p14", ssGetDataTypeId(S, "double"));

    /* Register the run-time parameter 15 */
    ssRegDlgParamAsRunTimeParam(S, 14, 14, "p15", ssGetDataTypeId(S, "double"));
}
#endif

#define MDL_START
#if defined(MDL_START)
/* Function: mdlStart =====================================================
 * Abstract:
 *   This function is called once at start of model execution. If you
 *   have states that should be initialized once, this is the place
 *   to do it.
 */
static void mdlStart(SimStruct *S)
{
    if (IS_SIMULATION_TARGET(S)) {

        /* Access bus/struct information */
        int32_T* __dtSizeInfo = (int32_T*) ssGetDWork(S, 0);
        int32_T* __dtBusInfo = (int32_T*) ssGetDWork(S, 1);


        /* Get common data type Id */
        DTypeId __groundContactId = ssGetDataTypeId(S, "groundContact");
        DTypeId __doubleId = ssGetDataTypeId(S, "double");
        DTypeId __shellsRFId = ssGetDataTypeId(S, "shellsRF");

        /* Get common data type size */
        __dtSizeInfo[0] = ssGetDataTypeSize(S, __groundContactId);
        __dtSizeInfo[1] = ssGetDataTypeSize(S, __doubleId);
        __dtSizeInfo[2] = ssGetDataTypeSize(S, __shellsRFId);

        /* Get information for accessing groundContact.RFpc_rr_ground */
        __dtBusInfo[0] = ssGetBusElementOffset(S, __groundContactId, 0);
        __dtBusInfo[1] = 16*__dtSizeInfo[1];

        /* Get information for accessing groundContact.RFpc_rl_ground */
        __dtBusInfo[2] = ssGetBusElementOffset(S, __groundContactId, 1);
        __dtBusInfo[3] = 16*__dtSizeInfo[1];

        /* Get information for accessing groundContact.RFpc_fr_ground */
        __dtBusInfo[4] = ssGetBusElementOffset(S, __groundContactId, 2);
        __dtBusInfo[5] = 16*__dtSizeInfo[1];

        /* Get information for accessing groundContact.RFpc_fl_ground */
        __dtBusInfo[6] = ssGetBusElementOffset(S, __groundContactId, 3);
        __dtBusInfo[7] = 16*__dtSizeInfo[1];

        /* Get information for accessing groundContact.friction_rr */
        __dtBusInfo[8] = ssGetBusElementOffset(S, __groundContactId, 4);
        __dtBusInfo[9] = __dtSizeInfo[1];

        /* Get information for accessing groundContact.friction_rl */
        __dtBusInfo[10] = ssGetBusElementOffset(S, __groundContactId, 5);
        __dtBusInfo[11] = __dtSizeInfo[1];

        /* Get information for accessing groundContact.friction_fr */
        __dtBusInfo[12] = ssGetBusElementOffset(S, __groundContactId, 6);
        __dtBusInfo[13] = __dtSizeInfo[1];

        /* Get information for accessing groundContact.friction_fl */
        __dtBusInfo[14] = ssGetBusElementOffset(S, __groundContactId, 7);
        __dtBusInfo[15] = __dtSizeInfo[1];

        /* Get information for accessing groundContact.rho_rr */
        __dtBusInfo[16] = ssGetBusElementOffset(S, __groundContactId, 8);
        __dtBusInfo[17] = __dtSizeInfo[1];

        /* Get information for accessing groundContact.rho_rl */
        __dtBusInfo[18] = ssGetBusElementOffset(S, __groundContactId, 9);
        __dtBusInfo[19] = __dtSizeInfo[1];

        /* Get information for accessing groundContact.rho_fr */
        __dtBusInfo[20] = ssGetBusElementOffset(S, __groundContactId, 10);
        __dtBusInfo[21] = __dtSizeInfo[1];

        /* Get information for accessing groundContact.rho_fl */
        __dtBusInfo[22] = ssGetBusElementOffset(S, __groundContactId, 11);
        __dtBusInfo[23] = __dtSizeInfo[1];

        /* Get information for accessing groundContact.in_mesh */
        __dtBusInfo[24] = ssGetBusElementOffset(S, __groundContactId, 12);
        __dtBusInfo[25] = __dtSizeInfo[1];

        /* Get information for accessing shellsRF.RFw_rr */
        __dtBusInfo[26] = ssGetBusElementOffset(S, __shellsRFId, 0);
        __dtBusInfo[27] = 16*__dtSizeInfo[1];

        /* Get information for accessing shellsRF.RFw_rl */
        __dtBusInfo[28] = ssGetBusElementOffset(S, __shellsRFId, 1);
        __dtBusInfo[29] = 16*__dtSizeInfo[1];

        /* Get information for accessing shellsRF.RFw_fr */
        __dtBusInfo[30] = ssGetBusElementOffset(S, __shellsRFId, 2);
        __dtBusInfo[31] = 16*__dtSizeInfo[1];

        /* Get information for accessing shellsRF.RFw_fl */
        __dtBusInfo[32] = ssGetBusElementOffset(S, __shellsRFId, 3);
        __dtBusInfo[33] = 16*__dtSizeInfo[1];


        /* Alloc memory for the pwork 1 (__y1BUS) */
        {
            groundContact* __y1BUS = (groundContact*)calloc(sizeof(groundContact), ssGetOutputPortWidth(S, 0));
            if (__y1BUS==NULL) {
                ssSetErrorStatus(S, "Unexpected error during the memory allocation for __y1BUS");
                return;
            } /* if */
            ssSetPWorkValue(S, 0, __y1BUS);
        }

        /* Alloc memory for the pwork 2 (__u1BUS) */
        {
            shellsRF* __u1BUS = (shellsRF*)calloc(sizeof(shellsRF), ssGetInputPortWidth(S, 0));
            if (__u1BUS==NULL) {
                ssSetErrorStatus(S, "Unexpected error during the memory allocation for __u1BUS");
                return;
            } /* if */
            ssSetPWorkValue(S, 1, __u1BUS);
        }

        {

            /* Get access to Parameter/Input/Output/DWork data */
            real_T* p1 = (real_T*) ssGetRunTimeParamInfo(S, 0)->data;
            real_T* p2 = (real_T*) ssGetRunTimeParamInfo(S, 1)->data;
            real_T* p3 = (real_T*) ssGetRunTimeParamInfo(S, 2)->data;
            real_T* p4 = (real_T*) ssGetRunTimeParamInfo(S, 3)->data;
            real_T* p5 = (real_T*) ssGetRunTimeParamInfo(S, 4)->data;
            real_T* p6 = (real_T*) ssGetRunTimeParamInfo(S, 5)->data;
            real_T* p7 = (real_T*) ssGetRunTimeParamInfo(S, 6)->data;
            real_T* p8 = (real_T*) ssGetRunTimeParamInfo(S, 7)->data;
            real_T* p9 = (real_T*) ssGetRunTimeParamInfo(S, 8)->data;
            real_T* p10 = (real_T*) ssGetRunTimeParamInfo(S, 9)->data;
            real_T* p11 = (real_T*) ssGetRunTimeParamInfo(S, 10)->data;
            real_T* p12 = (real_T*) ssGetRunTimeParamInfo(S, 11)->data;
            real_T* p13 = (real_T*) ssGetRunTimeParamInfo(S, 12)->data;


            /* Call the legacy code function */
            sfun_init(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
        }
    } /* if */
}
#endif

/* Function: mdlOutputs ===================================================
 * Abstract:
 *   In this function, you compute the outputs of your S-function
 *   block. Generally outputs are placed in the output vector(s),
 *   ssGetOutputPortSignal.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    if (IS_SIMULATION_TARGET(S)) {

        /* Access bus/struct information */
        int32_T* __dtSizeInfo = (int32_T*) ssGetDWork(S, 0);
        int32_T* __dtBusInfo = (int32_T*) ssGetDWork(S, 1);


        /* Get access to Parameter/Input/Output/DWork data */
        char* u1 = (char*) ssGetInputPortSignal(S, 0);
        char* y1 = (char*) ssGetOutputPortSignal(S, 0);
        real_T* p14 = (real_T*) ssGetRunTimeParamInfo(S, 13)->data;
        real_T* p15 = (real_T*) ssGetRunTimeParamInfo(S, 14)->data;

        shellsRF* __u1BUS = (shellsRF*) ssGetPWorkValue(S, 1);
        groundContact* __y1BUS = (groundContact*) ssGetPWorkValue(S, 0);

        /* Assign the Simulink structure u1 to user structure __u1BUS */
        (void) memcpy(__u1BUS[0].RFw_rr, u1 +  __dtBusInfo[26],  __dtBusInfo[27]);
        (void) memcpy(__u1BUS[0].RFw_rl, u1 +  __dtBusInfo[28],  __dtBusInfo[29]);
        (void) memcpy(__u1BUS[0].RFw_fr, u1 +  __dtBusInfo[30],  __dtBusInfo[31]);
        (void) memcpy(__u1BUS[0].RFw_fl, u1 +  __dtBusInfo[32],  __dtBusInfo[33]);

        /* Call the legacy code function */
        sfun_out(__u1BUS, __y1BUS, p14, p15);

        /* Assign the user structure __y1BUS to the Simulink structure y1 */
        (void) memcpy(y1 +  __dtBusInfo[0], __y1BUS[0].RFpc_rr_ground,  __dtBusInfo[1]);
        (void) memcpy(y1 +  __dtBusInfo[2], __y1BUS[0].RFpc_rl_ground,  __dtBusInfo[3]);
        (void) memcpy(y1 +  __dtBusInfo[4], __y1BUS[0].RFpc_fr_ground,  __dtBusInfo[5]);
        (void) memcpy(y1 +  __dtBusInfo[6], __y1BUS[0].RFpc_fl_ground,  __dtBusInfo[7]);
        (void) memcpy(y1 +  __dtBusInfo[8], &__y1BUS[0].friction_rr,  __dtBusInfo[9]);
        (void) memcpy(y1 +  __dtBusInfo[10], &__y1BUS[0].friction_rl,  __dtBusInfo[11]);
        (void) memcpy(y1 +  __dtBusInfo[12], &__y1BUS[0].friction_fr,  __dtBusInfo[13]);
        (void) memcpy(y1 +  __dtBusInfo[14], &__y1BUS[0].friction_fl,  __dtBusInfo[15]);
        (void) memcpy(y1 +  __dtBusInfo[16], &__y1BUS[0].rho_rr,  __dtBusInfo[17]);
        (void) memcpy(y1 +  __dtBusInfo[18], &__y1BUS[0].rho_rl,  __dtBusInfo[19]);
        (void) memcpy(y1 +  __dtBusInfo[20], &__y1BUS[0].rho_fr,  __dtBusInfo[21]);
        (void) memcpy(y1 +  __dtBusInfo[22], &__y1BUS[0].rho_fl,  __dtBusInfo[23]);
        (void) memcpy(y1 +  __dtBusInfo[24], &__y1BUS[0].in_mesh,  __dtBusInfo[25]);
    } /* if */
}

/* Function: mdlTerminate =================================================
 * Abstract:
 *   In this function, you should perform any actions that are necessary
 *   at the termination of a simulation.
 */
static void mdlTerminate(SimStruct *S)
{
    if (IS_SIMULATION_TARGET(S)) {

        /* Access bus/struct information */
        int32_T* __dtSizeInfo = (int32_T*) ssGetDWork(S, 0);
        int32_T* __dtBusInfo = (int32_T*) ssGetDWork(S, 1);

        {

            /* Call the legacy code function */
            sfun_end();
        }

        /* Free memory for the pwork 1 (__y1BUS) */
        {
            groundContact* __y1BUS = (groundContact*)ssGetPWorkValue(S, 0);
            if (__y1BUS!=NULL) {
                free(__y1BUS);
                ssSetPWorkValue(S, 0, NULL);
            } /* if */
        }

        /* Free memory for the pwork 2 (__u1BUS) */
        {
            shellsRF* __u1BUS = (shellsRF*)ssGetPWorkValue(S, 1);
            if (__u1BUS!=NULL) {
                free(__u1BUS);
                ssSetPWorkValue(S, 1, NULL);
            } /* if */
        }

    } /* if */
}

/* Function: CheckDataTypeChecksum ========================================
 * Abstract:
 *   CheckDataTypeChecksum invokes a MATLAB helper for checking the consistency
 *   between the data type definition used when this S-Function was generated
 *   and the data type used when calling the S-Function.
 */
static int_T CheckDataTypeChecksum(SimStruct *S, const char* dtypeName, uint32_T* chkRef)
{
    mxArray *plhs[1] = {NULL};
    mxArray *prhs[3];
    mxArray *err = NULL;
    const char *bpath = ssGetPath(S);
    int_T status = -1;

    prhs[0] = mxCreateString(bpath);
    prhs[1] = mxCreateString(dtypeName);
    prhs[2] = mxCreateDoubleMatrix(1, 4, mxREAL);
    mxGetPr(prhs[2])[0] = chkRef[0];
    mxGetPr(prhs[2])[1] = chkRef[1];
    mxGetPr(prhs[2])[2] = chkRef[2];
    mxGetPr(prhs[2])[3] = chkRef[3];

    err = mexCallMATLABWithTrap(1, plhs, 3, prhs, "legacycode.LCT.getOrCompareDataTypeChecksum");
    mxDestroyArray(prhs[0]);
    mxDestroyArray(prhs[1]);
    mxDestroyArray(prhs[2]);

    if (err==NULL && plhs[0]!=NULL) {
        status = mxIsEmpty(plhs[0]) ? -1 : (int_T) (mxGetScalar(plhs[0]) != 0);
        mxDestroyArray(plhs[0]);
    } /* if */

    return status;
}

/* Function: CheckDataTypes ===============================================
 * Abstract:
 *   CheckDataTypes verifies data type consistency between the data type 
 *   definition used when this S-Function was generated and the data type
 *   used when calling the S-Function.
 */
static void CheckDataTypes(SimStruct *S)
{

    /* Verify Bus/StructType 'groundContact', specification */
    {
        uint32_T chk[] = {847896458, 3721280763, 3181810719, 3915457260};
        int_T status;
        status = CheckDataTypeChecksum(S, "groundContact", &chk[0]);
        if (status==-1) {
          ssSetErrorStatus(S, "Unexpected error when checking the validity of the Simulink Bus/StructType 'groundContact'");
        } else if (status==0) {
          ssSetErrorStatus(S, "The Simulink Bus/StructType 'groundContact' definition has changed since the S-Function was generated");
        }
    }

    /* Verify Bus/StructType 'shellsRF', specification */
    {
        uint32_T chk[] = {4178193573, 1291726892, 4025122012, 1887786316};
        int_T status;
        status = CheckDataTypeChecksum(S, "shellsRF", &chk[0]);
        if (status==-1) {
          ssSetErrorStatus(S, "Unexpected error when checking the validity of the Simulink Bus/StructType 'shellsRF'");
        } else if (status==0) {
          ssSetErrorStatus(S, "The Simulink Bus/StructType 'shellsRF' definition has changed since the S-Function was generated");
        }
    }
}

/* Function: GetRTWEnvironmentMode ========================================
 * Abstract:
 *   Must be called when ssRTWGenIsCodeGen(S)==true. This function
 *   returns the code generation mode:
 *       -1 if an error occurred
 *        0 for standalone code generation target
 *        1 for simulation target (Accelerator, RTW-SFcn,...)
 */
static int_T GetRTWEnvironmentMode(SimStruct *S)
{
    int_T status;
    mxArray * err;
    mxArray *plhs[1];
    mxArray *prhs[1];

    /* Get the name of the Simulink block diagram */
    prhs[0] = mxCreateString(ssGetModelName(ssGetRootSS(S)));
    plhs[0] = NULL;

    /* Call "isSimulationTarget = rtwenvironmentmode(modelName)" in MATLAB */
    err = mexCallMATLABWithTrap(1, plhs, 1, prhs, "rtwenvironmentmode");

    mxDestroyArray(prhs[0]);

    /* Set the error status if an error occurred */
    if (err) {
        if (plhs[0]) {
            mxDestroyArray(plhs[0]);
            plhs[0] = NULL;
        } /* if: } */
        ssSetErrorStatus(S, "Unknown error during call to 'rtwenvironmentmode'.");
        return -1;
    } /* if */

    /* Get the value returned by rtwenvironmentmode(modelName) */
    if (plhs[0]) {
        status = (int_T) (mxGetScalar(plhs[0]) != 0);
        mxDestroyArray(plhs[0]);
        plhs[0] = NULL;
    } /* if */

    return status;
}

/* Required S-function trailer */
#ifdef    MATLAB_MEX_FILE
# include "simulink.c"
#else
# include "cg_sfun.h"
#endif

