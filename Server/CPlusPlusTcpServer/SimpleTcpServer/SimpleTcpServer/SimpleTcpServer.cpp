// SimpleTcpServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WINSOCK2.H>
#include <iostream>
#include "MessagePack/msgpack.hpp"

// Client send to server. 
struct FTestStruct
{
	char name[53];
	int8_t Int8;
	int16_t Int16;
	int32_t Int32;
	int64_t Int64;
	uint8_t UInt8;
	uint16_t UInt16;
	uint32_t UInt32;
	uint64_t UInt64;
	float Float;
	double Double;
	std::vector<int8_t> arrayInt8;
	std::string stringValue;

	/** Default constructor. */
	FTestStruct()
		: Int8(-127)
		, Int16(-32767)
		, Int32(-2147483647)
		, Int64(-92233720368547/*75807*/)
		, UInt8(255)
		, UInt16(65535)
		, UInt32(4294967295)
		, UInt64(18446744073709/*551615*/)
		, Float(4.125)
		, Double(1.03125)
		, stringValue("This is a string.")
	{ 
		arrayInt8.push_back(2);
		arrayInt8.push_back(3);
		arrayInt8.push_back(4);

		name[0] = 'm';
		name[1] = 'y';
		name[2] = 0;
	}

	MSGPACK_DEFINE(
		name,
		Int8, 
		Int16, 
		Int32, 
		Int64, 
		UInt8, 
		UInt16, 
		UInt32, 
		UInt64, 
		Float, 
		Double, 
		arrayInt8, 
		stringValue);
};

struct FTestStructEx
{
	char nameEx[53];
	FTestStruct child;

	FTestStructEx()
	{
		nameEx[0] = 'I';
		nameEx[1] = 0;
	}

	MSGPACK_DEFINE(
		nameEx,
		child
	);

};

// The bytes of message length's type.
const int MessageLengthTypeSize = sizeof(int16_t);

#pragma comment(lib,"ws2_32.lib")

void main()
{
	// Create socket
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(1, 1);
	int err;
	err = WSAStartup(myVersionRequest, &wsaData);
	if (err != 0)
	{		
		std::cout << "WSAStartup() failed!\n";
		return;
	}

	uint16_t port = 10008;

	SOCKET serSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip地址
	addr.sin_port = htons(port);//绑定端口

	err = bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//绑定完成
	if (err != 0)
	{
		std::cout << "Bind port failed " << port << "\n";
		return;
	}

	err = listen(serSocket, 1);//其中第二个参数代表能够接收的最多的连接数
	if (err != 0)
	{
		std::cout << "Listen failed!";
		return;
	}

	std::cout << "Listening in port: " << port << "\n";

	//////////////////////////////////////////////////////////////////////////
	//开始进行监听
	//////////////////////////////////////////////////////////////////////////
	SOCKADDR_IN clientsocket;
	int len = sizeof(SOCKADDR);
	
	{
		std::cout << "Waiting for incoming connect ...\n";
		SOCKET serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);
						
		std::cout << inet_ntoa(clientsocket.sin_addr) << "is connected.";

		std::cout << "Waiting for message packet ...";
		
		char receiveBuf[2048];
		int nCount = recv(serConn, receiveBuf, MessageLengthTypeSize, 0);	// Reciving message length.

		uint16_t nDataLength = *(uint16_t*)receiveBuf;

		// Read the messaage length and Id.
		nCount = recv(serConn, receiveBuf, nDataLength, 0);					// Reciveing message context.
		uint16_t messageId = *(uint16_t*)(receiveBuf);

		// Unpack the message.
		msgpack::object_handle objHandle = msgpack::unpack((const char*)receiveBuf + 2, nCount - 2);
		const msgpack::object& msgObj = objHandle.get();
		FTestStruct _recvStruct;
		msgObj.convert(_recvStruct);
		
		std::cout << "Recvived message : " << messageId << "\n"
			<< "int8: " << (int)_recvStruct.Int8 << "\n"
			<< "Int16: " << _recvStruct.Int16 << "\n"
			<< "Int32: " << _recvStruct.Int32 << "\n"
			<< "Int64: " << _recvStruct.Int64 << "\n"
			<< "UInt8: " << (uint32_t)_recvStruct.UInt8 << "\n"
			<< "UInt16: " << (int)_recvStruct.UInt16 << "\n"
			<< "UInt32: " << _recvStruct.UInt32 << "\n"
			<< "UInt64: " << _recvStruct.UInt64 << "\n"
			<< "Float: " << _recvStruct.Float << "\n"
			<< "Double: " << _recvStruct.Double << "\n"
			<< "arrayInt8: " << (int)_recvStruct.arrayInt8[0] << ", " << (int)_recvStruct.arrayInt8[1] << ", " << (int)_recvStruct.arrayInt8[2] << "\n"
			<< "stringValue: " << _recvStruct.stringValue << "\n"
			<< "-------------------------------------\n";

		std::cout << "Send back the recived message.\n";

		// Pack the message.
		msgpack::sbuffer sbuffer;
		// FTestStructEx _testEx;
		msgpack::pack(sbuffer, _recvStruct);

		int16_t nSendLength = (int16_t)sbuffer.size() + MessageLengthTypeSize + 2;
		err = send(serConn, (const char*)&nSendLength, MessageLengthTypeSize, 0);		// Send the length of message.
		messageId = 1002;
		err = send(serConn, (const char*)&messageId, sizeof(messageId), 0);			// Send the id of message.
		err = send(serConn, (const char*)sbuffer.data(), (int)sbuffer.size(), 0);			// Send the context of message.

		std::cout << "Enter to close this connect.";
		char ch = std::cin.get();

		closesocket(serConn);//关闭
		WSACleanup();//释放资源的操作
	}

	std::cout << "Server is closed. Enter for exit.";

	char ch = std::cin.get();
}