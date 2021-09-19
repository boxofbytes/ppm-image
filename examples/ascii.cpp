/* libraries */
#include <assert.h>
#include <ppm.hpp>
#include <stdio.h>
#include <string.h>

/* main function */
int main(int argc, const char* argv[]) {
	const image cool_image = image_open("./ppmtest.ppm");

	const char pixelTemplate[] = "\033[0;38;2;%i;%i;%im██";
	const size_t maxPixelLength = 28; /* maximum size of a pixel without null terminator */
	const size_t bufferLength =
		maxPixelLength * cool_image.height * cool_image.width +
		cool_image.width /* newlines */ +
		1; /* null terminator */
	size_t index = 0;

	char* buffer = new char[bufferLength];

	for(uint64_t y = 0; y < cool_image.height; y++) {
		for(uint64_t x = 0; x < cool_image.width; x++) {
			const rgb pixel = cool_image.buffer[x + (y * cool_image.width)];
			char pixelBuffer[maxPixelLength];
			const int pixelLength = snprintf(
				pixelBuffer, sizeof(pixelBuffer), pixelTemplate, 
				pixel.r, pixel.g, pixel.b
			);
			assert(pixelLength < maxPixelLength);
			memcpy(buffer + index, pixelBuffer, pixelLength);
			index += pixelLength;
		}
		buffer[index++] = '\n';
	}
	buffer[index++] = '\0';
	assert(index < bufferLength);

	puts(buffer);
	puts("\033[0m"); /* reset color to default */

	delete[] buffer;

	return 0;
}  
