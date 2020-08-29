#pragma once

#include "resource.h"

#include <windows.h>

#include "commdlg.h"

#include <string>

#include "ImageClass.h"

#include <d2d1.h>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <dwrite.h>

#include "D2DRenderClass.h"

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
