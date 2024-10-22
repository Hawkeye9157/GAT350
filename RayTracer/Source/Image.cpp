#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>


bool Image::Load(const std::string& filename)
{
    //load image getting the width and height
    int channels = 0;
    uint8_t* data = stbi_load(filename.c_str(), &m_width,&m_height,&channels,4);
    if (!data) {
        std::cerr << "Error Loading Image: " << filename << std::endl;
        return false;
    }

    m_buffer.resize(m_width * m_height);

    std::memcpy(m_buffer.data(), data, m_width * m_height * sizeof(color_t));

    stbi_image_free(data);

    return true;
}