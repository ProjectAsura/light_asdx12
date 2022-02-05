﻿//-----------------------------------------------------------------------------
// File : asdxApp.cpp
// Desc : Application.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------
#define GFX_IMPLEMENTATION_DEFINE

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <asdxApp.h>


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
    {
        const char* path = "../external/gfx/third_party/WinPixEventRuntime-1.0.200127001/bin/x64/WinPixEventRuntime.dll";
        m_HandlePix = LoadLibraryA(path);
        if (m_HandlePix == NULL)
        { return false; }
    }

    m_Window  = gfxCreateWindow(m_Width, m_Height, m_Title);
    m_Context = gfxCreateContext(m_Window);
    m_Scene   = gfxCreateScene();

    // Quad for PostProcess.
    {
        struct QuadVertex
        {
            glm::vec2 Pos;
            glm::vec2 Uv;
        };

        QuadVertex vertices[] = {
            { glm::vec2(-1.0f,  0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec2( 3.0f,  0.0f), glm::vec2(2.0f, 0.0f) },
            { glm::vec2(-1.0f, -3.0f), glm::vec2(0.0f, 2.0f) },
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
    gfxDestroyScene(m_Scene);
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
//      シーンを取得します.
//-----------------------------------------------------------------------------
GfxScene App::GetScene() const
{ return m_Scene; }

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

} // namespace asdx
