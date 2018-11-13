#ifndef GROUP_H
#define GROUP_H

#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <cmath>

struct Camera
{
  sf::Vector2f offSet = sf::Vector2f(0.f, 0.f);
  float zoom = 3;
};

struct VertexData
{
  sf::Vector2f vel = sf::Vector2f(0.f, 0.f);
  sf::Vector2f pos = sf::Vector2f(0.f, 0.f);
};

class Group
{
public:
  Group()
  {
    std::vector<VertexData> temp(amount);
    point.swap(temp);
    reset();
  }

  void drawUpdate(sf::RenderWindow& win, float& fps)
  {
  	for(std::size_t i = 0; i < amount; i++)
  	{
      point[i].pos.x += point[i].vel.x/fps;
      point[i].pos.y += point[i].vel.y/fps;

      draw[i].position.x = (point[i].pos.x + cam.offSet.x) / cam.zoom + width/2;
      draw[i].position.y = (point[i].pos.y + cam.offSet.y) / cam.zoom + height/2;
  	}
  	win.draw(draw);
  }

  inline float formula(const float force, const float distance,
                       const float xDis, const float yDis)
  {
    return ((force / distance) * std::abs(xDis)) /
            (std::abs(yDis) + std::abs(xDis));
  }

  void updateMouse(const sf::Vector2i mouse, const bool neg)
  {
  	for(VertexData& p : point)
  	{
      float xDis = p.pos.x - (mouse.x - width/2)*cam.zoom - cam.offSet.x;
      float yDis = p.pos.y - (mouse.y - height/2)*cam.zoom - cam.offSet.y;

           if(xDis < 0 && xDis > -min*cam.zoom) { xDis = -min*cam.zoom; }
      else if(xDis >= 0 && xDis < min*cam.zoom) { xDis = min*cam.zoom; }

           if(yDis < 0 && yDis > -min*cam.zoom) { yDis = -min*cam.zoom; }
      else if(yDis >= 0 && yDis < min*cam.zoom) { yDis = min*cam.zoom; }

      const float distance = sqrtf((xDis*xDis) + (yDis*yDis)) / cam.zoom;

      if(xDis > 0 ^ neg) p.vel.x -= formula(force, distance, xDis, yDis);
                    else p.vel.x += formula(force, distance, xDis, yDis);
      if(yDis > 0 ^ neg) p.vel.y -= formula(force, distance, yDis, xDis);
                    else p.vel.y += formula(force, distance, yDis, xDis);
  	}
  }

  void reset()
  {
  	for(std::size_t i = 0; i < amount; ++i)
  	{
      point[i].vel = sf::Vector2f(0, 0);
      point[i].pos = sf::Vector2f(i%sqrtAmount, ((i-(i%sqrtAmount))/sqrtAmount));

      draw[i].color = sf::Color((point[i].pos.x * 255.f) / sqrtAmount,
                                (point[i].pos.y * 255.f) / sqrtAmount,
                       255.f - ((point[i].pos.x * 255.f) / sqrtAmount));
  	}
  }

  Camera cam;
  std::vector<VertexData> point;
  sf::VertexArray draw = sf::VertexArray(sf::Points, amount);
};

#endif
