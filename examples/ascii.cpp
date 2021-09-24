/* libraries */
#include <assert.h>
#include <ppm.hpp>
#include <stdio.h>
#include <string.h>

/* ppm namespace */
using namespace ppm;

/* main function */
int main(int argc, const char* argv[]) {
	const image cool_image = image_open("./ppmtest.ppm");

	const char pixel_template[] = "\033[0;38;2;%i;%i;%im██";
	const size_t max_pixel_length = 28; 							/* maximum size of a pixel without null terminator */
	const size_t buffer_length =
		max_pixel_length * cool_image.height * cool_image.width +
		cool_image.width + 								/* newlines */ 
		1; 										/* null terminator */
	size_t index = 0;

	char* buffer = new char[buffer_length];
	rgb pixel;
	char pixel_buffer[max_pixel_length];

	for(uint64_t y = 0; y < cool_image.height; y++) {
		for(uint64_t x = 0; x < cool_image.width; x++) {
			pixel = cool_image.buffer[x + (y * cool_image.width)];
			const int pixel_length = snprintf(
				pixel_buffer, sizeof(pixel_buffer), pixel_template, 
				pixel.r, pixel.g, pixel.b
			);
			assert(pixel_length < max_pixel_length);
			memcpy(buffer + index, pixel_buffer, pixel_length);
			index += pixel_length;
		}
		buffer[index++] = '\n';
	}
	buffer[index++] = '\0';
	assert(index < buffer_length);

	puts(buffer);
	puts("\033[0m");	/* reset color to default */

	delete[] buffer;

	return 0;
}  
