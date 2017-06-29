#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
//    winSocket needed

#include "s_NetworkManager.h"
#include "Logmanager2.h"
#include "s_GraphicsManager.h"
#include "s_WorldManager.h"

#include <iostream>
#include <sstream>

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

		
									

									 //initiate the socket 


		s_Manager::startUp();
		return 0;
	}

	void s_NetworkManager::shutDown()
	{
		s_Manager::shutDown();
	}

	bool s_NetworkManager::isValid(std::string event_type) const
	{
		return false;
	}

	int s_NetworkManager::df_accept(std::string port)
	{
		return 0;
	}

	int s_NetworkManager::df_connect(std::string host, std::string port)
	{

		//SOCKADDR_IN addr; // address that we will bind out listening socket to.
		inet_pton(AF_INET, host.c_str(), &addr.sin_addr);

		//addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //broadcast locally.

		addr.sin_port = htons(atoi(port.c_str())); //port   // why is htons???   host to network short big and little edean
		addr.sin_family = AF_INET;// IPV4;

		connection = socket(AF_INET, SOCK_STREAM, NULL);  // listen connection

		int addrlen = sizeof(addr);
		if (connect(connection, (SOCKADDR*)&addr, addrlen) != 0)
		{
			LogManager2::getInstance().writeLog("failed to connect");
			return -1;

		}
		LogManager2::getInstance().writeLog("client connected");

		/*char * buffer = new char[4];
		buffer[3] = '\0';
		int revCheck = recv(connection, buffer, 3, NULL);
		LogManager2::getInstance().writeLog("the test recv value is %d", revCheck);*/

		unsigned long byte_availble = 1;
		ioctlsocket(connection, FIONBIO, &byte_availble);  // set unblocking

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

	int s_NetworkManager::df_send(void* buffer, int _bytes)
	{
		int length = _bytes;
		//send(connection, (char*)length, sizeof(int), NULL);
		if (send(connection, (char*)buffer, length, NULL) != SOCKET_ERROR)
		{
			LogManager2::getInstance().writeLog("successfully send the message.");
			return 0;
		}
		else
			return -1;
	}

	/*int s_NetworkManager::df_receive(void* &buffer, int bytes, bool peek)
	{
		int length = 0;
		int lengthCheck = recv(connection, (char *)&length,sizeof(int),NULL);
		LogManager2::getInstance().writeLog("the receive value is %d", length);
		LogManager2::getInstance().writeLog("the receive status is %d", lengthCheck);
		char * temBuffer = new char[length + 1];
		temBuffer[length] = '\0';
		int resCheck = 0;
		if (peek)
		{
			resCheck = recv(connection, temBuffer, length, MSG_PEEK);
			buffer = temBuffer;
		}
		else
		{
			resCheck = recv(connection, temBuffer, length, NULL);
			buffer = temBuffer;
		}
		delete[] temBuffer;
		if (resCheck == SOCKET_ERROR)
		{
			LogManager2 &logmanager = LogManager2::getInstance();
			logmanager.writeLog("socket receive error\n");
			std::cout << "socket receive error" << std::endl;
			return -1;
		}
		else
		{
			return length;
		}
	}*/
	int s_NetworkManager::df_receive(void* &buffer, int bytes, bool peek)
	{
		int length = 1;
	
		// get the socket available length.
		graphicsPacketCh graphic_packet2;
		int len_res = recv(connection, (char*)&length, sizeof(unsigned int), MSG_PEEK);
		char * temBuffer2 = new char[28 + 1];
		recv(connection, temBuffer2, sizeof(graphic_packet2), MSG_PEEK);
		memcpy(&graphic_packet2, temBuffer2, sizeof(graphic_packet2));
		LogManager2::getInstance().writeLog("graphic packet color is %d", graphic_packet2.color);
		LogManager2::getInstance().writeLog("graphic packet content is %d", graphic_packet2.content);
		// get the struct length property
		LogManager2::getInstance().writeLog("the struct length is %d", len_res);
		delete[] temBuffer2;
		if (length == sizeof(graphicsPacketCh))
		{
			graphicsPacketCh graphic_packet;
			char * temBuffer = new char[length + 1];
			temBuffer[length] = '\0';
			int resCheck = 0;
			if (peek)
			{
				resCheck = recv(connection, temBuffer, sizeof(graphic_packet), MSG_PEEK);
				memcpy(buffer, temBuffer, sizeof(graphic_packet));  // memcpy to the buffer
																	//buffer = temBuffer;
			}
			else
			{
				resCheck = recv(connection, temBuffer, sizeof(graphic_packet), NULL);
				memcpy(buffer, temBuffer, sizeof(graphic_packet));  // memcpy to the buffer
			}
			delete[] temBuffer;
			int nError = WSAGetLastError();
			if (nError != WSAEWOULDBLOCK && nError != 0)
			{
				LogManager2::getInstance().writeLog("server no more send data");
				shutdown(connection, SD_SEND);
			}
			if (resCheck == SOCKET_ERROR)
			{
				LogManager2 &logmanager = LogManager2::getInstance();
				logmanager.writeLog("socket receive error\n");
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

	int s_NetworkManager::isData() const
	{
		return 0;
	}

	std::vector<std::string> s_NetworkManager::split(const std::string & s, char delim)
	{
			std::stringstream ss(s);
			std::string item;
			std::vector<std::string> tokens;
			while (getline(ss, item, delim)) {
				tokens.push_back(item);
			}
			return tokens;
	}

	int s_NetworkManager::checkGraphicPack()
	{
		unsigned long bites = 0;
		ioctlsocket(connection, FIONREAD, &bites);
		LogManager2::getInstance().writeLog("the bites are %d", bites);
		int i = 0;
		while (bites>= sizeof(graphicsPacketCh) && i<300)
		{
			LogManager2::getInstance().writeLog("the i is %d", i);
			graphicsPacketCh g_packCh;
			void * g = static_cast<graphicsPacketCh *>(&g_packCh);
			int gra_res =s_NetworkManager::getInstance().df_receive(g,0,false);
		 	if (gra_res>0)  // success
			{
				if (g_packCh.type!=2)
				{
					s_GraphicsManager::getInstance().drawCh(Position(g_packCh.x, g_packCh.y), g_packCh.content, g_packCh.color);
					s_WorldManager::getInstance().setTimeCounter(g_packCh.timeCounter);
				}
				else
				{
					LogManager2::getInstance().writeLog("frame is end");
					break;
				}
			 	
			}
			int nError = WSAGetLastError();
			LogManager2:: getInstance().writeLog("the nerror is %d", nError);
			if (nError !=WSAEWOULDBLOCK && nError != 0)
			{
				LogManager2::getInstance().writeLog("server no more graphics data");
				shutdown(connection, SD_SEND);
			}
			i++;
			ioctlsocket(connection, FIONREAD, &bites);   // update bites variables.
		}
		return 0;
	}

/*	int s_NetworkManager::parseDataAndDraw(std::string command)
	{
		s_GraphicsManager & graphic_manager = s_GraphicsManager::getInstance();
		std::vector<std::string> comms = split(command, '|');

		if (comms.size() <= 0)
		{
			LogManager2::getInstance().writeLog("wrong data format.");
			return -1;
		}
		else
		{
			if (comms[0] == "draw")
			{
				std::vector<std::string> coordinates = split(comms[1], ',');
				int x = atoi(coordinates[0].c_str());
				int y = atoi(coordinates[1].c_str());
				std::string character = comms[2].c_str();
				char ch = character[0];
				int colorIndex = atoi(comms[3].c_str());
				df::Color color;
				switch (colorIndex)
				{
				case 0:
					color = BLACK;
					break;
				case 1:
					color = RED;
					break;
				case 2:
					color = GREEN;
					break;
				case 3:
					color = YELLOW;
					break;
				case 4:
					color = BLUE;
					break;
				case 5:
					color = MAGENTA;
					break;
				case 6:
					color = CYAN;
					break;
				case 7:
					color = WHITE;
					break;
				default:
					break;
				}
				
				graphic_manager.drawCh(df::Position(x, y), ch, color);
			}
			else if(comms[0] == "drawString")
			{
				std::vector<std::string> coordinates = split(comms[1], ',');
				int x = atoi(coordinates[0].c_str());
				int y = atoi(coordinates[1].c_str());
				std::string str = comms[2].c_str();
				int justIndex = atoi(comms[3].c_str());
				df::Justification just;
				switch (justIndex)
				{
				case 0:
					just = LEFT_JUSTIFIED;
					break;
				case 1:
					just = CENTER_JUSTIFIED;
					break;
				case 2:
					just = RIGHT_JUSTIFIED;
					break;
				default:
					break;
				}
				int colorIndex = atoi(comms[4].c_str());
				df::Color color;
				switch (colorIndex)
				{
				case 0:
					color = BLACK;
					break;
				case 1:
					color = RED;
					break;
				case 2:
					color = GREEN;
					break;
				case 3:
					color = YELLOW;
					break;
				case 4:
					color = BLUE;
					break;
				case 5:
					color = MAGENTA;
					break;
				case 6:
					color = CYAN;
					break;
				case 7:
					color = WHITE;
					break;
				default:
					break;
				}
				graphic_manager.drawString(df::Position(x, y), str, just,color);
			}
		}

		return 0;
	}
*/

s_NetworkManager df::s_NetworkManager::operator=(s_NetworkManager const &)   // don't allow
{
	return s_NetworkManager();
}




}