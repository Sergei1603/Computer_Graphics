/*

    Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <iostream>
#include "texture.h"
#include <stb_image.h>

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
//    m_pImage = NULL;
}

bool Texture::Load()
{/*
    try {
        m_pImage = new Magick::Image(m_fileName);
        m_pImage->write(&m_blob, "RGBA");
    }
    catch (Magick::Error& Error) {
        std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
        return false;
    }*/
    stbi_set_flip_vertically_on_load(1);
    int width, height, bpp = 0;

    unsigned char* image_data = stbi_load(m_fileName.c_str(), &width, &height, &bpp, 0);

    if (!image_data) {
        printf("Can't load texture from '%s' - %s\n", m_fileName.c_str(), stbi_failure_reason());
        exit(0);
    }

    printf("Width %d, height %d, bpp %d\n", width, height, bpp);

    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);
    if (m_textureTarget == GL_TEXTURE_2D) {
        glTexImage2D(m_textureTarget, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    }
    else {
        printf("Support......");
    }
    glTexParameteri(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);

 //   glGenerateMipmap(m_textureTarget);

    glBindTexture(m_textureTarget, 0);

    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}