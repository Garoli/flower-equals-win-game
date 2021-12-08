#version 410

out vec4 fragColor ;
uniform sampler2D color;
in vec2 uv;
void main()
{
    fragColor=texture(color,uv);
    if(fragColor.a<0.01){
        discard;
    }
}