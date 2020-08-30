#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <dwrite.h>
#include <string>
#include <windows.h>
#include <vector>

typedef struct {
    std::wstring fontName;
    std::wstring text;
    DWRITE_TEXT_ALIGNMENT textAligment;
    DWRITE_PARAGRAPH_ALIGNMENT paragraphAligment;
    float fontSize;
    float left;
    float top;
    float width;
    float height;
} TextStruct;

class D2DRenderClass
{
public:
    D2DRenderClass();
    D2DRenderClass(HWND hwnd);
    ~D2DRenderClass();

    template<class Interface>
    inline void
        SafeRelease(
            Interface** ppInterfaceToRelease
        )
    {
        if (*ppInterfaceToRelease != NULL)
        {
            (*ppInterfaceToRelease)->Release();

            (*ppInterfaceToRelease) = NULL;
        }
    }



    IWICImagingFactory* pWICImagingFactory = nullptr;
    ID2D1Factory* pD2D1Factory = nullptr;
    IDWriteFactory* pDirectWriteFactory = nullptr;
    IDWriteTextFormat* pDWriteTextFormat = nullptr;
    ID2D1HwndRenderTarget* pRenderTarget = nullptr;
    ID2D1SolidColorBrush* pBlackBrush = nullptr;

    std::vector<std::pair<IDWriteTextFormat*, TextStruct> > textList = {};


    void DiscardDeviceResources();

    HRESULT CreateD2Ddevice();

    HRESULT CreateD2DDeviceResource();

    HRESULT CreateD2DText(const TextStruct &data);

    HRESULT OnRender();

    HRESULT OnRenderText();

    TextStruct CreateTextStructData(const std::wstring& fontName, const std::wstring& text, const float &fontSize = 12.0,
        const DWRITE_TEXT_ALIGNMENT &textAlignment = DWRITE_TEXT_ALIGNMENT_CENTER, const DWRITE_PARAGRAPH_ALIGNMENT &paragraphAligment = DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 
        const float &left = 0.0, const float &top = 0.0);

private:
    HWND hWnd = NULL;
};

