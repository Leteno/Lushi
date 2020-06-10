#pragma once

#include <SFML/Graphics.hpp>

namespace frame {
class Event
{
public:
    enum Type{
        LEFT, RIGHT, BOTTOM, UP
    };
    Event(Type type) : type(type) {}

    static Event from(sf::Event event);

    Type type;
};
}