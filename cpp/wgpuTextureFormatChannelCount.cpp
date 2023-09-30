#include <webgpu/webgpu.h>

namespace wgpu {

/**
 * Tell how many channels a given texture format has
 * 
 * @param format the texel format of the texture
 * 
 * @return the number of channels
 */
uint32_t textureFormatChannelCount(TextureFormat format) {
	switch (format) {
	case TextureFormat::Undefined:
		return 0;
	case TextureFormat::R8Unorm:
	case TextureFormat::R8Snorm:
	case TextureFormat::R8Uint:
	case TextureFormat::R8Sint:
	case TextureFormat::R16Uint:
	case TextureFormat::R16Sint:
	case TextureFormat::R16Float:
	case TextureFormat::R32Float:
	case TextureFormat::R32Uint:
	case TextureFormat::R32Sint:
	case TextureFormat::Stencil8:
	case TextureFormat::Depth16Unorm:
	case TextureFormat::Depth24Plus:
	case TextureFormat::Depth32Float:
	case TextureFormat::BC4RUnorm:
	case TextureFormat::BC4RSnorm:
	case TextureFormat::EACR11Unorm:
	case TextureFormat::EACR11Snorm:
		return 1;
	case TextureFormat::RG8Unorm:
	case TextureFormat::RG8Snorm:
	case TextureFormat::RG8Uint:
	case TextureFormat::RG8Sint:
	case TextureFormat::RG16Uint:
	case TextureFormat::RG16Sint:
	case TextureFormat::RG16Float:
	case TextureFormat::RG32Float:
	case TextureFormat::RG32Uint:
	case TextureFormat::RG32Sint:
	case TextureFormat::Depth24PlusStencil8:
	case TextureFormat::Depth32FloatStencil8:
	case TextureFormat::BC5RGUnorm:
	case TextureFormat::BC5RGSnorm:
	case TextureFormat::EACRG11Unorm:
	case TextureFormat::EACRG11Snorm:
		return 2;
	case TextureFormat::RG11B10Ufloat:
	case TextureFormat::RGB9E5Ufloat:
	case TextureFormat::BC6HRGBUfloat:
	case TextureFormat::BC6HRGBFloat:
	case TextureFormat::ETC2RGB8Unorm:
	case TextureFormat::ETC2RGB8UnormSrgb:
		return 3;
	case TextureFormat::RGBA8Unorm:
	case TextureFormat::RGBA8UnormSrgb:
	case TextureFormat::RGBA8Snorm:
	case TextureFormat::RGBA8Uint:
	case TextureFormat::RGBA8Sint:
	case TextureFormat::BGRA8Unorm:
	case TextureFormat::BGRA8UnormSrgb:
	case TextureFormat::RGB10A2Unorm:
	case TextureFormat::RGBA16Uint:
	case TextureFormat::RGBA16Sint:
	case TextureFormat::RGBA16Float:
	case TextureFormat::RGBA32Float:
	case TextureFormat::RGBA32Uint:
	case TextureFormat::RGBA32Sint:
	case TextureFormat::BC1RGBAUnorm:
	case TextureFormat::BC1RGBAUnormSrgb:
	case TextureFormat::BC2RGBAUnorm:
	case TextureFormat::BC2RGBAUnormSrgb:
	case TextureFormat::BC3RGBAUnorm:
	case TextureFormat::BC3RGBAUnormSrgb:
	case TextureFormat::BC7RGBAUnorm:
	case TextureFormat::BC7RGBAUnormSrgb:
	case TextureFormat::ETC2RGB8A1Unorm:
	case TextureFormat::ETC2RGB8A1UnormSrgb:
	case TextureFormat::ETC2RGBA8Unorm:
	case TextureFormat::ETC2RGBA8UnormSrgb:
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
	default:
		throw std::runtime_error("Unhandled format");
	}
}

} // namespace wgpu

