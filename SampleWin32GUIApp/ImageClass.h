#pragma once

#include <Windows.h>
#include <string>
#include <cstring>
#include <locale>
#include <codecvt>

class ImageClass
{
public:
	ImageClass();
	~ImageClass();

	void SetImage(const std::wstring &filePath);

	HBITMAP GetImage();

private:
	HBITMAP hbmp;

};

