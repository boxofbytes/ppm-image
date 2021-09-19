# ppm-image
A PPM image parser with only one header file. The header file is in `/src/` and to use it, you just include it.
There is an `image_open` function, it returns an `image` structure with a width, height, and a buffer. The buffer is a vector of `rgb`  structures, and each element is one pixel left to right top to bottom. The `rgb` structures have an r, g, and b value.
# dependencies
It only uses the C++ standard library, so there are no dependencies.
# development
If you found a bug or you have a suggestion, you can always open up an issue about it. However, if you want to add actual code to the repository, then you can submit a pull request.
# examples
This image was rendered in `gnome-terminal`, with the PPM image parser. It uses ANSI escape sequences to make the characters colorized, and it uses full block characters.
![Screenshot](./examples/asciiexample.png)
Heres the source code, compile it with `g++ code.cpp -o exec` in a terminal and run it with `./exec`. Of course, you will need to move the main `ppm.hpp` file to your header include folder. (`/usr/include` on linux.) Or you can just add the `-I` flag to g++ and set it to the folder where your `ppm.hpp` file is. Change the image directory parameter in `image_open()` or copy the `ppmtest.ppm` image in this repository into the folder where your code file is at.
```c++
/* libraries */
#include <stdio.h>
#include <ppm.hpp>

/* prints out a message that is colored in an rgb color and then it resets the terminal color */
void print_color(const char* message, int r, int g, int b) {
   std::string mainCode = "\033[0;38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
   printf(mainCode.c_str());
   printf(message);
   printf("\033[0m");
}


/* main function */
int main(int argc, const char* argv[]) {
   image cool_image;
   cool_image = image_open("./ppmtest.ppm");
   for(uint64_t y = 0; y < cool_image.height; y++) {
      for(uint64_t x = 0; x < cool_image.width; x++) {
         const char* message = "█";
         rgb current_pixel = cool_image.buffer[x + (y * cool_image.width)];
         print_color(message, current_pixel.r, current_pixel.g, current_pixel.b);
         print_color(message, current_pixel.r, current_pixel.g, current_pixel.b);
      }
      printf("\n");
   }
   return 0;
}  
```
