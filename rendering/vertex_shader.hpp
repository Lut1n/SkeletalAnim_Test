#ifndef VERTEX_SHADER_HPP
#define VERTEX_SHADER_HPP

#define GLSL_CODE(code) #code

std::string vertCode = GLSL_CODE(

const int MAX_BONES = 50;
uniform mat4 u_joinTransforms[MAX_BONES];
uniform float u_joinCount;

void main()
{
    int indexes[3];
    indexes[0] = int(gl_Color[0]*u_joinCount);
    indexes[1] = int(gl_Color[1]*u_joinCount);
    indexes[2] = int(gl_Color[2]*u_joinCount);

    vec4 output_vertex = vec4(0.0,0.0,0.0,1.0);
    float weight = 0.7;
    for(int i=0;i<2;++i)
    {
        output_vertex.xyz += (u_joinTransforms[indexes[i]] * gl_Vertex).xyz * weight;
        weight = 0.3;
    }

    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * output_vertex;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = vec4(1.0);
}


);

#endif // VERTEX_SHADER_HPP
