//-----------------------------------------------------------------------------
// File : asdxBuiltinShader.h
// Desc : Built-in Shader.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------
#pragma once

namespace asdx {

///////////////////////////////////////////////////////////////////////////////
// BuiltinShader class
///////////////////////////////////////////////////////////////////////////////
class BuiltinShader
{
public:
    static const char* GetQuad_VS();
    static const char* GetCopyRGBA_PS();
    static const char* GetCopyRRRR_PS();
    static const char* GetCopyGGGG_PS();
    static const char* GetCopyBBBB_PS();
    static const char* GetCopyAAAA_PS();
    static const char* GetLinearDepth_PS();
    static const char* GetDepthDownSample_PS();
};

} // namespace asdx