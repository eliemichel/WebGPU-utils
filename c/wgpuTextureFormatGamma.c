#include <webgpu/webgpu.h>

/**
 * Indicate what gamma correction must be applied to a linear color prior to
 * writing it in a texture that has the given format.
 * 
 * For instance, if your color attachment has the given format, your fragment
 * should end like this (assuming it is operating on linear colors):
 * 
 *     let corrected_color = pow(linear_color, vec4f(gamma));
 *     return corrected_color;
 * 
 * @param format the format of the texture we write to
 * 
 * @return a gamma of 2.2 if the format uses the sRGB scale, 1.0 otherwise
 *         (i.e., it uses a linear scale)
 */
float wgpuTextureFormatGamma(WGPUTextureFormat format) {
	switch (format)
	{
	case WGPUTextureFormat_ASTC10x10UnormSrgb:
	case WGPUTextureFormat_ASTC10x5UnormSrgb:
	case WGPUTextureFormat_ASTC10x6UnormSrgb:
	case WGPUTextureFormat_ASTC10x8UnormSrgb:
	case WGPUTextureFormat_ASTC12x10UnormSrgb:
	case WGPUTextureFormat_ASTC12x12UnormSrgb:
	case WGPUTextureFormat_ASTC4x4UnormSrgb:
	case WGPUTextureFormat_ASTC5x5UnormSrgb:
	case WGPUTextureFormat_ASTC6x5UnormSrgb:
	case WGPUTextureFormat_ASTC6x6UnormSrgb:
	case WGPUTextureFormat_ASTC8x5UnormSrgb:
	case WGPUTextureFormat_ASTC8x6UnormSrgb:
	case WGPUTextureFormat_ASTC8x8UnormSrgb:
	case WGPUTextureFormat_BC1RGBAUnormSrgb:
	case WGPUTextureFormat_BC2RGBAUnormSrgb:
	case WGPUTextureFormat_BC3RGBAUnormSrgb:
	case WGPUTextureFormat_BC7RGBAUnormSrgb:
	case WGPUTextureFormat_BGRA8UnormSrgb:
	case WGPUTextureFormat_ETC2RGB8A1UnormSrgb:
	case WGPUTextureFormat_ETC2RGB8UnormSrgb:
	case WGPUTextureFormat_ETC2RGBA8UnormSrgb:
	case WGPUTextureFormat_RGBA8UnormSrgb:
		return 2.2f;
	default:
		return 1.0f;
	}
}
