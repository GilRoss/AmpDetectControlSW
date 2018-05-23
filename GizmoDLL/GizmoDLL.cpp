// GizmoDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "GizmoDLL.h"


HANDLE			hSerial = NULL;
DCB				dcbSerialParams = { 0 };
COMMTIMEOUTS	timeouts = { 0 };

// Open device communications port.
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

// Open device communications port.
GIZMOLIBRARY_API int CloseComm()
{
	if (CloseHandle(hSerial))
	{
		hSerial = NULL;
		return 0;
	}
	return 1;
}

// Determine if device communications port is open.
GIZMOLIBRARY_API bool IsPortOpenFlg()
{ 
	return hSerial != NULL;
}

// Set LED state.
GIZMOLIBRARY_API int SetOpticsLed(int nSiteIdx, int nChanIdx, int nIntensity, int nDuration_us)
{ 
	int nErrCode = 1;

	if (IsPortOpenFlg() == true)
	{
		SetOpticsLedReq request;
		HostMsg			response;
		request.SetSiteIdx(nSiteIdx);
		request.SetChanIdx(nChanIdx);
		request.SetIntensity(nIntensity);
		request.SetDuration(nDuration_us);

		MsgTransaction(request, &response);
		nErrCode = response.GetError();
	}

	return nErrCode;
}

uint32_t MsgTransaction(HostMsg& request, HostMsg* pResponse)
{
	uint32_t	nErr = ErrCode::kDeviceCommErr;

//	_hostCommSem->Wait();
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
		DWORD nBytesRead;
		ReadFile(hSerial, arResBuf, msgHdr.GetStreamSize(), &nBytesRead, NULL);
		while ((nBytesRead >= msgHdr.GetStreamSize()) && (nTimeout_ms < 2000))
		{
			::Sleep(5);
			nTimeout_ms += 5;
			ReadFile(hSerial, arResBuf, msgHdr.GetStreamSize(), &nBytesRead, NULL);
		}

		if (nTimeout_ms < 2000)
		{
			msgHdr << arResBuf;

			//If there is more data in this response than just the header.
			if (msgHdr.GetMsgSize() > msgHdr.GetStreamSize())
			{
				//Get remaining bytes in response.
				int nTotalBytes = msgHdr.GetStreamSize();
				nTimeout_ms = 0;
				ReadFile(hSerial, &arResBuf[nTotalBytes], msgHdr.GetMsgSize() - msgHdr.GetStreamSize(), &nBytesRead, NULL);
				nTotalBytes += nBytesRead;
				while ((nTotalBytes >= (int)msgHdr.GetMsgSize()) && (nTimeout_ms < 2000))
				{
					Sleep(5);
					nTimeout_ms += 5;
					ReadFile(hSerial, &arResBuf[(int)msgHdr.GetMsgSize()], msgHdr.GetMsgSize() - msgHdr.GetStreamSize(), &nBytesRead, NULL);
					nTotalBytes += nBytesRead;
				}
			}
			*pResponse << arResBuf;
			nErr = pResponse->GetError();
		}
	}
	catch (...)
	{
	}

//	_hostCommSem->Release();
	return nErr;
}

