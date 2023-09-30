#include <webgpu/webgpu.h>

namespace wgpu {

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
float textureFormatGamma(TextureFormat format) {
	switch (format)
	{
	case TextureFormat::ASTC10x10UnormSrgb:
	case TextureFormat::ASTC10x5UnormSrgb:
	case TextureFormat::ASTC10x6UnormSrgb:
	case TextureFormat::ASTC10x8UnormSrgb:
	case TextureFormat::ASTC12x10UnormSrgb:
	case TextureFormat::ASTC12x12UnormSrgb:
	case TextureFormat::ASTC4x4UnormSrgb:
	case TextureFormat::ASTC5x5UnormSrgb:
	case TextureFormat::ASTC6x5UnormSrgb:
	case TextureFormat::ASTC6x6UnormSrgb:
	case TextureFormat::ASTC8x5UnormSrgb:
	case TextureFormat::ASTC8x6UnormSrgb:
	case TextureFormat::ASTC8x8UnormSrgb:
	case TextureFormat::BC1RGBAUnormSrgb:
	case TextureFormat::BC2RGBAUnormSrgb:
	case TextureFormat::BC3RGBAUnormSrgb:
	case TextureFormat::BC7RGBAUnormSrgb:
	case TextureFormat::BGRA8UnormSrgb:
	case TextureFormat::ETC2RGB8A1UnormSrgb:
	case TextureFormat::ETC2RGB8UnormSrgb:
	case TextureFormat::ETC2RGBA8UnormSrgb:
	case TextureFormat::RGBA8UnormSrgb:
		return 2.2f;
	default:
		return 1.0f;
	}
}

} // namespace wgpu

