#pragma once
#include "../../config.h"

namespace util {
	Image load_from_file(const char* filename);

	void free_image_memory(Image oldImage);
	float rand_FloatRange(float a, float b);
}