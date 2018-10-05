#pragma once

#include <iostream>

class Color
{
  float colors[3]; // R = color

public:
  Color();
  Color(float r, float g, float b);
  ~Color();

  void setColor(float r, float g, float b);
  void setRed(float r);
  void setGreen(float g);
  void setBlue(float b);

  float getRed();
  float getGreen();
  float getBlue();

  void print();
};
