
#include <map>

#include "Event.h"

using namespace frame;

Event Event::from(sf::Event event)
{
    Event ret(Event::Code::NONE_CODE, Event::Type::NONE_TYPE);

    std::map<sf::Event::EventType, Event::Type> typo2type =
    {
        {sf::Event::KeyPressed, Event::Type::PRESSED},
        {sf::Event::KeyReleased, Event::Type::RELEASED},
    };
    auto s = typo2type.find(event.type);
    if (s != typo2type.end())
    {
        ret.type = s->second;
    }

    std::map<sf::Keyboard::Key, Event::Code> key2code =
    {
        {sf::Keyboard::Left, Event::Code::LEFT},
        {sf::Keyboard::Right, Event::Code::RIGHT},
        {sf::Keyboard::Up, Event::Code::UP},
        {sf::Keyboard::Down, Event::Code::DOWN},
    };
    auto f = key2code.find(event.key.code);
    if (f != key2code.end())
    {
        ret.code = f->second;
    }

    return ret;
}