#include <iostream>
#include <fstream>
#include <array>

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

int main()
{
const  int buffer_w = 640;
const   int buffer_h = 480;
  std::array<uint32_t, buffer_w * buffer_h>  buffer;

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

  std::string outname = "outppm.ppm";
  print_ppm_image<buffer_w, buffer_h>(outname, buffer_w, buffer_h, buffer);

  return 0;
  }