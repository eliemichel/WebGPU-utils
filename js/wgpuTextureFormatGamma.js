
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
 * @param format (GPUTextureFormat) the format of the texture we write to
 * 
 * @return a gamma of 2.2 if the format uses the sRGB scale, 1.0 otherwise
 *         (i.e., it uses a linear scale)
 */
function wgpuTextureFormatGamma(format) {
	switch (format)
	{
	case "astc10x10unorm-srgb":
	case "astc10x5unorm-srgb":
	case "astc10x6unorm-srgb":
	case "astc10x8unorm-srgb":
	case "astc12x10unorm-srgb":
	case "astc12x12unorm-srgb":
	case "astc4x4unorm-srgb":
	case "astc5x5unorm-srgb":
	case "astc6x5unorm-srgb":
	case "astc6x6unorm-srgb":
	case "astc8x5unorm-srgb":
	case "astc8x6unorm-srgb":
	case "astc8x8unorm-srgb":
	case "bc1rgbaunorm-srgb":
	case "bc2rgbaunorm-srgb":
	case "bc3rgbaunorm-srgb":
	case "bc7rgbaunorm-srgb":
	case "bgra8unorm-srgb":
	case "etc2rgb8a1unorm-srgb":
	case "etc2rgb8unorm-srgb":
	case "etc2rgba8unorm-srgb":
	case "rgba8unorm-srgb":
		return 2.2;
	default:
		return 1.0;
	}
}
