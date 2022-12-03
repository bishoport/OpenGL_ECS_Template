#include "imageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image util::load_from_file(const char* filename) {
	Image image;
	image.pixels = stbi_load(filename, &(image.width), &(image.height), &(image.channels), STBI_rgb_alpha);
	return image;
}

void util::free_image_memory(Image oldImage) {
	stbi_image_free(oldImage.pixels);
}

float util::rand_FloatRange(float a, float b)
{
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}