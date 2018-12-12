#pragma once
#include <string>
#include <map>
#include <vector>
#include <cassert>

namespace Engine
{
	class Messenger
	{

	public:
		static void ClearData();


		//virtual ~Messenger() = 0;
		virtual void ProcessMessage(const std::string & message, void* payload) = 0;
	};

	void AddMessageReciever(std::string& RecieverName, Messenger* reciever);
	void RemoveMessageReciever(std::string& RecieverName, Messenger* reciever);
	void SendMessageToRecievers(std::string& Message, void* payload);
	static std::map<std::string, std::vector<Messenger*>> ReceiverMap;


}
