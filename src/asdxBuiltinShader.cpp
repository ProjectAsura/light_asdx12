//-----------------------------------------------------------------------------
// File : asdxBuiltinShader.cpp
// Desc : Built-in Shader.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <asdxBuiltinShader.h>


namespace {

//-----------------------------------------------------------------------------
// Constant Values.
//-----------------------------------------------------------------------------
const char g_Quad_VS[] = {
#include "../res/shader/Quad_VS.txt"
};
const char g_CopyRGBA_PS[] = {
#include "../res/shader/CopyRGBA_PS.txt"
};
const char g_CopyRRRR_PS[] = {
#include "../res/shader/CopyRRRR_PS.txt"
};
const char g_CopyGGGG_PS[] = {
#include "../res/shader/CopyGGGG_PS.txt"
};
const char g_CopyBBBB_PS[] = {
#include "../res/shader/CopyBBBB_PS.txt"
};
const char g_CopyAAAA_PS[] = {
#include "../res/shader/CopyAAAA_PS.txt"
};
const char g_LinearDepth_PS[] = {
#include "../res/shader/LinearDepth_PS.txt"
};
const char g_DepthDownSample_PS[] = {
#include "../res/shader/DepthDownSample_PS.txt"
};

} // namespace

namespace asdx {

///////////////////////////////////////////////////////////////////////////////
// BuiltinShader class
///////////////////////////////////////////////////////////////////////////////
const char* BuiltinShader::GetQuad_VS() { return g_Quad_VS; }
const char* BuiltinShader::GetCopyRGBA_PS() { return g_CopyRGBA_PS; }
const char* BuiltinShader::GetCopyRRRR_PS() { return g_CopyRRRR_PS; }
const char* BuiltinShader::GetCopyGGGG_PS() { return g_CopyGGGG_PS; }
const char* BuiltinShader::GetCopyBBBB_PS() { return g_CopyBBBB_PS; }
const char* BuiltinShader::GetCopyAAAA_PS() { return g_CopyAAAA_PS; }
const char* BuiltinShader::GetLinearDepth_PS() { return g_LinearDepth_PS; }
const char* BuiltinShader::GetDepthDownSample_PS() { return g_DepthDownSample_PS; }

} // namespace asdx
