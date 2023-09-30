#include <webgpu/webgpu.h>

namespace wgpu {

/**
 * Tell how many bits each texel occupies for a given texture format has.
 * 
 * @param format the texel format of the texture
 * 
 * @return the number of bits
 * 
 * NB: Some compressed format use less than 1 byte (8 bits) per texel, which
 * is why this function cannot return a byte number instead of bits.
 */
uint32_t textureFormatBitsPerTexel(TextureFormat format) {
	switch (format) {
	case TextureFormat::Undefined:
		return 0;
	case TextureFormat::BC1RGBAUnorm:
	case TextureFormat::BC1RGBAUnormSrgb:
	case TextureFormat::BC4RUnorm:
	case TextureFormat::BC4RSnorm:
	case TextureFormat::ETC2RGB8Unorm:
	case TextureFormat::ETC2RGB8UnormSrgb:
	case TextureFormat::ETC2RGB8A1Unorm:
	case TextureFormat::ETC2RGB8A1UnormSrgb:
	case TextureFormat::EACR11Unorm:
	case TextureFormat::EACR11Snorm:
	case TextureFormat::ASTC4x4Unorm:
	case TextureFormat::ASTC4x4UnormSrgb:
	case TextureFormat::ASTC5x4Unorm:
	case TextureFormat::ASTC5x4UnormSrgb:
	case TextureFormat::ASTC5x5Unorm:
	case TextureFormat::ASTC5x5UnormSrgb:
	case TextureFormat::ASTC6x5Unorm:
	case TextureFormat::ASTC6x5UnormSrgb:
	case TextureFormat::ASTC6x6Unorm:
	case TextureFormat::ASTC6x6UnormSrgb:
	case TextureFormat::ASTC8x5Unorm:
	case TextureFormat::ASTC8x5UnormSrgb:
	case TextureFormat::ASTC8x6Unorm:
	case TextureFormat::ASTC8x6UnormSrgb:
	case TextureFormat::ASTC8x8Unorm:
	case TextureFormat::ASTC8x8UnormSrgb:
	case TextureFormat::ASTC10x5Unorm:
	case TextureFormat::ASTC10x5UnormSrgb:
	case TextureFormat::ASTC10x6Unorm:
	case TextureFormat::ASTC10x6UnormSrgb:
	case TextureFormat::ASTC10x8Unorm:
	case TextureFormat::ASTC10x8UnormSrgb:
	case TextureFormat::ASTC10x10Unorm:
	case TextureFormat::ASTC10x10UnormSrgb:
	case TextureFormat::ASTC12x10Unorm:
	case TextureFormat::ASTC12x10UnormSrgb:
	case TextureFormat::ASTC12x12Unorm:
	case TextureFormat::ASTC12x12UnormSrgb:
		return 4;
	case TextureFormat::R8Unorm:
	case TextureFormat::R8Snorm:
	case TextureFormat::R8Uint:
	case TextureFormat::R8Sint:
	case TextureFormat::Stencil8:
	case TextureFormat::BC2RGBAUnorm:
	case TextureFormat::BC2RGBAUnormSrgb:
	case TextureFormat::BC3RGBAUnorm:
	case TextureFormat::BC3RGBAUnormSrgb:
	case TextureFormat::BC5RGUnorm:
	case TextureFormat::BC5RGSnorm:
	case TextureFormat::BC6HRGBUfloat:
	case TextureFormat::BC6HRGBFloat:
	case TextureFormat::BC7RGBAUnorm:
	case TextureFormat::BC7RGBAUnormSrgb:
	case TextureFormat::ETC2RGBA8Unorm:
	case TextureFormat::ETC2RGBA8UnormSrgb:
	case TextureFormat::EACRG11Unorm:
	case TextureFormat::EACRG11Snorm:
		return 8;
	case TextureFormat::R16Uint:
	case TextureFormat::R16Sint:
	case TextureFormat::R16Float:
	case TextureFormat::RG8Unorm:
	case TextureFormat::RG8Snorm:
	case TextureFormat::RG8Uint:
	case TextureFormat::RG8Sint:
	case TextureFormat::Depth16Unorm:
		return 16;
	case TextureFormat::Depth24Plus:
		return 24;
	case TextureFormat::R32Float:
	case TextureFormat::R32Uint:
	case TextureFormat::R32Sint:
	case TextureFormat::RG16Uint:
	case TextureFormat::RG16Sint:
	case TextureFormat::RG16Float:
	case TextureFormat::RGBA8Unorm:
	case TextureFormat::RGBA8UnormSrgb:
	case TextureFormat::RGBA8Snorm:
	case TextureFormat::RGBA8Uint:
	case TextureFormat::RGBA8Sint:
	case TextureFormat::BGRA8Unorm:
	case TextureFormat::BGRA8UnormSrgb:
	case TextureFormat::Depth32Float:
	case TextureFormat::Depth24PlusStencil8:
	case TextureFormat::RG11B10Ufloat:
	case TextureFormat::RGB9E5Ufloat:
	case TextureFormat::RGB10A2Unorm:
		return 32;
	case TextureFormat::Depth32FloatStencil8:
		return 40;
	case TextureFormat::RG32Float:
	case TextureFormat::RG32Uint:
	case TextureFormat::RG32Sint:
	case TextureFormat::RGBA16Uint:
	case TextureFormat::RGBA16Sint:
	case TextureFormat::RGBA16Float:
		return 64;
	case TextureFormat::RGBA32Float:
	case TextureFormat::RGBA32Uint:
	case TextureFormat::RGBA32Sint:
		return 128;
	default:
		throw std::runtime_error("Unhandled format");
	}
}

} // namespace wgpu

