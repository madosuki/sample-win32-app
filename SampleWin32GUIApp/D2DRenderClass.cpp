#include "D2DRenderClass.h"

D2DRenderClass::D2DRenderClass()
{
}

D2DRenderClass::D2DRenderClass(HWND hwnd)
{
    this->hWnd = hwnd;
}

D2DRenderClass::~D2DRenderClass()
{
    DiscardDeviceResources();
}

void D2DRenderClass::DiscardDeviceResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBlackBrush);
}

HRESULT D2DRenderClass::CreateD2DText(const TextStruct &data)
{
 
    HRESULT result = pDirectWriteFactory->CreateTextFormat(
        data.fontName.c_str(),
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        data.fontSize,
        L"",
        &pDWriteTextFormat
    );
 

    if (SUCCEEDED(result)) {
        pDWriteTextFormat->SetTextAlignment(data.textAligment);
        pDWriteTextFormat->SetParagraphAlignment(data.paragraphAligment);
    }
    else {

        printf_s("Detect Error at CreateTextFormat");
    }


    return result;
}

HRESULT D2DRenderClass::CreateD2Ddevice()
{
    ID2D1GeometrySink* pSink = nullptr;

    HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2D1Factory);

    if (SUCCEEDED(result)) {
        result = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(pDirectWriteFactory),
            reinterpret_cast<IUnknown**>(&pDirectWriteFactory)
        );
    }


    // SafeRelease(pSink);

    return result;
}

HRESULT D2DRenderClass::CreateD2DDeviceResource()
{
    HRESULT result = S_FALSE;

    if (!pRenderTarget) {
        RECT rc;
        GetClientRect(hWnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top

        );

        result = pD2D1Factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hWnd, size),
            &pRenderTarget
        );

        if (SUCCEEDED(result)) {
            result = pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Black),
                &pBlackBrush
            );
        }
    }

    return result;
}


HRESULT D2DRenderClass::OnRender()
{
    HRESULT result = CreateD2DDeviceResource();

    if (SUCCEEDED(result)) {
        static const WCHAR hello[] = L"Hello World in Y Gakuen!";

        D2D1_SIZE_F renderTargetSize = pRenderTarget->GetSize();

        pRenderTarget->BeginDraw();

        pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

        pRenderTarget->DrawText(
            hello,
            ARRAYSIZE(hello) - 1,
            pDWriteTextFormat,
            D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
            pBlackBrush
        );

        result = pRenderTarget->EndDraw();

        if (result == D2DERR_RECREATE_TARGET) {
            result = S_OK;
            DiscardDeviceResources();
        }
    }

    return result;
}

HRESULT D2DRenderClass::OnRenderText(const TextStruct &data)
{
    HRESULT result = CreateD2DDeviceResource();

    if (SUCCEEDED(result)) {
        result = CreateD2DText(data);
    }

    if (SUCCEEDED(result)) {
        // static const WCHAR hello[] = L"Hello World in Y Gakuen!";

        D2D1_SIZE_F renderTargetSize = pRenderTarget->GetSize();

        pRenderTarget->BeginDraw();

        pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

        pRenderTarget->DrawText(
            data.text.c_str(),
            data.text.size(),
            pDWriteTextFormat,
            D2D1::RectF(data.left, data.top, renderTargetSize.width, renderTargetSize.height),
            pBlackBrush
        );

        result = pRenderTarget->EndDraw();

        if (result == D2DERR_RECREATE_TARGET) {
            result = S_OK;
            DiscardDeviceResources();
        }
    }

    return result;
}

TextStruct D2DRenderClass::CreateTextStructData(const std::wstring& fontName, const std::wstring& text, const float& fontSize,
    const DWRITE_TEXT_ALIGNMENT &textAlignment, const DWRITE_PARAGRAPH_ALIGNMENT &paragraphAligment,
    const float &left, const float &top)
{
    auto tmp = TextStruct{};


    tmp.fontName = fontName;
    tmp.text = text;
    tmp.fontSize = fontSize;
    tmp.textAligment = textAlignment;
    tmp.paragraphAligment = paragraphAligment;
    tmp.left = left;
    tmp.top = top;

    return tmp;

}