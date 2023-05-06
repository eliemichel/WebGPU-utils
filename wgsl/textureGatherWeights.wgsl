// requires CubeMapUVL.wgsl

/**
 * Compute the u/v weights corresponding to the bilinear mix of samples
 * returned by textureGather.
 */
fn textureGatherWeights_2df(t: texture_2d<f32>, coords: vec2f) -> vec2f {
    let dim = textureDimensions(t).xy;
    let scaled_uv = coords * vec2f(dim);
    // This is not accurate, see see https://www.reedbeta.com/blog/texture-gathers-and-coordinate-precision/
    // but bottom line is:
    //   "Unfortunately, if we need this to work, there seems to be no option but to check
    //    which hardware you are running on and apply the offset or not accordingly."
    return fract(scaled_uv - 0.5);
}

/**
 * Compute the u/v weights corresponding to the bilinear mix of samples
 * returned by textureGather.
 */
fn textureGatherWeights_cubef(t: texture_cube<f32>, coords: vec3f) -> vec2f {
    // major axis direction
    let cubemap_uvl = cubeMapUVLFromDirection(coords);
    let dim = textureDimensions(t).xy;
    var uv = cubemap_uvl.uv;

    // Empirical fix...
    if (cubemap_uvl.layer == 4u || cubemap_uvl.layer == 5u) {
        uv.x = 1.0 - uv.x;
    }

    let scaled_uv = uv * vec2f(dim);
    // This is not accurate, see see https://www.reedbeta.com/blog/texture-gathers-and-coordinate-precision/
    // but bottom line is:
    //   "Unfortunately, if we need this to work, there seems to be no option but to check
    //    which hardware you are running on and apply the offset or not accordingly."
    return fract(scaled_uv - 0.5);
}
