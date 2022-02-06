//-----------------------------------------------------------------------------
// File : asdxApp.cpp
// Desc : Application.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------
#define GFX_IMPLEMENTATION_DEFINE

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <asdxApp.h>
#include <asdxMath.h>
#include <asdxResTexture.h>


namespace {

//-----------------------------------------------------------------------------
// Constant Values.
//-----------------------------------------------------------------------------
const char g_Quad_VS[] = {
#include "../res/shader/Quad_VS.txt"
};
const char g_LinearDepth_PS[] = {
#include "../res/shader/LinearDepth_PS.txt"
};
const char g_DepthDownSample_PS[] = {
#include "../res/shader/DepthDownSample_PS.txt"
};
const char g_CopyRed_PS[] = {
#include "../res/shader/CopyRRRR_PS.txt"
};
const char g_CopyGreen_PS[] = {
#include "../res/shader/CopyGGGG_PS.txt"
};
const char g_CopyBlue_PS[] = {
#include "../res/shader/CopyBBBB_PS.txt"
};
const char g_CopyAlpha_PS[] = {
#include "../res/shader/CopyAAAA_PS.txt"
};

} // namespcae

namespace asdx {

///////////////////////////////////////////////////////////////////////////////
// App class
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//      コンストラクタです.
//-----------------------------------------------------------------------------
App::App(const char* title, uint32_t width, uint32_t height)
: m_Title   (title)
, m_Width   (width)
, m_Height  (height)
{ /* DO_NOTHING */ }

//-----------------------------------------------------------------------------
//      デストラクタです.
//-----------------------------------------------------------------------------
App::~App()
{ /* DO_NOTHING */ }

//-----------------------------------------------------------------------------
//      アプリケーションを実行します.
//-----------------------------------------------------------------------------
void App::Run()
{
    if (Init())
    { MainLoop(); }

    Term();
}

//-----------------------------------------------------------------------------
//      初期化処理を行います.
//-----------------------------------------------------------------------------
bool App::Init()
{
    m_Window  = gfxCreateWindow(m_Width, m_Height, m_Title);
    m_Context = gfxCreateContext(m_Window);

    // Quad for PostProcess.
    {
        struct QuadVertex
        {
            Vector2 Pos;
            Vector2 Uv;
        };

        QuadVertex vertices[] = {
            { Vector2(-1.0f,  1.0f), Vector2(0.0f, 0.0f) },
            { Vector2( 3.0f,  1.0f), Vector2(2.0f, 0.0f) },
            { Vector2(-1.0f, -3.0f), Vector2(0.0f, 2.0f) },
        };

        m_QuadVB = gfxCreateBuffer(m_Context, sizeof(vertices), vertices);
    }

    if (!OnInit(m_Context))
    { return false; }

    return true;
}

//-----------------------------------------------------------------------------
//      終了処理を行います.
//-----------------------------------------------------------------------------
void App::Term()
{
    OnTerm(m_Context);
    gfxDestroyBuffer(m_Context, m_QuadVB);
    gfxDestroyContext(m_Context);
    gfxDestroyWindow(m_Window);
}

//-----------------------------------------------------------------------------
//      メインループです.
//-----------------------------------------------------------------------------
void App::MainLoop()
{
    while(!gfxWindowIsCloseRequested(m_Window))
    {
        gfxWindowPumpEvents(m_Window);

        OnDraw(m_Context);

        // シェーダリロード.
        if (gfxWindowIsKeyPressed(m_Window, VK_F5))
        { gfxKernelReloadAll(m_Context); }
        // アプリ終了.
        else if (gfxWindowIsKeyPressed(m_Window, VK_ESCAPE))
        { PostQuitMessage(0); }
    }
}

//-----------------------------------------------------------------------------
//      キーが下がったかどうか.
//-----------------------------------------------------------------------------
bool App::IsKeyDown(uint32_t keyCode)
{ return gfxWindowIsKeyDown(m_Window, keyCode); }

//-----------------------------------------------------------------------------
//      キーが押されたかどうか.
//-----------------------------------------------------------------------------
bool App::IsKeyPressed(uint32_t keyCode)
{ return gfxWindowIsKeyPressed(m_Window, keyCode); }

//-----------------------------------------------------------------------------
//      キーが離されたかどうか.
//-----------------------------------------------------------------------------
bool App::IsKeyReleased(uint32_t keyCode)
{ return gfxWindowIsKeyReleased(m_Window, keyCode); }

//-----------------------------------------------------------------------------
//      フォーカスを持つかどうか.
//-----------------------------------------------------------------------------
bool App::HasFocus() const
{ return GetActiveWindow() == m_Window.getHWND(); }

//-----------------------------------------------------------------------------
//      ウィンドウを取得します.
//-----------------------------------------------------------------------------
GfxWindow App::GetWindow() const
{ return m_Window; }

//-----------------------------------------------------------------------------
//      コンテキストを取得します.
//-----------------------------------------------------------------------------
GfxContext App::GetContext() const
{ return m_Context; }

//-----------------------------------------------------------------------------
//      横幅を取得します.
//-----------------------------------------------------------------------------
uint32_t App::GetWidth() const
{ return gfxGetBackBufferWidth(m_Context); }

//-----------------------------------------------------------------------------
//      縦幅を取得します.
//-----------------------------------------------------------------------------
uint32_t App::GetHeight() const
{ return gfxGetBackBufferHeight(m_Context); }

//-----------------------------------------------------------------------------
//      矩形を描画します.
//-----------------------------------------------------------------------------
void App::DrawQuad()
{
    gfxCommandBindVertexBuffer(m_Context, m_QuadVB);
    gfxCommandDraw(m_Context, 3);
}

//-----------------------------------------------------------------------------
//      テクスチャを生成します.
//-----------------------------------------------------------------------------
GfxTexture App::CreateTexture(const char* path)
{
    GfxTexture result = {};

    ResTexture resTexture;
    if (!resTexture.LoadFromFileA(path))
    {
        resTexture.Dispose();
        return result;
    }

    GfxBuffer buffer = gfxCreateBuffer(
        m_Context,
        resTexture.PixelSize,
        resTexture.pPixels,
        kGfxCpuAccess_Write);
    if (buffer.getSize() == 0)
    {
        resTexture.Dispose();
        return result;
    }

    switch(resTexture.Dimension)
    {
    case TEXTURE_DIMENSION_1D:
        result = gfxCreateTexture2D(
            m_Context,
            resTexture.Width,
            1u, (DXGI_FORMAT)resTexture.Format,
            resTexture.MipMapCount);
        break;

    case TEXTURE_DIMENSION_2D:
        result = gfxCreateTexture2D(
            m_Context,
            resTexture.Width,
            resTexture.Height,
            (DXGI_FORMAT)resTexture.Format,
            resTexture.MipMapCount);
        break;

    case TEXTURE_DIMENSION_3D:
        result = gfxCreateTexture3D(
            m_Context,
            resTexture.Width,
            resTexture.Height,
            resTexture.Depth,
            (DXGI_FORMAT)resTexture.Format,
            resTexture.MipMapCount);
        break;

    case TEXTURE_DIMENSION_CUBE:
        result = gfxCreateTextureCube(
            m_Context,
            resTexture.Width,
            (DXGI_FORMAT)resTexture.Format,
            resTexture.MipMapCount);
        break;
    }

    gfxCommandCopyBufferToTexture(m_Context, result, buffer);
    gfxDestroyBuffer(m_Context, buffer);
    resTexture.Dispose();

    return result;
}

const char* App::GetQuadVS()
{ return g_Quad_VS; }

const char* App::GetLinearDepthPS()
{ return g_LinearDepth_PS; }

const char* App::GetDepthDownSamplePS()
{ return g_DepthDownSample_PS; }

const char* App::GetCopyRedPS()
{ return g_CopyRed_PS; }

const char* App::GetCopyGreenPS()
{ return g_CopyGreen_PS; }

const char* App::GetCopyBluePS()
{ return g_CopyBlue_PS; }

const char* App::GetCopyAlphaPS()
{ return g_CopyAlpha_PS; }

} // namespace asdx
