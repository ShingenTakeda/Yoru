#pragma once

#include <iostream>

#include "Yoru/ECS/MessageBus.hpp"

namespace Yoru
{
    class BusNode
    {
        public:
            BusNode(MessageBus *messageBus)
            {
                this->messageBus = messageBus;
                this->messageBus->AddReceiver(this->GetNotifyFunc());
            }
            //Remember to implement the stuuf in the update function

        protected:
            MessageBus *messageBus;

            std::function<void (Message)> GetNotifyFunc()
            {
                auto messageListener = [=](Message message) -> void
                {
                    this->OnNotify(message);
                };
            }

            void Send(Message message)
            {
                messageBus->SendMessage(message);
            }

            virtual void OnNotify(Message message)
            {
                //Do something here
                //Like hooking up a logging system
            }
    };
}