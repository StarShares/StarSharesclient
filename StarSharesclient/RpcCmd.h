#pragma once
#include <string>
using namespace std;
class CRpcCmd
{
public:
	CRpcCmd(void);
	CRpcCmd(const CStringA	 ip,int port,int timerout)
	{
		mIp = ip;
		mPort = port;
		mTimerout = timerout;
	}
	void SetHeadString(const string	 &sendPreHeadstr,const string &sendendHeadstr)
	{
		m_sendPreHeadstr = sendPreHeadstr;
		m_sendendHeadstr = sendendHeadstr;
	}
	void SetPort(int port)
	{
		mPort = port;
	}
	void SetSeverIp(const string & ip){
		mIp = ip;
	}
	 CStringA RpcJosnStr;
    void BuildSendString(const string	 &cmd,string &sendStr);
	
	~CRpcCmd(void);
private:
	string				m_sendPreHeadstr;
	string				m_sendendHeadstr;
	string               mIp;
	int mPort;
	int mTimerout;
	void RPCCommandToJson(const string& strRPCCommand,string& strSendData);

//add by lbf 20160816******web∂À≈‰÷√≤Œ ˝
private:
	string				m_sendWebPreHeadstr;
	string				m_sendWebEndHeadstr;
	string              m_WebIp;
	int					m_nWebPort;
	int					m_nWebTimeout;
	void WebRPCCommandToJson(const string& strRPCCommand,string& strSendData);
public:
	void BuildWebSendString(const string &cmd,string &sendStr);
	int SendWebRpc(string strCommand,string &rev);

public:
	void SetWebHeadString(const string	 &sendWebPreHeadstr,const string &sendWebendHeadstr)
	{
		m_sendWebPreHeadstr = sendWebPreHeadstr;
		m_sendWebEndHeadstr = sendWebendHeadstr;
	}
	void SetWebPort(int webPort)
	{
		m_nWebPort = webPort;
	}
	void SetWebSeverIp(const string & webIp){
		m_WebIp = webIp;
	}

public:
	int SendRpc(string cmd,string &rev);
	int SendContactRpc(string cmd,string &rev);
};

extern bool IsAllDigtal(const char* pData);