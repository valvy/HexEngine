#version 410 core

out VS_OUT{
    vec4 color;
} vs_out;

uniform mat4 cam_matrix;
uniform mat4 projection_matrix;
uniform mat4 mv_matrix;

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normals;

out vec2 UV;

void main(void){
    
    vec4 P =  projection_matrix * cam_matrix * mv_matrix * position;//cam position;
    vs_out.color = position;
    gl_Position =  P;
  //  vs_out.color =
    UV = vertexUV;
    
}


