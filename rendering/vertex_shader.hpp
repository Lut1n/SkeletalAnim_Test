#ifndef VERTEX_SHADER_HPP
#define VERTEX_SHADER_HPP

#define GLSL_CODE(code) #code

// --------------------------------------------------------------------------
// vertex shader used by SkinDrawable in skeletal animation
static const std::string s_riggingVertCode_skin = GLSL_CODE(

const int MAX_BONES = 50;
uniform mat4 u_jointTransforms[MAX_BONES];
uniform float u_jointCount;

void main()
{
    // extract transform indexes from input vertex color
    int indexes[2];
    float weights[2];
    indexes[0] = int(gl_Color[0]*u_jointCount);
    indexes[1] = int(gl_Color[1]*u_jointCount);

    weights[0] = gl_Color[2];
    weights[1] = gl_Color[3];

    // apply weighted transforms on vertex
    vec4 output_vertex = vec4(0.0,0.0,0.0,1.0);
    for(int i=0;i<2;++i)
    {
        output_vertex.xyz += (u_jointTransforms[indexes[i]] * gl_Vertex).xyz * weights[i];
    }

    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * output_vertex;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = vec4(1.0);
}


);


// --------------------------------------------------------------------------
// vertex shader used by WeightDrawable in skeletal animation
static const std::string s_riggingVert_weights = GLSL_CODE(

const int MAX_BONES = 50;
uniform mat4 u_jointTransforms[MAX_BONES];
uniform float u_jointCount;

void main()
{
    // extract transform indexes from input vertex color
    int indexes[2];
    float weights[2];
    indexes[0] = int(gl_Color[0]*u_jointCount);
    indexes[1] = int(gl_Color[1]*u_jointCount);

    weights[0] = gl_Color[2];
    weights[1] = gl_Color[3];

    float op = (gl_VertexID%2==0) ? 1.0 : 0.0;

    // apply weighted transforms on vertex
    vec4 output_vertex = vec4(0.0,0.0,0.0,1.0);
    for(int i=0;i<2;++i)
    {
        output_vertex.xyz += (u_jointTransforms[indexes[i]] * gl_Vertex).xyz * weights[i];
    }

    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * output_vertex;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = vec4(op,op,weights[0],1.0);
}


);

#endif // VERTEX_SHADER_HPP
