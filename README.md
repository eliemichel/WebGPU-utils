<div align="center">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://raw.githubusercontent.com/eliemichel/LearnWebGPU/main/images/webgpu-dark.svg">
    <source media="(prefers-color-scheme: light)" srcset="https://raw.githubusercontent.com/eliemichel/LearnWebGPU/main/images/webgpu-light.svg">
    <img alt="Learn WebGPU Logo" src="images/webgpu-dark.svg" width="200">
  </picture>

  <a href="https://github.com/eliemichel/LearnWebGPU">LearnWebGPU</a> &nbsp;|&nbsp; <a href="https://github.com/eliemichel/WebGPU-Cpp">WebGPU-C++</a> &nbsp;|&nbsp; <a href="https://github.com/eliemichel/glfw3webgpu">glfw3webgpu</a> &nbsp;|&nbsp; <a href="https://github.com/eliemichel/WebGPU-distribution">WebGPU-distribution</a>
  
  <a href="https://discord.gg/2Tar4Kt564"><img src="https://img.shields.io/static/v1?label=Discord&message=Join%20us!&color=blue&logo=discord&logoColor=white" alt="Discord | Join us!"/></a>
</div>

WebGPU standard utils
=====================

This tiny library provides bunch of utility functions that solely depend on `webgpu.h` and implement information coming from the **WebGPU specification** but not directly available in `webgpu.h`.

Functions are available in **C**, **C++**, **JavaScript** and **WGSL** depending on the context.

Utility functions for C++ are consolidated in [`webgpu_std_utils.hpp`](webgpu_std_utils.hpp) and assume that you are using a C++ wrapper like [WebGPU-C++](https://github.com/eliemichel/WebGPU-Cpp). Each utility function is also provided in its own file for clarity; and can be individually **copy pasted in your project**.

These are **unopinionated utils**, meaning that they are written like anybody would write them because they address very straighforward utility problems. Anything more advanced does not belong here.

**NB** The C++ directory is likely more complete than the others at the moment.

Available utility functions
---------------------------

### `maxMipLevelCount`

[`C`](c/wgpuMaxMipLevelCount.c) | [`C++`](cpp/wgpuMaxMipLevelCount.cpp) | [`JavaScript`](js/wgpuMaxMipLevelCount.js)

```C
uint32_t wgpuMaxMipLevelCount(WGPUExtent size, WGPUTextureDimension dimension);
uint32_t wgpuMaxMipLevelCount1D(WGPUExtent size);
uint32_t wgpuMaxMipLevelCount2D(WGPUExtent size);
uint32_t wgpuMaxMipLevelCount3D(WGPUExtent size);
```

Compute the maximum number of MIP levels for a texture as standardized [in WebGPU spec](https://www.w3.org/TR/webgpu/#abstract-opdef-maximum-miplevel-count).

**param `size`** size of the texture

**param `dimension`** dimension of the texture

**return** maximum value allowed for `mipLevelCount` in a texture descriptor that has the given size and dimension.

You may specify the dimension either statically in the name of the function or dynamically as a second argument.

```C
// Example of use case
textureDesc.mipLevelCount = wgpuMaxMipLevelCount(textureDesc.size, textureDesc.dimension);
```

### `textureFormatGamma`

[`C`](c/wgpuTextureFormatGamma.c) | [`C++`](cpp/wgpuTextureFormatGamma.cpp) | [`JavaScript`](js/wgpuTextureFormatGamma.js)

```C
float wgpuTextureFormatGamma(WGPUTextureFormat format);
```

Indicate what gamma correction must be applied to a linear color prior to
writing it in a texture that has the given format.

**param `format`** the format of the texture we write to

**return** a gamma of 2.2 if the format uses the sRGB scale, 1.0 otherwise
      (i.e., it uses a linear scale)

For instance, if your color attachment has the given format, your fragment
should end like this (assuming it is operating on linear colors):

```rust
// Example of use case
let corrected_color = pow(linear_color, vec4f(gamma));
return corrected_color;
```

### `textureFormatBitsPerTexel`

[`C++`](cpp/wgpuTextureFormatBitsPerTexel.cpp)

```C
uint32_t wgpuTextureFormatBitsPerTexel(WGPUTextureFormat format);
```

Tell how many bits each texel occupies for a given texture format has.

**param `format`** the texel format of the texture

**return** the number of bits

**NB:** Some compressed format use less than 1 byte (8 bits) per texel, which
is why this function cannot return a byte number instead of bits.

```C
// Example of use case
sourceLayout.bytesPerRow = wgpuTextureFormatBitsPerTexel(textureDesc.format) * textureDesc.size.width / 8;
```

### `textureFormatChannelCount`

[`C++`](cpp/wgpuTextureFormatChannelCount.cpp)

```C
uint32_t wgpuTextureFormatChannelCount(WGPUTextureFormat format);
```

Tell how many channels a given texture format has

**param `format`** the texel format of the texture

**return** the number of channels

```C
// Example of use case
wgpuTextureFormatChannelCount(textureDesc.format);
```

### `textureFormatSupportedSampleType`

[`C++`](cpp/wgpuTextureFormatSupportedSampleType.cpp)

```C
WGPUTextureSampleType wgpuTextureFormatSupportedSampleType(WGPUTextureFormat format);
```

Provide an example of sample type that can be used with the texture.

**param `format`** the texel format of the texture

**return** one supported sample type from a given texture format

**NB:** Among the possibilities, UnfilterableFloat is not returned unless it is
the only possibility

**NB:** For mixed depth/stencil textures the query is ambiguous because it
depends on the aspect. In such a case this function returns Depth.

```C
// Example of use case
bindGroupLayoutEntry.texture.sampleType = wgpuTextureFormatSupportedSampleType(texture.getFormat());
```

### `vertexFormatByteSize`

[`C++`](cpp/wgpuVertexFormatByteSize.cpp)

```C
uint32_t wgpuVertexFormatByteSize(WGPUTextureFormat format);
```

Tell how many bytes a given vertex format occupies.

**param `format`** the vertex format

**return** the number of bytes

```C
// Example of use case
layout.arrayStride = wgpuVertexFormatByteSize(attrib.format);
```

### `textureGatherWeights`

[`WGSL`](wgsl/textureGatherWeights.wgsl)

```rust
fn textureGatherWeights_2df(t: texture_2d<f32>, coords: vec2f) -> vec2f;
fn textureGatherWeights_cubef(t: texture_cube<f32>, coords: vec3f) -> vec2f;
```

Compute the weights corresponding to the bilinear mix of samples
returned by [`textureGather`](https://gpuweb.github.io/gpuweb/wgsl/#texturegather).

**param `t`** The texture to sample (must match the `t` argument of `textureGather`)

**param `coords`** The texture coordinate at which we query the texture (must match the `coords` argument of `textureGather`). Note that a cube map is queried by a direction rather than a 2D texture coordinate.

**return** a pair of weights (s,t) where such that the queried texture coordinate U is `mix(U_min, U_max, s)` and the coordinate V is `mix(V_min, V_max, t)`. The min/max UV are the texture coordinates of the texel returned by [`textureGather`](https://gpuweb.github.io/gpuweb/wgsl/#texturegather) (see notations there).

This is used to sample textures from a compute or vertex shader (where `textureSample` is not available).

```rust
// Example of use case
let samples = array<vec4f, 4>(
    textureGather(0, cubemapTexture, textureSampler, direction),
    textureGather(1, cubemapTexture, textureSampler, direction),
    textureGather(2, cubemapTexture, textureSampler, direction),
    textureGather(3, cubemapTexture, textureSampler, direction),
);

let w = textureGatherWeights_cubef(cubemapTexture, direction);

// TODO: could be represented as a matrix/vector product
let color = vec4f(
    mix(mix(samples[0].w, samples[0].z, w.x), mix(samples[0].x, samples[0].y, w.x), w.y),
    mix(mix(samples[1].w, samples[1].z, w.x), mix(samples[1].x, samples[1].y, w.x), w.y),
    mix(mix(samples[2].w, samples[2].z, w.x), mix(samples[2].x, samples[2].y, w.x), w.y),
    mix(mix(samples[3].w, samples[3].z, w.x), mix(samples[3].x, samples[3].y, w.x), w.y),
);
```

Other resources
---------------

 - [JavaScript WebGPU utils](https://github.com/greggman/webgpu-utils)

TODO
----

Some suggestions of new utility functions to add to this library:

 - size of component from format (for uniform formats)
 - mip level size
