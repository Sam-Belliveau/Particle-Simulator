#ifndef GROUP_H
#define GROUP_H

#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <cmath>

// Camera position and zoom information
struct Camera
{
  sf::Vector2f offSet = sf::Vector2f(0.f, 0.f);
  float zoom = 3;
};

// Partical Data before being turned into a vertex
struct VertexData
{
  sf::Vector2f vel = sf::Vector2f(0.f, 0.f);
  sf::Vector2f pos = sf::Vector2f(0.f, 0.f);
};

// Group Of Vertexs, Camera, and SFML Group
class Group
{
public:
  Group()
  {
    // Make particle array
    std::vector<VertexData> temp(amount);
    point.swap(temp);
    reset();
  }

  void drawUpdate(sf::RenderWindow& win, const float fps)
  {
    // Loop through particles
  	for(std::size_t i = 0; i < amount; i++)
  	{
      // Calculate velosity based on FPS
      point[i].pos.x += point[i].vel.x/fps;
      point[i].pos.y += point[i].vel.y/fps;

      // Turn particle information into a spot on the screen
      draw[i].position.x = particleToScreen(point[i].pos.x, cam.offSet.x, width);
      draw[i].position.y = particleToScreen(point[i].pos.y, cam.offSet.y, height);
  	}

    // Draw particles
  	win.draw(draw);
  }

  void updateMouse(const sf::Vector2i mouse, const bool neg)
  {
  	for(VertexData& p : point)
  	{
      // Take the distance between particle pos and mouse position per axis.
      float xDis = p.pos.x - screenToParticle(mouse.x, cam.offSet.x, width);
      float yDis = p.pos.y - screenToParticle(mouse.y, cam.offSet.y, height);

      // Handle division by 0 like stuff
           if(xDis < 0 && xDis > -min) { xDis = -min*cam.zoom; }
      else if(xDis >= 0 && xDis < min) { xDis =  min*cam.zoom; }

           if(yDis < 0 && yDis > -min) { yDis = -min*cam.zoom; }
      else if(yDis >= 0 && yDis < min) { yDis =  min*cam.zoom; }

      // Take distance of particle to mouse
      const float distance = sqrtf((xDis*xDis) + (yDis*yDis)) / cam.zoom;

      // Change velosity based on formula
      if((xDis > 0) != neg) p.vel.x -= formula(force, distance, xDis, yDis);
                       else p.vel.x += formula(force, distance, xDis, yDis);
      if((yDis > 0) != neg) p.vel.y -= formula(force, distance, yDis, xDis);
                       else p.vel.y += formula(force, distance, yDis, xDis);
  	}
  }

  // Reset particle positions and velositys
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

private: // Helper functions
  // Formula to turn particle positions into screen positions
  float particleToScreen(const float in, const float c, const float d)
  { return (in + c) / cam.zoom + d/2; }

  // Formula to turn screen positions into particle positions
  float screenToParticle(const float in, const float c, const float d)
  { return (in - d/2) * cam.zoom - c; }

  // Force formula
  float formula(const float force, const float distance,
                const float xDis, const float yDis)
  {
    return ((force / distance) * std::abs(xDis)) /
            (std::abs(yDis) + std::abs(xDis));
  }

};

#endif
