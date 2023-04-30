#include <cstdint>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#define _USE_MATH_DEFINES
#include <cmath>


// COLORS
uint32_t pack_color(const uint8_t &red, const uint8_t &green, const uint8_t &blue, const uint8_t &alpha=255)
{
  uint32_t color {0};
  color = (red << 24) + (green << 16) + (blue << 8) + alpha;
  return color;
}

void unpack_color(const uint32_t &color, uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t &alpha)
{
  alpha = color & 255;
  blue =  (color >> 8) & 255;
  green = (color >> 16) & 255;
  red   = (color >> 24) & 255;
}

template<size_t w, size_t h>
void print_ppm_image(const std::string filename, const int image_w, const int image_h, const std::array<uint32_t,(w*h)> &buffer)
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
void draw_pixel(int pixel_x, int pixel_y,  std::array<uint32_t, w*h> &buffer, uint32_t color)
{
	  buffer[pixel_y*w + pixel_x] = color;
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

template<size_t w, size_t h>
void draw_texture(const int texture_x, const int texture_y, std::array<uint32_t, w*h> &buffer, const std::array<uint32_t, 64*64> &texture){
  for (int i = texture_y; i  < texture_y + 64; ++i)
    {
      for (int j = texture_x; j < texture_x + 64; ++j)
	{
	  buffer[i*w + j] = texture[(i - texture_y) * 64 + j - texture_x];
	}
    }
}

template <size_t w, size_t h, size_t wall_h>
std::array<uint32_t, wall_h> draw_texture_column (const float frac_hit, const int column_x, std::array<uint32_t, w*h> &buffer, const std::array<uint32_t, 64*64> &texture){

  std::array<uint32_t, wall_h> column {0};
  for (int y = 0; y < wall_h; 
  
}


std::array<uint32_t, 64*64> load_texture(const std::string texture_file_name){
  std::fstream texture_stream(texture_file_name, std::ios_base::in);
  std::string line;
  std::array<int, 64*64*3> texture_buffer {0};
  int line_number = 0;
  
  while(std::getline(texture_stream, line)){


    //skips the header
    if(line_number < 4){;}
    else{

    int line_value = std::stoi(line);
    texture_buffer[line_number - 4] = line_value;
    }
    ++line_number;
  }

  std::vector<uint32_t> texture_vec {0};
  std::array<uint32_t, 64*64> texture {0};
  
  for(int i {0}; i < (64*64*3) - 3; i += 3){
    uint8_t red   = texture_buffer[i];
    uint8_t green = texture_buffer[i+1];
    uint8_t blue  = texture_buffer[i+2];
    uint32_t color = pack_color(red, green, blue);
    //error on last pixel?
    texture[i/3] = color;
  }

  return texture;
  }


int main()
{
  const  int buffer_w = 640;
  const  int buffer_h = 480;
  //  std::array<uint32_t, buffer_w * buffer_h>  buffer;

  int map_h = 40;
  int map_w = 40;

  int map_xsize = buffer_w/map_w;
  int map_ysize = buffer_h/map_h;

  //COLORS
  std::array<uint32_t, 5> four_colors;
  four_colors[0] = pack_color(0,0,0);  //crna
  four_colors[1] = pack_color(51,150,255); //modra
  four_colors[2] = pack_color(255,92,92);  //rdeca
  four_colors[3] = pack_color(245,235,120);  //rumena
  four_colors[4] = pack_color(67,255,116);  //zelena

  
  const char* map[map_xsize * map_ysize] = {"1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1",
					    "1", "0", "0", "0", "1", "0", "0", "0", "0", "4", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "0", "2", "0", "0", "0", "0", "3", "0", "0", "0", "0", "0", "2",
					    "1", "0", "0", "0", "3", "0", "0", "0", "0", "2", "0", "0", "0", "0", "0", "3",
					    "1", "0", "0", "0", "4", "0", "0", "0", "0", "4", "0", "0", "0", "0", "0", "4",
					    "1", "0", "0", "0", "2", "3", "4", "2", "0", "3", "0", "0", "0", "0", "0", "3",
					    "1", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "2",
					    "1", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "1",
					    "1", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "2",
					    "1", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "2", "3", "3",
					    "1", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "3", "4", "1",
					    "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1"};

  //draws the gradient
// for (size_t i = 0; i < buffer_h; ++i)
// {
//   for(size_t j = 0; j < buffer_w; ++j){
//     uint8_t r,g,b,a;
//     r = i*(255/static_cast<float>(buffer_h));
//     g = 100;
//     b = j*(255/(float)(buffer_w));
//     buffer[i*buffer_w + j] = pack_color(r,g,b);
//   }
// }

  //draws the map
//  for (int i = 0; i < map_ysize; ++i)
//    {
//      for(int j = 0; j < map_xsize; ++j)
//	{
//	  if (map[i*map_xsize + j] != "0")
//	    {
//	      draw_rectangle<buffer_w, buffer_h>(map_h, map_w, j*map_w, i*map_h, buffer, pack_color(255,0,0));
//	    }
//	}
//    }

  float player_x = 1.1;
  float player_y = 7;
  float player_a = float(M_PI/180.f) * 0;
  float player_fov = float(M_PI/180.f) * 50;
  float d_angle = player_fov / buffer_w;
  float player_fov2 = player_fov / 2.0;

  std::array<float, buffer_w> wall_texture_index {0};  

  //draw player position
  //  draw_rectangle<buffer_w, buffer_h>(5, 5, player_x * map_w, player_y * map_h, buffer, pack_color(0,0,0));
  
  //main 3D window
  std::string viewportname = "viewport.ppm";
  std::array<uint32_t, buffer_w * buffer_h> viewport;

  //draw skybox and ground
  draw_rectangle<buffer_w, buffer_h>(buffer_h/2, buffer_w, 0, 0, viewport, pack_color(30, 0, 60));
  draw_rectangle<buffer_w, buffer_h>(buffer_h/2, buffer_w, 0, buffer_h/2, viewport, pack_color(102, 51, 0));

  
  //main raymarching loop
  
  for(int horizont = 0; horizont < buffer_w; ++horizont){
    float angle = player_a - player_fov2 + ((player_fov/buffer_w) * horizont);
    float p = 0;
    float hit_x {0};
    float hit_y {0};
    float hit_frac {0};
    bool is_horizontal = false;
    int texture_index {0};
    
    for(; p < 20; p += 0.05)
      {
	float ray_ax = std::cos(angle) * p  + player_x;
	float ray_ay = std::sin(angle) * p  + player_y;
	int target = std::stoi(map[(int(ray_ay) * map_xsize) + int(ray_ax)]);
	//draw_rectangle<buffer_w, buffer_h>(1, 1, ray_ax * map_w, ray_ay * map_h,buffer, pack_color(255,255,255));    //draw ray
	if (target != 0){
	  hit_x = ray_ax - static_cast<int>(ray_ax);
	  hit_y = ray_ay - static_cast<int>(ray_ay);
	  texture_index = target;
	  break;}
      }

    if (hit_x > hit_y)
      {
	is_horizontal = true;
	hit_frac = 64 * hit_x;
      }
    else {hit_frac = 64 * hit_y;}

    

    
    //    std::string outname = "outppm.ppm";
    //    print_ppm_image<buffer_w, buffer_h>(outname, buffer_w, buffer_h, buffer);
      
    wall_texture_index[horizont] = texture_index;
    float wall_distance = p * std::cos(angle - player_a);    

    //draw wall
    float wall_height = std::min(float(buffer_h), buffer_h/wall_distance);
    int y_i = static_cast<int>(buffer_h - (static_cast<float>(buffer_h)/2) - (wall_height/2));
    draw_rectangle<buffer_w, buffer_h>(wall_height, 1, horizont, y_i, viewport, four_colors[wall_texture_index[horizont]]); //height, widt, x, y
  }


  //load and draw texture
  auto  kr = load_texture(std::string("teal_brick_wall.ppm"));
  draw_texture<buffer_w, buffer_h>(0, 0, viewport, kr);
  //um

  //print final 3D view
  print_ppm_image<buffer_w, buffer_h>(viewportname, buffer_w, buffer_h, viewport);

  return 0;
  }
