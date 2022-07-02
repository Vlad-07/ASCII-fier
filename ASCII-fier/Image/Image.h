#include <iostream>
#include <string>
#include "../Utils.h"
#include "../vendor/stb_image/stb_image.h"

class Image
{
public:
	enum ColorFormat
	{
		None = 0, Y, R, G, B, RG, GB, RB, RGB
	};

	Image(const std::string path);
	Image(stbi_uc* data, int width, int height, int channels);
	~Image();

	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }
	int GetChannels() { return m_Channels; }
	bool IsOK() { return m_IsOK; }
	stbi_uc* GetData() { return m_Data; }
	Vec3 GetPixel(int x, int y);
	Vec3S GetModifialePixel(int x, int y);

	void SetChannels(int channels) { m_Channels = channels; }
	void ChangeColorFormat(ColorFormat format);
	Image Resize(int newWidth, int newHeight, int newChannels = 0);

	void SaveToDisk(const std::string name);

	uint8_t operator[](int i);

private:
	stbi_uc* m_Data;
	int m_Width, m_Height, m_Channels;
	bool m_IsOK = false;
};