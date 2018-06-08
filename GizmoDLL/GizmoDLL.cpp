// GizmoDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "GizmoDLL.h"


HANDLE			hSerial = NULL;
DCB				dcbSerialParams = { 0 };
COMMTIMEOUTS	timeouts = { 0 };

/** 
*	Name: int OpenComm(const char* pPortName)
*	Input Parameters: 
*		const char* pPortName: COM Port
*	Return Value:
*		int nErrCode: Returns specific error code
*					  0: No Error
*					  otherwise: Error 
*	Description: Open device communications port.
*/
GIZMOLIBRARY_API int OpenComm(const char* pPortName)
{
	int nErrCode = 0;
	std::string stemp(pPortName);
	std::wstring sPortName = std::wstring(stemp.begin(), stemp.end());

	// Open the highest available serial port number
	hSerial = CreateFile(
		sPortName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hSerial == INVALID_HANDLE_VALUE)
	{
		hSerial = NULL;
		return 1;
	}

	// Set device parameters (38400 baud, 1 start bit,
	// 1 stop bit, no parity)
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (GetCommState(hSerial, &dcbSerialParams) == 0)
	{
		CloseHandle(hSerial);
		hSerial = NULL;
		return 1;
	}

	dcbSerialParams.BaudRate = CBR_38400;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (SetCommState(hSerial, &dcbSerialParams) == 0)
	{
		CloseHandle(hSerial);
		hSerial = NULL;
		return 1;
	}

	// Set COM port timeout settings
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (SetCommTimeouts(hSerial, &timeouts) == 0)
	{
		CloseHandle(hSerial);
		hSerial = NULL;
		return 1;
	}

	return nErrCode;
}

/**
*	Name: int CloseComm()
*	Input Parameters:
*		void
*	Return Value: 
*		int nErrCode: Returns specific error code
*					  0: No Error
*					  otherwise: Error
*	Description: Close device communications port.
*/
GIZMOLIBRARY_API int CloseComm()
{
	if (CloseHandle(hSerial))
	{
		hSerial = NULL;
		return 0;
	}
	return 1;
}

/**
*	Name: int CloseComm()
*	Input Parameters:
*		void
*	Return Value:
*		bool: Returns status of communication port
*					  true: No Error
*					  false: Error
*	Description: Determine if device communications port is open.
*/
GIZMOLIBRARY_API bool IsPortOpenFlg()
{ 
	return hSerial != NULL;
}

/**
*	Name: int SetOpticsLed(int nSiteIdx, int nChanIdx, int nIntensity, int nDuration_us)
*	Input Parameters:
*		int nSiteIdx: Site Number
*		int nLedIdx: Led Number (0-5)
*		int nLedIntensity: Led Intensity (0-40000)
*		int nLedDuration_us: Led On Duration (not currently used)
*	Return Value:
*		int nErrCode: Returns specific error code
*					  0: No Error
*					  otherwise: Error
*	Description: Turns On/Off specified LED.
*/
GIZMOLIBRARY_API int SetOpticsLed(int nSiteIdx, int nLedIdx, int nLedIntensity, int nLedDuration_us)
{ 
	int nErrCode = ErrCode::kDeviceCommErr;

	if (IsPortOpenFlg() == true)
	{
		SetOpticsLedReq request;
		HostMsg			response;
		request.SetSiteIdx(nSiteIdx);
		request.SetChanIdx(nLedIdx);
		request.SetIntensity(nLedIntensity);
		request.SetDuration(nLedDuration_us);

		MsgTransaction(request, &response);
		nErrCode = response.GetError();
	}

	return nErrCode;
}

/**
*	Name: int GetDiodeValue(int nDiodeIdx)
*	Input Parameters:
*		int nDiodeIdx: Photo Diode Number (0-5)
*	Return Value:
*		int nErrCode: Returns specific error code
*					  0: No Error
*					  otherwise: Error
*	Description: Read specified photo diode output.
*/
GIZMOLIBRARY_API int GetDiodeValue(int nDiodeIdx, int* data)
{
	int nErrCode = ErrCode::kDeviceCommErr;

	if (IsPortOpenFlg() == true)
	{
		GetOpticsDiodeReq request;
		GetOpticsDiodeRes response;
		request.SetDiodeIdx(nDiodeIdx);

		nErrCode = (int) MsgTransaction(request, &response);
		*data = response.GetDiodeValue();
	}

	return nErrCode;
}

/**
*	Name: int ReadOptics(int nDiodeIdx, int nLedIdx, int nLedIntensity, int nIntegrationTime_us, int* data)
*	Input Parameters:
*		int nDiodeIdx: Photo Diode Number (0-5)
*		int nLedIdx: Led Number (0-5)
*		int nLedIntensity: Led Intensity (0-40000)
*		int nIntegrationTime_us: Photo Diode integration time (1000-1000000) in microseconds
*		int* data: Pointer to photo diode value
*	Return Value:
*		int nErrCode: Returns specific error code
*					  0: No Error
*					  otherwise: Error
*	Description: 1. Turns On Led
*				 2. Triggers Photo Diode Integration for specified time
*				 3. Holds integrated value
*				 4. Reads value using ADC
*				 5. Turns Off Led
*/
GIZMOLIBRARY_API int ReadOptics(int nDiodeIdx, int nLedIdx, int nLedIntensity, int nIntegrationTime_us, int* data)
{
	int nErrCode = ErrCode::kDeviceCommErr;

	if (IsPortOpenFlg() == true)
	{
		ReadOpticsReq request;
		ReadOpticsRes response;
		request.SetLedIdx(nLedIdx);
		request.SetDiodeIdx(nDiodeIdx);
		request.SetLedIntensity(nLedIntensity);
		request.SetIntegrationTime(nIntegrationTime_us);

		nErrCode = (int) MsgTransaction(request, &response);

		*data = response.GetDiodeValue();
	}

	return nErrCode;
}

uint32_t MsgTransaction(HostMsg& request, HostMsg* pResponse)
{
	uint32_t	nErr = ErrCode::kDeviceCommErr;
	uint32_t	comErr = ErrCode::kNoError;
	DWORD nBytesRead = 0;

	//_hostCommSem->Wait();
	try
	{
		//Send request to firmware.
		request.SetMsgSize(request.GetStreamSize());
		uint8_t arReqBuf[HostMsg::kMaxRequestSize];
		request >> arReqBuf;
		DWORD nBytesWritten;
		WriteFile(hSerial, arReqBuf, request.GetStreamSize(), &nBytesWritten, NULL);

		//Get response header.
		HostMsg msgHdr;
		uint8_t arResBuf[HostMsg::kMaxResponseSize];
		int	nTimeout_ms = 0;
		while ((nBytesRead < msgHdr.GetStreamSize()) && (nTimeout_ms < 2000))
		{
			comErr = ReadFile(hSerial, arResBuf, msgHdr.GetStreamSize(), &nBytesRead, NULL);
			::Sleep(5);
			nTimeout_ms += 5;
		}

		if (nTimeout_ms < 2000)
		{
			/* If data was read successfully */
			if (comErr == ErrCode::kDeviceCommErr)
			{
				msgHdr << arResBuf;
				nErr = ErrCode::kNoError;
			}
			//If there is more data in this response than just the header.
			if ((msgHdr.GetMsgSize() > msgHdr.GetStreamSize()) && (nErr == ErrCode::kNoError))
			{
				//Get remaining bytes in response.
				int nTotalBytes = msgHdr.GetStreamSize();
				nTimeout_ms = 0;

				while ((nTotalBytes < (int)msgHdr.GetMsgSize()) && (nTimeout_ms < 2000))
				{
					comErr = ReadFile(hSerial, &arResBuf[(int)msgHdr.GetStreamSize()], msgHdr.GetMsgSize() - msgHdr.GetStreamSize(), &nBytesRead, NULL);
					Sleep(5);
					nTimeout_ms += 5;
					nTotalBytes += nBytesRead;
				}
				/* If data was read successfully */
				if (comErr == ErrCode::kDeviceCommErr)
				{
					nErr = ErrCode::kNoError;
				}
			}

			if (nErr == ErrCode::kNoError)
			{
				*pResponse << arResBuf;
				nErr = pResponse->GetError();
			}
		}
	}
	catch (...)
	{
	}

//	_hostCommSem->Release();
	return nErr;
}

