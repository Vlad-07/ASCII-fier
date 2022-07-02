#include "Image.h"
#include "../vendor/stb_image_resize/stb_image_resize.h"
#include "../vendor/stb_image_write/stb_image_write.h"

Image::Image(const std::string path)
{
	int width = 0, height = 0, channels = 0;
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, channels);
	if (!data)
	{
		std::cout << "Invalid image path: " + path + "\n\n";
		m_Data = 0;
		m_Width = 0;
		m_Height = 0;
		m_Channels = 0;
		return;
	}

	m_IsOK = true;
	m_Data = data;
	m_Width = width;
	m_Height = height;
	m_Channels = channels;
}

Image::Image(stbi_uc* data, int width, int height, int channels)
{
	m_Data = data;
	m_Width = width;
	m_Height = height;
	m_Channels = channels;
}

Image::~Image()
{
	stbi_image_free(m_Data);
}

Vec3 Image::GetPixel(int x, int y)
{
	Vec3 pixel (m_Data[x * m_Channels + y * m_Width * m_Channels],
				m_Data[x * m_Channels + y * m_Width * m_Channels + 1],
				m_Data[x * m_Channels + y * m_Width * m_Channels + 2]);
	return pixel;
}

Vec3S Image::GetModifialePixel(int x, int y)
{
	Vec3S pixel(m_Data + x * m_Channels + y * m_Width * m_Channels,
				m_Data + x * m_Channels + y * m_Width * m_Channels + 1,
				m_Data + x * m_Channels + y * m_Width * m_Channels + 2);

	return pixel;
}

Image Image::Resize(int newWidth, int newHeight, int newChannels)
{
	if (newChannels == 0)
		newChannels = m_Channels;

	stbi_uc* newData = new stbi_uc[newWidth * newHeight * m_Channels];
	stbir_resize_uint8(m_Data, m_Width, m_Height, 0, newData, newWidth, newHeight, 0, newChannels);

	return Image(newData, newWidth, newHeight, newChannels);
}

void Image::ChangeColorFormat(ColorFormat format)
{
	if (format == None)
	{
		std::cout << "Invalid color format used!\n";
		return;
	}

	if (format == RGB)
		return;

	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			Vec3S pixel = GetModifialePixel(x, y);
			switch (format)
			{
			case Image::Y:
				*(uint8_t*)pixel.x = *(uint8_t*)pixel.y = *(uint8_t*)pixel.z = (*(uint8_t*)pixel.x + *(uint8_t*)pixel.y + *(uint8_t*)pixel.z) / 3;
				break;
			case Image::R:
				*(uint8_t*)pixel.y = *(uint8_t*)pixel.z = 0;
				break;
			case Image::G:
				*(uint8_t*)pixel.x = *(uint8_t*)pixel.z = 0;
				break;
			case Image::B:
				*(uint8_t*)pixel.x = *(uint8_t*)pixel.y = 0;
				break;
			case Image::RG:
				*(uint8_t*)pixel.z = 0;
				break;
			case Image::GB:
				*(uint8_t*)pixel.x = 0;
				break;
			case Image::RB:
				*(uint8_t*)pixel.y = 0;
				break;
			default:
				break;
			}
		}
	}
}

void Image::SaveToDisk(const std::string name)
{
	auto i = name.find_last_of(".");
	std::string type = name.substr(i);

	if (type == ".png")
		stbi_write_png(name.c_str(), m_Width, m_Height, m_Channels, m_Data, 0);
	else if (type == ".jpg")
		stbi_write_jpg(name.c_str(), m_Width, m_Height, m_Channels, m_Data, 0);
	else if (type == ".bmp")
		stbi_write_bmp(name.c_str(), m_Width, m_Height, m_Channels, m_Data);
	else if (type == ".tga")
		stbi_write_tga(name.c_str(), m_Width, m_Height, m_Channels, m_Data);
	else
		std::cout << "Invalid file type given for: '" << name << "'!\n";
}

uint8_t Image::operator[](int i)
{
	return m_Data[i];
}