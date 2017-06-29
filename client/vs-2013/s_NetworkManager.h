#ifndef _NETWORK_MANAGER_H
#define _NETWORK_MANAGER_H
#endif // !_NETWORK_MANAGER_H
#pragma comment(lib,"ws2_32.lib")
#pragma warning
#pragma once
//system requires
#include <string.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
//engine requires
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>

#include "s_Manager.h"
#include "s_GraphicsManager.h"
#include "s_InputManager.h"
#include "s_EventKeyBoard.h"
#define DRAGONFLY_PORT "1111"
namespace df {
	struct graphicsPacketCh {
		unsigned int len;
		unsigned int type;   // draw or draw string
		int x;
		int y;				// position x and y
		char content;
		df::s_Color color;
		unsigned int timeCounter;
	};
	struct graphicsPakcetStr {
		unsigned int len;
		unsigned int type;
		int x;
		int y;
		char* content;
		df::Justification just;
		df::s_Color color;
	};
	
	struct commandPakcetKey
	{
		unsigned int len;
		//std::string type;
		Input::Key keyborad_value;
		EventKeyboardAction keyboard_action;
		bool hasEvent;
		unsigned int timeCounter;

	};  // keyboard event
	struct noEvent
	{
		int hasEvent;
	};
	class s_NetworkManager : public s_Manager
	{
		
	private:
		s_NetworkManager();
		s_NetworkManager(s_NetworkManager const&);   //don't allow copy
		s_NetworkManager operator=(s_NetworkManager const&);   // don't allow assignment ...why is void?
		int sock;   // network socket   can be SOCKET type?
		SOCKET m_sock;	// for connecting socket	
		SOCKET connection;		// for listen socket
		SOCKADDR_IN addr;  // for bind info
	public:

		static s_NetworkManager & getInstance();

		int startUp();

		void shutDown();

		bool isValid(std::string event_type) const;

		int df_accept(std::string port = DRAGONFLY_PORT);

		// Make network connection. 
		// Return 0 if success, else -1. 
		int df_connect(std::string host, std::string port = DRAGONFLY_PORT);

		// Close network connection. 
		// Return 0 if success, else -1. 
		int close();

		bool isClosed() const;

		int getSocket() const;

		// Send buffer to connected network. 
		// Return 0 if success, else -1. 
		int df_send(void* buffer, int _bytes);

		// Receive from connected network (no more than nbytes). 
		// If peek is true, leave data in socket, else remove. 
		// Return number of bytes received, else -1 if error. 
		int df_receive(void * &buffer, int bytes, bool peek = false);

		int isData() const;

		std::vector<std::string> split(const std::string &s, char delim);

		int checkGraphicPack();
		//int parseDataAndDraw(std::string command); 
	

	};
}

