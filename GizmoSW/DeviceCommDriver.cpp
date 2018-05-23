#include "stdafx.h"
#include <cstdint>
#include "DeviceCommDriver.h"


////////////////////////////////////////////////////////////////////////////
DeviceCommDriver::DeviceCommDriver()
{
	_serialPort = gcnew SerialPort();
	_hostCommSem = gcnew SemaphoreSlim(1);
}

////////////////////////////////////////////////////////////////////////////
DeviceCommDriver::~DeviceCommDriver()
{
}

////////////////////////////////////////////////////////////////////////////
uint32_t DeviceCommDriver::MsgTransaction(HostMsg& request, HostMsg* pResponse)
{
	uint32_t	nErr = ErrCode::kDeviceCommErr;

	_hostCommSem->Wait();
	try
	{
		if (!_serialPort->IsOpen)
			InitializePort(_sPortId);

		//Send request to firmware.
		request.SetMsgSize(request.GetStreamSize());
		uint8_t arReqBuf[HostMsg::kMaxRequestSize];
		request >> arReqBuf;
		array<uint8_t>^ reqBuf = gcnew array<uint8_t>(request.GetStreamSize());
		for (int i = 0; i < (int)request.GetStreamSize(); i++)
			reqBuf[i] = arReqBuf[i];
		_serialPort->Write(reqBuf, 0, reqBuf->Length);

		//Get response header.
		HostMsg msgHdr;
		uint8_t arResBuf[HostMsg::kMaxResponseSize];
		array<uint8_t>^ resBuf = gcnew array<uint8_t>(msgHdr.GetStreamSize());
		int	nTimeout_ms = 0;
		while ((_serialPort->BytesToRead < (int)msgHdr.GetStreamSize()) && (nTimeout_ms < 2000))
		{
			Thread::Sleep(5);
			nTimeout_ms += 5;
		}

		if (nTimeout_ms < 2000)
		{
			_serialPort->Read(resBuf, 0, msgHdr.GetStreamSize());
			for (int i = 0; i < (int)msgHdr.GetStreamSize(); i++)
				arResBuf[i] = resBuf[i];
			msgHdr << arResBuf;

			//If there is more data in this response than just the header.
			if (msgHdr.GetMsgSize() > msgHdr.GetStreamSize())
			{
				//Get remaining bytes in response.
				Array::Resize(resBuf, msgHdr.GetMsgSize());
				nTimeout_ms = 0;
				while ((_serialPort->BytesToRead < (int)msgHdr.GetMsgSize() - (int)msgHdr.GetStreamSize()) && (nTimeout_ms < 2000))
				{
					Thread::Sleep(5);
					nTimeout_ms += 5;
				}

				if (nTimeout_ms < 2000)
				{
					_serialPort->Read(resBuf, msgHdr.GetStreamSize(), msgHdr.GetMsgSize() - msgHdr.GetStreamSize());
					for (int i = (int)msgHdr.GetStreamSize(); i < (int)msgHdr.GetMsgSize(); i++)
						arResBuf[i] = resBuf[i];
				}
			}
			*pResponse << arResBuf;
			nErr = pResponse->GetError();
		}
	}
	catch (...)
	{
	}

	_hostCommSem->Release();
	return nErr;
}



////////////////////////////////////////////////////////////////////////////
void DeviceCommDriver::InitializePort(String^ sPortId)
{
	//If the host comm port is opened.
	if (_serialPort->IsOpen)
		_serialPort->Close();

	_serialPort->PortName = sPortId;
	_serialPort->BaudRate = 38400;
	_serialPort->Parity = Parity::None;
	_serialPort->DataBits = 8;
	_serialPort->StopBits = StopBits::One;
	_serialPort->Handshake = Handshake::None;
	_serialPort->ReadTimeout = 3000;
	_serialPort->WriteTimeout = 3000;
	_serialPort->Open();
}

