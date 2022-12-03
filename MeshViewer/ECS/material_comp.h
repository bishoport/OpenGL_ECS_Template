#pragma once

#include "Components.h"
#include "../config.h"

#include "../view/loaders/imageLoader.h"

class MaterialComp : public Component
{
public:
	
	unsigned int texture;
	Image* image;

	void init() override{}

	void update() override{}

	

	void setImage(Image* _image)
	{
		this->image = _image;
		int texWidth, texHeight;

		texWidth = image->width;
		texHeight = image->height;
		unsigned char* data = image->pixels;
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		glTextureStorage2D(texture, 1, GL_RGBA8, texWidth, texHeight);
		glTextureSubImage2D(texture, 0, 0, 0, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void use() {
		glBindTextureUnit(0, texture);
	}


	void onDestroy() override
	{
		glDeleteTextures(1, &texture);
	}
};
