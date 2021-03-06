/*
* Copyright(c) 2018 Intel Corporation
* SPDX - License - Identifier: BSD - 2 - Clause - Patent
*/

#ifndef EbAppContext_h
#define EbAppContext_h

#include "EbAppTypes.h"
#include "EbApi.h"
#include "EbAppConfig.h"
#include "EbAppFifo.h"

/***************************************

 * App Callback data struct
 ***************************************/
typedef struct EbAppContext_s {
    void                               *cmdSemaphoreHandle;
    void                               *inputSemaphoreHandle;
    void                               *streamSemaphoreHandle;
    void                               *reconSemaphoreHandle;
    EB_PARAM_PORTDEFINITIONTYPE        inputPortDefinition;
    EB_PARAM_PORTDEFINITIONTYPE        outputStreamPortDefinition;
    EB_H265_ENC_CONFIGURATION           ebEncParameters;

    // Local Contexts
    InputBitstreamContext_t             inputContext;

    // Output Ports Active Flags
    APPPORTACTIVETYPE                   outputStreamPortActive;

    // Component Handle
    EB_HANDLETYPE                      svtEncoderHandle;

    // Buffer Pools
    EB_BUFFERHEADERTYPE              **inputBufferPool;
    EB_BUFFERHEADERTYPE              **streamBufferPool;

	// Instance Index
	EB_U8								instanceIdx;

	// Buffer Fifo
    AppCommandFifo_t                    *fifoPtr;

    // End of sequence in the feedback flag
    EB_BOOL                            feedBackIsComplete;

} EbAppContext_t;

typedef struct EbParentAppContext_s {
    void                               *cmdSemaphoreHandle;
    void                               *inputSemaphoreHandle;
    void                               *streamSemaphoreHandle;
    void                               *reconSemaphoreHandle;
   
    // Buffer Fifo
    AppCommandFifo_t                    fifo;

	// Children Application CallBacks
	EbAppContext_t					   *appCallBacks[MAX_CHANNEL_NUMBER];

	// Number of channels active 
	EB_U8							    numChannels;

} EbParentAppContext_t;



/********************************
 * External Function
 ********************************/
extern void EbAppContextCtor(EbAppContext_t *contextPtr);
extern void EbParentAppContextCtor(EbAppContext_t **contextPtr, EbParentAppContext_t *parentContextPtr, EB_U32 numChannels, EB_U32 totalBuffersSize);
extern void EbParentAppContextDtor(EbParentAppContext_t *parentContextPtr);
extern EB_ERRORTYPE InitEncoder(EbConfig_t *config, EbAppContext_t *callbackData, EB_U32 instanceIdx);
extern EB_ERRORTYPE DeInitEncoder(EbAppContext_t *callbackDataPtr, EB_U32 instanceIndex, EB_ERRORTYPE   libExitError);
extern EB_ERRORTYPE StartEncoder(EbAppContext_t *callbackDataPtr);
extern EB_ERRORTYPE StopEncoder(EbAppContext_t *callbackDataPtr);

#endif // EbAppContext_h