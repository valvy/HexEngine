#version 410 core

out vec4 color;

uniform sampler2D text;
in VS_OUT{
    vec4 color;
} fs_in;

in vec2 UV;

void main(void){
    color = vec4(texture(text,UV).rgb,UV);//vec4(0.0, 0.8, 1.0, 1.0);
}
