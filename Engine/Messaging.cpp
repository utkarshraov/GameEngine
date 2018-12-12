#include "Messaging.h"

namespace Engine
{

	void Engine::AddMessageReciever(std::string& MessageName, Messenger* reciever)
	{
		auto& someval = ReceiverMap[MessageName];
		someval.push_back(reciever);


	}

	void Engine::RemoveMessageReciever(std::string& MessageName, Messenger* reciever)
	{
		auto MessageRecievers = ReceiverMap.find(MessageName);
		if (MessageRecievers != ReceiverMap.end())
		{
			auto Reciever = MessageRecievers->second;
		}
	}

	void Engine::SendMessageToRecievers(std::string& Message, void* payload)
	{
		auto MessageRecievers = ReceiverMap.find(Message);

		if (MessageRecievers != ReceiverMap.end())
		{
			auto Recievers = MessageRecievers->second;
			for (auto Reciver : Recievers)
			{
				Reciver->ProcessMessage(Message, payload);
			}
		}
	}




	void Messenger::ClearData()
	{
		ReceiverMap.clear();

	}
}