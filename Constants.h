#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <cmath>

const unsigned long amount = 768*768;

const unsigned int width = 1280;
const unsigned int height = 720;

const unsigned long sqrtAmount = std::sqrt(amount);

const float zSpeed = 2;
const float speed = 0x200;
const float min = 1;
const float force = 0x800;
const float maxZoom = (1.f/8.f);

const sf::Color front = sf::Color(255, 255, 255);
const sf::Color back = sf::Color(255, 255, 255);

#endif
