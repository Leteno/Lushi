#pragma once

#include <SFML/Graphics.hpp>

namespace frame {
class Event
{
public:
    enum Code {
        LEFT, RIGHT, UP, DOWN,
        NONE_CODE
    };
    enum Type {
        PRESSED, RELEASED,
        NONE_TYPE
    };
    Event(Code code, Type type)
        : code(code), type(type) {}

    static Event from(sf::Event event);

    Type type;

    Code code;
};
}