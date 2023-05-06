/**
 * Identify a cubemap sample location by a layer/face and a normalized UV
 * coordinate within this face.
 */
struct CubeMapUVL {
    uv: vec2f,
    layer: u32,
}

/**
 * Utility function for textureGatherWeights
 */
fn cubeMapUVLFromDirection(direction: vec3f) -> CubeMapUVL {
    let abs_direction = abs(direction);
    var major_axis_idx = 0u;
    //  Using the notations of https://www.khronos.org/registry/OpenGL/specs/gl/glspec46.core.pdf page 253
    // as suggested here: https://stackoverflow.com/questions/55558241/opengl-cubemap-face-order-sampling-issue
    var ma = 0.0;
    var sc = 0.0;
    var tc = 0.0;
    if (abs_direction.x > abs_direction.y && abs_direction.x > abs_direction.z) {
        major_axis_idx = 0u;
        ma = direction.x;
        if (ma >= 0) {
            sc = -direction.z;
        } else {
            sc = direction.z;
        }
        tc = -direction.y;
    } else if (abs_direction.y > abs_direction.x && abs_direction.y > abs_direction.z) {
        major_axis_idx = 1u;
        ma = direction.y;
        sc = direction.x;
        if (ma >= 0) {
            tc = direction.z;
        } else {
            tc = -direction.z;
        }
    } else {
        major_axis_idx = 2u;
        ma = direction.z;
        if (ma >= 0) {
            sc = -direction.x;
        } else {
            sc = direction.x;
        }
        tc = -direction.y;
    }
    var sign_offset = 0u;
    if (ma < 0) {
        sign_offset = 1u;
    }
    let s = 0.5 * (sc / abs(ma) + 1.0);
    let t = 0.5 * (tc / abs(ma) + 1.0);
    return CubeMapUVL(
        vec2f(s, t),
        2 * major_axis_idx + sign_offset,
    );
}

/**
 * Inverse of cubeMapUVLFromDirection
 * This returns an unnormalized direction, to save some calculation
 */
fn directionFromCubeMapUVL(uvl: CubeMapUVL) -> vec3f {
    let s = uvl.uv.x;
    let t = uvl.uv.y;
    let abs_ma = 1.0;
    let sc = 2.0 * s - 1.0;
    let tc = 2.0 * t - 1.0;
    var direction = vec3f(0.0);
    switch (uvl.layer) {
        case 0u {
            return vec3f(1.0, -tc, -sc);
        }
        case 1u {
            return vec3f(-1.0, -tc, sc);
        }
        case 2u {
            return vec3f(sc, 1.0, tc);
        }
        case 3u {
            return vec3f(sc, -1.0, -tc);
        }
        case 4u {
            return vec3f(sc, -tc, 1.0);
        }
        case 5u {
            return vec3f(-sc, -tc, -1.0);
        }
        default {
            return vec3f(0.0); // should not happen
        }
    }
}
