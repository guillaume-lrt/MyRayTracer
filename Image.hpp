#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>

#include "Vec3.h"

class Image{
    public:
        inline Image(size_t width = 520, size_t height = 520): m_width(width), m_height(height){
            m_pixels.resize(width*height);
        }
        
        inline virtual ~Image () {};        // destructor

        inline size_t width() const {return m_width;}
        inline size_t height() const {return m_height;}
        inline std::vector<Vec3f> pixels() const {return m_pixels;}

        inline const Vec3f &operator() (size_t x, size_t y) const {return m_pixels[y*m_width + x];}
        inline Vec3f &operator() (size_t x, size_t y) {return m_pixels[y*m_width + x];}

        void savePPM(const std::string & filename){
            std::ofstream out (filename.c_str ());
            if (!out){
                std::cerr << "Cannot open file " << filename.c_str() << std::endl;
            }
            out << "P3" << std::endl
                << m_width << " " << m_height << std::endl
                << "255" << std::endl;

            for (size_t y = 0; y < m_height; y++){
                for (size_t x = 0; x<m_width; x++){
                    out << std::min(255u, static_cast<unsigned int>(255.f * m_pixels[y * m_width + x][0])) << " "
                        << std::min(255u, static_cast<unsigned int>(255.f * m_pixels[y * m_width + x][1])) << " "
                        << std::min(255u, static_cast<unsigned int>(255.f * m_pixels[y * m_width + x][2])) << " ";
                }
                out << std::endl;
            }
            out.close();
        }

        // void saveJPG(const char *filename) {
        //     auto image_to_write = new unsigned char[m_height*m_width*3];
        //     #pragma omp parallel for 
        //     for (size_t y = 0; y < m_height; y++){
        //         #pragma omp parallel for
        //         for (size_t x = 0; x<m_width; x++){
        //             image_to_write[(y * m_width + x)*3 + 0] = std::min(255u, static_cast<unsigned int>(255.f * m_pixels[y * m_width + x][0]));
        //             image_to_write[(y * m_width + x)*3 + 1] = std::min(255u, static_cast<unsigned int>(255.f * m_pixels[y * m_width + x][1]));
        //             image_to_write[(y * m_width + x)*3 + 2] = std::min(255u, static_cast<unsigned int>(255.f * m_pixels[y * m_width + x][2]));
        //         }
        //     }
        //     stbi_write_jpg("image.jpg", m_width, m_height, 3, image_to_write, 0);
        // }

        void fillBackground(const Vec3f &color = Vec3f(0.f,0.f,1.f)) {
            // #pragma omp parallel for 
            for (size_t y = 0; y < m_height; y++)
            {
                // #pragma omp parallel for
                for (size_t x = 0; x < m_width; x++)
                {
                    static const Vec3f color0 (0.1f,.2f,.8f);
                    static const Vec3f color1 (.9f,.9f,1.0f);
                    float alpha = std::clamp (static_cast<float> (y)/(m_height-1),0.f,1.f);
                    m_pixels[y*m_width+x] = mix (color0, color1,alpha);
                }
            }
        }


    private:
        size_t m_width;
        size_t m_height;
        std::vector<Vec3f> m_pixels;
};