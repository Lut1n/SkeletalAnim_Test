#ifndef WIND_FX_GLSL_HPP
#define WIND_FX_GLSL_HPP

#define GLSL_CODE(code) #code

// --------------------------------------------------------------------------
std::string windFx_Glsl = GLSL_CODE(

uniform float u_ellapsed_s;
uniform sampler2D texture;

// basic simple hash
float hash(vec2 p)
{
    return abs(  fract( sin( dot(p, vec2(1455.887,24554.653) ) )* 1852943.113474   ));
}

float noise(vec2 uv, float freq)
{
    vec2 i = floor(uv * freq);
    vec2 f = fract(uv * freq);

    f = 3.0*f*f - 2.0*f*f*f;

    float v0 = hash( i+vec2(0.0,0.0) );
    float v1 = hash( i+vec2(1.0,0.0) );
    float v2 = hash( i+vec2(0.0,1.0) );
    float v3 = hash( i+vec2(1.0,1.0) );

    float v01 = mix(v0,v1,f.x);
    float v23 = mix(v2,v3,f.x);

    return mix(v01,v23,f.y);
}

float fracNoise(vec2 uv, int octave, float persist)
{
    float intensity = persist;
    float total = 0.0;
    float freq = 2.0;

    float r = 0.0;

    const int MAX_OCTAVE = 10;
    for(int i=0; i<MAX_OCTAVE; i++)
    {
        if(i>=octave)break;

        r += noise(uv, freq) * intensity;
        total += intensity;

        freq *= 2.0;
        intensity *= persist;
    }

    return r/total;
}

float computeWindAt(vec2 uv, float ellapsed, float force)
{
    vec2 f = vec2(ellapsed * 0.5, sin(ellapsed * 0.1) );
    return fracNoise(vec3(uv + f*force,0.0), 8, 0.7);
}

void main()
{
    vec2 tx = gl_TexCoord[0].xy * vec2(640.0,360.0);
    vec2 flow = vec2(computeWindAt(tx, u_ellapsed_s, 1.0));
    vec2 uv = tx+flow*0.1;
    gl_FragColor = texture2D(texture, uv);
}


);

#endif // WIND_FX_GLSL_HPP
