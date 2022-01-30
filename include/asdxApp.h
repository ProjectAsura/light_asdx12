//-----------------------------------------------------------------------------
// File : asdxApp.h
// Desc : Application.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <gfx.h>
#include <gfx_window.h>
#include <gfx_imgui.h>
#include <gfx_scene.h>


#ifdef ASDX_AUTO_LINK
//-----------------------------------------------------------------------------
// Linker
//-----------------------------------------------------------------------------
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgui.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib" )
#pragma comment(lib, "comctl32.lib" )
#pragma comment(lib, "dxcompiler.lib" )
#endif


namespace asdx {

///////////////////////////////////////////////////////////////////////////////
// App class
///////////////////////////////////////////////////////////////////////////////
class App
{
public:
    App(const char* title, uint32_t width = 1920, uint32_t height = 1080);
    virtual ~App();
    void Run();

    bool IsKeyDown      (uint32_t keyCode);
    bool IsKeyPressed   (uint32_t keyCode);
    bool IsKeyReleased  (uint32_t keyCode);
    bool HasFocus       () const;
    uint32_t GetWidth   () const;
    uint32_t GetHeight  () const;

protected:
    virtual bool OnInit (GfxContext context) { return true; }
    virtual void OnTerm (GfxContext context) {}
    virtual void OnDraw (GfxContext context) {}
    GfxWindow  GetWindow () const;
    GfxContext GetContext() const;

private:
    GfxContext  m_Context;
    GfxWindow   m_Window;
    const char* m_Title     = nullptr;
    uint32_t    m_Width     = 1920;
    uint32_t    m_Height    = 1080;

    bool Init       ();
    void Term       ();
    void MainLoop   ();
};

} // namespace asdx
