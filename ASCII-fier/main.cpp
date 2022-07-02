#include <iostream>
#include <string>
#include "Image/Image.h"

int Map(int x, int in_min, int in_max, int out_min, int out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

std::string ImageToAscii(Image& image, int offset)
{
	image.ChangeColorFormat(Image::Y);

	std::string result;
	for (int y = 0; y < image.GetHeight(); y++)
	{
		for (int x = 0; x < image.GetWidth(); x++)
		{
			int val = Map(image.GetPixel(x, y).x, 0, 255, 0, 100) + offset;

			if (val > 90)
				result += '@';
			else if (val > 80)
				result += '#';
			else if (val > 60)
				result += 'M';
			else if (val > 50)
				result += '=';
			else if (val > 25)
				result += '*';
			else if (val > 10)
				result += '.';
			else
				result += ' ';
		}
		result += '\n';
	}

	return result;
}


int main(int argc, char** argv)
{
	std::string path;
	int width = 0, height = 0, brightness = 0;
	std::string result = "Created using ASCII-fier by Vlad-07\n";

	std::cout << "Image path:\n";
	std::cin >> path;

	Image image(path);
	if (!image.IsOK())
		return 1;

	std::cout << "ASCII size (w h)(0 0 for default):\n";
	std::cin >> width >> height;

	std::cout << "Brightness level (-10 to 10 recommended; 0 default):\n";
	std::cin >> brightness;

	if (width == 0 && height == 0)
		width = 200, height = 80;

	Image smol(image.Resize(width, height));
	

	result += ImageToAscii(smol, brightness);
	std::cout << result << "\n\n Save intermediare image to disk?(y/n) ";

	char c;
	std::cin >> c;
	if (c == 'y')
		smol.SaveToDisk("intermediare.png");
	return 0;
}