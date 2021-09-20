# ppm-image
A PPM image parser with only one header file. The header file is in `/src/` and to use it, you just include it.
There is an `image_open` function, it returns an `image` structure with a width, height, and a buffer. The buffer is a `std::vector` of `rgb` structures, and each element is one pixel left to right top to bottom. The `rgb` structures have an r, g, and b value.
# dependencies
It only uses the C++ standard library, so there are no dependencies.
# development
If you found a bug or you have a suggestion, you can always open up an issue about it. However, if you want to add actual code to the repository, then you can submit a pull request.
# examples
This image was rendered in `gnome-terminal`, with the PPM image parser. It uses ANSI escape sequences to make the characters colorized, and it uses full block characters. You can try this yourself by compiling [this](./examples/ascii.cpp).
![Screenshot](./examples/asciiexample.png)
