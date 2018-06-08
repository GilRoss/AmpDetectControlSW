#pragma once

#include "HostMessages.h"


#ifdef GIZMODLL_EXPORTS
#define GIZMOLIBRARY_API __declspec(dllexport)
#else
#define GIZMOLIBRARY_API __declspec(dllimport)
#endif

uint32_t MsgTransaction(HostMsg& request, HostMsg* pResponse);

// Open device communications port.
extern "C" GIZMOLIBRARY_API int OpenComm(const char* pPortName);

// Close device communications port.
extern "C" GIZMOLIBRARY_API int CloseComm();

// Determine if device communications port is open.
extern "C" GIZMOLIBRARY_API bool IsPortOpenFlg();

// Set LED state.
extern "C" GIZMOLIBRARY_API int SetOpticsLed(int nSiteIdx, int nLedIdx, int nLedIntensity, int nLedDuration_us);

// Get Diode value.
extern "C" GIZMOLIBRARY_API int GetDiodeValue(int nDiodeIdx, int* data);

// Read Optics.
extern "C" GIZMOLIBRARY_API int ReadOptics(int nDiodeIdx, int nLedIdx, int nLedIntensity, int nIntegrationTime_us, int* data);
