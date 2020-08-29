#include "ImageClass.h"

ImageClass::ImageClass()
{
	hbmp = NULL;
}

ImageClass::~ImageClass()
{

}

void ImageClass::SetImage(const std::wstring& filePath)
{

	hbmp = (HBITMAP)LoadImage(NULL, filePath.c_str(), IMAGE_BITMAP, 
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

HBITMAP ImageClass::GetImage()
{
	return hbmp;
}