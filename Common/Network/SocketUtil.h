#pragma once

class SocketUtil 
{
private:
	static GUID guidAcceptEx;
	static GUID guidConnectEx;
	static GUID guidDisconnectEx;

	static LPFN_ACCEPTEX lpfnAcceptEx;
	static LPFN_CONNECTEX lpfnConnectEx;
	static LPFN_DISCONNECTEX lpfnDisconnectEx;

private:
	template<typename FN, typename GUID_TYPE>
	static BOOL SetIocpWSAIoctl(SOCKET _sock, OUT FN& _fn, OUT GUID_TYPE& _guid);
	static BOOL SetAcceptFunc();
	static BOOL SetConnectFunc();
	static BOOL SetDisconnectFunc();

public:
	static BOOL SetExFunctions();

public:
	static SOCKET CreateTCP();
	static SOCKET CreateIocpTCP();
	static SOCKET CreateUDP(); 
	static void SetReuse(SOCKET _sock, bool _flag); 
	static void SetLinger(SOCKET _sock, DWORD _onoff, DWORD _linger); 
	static void SetConditionalAccept(SOCKET _listener);
	static BOOL UpdateAcceptToSock(SOCKET _client, SOCKET _listener);
	static BOOL UpdateConnectToSock(SOCKET _client);

public:
	static BOOL AcceptEx(IocpObjSptr _listener, class IocpAccept* _accepter, SessionSptr _client);
	static BOOL ConnectEx(SOCKET _sock, const SOCKADDR* _addr, class IocpConnect* _event);
};


template<typename FN, typename GUID_TYPE>
BOOL SocketUtil::SetIocpWSAIoctl(SOCKET _sock, OUT FN& _fn, OUT GUID_TYPE& _guid) {
	DWORD dwBytes = 0;
	int ret = WSAIoctl(_sock, SIO_GET_EXTENSION_FUNCTION_POINTER
		, &_guid, sizeof(_guid)
		, &_fn, sizeof(_fn)
		, &dwBytes, nullptr, nullptr
	);

	return ret != SOCKET_ERROR;
}