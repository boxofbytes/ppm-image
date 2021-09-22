/* include guard */
#ifndef PPM_HPP
#define PPM_HPP

/* libraries */
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>

/* macros */
#define PPM_BEGIN 3
#define SPACE 0x20
#define NEW_LINE 0x0A

/* rgb struct */
struct rgb {
   uint8_t r, g, b;
   void clear() {
      r = 0;
      g = 0;
      b = 0;
   }
};

/* image structure */
struct image {
   public:
   std::vector<rgb> buffer;
   uint64_t width;
   uint64_t height;
   uint16_t original_index;
};

/* function for opening a PPM image, it returns an image class with the */
/* image width and height properties as well as an image buffer         */
image image_open(const std::string& image_path) {
   std::ifstream file(image_path);
   assert(file.is_open() != false);
   std::ostringstream string_stream;
   string_stream << file.rdbuf();
   const std::string& str = string_stream.str();
   std::vector<char> buffer(str.begin(), str.end());
   std::vector<char> char_vector;
   uint64_t image_width;
   uint64_t image_height;
   bool space_found = false;
   uint64_t index = PPM_BEGIN;
   while(!space_found) {
      char current_char = buffer[index];
      if(current_char == SPACE) {
         space_found = true;
      }
      char_vector.push_back(current_char);
      ++index;
   }
   char width_str[char_vector.size()];
   for(uint64_t i = 0; i < char_vector.size(); i++) {
      width_str[i] = char_vector[i];
   }
   image_width = atoi(width_str);
   space_found = false;
   char_vector.clear();
   while(!space_found) {
      char current_char = buffer[index];
      if(current_char == NEW_LINE) {
         space_found = true;
      }
      char_vector.push_back(current_char);
      ++index;
   }
   char height_str[char_vector.size()];
   for(uint64_t i = 0; i < char_vector.size(); i++) {
      height_str[i] = char_vector[i];
   }
   image_height = atoi(height_str);
   space_found = false;
   while(!space_found) {
      char current_char = buffer[index];
      if(current_char == NEW_LINE) {
         space_found = true;
      }
      ++index;
   }
   bool first_pixel_found = false;
   std::vector<rgb> pixel_buffer;
   rgb current_pixel;
   current_pixel.clear();
   ++index;
   uint64_t original_index = index;
   for(; index <= buffer.size(); index++) {
      uint8_t rgb_index = (index - original_index) % 3;
      if(rgb_index == 0) {
         if(first_pixel_found == false) {
            first_pixel_found = true;
         } else {
            pixel_buffer.push_back(current_pixel);
            current_pixel.clear();
         }
         current_pixel.r = buffer[index - 1];
      } else if (rgb_index == 1) {
         current_pixel.g = buffer[index - 1];
         if(index == buffer.size()) {
            pixel_buffer.push_back(current_pixel);
         }
      } else {
         current_pixel.b = buffer[index - 1];
         if(index == buffer.size()) {
            pixel_buffer.push_back(current_pixel);
         }
      }
   }
   image returned_image;
   returned_image.buffer = pixel_buffer;
   returned_image.width = image_width;
   returned_image.height = image_height;
   returned_image.original_index = original_index;
   return returned_image;
}

/* function for inverting an images colors */
void image_invert(image& given_image) {
   rgb new_pixel;
   rgb current_pixel;
   for(uint64_t i = 0; i < given_image.width * given_image.height; i++) {
      current_pixel = given_image.buffer[i];
      new_pixel.clear();
      new_pixel.r = 255 - current_pixel.r;
      new_pixel.g = 255 - current_pixel.g;
      new_pixel.b = 255 - current_pixel.b;
      given_image.buffer[i] = new_pixel;
   }
}

#endif
