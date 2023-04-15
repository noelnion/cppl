#include <iostream>
#include <fstream>
#include <array>
#include <cmath>

uint32_t pack_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=255)
{
  uint32_t color {0};
  color = (red << 24) + (green << 16) + (blue << 8) + alpha;
  return color;
}

void unpack_color(const uint32_t color, uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t &alpha)
{
  alpha = color & 255;
  blue =  (color >> 8) & 255;
  green = (color >> 16) & 255;
  red   = (color >> 24) & 255;
}

template<size_t w, size_t h>
void print_ppm_image(std::string filename, int image_w, int image_h, std::array<uint32_t,(w*h)> &buffer)
{
  std::ofstream ofs(filename);
  ofs << "P6\n" << image_w << " " << image_h <<"\n255\n";
  for(int i = 0; i < image_w * image_h; ++i)
    {
      uint8_t r,g,b,a;
      unpack_color(buffer[i], r,g,b,a);
      ofs << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
    }
  ofs.close();
}

template<size_t w, size_t h>
void draw_rectangle(int rect_h, int rect_w, int rect_x, int rect_y, std::array<uint32_t, w*h> &buffer, uint32_t color)
{
  for (int i = rect_y; i  < rect_y + rect_h; ++i)
    {
      for (int j = rect_x; j < rect_x + rect_w;     ++j)
	{
	  buffer[i*w + j] = color;
	}
    }
}

int main()
{
const  int buffer_w = 640;
const   int buffer_h = 480;
  std::array<uint32_t, buffer_w * buffer_h>  buffer;

  int map_h = 40;
  int map_w = 40;

  int map_xsize = buffer_w/map_w;
  int map_ysize = buffer_h/map_h;
  
  const char* map[map_xsize * map_ysize] = {"1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1",
					    "1", "0", "0", "1", "0", "1", "0", "0", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "1", "0", "1", "0", "0", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "1", "0", "1", "0", "0", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "0", "0", "1", "0", "0", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "0", "0", "1", "0", "1", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "0", "0", "0", "0", "1", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "1", "0", "0", "0", "1", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "1", "0", "0", "0", "1", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "1", "0", "0", "0", "1", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "1", "0", "0", "0", "1", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1"};

  
  for (size_t i = 0; i < buffer_h; ++i)
  {
    for(size_t j = 0; j < buffer_w; ++j){
      uint8_t r,g,b,a;
      r = i*(255/static_cast<float>(buffer_h));
      g = 100;
      b = j*(255/(float)(buffer_w));
      buffer[i*buffer_w + j] = pack_color(r,g,b);
    }
  }

  for (int i = 0; i < map_ysize; ++i)
    {
      for(int j = 0; j < map_xsize; ++j)
	{
	  if (map[i*map_xsize + j] == "1")
	    {
	      draw_rectangle<buffer_w, buffer_h>(map_h, map_w, j*map_w, i*map_h, buffer, pack_color(255,0,0));
	    }
	}
    }

  float player_x = 2 * map_w;
  float player_y = 2 * map_h;
  float player_a = 180/3.141592 * 45;

  draw_rectangle<buffer_w, buffer_h>(5, 5, 80, 240, buffer, pack_color(0,0,0));

  for(float p = 0; p < 20; p += 0.05)
    {
      float dy, dx;
      dx = std::
    }
  
  std::string outname = "outppm.ppm";
  print_ppm_image<buffer_w, buffer_h>(outname, buffer_w, buffer_h, buffer);
  std::cout << "done" <<"\n"; 

  return 0;
  }
