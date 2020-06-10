
#include "Event.h"

using namespace frame;

Event Event::from(sf::Event event)
{
    return Event(Event::Type::LEFT);
}