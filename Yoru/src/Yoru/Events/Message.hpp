#pragma once

#include <string>

namespace Yoru
{
    class Message
    {
        public:
            Message(const std::string event)
            {
                messageEvent = event;
            }
            std::string GetEvent()
            {
                return messageEvent;
            }

        private:
            std::string messageEvent;
    };
}