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

Functions are available in **C**, **JavaScript** and **WGSL** depending on the context.

Each utility function is provided in its own file for clarity; the recommended way to use them is to **copy paste them in your project**.

Available utility functions
---------------------------

### `wgpuMaxMipLevels`

[`C`](c/wgpuMaxMipLevels.c) | [`JavaScript`](js/wgpuMaxMipLevels.js)

```C
uint32_t wgpuMaxMipLevels(WGPUExtent size, WGPUTextureDimension dimension);
uint32_t wgpuMaxMipLevels1D(WGPUExtent size);
uint32_t wgpuMaxMipLevels2D(WGPUExtent size);
uint32_t wgpuMaxMipLevels3D(WGPUExtent size);
```

Compute the maximum number of MIP levels for a texture as standardized [in WebGPU spec](https://www.w3.org/TR/webgpu/#abstract-opdef-maximum-miplevel-count).

**param `size`** size of the texture

**param `dimension`** dimension of the texture

**return** maximum value allowed for `mipLevelCount` in a texture descriptor that has the given size and dimension.

You may specify the dimension either statically in the name of the function or dynamically as a second argument.

```C
// Example of use case
textureDesc.mipLevelCount = wgpuMaxMipLevels(textureDesc.size, textureDesc.dimension);
```

### `wgpuTextureFormatGamma`

[`C`](c/wgpuTextureFormatGamma.c) | [`JavaScript`](js/wgpuTextureFormatGamma.js)

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
