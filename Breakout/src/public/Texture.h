#pragma once


class Texture2D {
public:
    Texture2D();

    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;

    unsigned int getID() const;
    void setInternalFormat(unsigned int internalFormat);
    void setImageFormat(unsigned int imageFormat);

private:
    unsigned int m_ID;

    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_internalFormat;
    unsigned int m_imageFormat;
    unsigned int m_wrapS;
    unsigned int m_wrapT;
    unsigned int m_filterMin;
    unsigned int m_filterMax;
};
