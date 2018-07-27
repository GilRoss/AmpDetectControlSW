#pragma once

#include "HostMessages.h"

using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;


////////////////////////////////////////////////////////////////////////////
ref class DeviceCommDriver
{
public:
	DeviceCommDriver();
	virtual ~DeviceCommDriver();

	void			SetPortId(String^ sPortId)	{ _sPortId = sPortId; }
	const String^	GetPortId()					{ return _sPortId; }
	void			InitializePort(String^ sPortId);
	uint32_t		MsgTransaction(HostMsg& request, HostMsg* pResponse);

private:
	String ^		_sPortId;
	SerialPort^		_serialPort;
	SemaphoreSlim^	_hostCommSem;
};

