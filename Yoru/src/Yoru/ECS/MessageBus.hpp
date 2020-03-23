#pragma once

#include <functional>
#include <queue>
#include <vector>

#include "Yoru/ECS/Message.hpp"

namespace Yoru
{
    class MessageBus
    {
        public:
            MessageBus()
            {

            }
            ~MessageBus()
            {

            }

            void AddReceiver(std::function<void (Message)> messageReceiver)
            {
                receivers.push_back(messageReceiver);
            }

            void SendMessage(Message message)
            {
                messages.push(message);
            }

            void Notify()
            {
                while (!messages.empty())
                {
                    for(auto iter = receivers.begin(); iter != receivers.end(); iter++)
                    {
                        (*iter)(messages.front);
                    }

                    messages.pop();
                }
            }

        private:
            std::vector<std::function<void (Message)>> receivers;
            std::queue<Message> messages;
    };
}