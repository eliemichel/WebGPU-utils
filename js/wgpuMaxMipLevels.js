
// Equivalent of std::bit_width that is available in C++20
function bit_width(m) {
	if (m == 0) return 0;
	else { var w = 0; while (m >>= 1) ++w; return w; }
}

/**
 * Variant of wgpuMaxMipLevels for when one statically knows that the texture
 * dimension is 1D.
 */
function wgpuMaxMipLevels1D(size) {
	return 1;
}

/**
 * Variant of wgpuMaxMipLevels for when one statically knows that the texture
 * dimension is 2D.
 */
function wgpuMaxMipLevels2D(size) {
	return bit_width(Math.max(size.width, size.height));
}

/**
 * Variant of wgpuMaxMipLevels for when one statically knows that the texture
 * dimension is 3D.
 */
function wgpuMaxMipLevels3D(size) {
	return bit_width(Math.max(size.width, Math.max(size.height, size.depthOrArrayLayer)));
}

/**
 * Compute the maximum number of MIP levels for a texture as standardized
 * [in WebGPU spec](https://www.w3.org/TR/webgpu/#abstract-opdef-maximum-miplevel-count).
 * 
 * You may specify the dimension either statically in the name of the function
 * or dynamically as a second argument.
 * 
 *     textureDesc.mipLevelCount = wgpuMaxMipLevels(textureDesc.size, textureDesc.dimension);
 * 
 * @param size (GPUExtent) size of the texture
 * 
 * @param dimension (GPUTextureDimension) of the texture
 * 
 * @return (int) maximum value allowed for `mipLevelCount` in a texture descriptor
 *         that has the given size and dimension.
 */
function wgpuMaxMipLevels(size,  dimension) {
	switch (dimension) {
	case "1d":
		return wgpuMaxMipLevels1D(size);
	case "2d":
		return wgpuMaxMipLevels2D(size);
	case "3d":
		return wgpuMaxMipLevels3D(size);
	default:
		// Should not happen
		console.assert(false);
	}
}
