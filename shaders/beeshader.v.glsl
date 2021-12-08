#version 410
// ins (inputs)
layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 vertexUV;
uniform float scale;
out vec2 uv;
uniform vec2 offset;
void main()
{
    vec4 positionH=vec4(vertexPosition + offset,0,1/scale);
    gl_Position =  positionH;
    uv = vertexUV;
}
