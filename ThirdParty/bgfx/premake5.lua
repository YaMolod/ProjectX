local BUILD_DIR = path.join("build", _ACTION)
if _OPTIONS["cc"] ~= nil then
	BUILD_DIR = BUILD_DIR .. "_" .. _OPTIONS["cc"]
end
local BGFX_DIR = "bgfx"
local BIMG_DIR = "bimg"
local BX_DIR = "bx"
local GLFW_DIR = "glfw"

function setBxCompat()
	filter "action:vs*"
		includedirs { path.join(BX_DIR, "include/compat/msvc") }
	filter { "system:windows", "action:gmake" }
		includedirs { path.join(BX_DIR, "include/compat/mingw") }
end

project "bgfx"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	exceptionhandling "Off"
	rtti "Off"
	defines "__STDC_FORMAT_MACROS"
	staticruntime "on"
	files
	{
		path.join(BGFX_DIR, "include/bgfx/**.h"),
		path.join(BGFX_DIR, "src/*.cpp"),
		path.join(BGFX_DIR, "src/*.h"),
	}
	excludes
	{
		path.join(BGFX_DIR, "src/amalgamated.cpp"),
	}
	includedirs
	{
		path.join(BX_DIR, "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "3rdparty/dxsdk/include"),
		path.join(BGFX_DIR, "3rdparty/khronos")
	}
	filter "action:vs*"
		defines "_CRT_SECURE_NO_WARNINGS"
		excludes
		{
			path.join(BGFX_DIR, "src/glcontext_glx.cpp"),
			path.join(BGFX_DIR, "src/glcontext_egl.cpp")
		}
	filter "configurations:Release"
		defines "BX_CONFIG_DEBUG=0"
		runtime "Release"
	filter "configurations:Debug"
		defines "BX_CONFIG_DEBUG=1"
		runtime "Debug"
	filter "action:vs*"
		defines "_CRT_SECURE_NO_WARNINGS"
	setBxCompat()

	project "bimg"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	exceptionhandling "Off"
	rtti "Off"
	staticruntime "on"

	local ASTC_CODEC_DIR = path.join(BIMG_DIR, "3rdparty/astc-codec")
	
	files
	{
		path.join(BIMG_DIR, "include/**"),
		path.join(BIMG_DIR, "src/image_decode.cpp"),
		path.join(BIMG_DIR, "include/bimg/*.h"),
		path.join(BIMG_DIR, "src/image.cpp"),
		path.join(BIMG_DIR, "src/image_gnf.cpp"),
		path.join(BIMG_DIR, "src/*.h"),
		path.join(BIMG_DIR, "3rdparty/astc-codec/src/decoder/*.cc"),

		path.join(ASTC_CODEC_DIR, "src/decoder/astc_file.*"),
		path.join(ASTC_CODEC_DIR, "src/decoder/codec.*"),
		path.join(ASTC_CODEC_DIR, "src/decoder/endpoint_codec.*"),
		path.join(ASTC_CODEC_DIR, "src/decoder/footprint.*"),
		path.join(ASTC_CODEC_DIR, "src/decoder/integer_sequence_codec.*"),
		path.join(ASTC_CODEC_DIR, "src/decoder/intermediate_astc_block.*"),
		path.join(ASTC_CODEC_DIR, "src/decoder/logical_astc_block.*"),
		path.join(ASTC_CODEC_DIR, "src/decoder/partition.*"),
		path.join(ASTC_CODEC_DIR, "src/decoder/physical_astc_block.*"),
		path.join(ASTC_CODEC_DIR, "src/decoder/quantization.*"),
		path.join(ASTC_CODEC_DIR, "src/decoder/weight_infill.*"),

		path.join(BIMG_DIR, "3rdparty/tinyexr/deps/miniz/miniz.*"),
	}
	includedirs
	{
		path.join(BX_DIR, "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BIMG_DIR, "3rdparty"),
		path.join(BIMG_DIR, "3rdparty/astc-codec"),
		path.join(BIMG_DIR, "3rdparty/astc-codec/include"),
		path.join(BIMG_DIR, "3rdparty/tinyexr/deps/miniz"),
	}
	filter "configurations:Release"
		defines "BX_CONFIG_DEBUG=0"
		runtime "Release"
	filter "configurations:Debug"
		defines "BX_CONFIG_DEBUG=1"
		runtime "Debug"
	filter "action:vs*"
		defines "_CRT_SECURE_NO_WARNINGS"
	setBxCompat()

project "bx"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	exceptionhandling "Off"
	rtti "Off"
	defines "__STDC_FORMAT_MACROS"
	staticruntime "on"
	files
	{
		path.join(BX_DIR, "include/bx/*.h"),
		path.join(BX_DIR, "include/bx/inline/*.inl"),
		path.join(BX_DIR, "src/*.cpp")
	}
	excludes
	{
		path.join(BX_DIR, "src/amalgamated.cpp"),
		path.join(BX_DIR, "src/crtnone.cpp")
	}
	includedirs
	{
		path.join(BX_DIR, "3rdparty"),
		path.join(BX_DIR, "include")
	}
	filter "configurations:Release"
		defines "BX_CONFIG_DEBUG=0"
		runtime "Release"
	filter "configurations:Debug"
		defines "BX_CONFIG_DEBUG=1"
		runtime "Debug"
	filter "action:vs*"
		defines "_CRT_SECURE_NO_WARNINGS"
	setBxCompat()
		
project "glfw"
	kind "StaticLib"
	language "C"
	staticruntime "on"
	files
	{
		path.join(GLFW_DIR, "include/GLFW/*.h"),
		path.join(GLFW_DIR, "src/context.c"),
		path.join(GLFW_DIR, "src/egl_context.*"),
		path.join(GLFW_DIR, "src/init.c"),
		path.join(GLFW_DIR, "src/input.c"),
		path.join(GLFW_DIR, "src/internal.h"),
		path.join(GLFW_DIR, "src/monitor.c"),
		path.join(GLFW_DIR, "src/null*.*"),
		path.join(GLFW_DIR, "src/osmesa_context.*"),
		path.join(GLFW_DIR, "src/platform.c"),
		path.join(GLFW_DIR, "src/vulkan.c"),
		path.join(GLFW_DIR, "src/window.c"),
	}
	includedirs { path.join(GLFW_DIR, "include") }
	filter "system:windows"
		defines "_GLFW_WIN32"
		files
		{
			path.join(GLFW_DIR, "src/win32_*.*"),
			path.join(GLFW_DIR, "src/wgl_context.*")
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
	filter "action:vs*"
		defines "_CRT_SECURE_NO_WARNINGS"
