#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>


//    winSocket needed

#include "s_NetworkManager.h"
#include "Logmanager2.h"
#include "s_WorldManager.h"
#include "s_timeWarp.h"
#include "Clock.h"
namespace df {
	s_NetworkManager::s_NetworkManager()
	{
	}
	s_NetworkManager & s_NetworkManager::getInstance()
	{
		// TODO: insert return statement here
		static s_NetworkManager *networkManger = NULL;
		if (!networkManger)
		{
			networkManger = new s_NetworkManager;
		}
		return *networkManger;

	}

	int s_NetworkManager::startUp()
	{
		
		WSADATA wsaData;
		WORD DLLVersion = MAKEWORD(2, 2);
		if (WSAStartup(DLLVersion, &wsaData) != 0)  // wsaStarup return other than 0, then there is an error
		{
			//MessageBoxA(NULL, "Winsock startup failed.", "Error", MB_OK | MB_ICONERROR);
			exit(1);
		}

		//SOCKADDR_IN addr; // address that we will bind out listening socket to.
		inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
		//inet_pton(AF_INET, "130.215.27.158", &addr.sin_addr);
		//addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //broadcast locally.

		addr.sin_port = htons(atoi(DRAGONFLY_PORT)); //port   // why is htons???   host to network short big and little edean
		addr.sin_family = AF_INET;// IPV4;

		sListen = socket(AF_INET, SOCK_STREAM, NULL);  // listen connection
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
		listen(sListen, SOMAXCONN);  // max queue length.

		// what is the purpose of the accept function and send function in the engine. why just use the system call?

		//initiate the socket 


		s_Manager::startUp();
		return 0;
	}

	void s_NetworkManager::shutDown()
	{
	}

	bool s_NetworkManager::isValid(std::string event_type) const
	{
		return false;
	}

	int s_NetworkManager::df_accept(std::string port)
	{
		int addrlen = sizeof(addr);
		m_sock = accept(sListen,(SOCKADDR*)&addr, &addrlen);

		if (m_sock == 0)
		{
			std::cout << "Failed to accept client's connection." << std::endl;
		}
		else
		{
			LogManager2 &logmanager = LogManager2::getInstance();
			
			/*if (!df_send(testMessage, sizeof(testMessage)))
			{
				
				logmanager.writeLog("successful send the message");

			}
			else
			{
				logmanager.writeLog("failed to send the message");
			}
			//send message to the connection socket.-->m_sock
			*/
		}
		unsigned long byte_availble = 1;
		ioctlsocket(m_sock, FIONBIO, &byte_availble);   // set unblocking
		return 0;
		int flag = 1;
		setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(int));
	}

	int s_NetworkManager::df_connect(std::string host, std::string port)
	{
		// for the client
		return 0;
	}

	int s_NetworkManager::close()
	{
		if (!closesocket(m_sock))
		{
			return 0;
		}
		else return -1;
	}

	bool s_NetworkManager::isClosed() const
	{
		return false;
	}

	int s_NetworkManager::getSocket() const
	{
		return m_sock;
	}

	/*int s_NetworkManager::df_send(std::string buffer, int _bytes)
	{
		LogManager2::getInstance().writeLog("send value is : %d", _bytes);
		int length = _bytes;
		int re = send(m_sock, (char*)&length , sizeof(int), NULL);
		LogManager2::getInstance().writeLog("send length is %d",re);
		int stringLen = buffer.size();
		if (send(m_sock, buffer.c_str(), stringLen, NULL) != SOCKET_ERROR)
		{
			LogManager2::getInstance().writeLog("success send the message.");
			return 0;
		}
		else
			return -1;
	}*/
	int s_NetworkManager::df_send(void *buffer, int _bytes)
	{
		//LogManager2::getInstance().writeLog("length is : %d", _bytes);
		int length = _bytes;
		
	/*	struct graphicsPacketCh graphicsComm;
		graphicsComm.type = 1;
		graphicsComm.len = sizeof(struct graphicsPacketCh);
		graphicsComm.content = 'x';
		graphicsComm.x = 20;
		graphicsComm.y = 20;
		graphicsComm.color = df::GREEN;
		*/
		//send(m_sock, (char*)length, sizeof(int), NULL);   // sending length
		if (send(m_sock, (char*)buffer, length, NULL) != SOCKET_ERROR)
		{
			//LogManager2::getInstance().writeLog("success send the message.");
			return 0;
		}
		else
			return -1;
	}

	int s_NetworkManager::df_receive(void* &buffer, int bytes, bool peek)
	{
		int length = 0;
		

		recv(m_sock, (char*)&length, sizeof(unsigned int), MSG_PEEK);
		// get the struct length property
		//LogManager2::getInstance().writeLog("the struct length is %d", length);
		if (length==sizeof(commandPakcetKey))
		{
			commandPakcetKey command_packet;
			char * temBuffer = new char[length + 1];
			temBuffer[length] = '\0';
			int resCheck = 0;
			if (peek)
			{
				resCheck = recv(m_sock, temBuffer, sizeof(command_packet), MSG_PEEK);
				memcpy(buffer, temBuffer, sizeof(command_packet));  // memcpy to the buffer
																	//buffer = temBuffer;
			}
			else
			{
				resCheck = recv(m_sock, temBuffer, sizeof(command_packet), NULL);
				memcpy(buffer, temBuffer, sizeof(command_packet));  // memcpy to the buffer
			}
			delete[] temBuffer;
			int nError = WSAGetLastError();
			if (nError != WSAEWOULDBLOCK && nError != 0)
			{
				//LogManager2::getInstance().writeLog("client no more send data");
				shutdown(m_sock, SD_SEND);
			}
			if (resCheck == SOCKET_ERROR)
			{
				LogManager2 &logmanager = LogManager2::getInstance();
				//logmanager.writeLog("socket receive error");
				std::cout << "socket receive error" << std::endl;
				return -1;
			}
			else
			{
				return length;
			}
		}
		else return 0;
	}

	int s_NetworkManager::checkCommPack()
	{

		unsigned long bites = 0;
		ioctlsocket(m_sock, FIONREAD, &bites);
		LogManager2::getInstance().writeLog("the command bites are %d", bites);
		if (bites != 0)
		{
			df::commandPakcetKey cpk;
			void *cpk_p = static_cast<df::commandPakcetKey *> (&cpk);
			int net_res = df::s_NetworkManager::getInstance().df_receive(cpk_p, 0, false);
			if (cpk.hasEvent == false)  // no event
			{

				return -1;   // no event
			}


			//LogManager2::getInstance().writeLog("the cpk length and net res is %d,%d", cpk.len, net_res);

			// then should apply the event onto the input manager.
			if (net_res >= 0 && cpk.len > 0)
			{
				s_EventKeyBoard *p_kevent = new s_EventKeyBoard();
				if (cpk.keyboard_action == KEY_PRESSED)
				{
					p_kevent->setKey(cpk.keyborad_value);
					LogManager2::getInstance().writeLog("current time counter is %d", s_timeWarp::getInstance().current_time_counter);
					LogManager2::getInstance().writeLog("key value is %d", cpk.keyborad_value);
					p_kevent->setKeyboardAction(cpk.keyboard_action);
					//p_kevent->setType(cpk.type);

					/////////////////////doing the time warp things////////////////////

					if (cpk.timeCounter >= s_timeWarp::getInstance().current_time_counter || s_timeWarp::getInstance().timeWarpOn == false)
					{

						s_WorldManager::getInstance().onEvent(p_kevent);
						// add event into the world manager
						df::LogManager2::getInstance().writeLog("the event key value: %d", p_kevent->getKey());
					}
					else {
						
						Clock *clock = new Clock();
						long int loop_time;
						
						//unsigned int current_time = df::s_timeWarp::getInstance().current_time_counter - 1;
						LogManager2::getInstance().writeLog("the event time counter is %d", cpk.timeCounter);
						df::WorldFrameByTimeCounter world_frame = df::s_timeWarp::getInstance().getWorldFrameByTimeCounter(cpk.timeCounter);
						df::ObjectList2 objCurrent = world_frame.getObjectList();
						df::ObjectListIterator2 li = df::ObjectListIterator2(&objCurrent);
						s_WorldManager::getInstance().setUpdates(objCurrent);
						s_WorldManager::getInstance().onEvent(p_kevent);

						/*fetch the previous game world and then update as the update list in the world manager*/
						/*reset a new world frame and save it into the timewarp list and re-apply it*/
						df::ObjectList2 objModified = s_WorldManager::getInstance().getAllObjects();
						df::WorldFrameByTimeCounter new_world_frame = df::s_timeWarp::getInstance().deepCopy(world_frame.timeCounter);
						df::s_timeWarp::getInstance().saveWorldFrame(new_world_frame);

						loop_time = clock->split();
						LogManager2::getInstance().writeLog("the deep copy takes %8d\n", loop_time);
						// 					int i = 0;
						// 					while (!li.isDone())
						// 					{
						// 						++i;
						// 						li.currentObject()->eventHandler(p_kevent);
						// 						li.next();
						// 					}  // apply events

						df::s_timeWarp::getInstance().reApplyGameWorlds(new_world_frame);
						loop_time = clock->split();
						LogManager2::getInstance().writeLog("the re-apply takes %8d\n", loop_time);
					
					}


				}

			}
			int nError = WSAGetLastError();
			if (nError != WSAEWOULDBLOCK && nError != 0)
			{
				LogManager2::getInstance().writeLog("client no more input data");
				shutdown(m_sock, SD_SEND);
			}

			return 0;
		}
		
		else return -2;  // no command queue
		
	}

	int s_NetworkManager::isData() const
	{
		return 0;
	}


s_NetworkManager df::s_NetworkManager::operator=(s_NetworkManager const &)   // don't allow
{
	return s_NetworkManager();
}




}