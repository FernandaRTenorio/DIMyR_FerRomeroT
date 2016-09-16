#version 330 core
// Input color from the vertex program.
in vec3 ex_color;
in vec2 ex_texCoord;

out vec4 out_color;

uniform sampler2D sampler;
//uniform sampler2D ourTexture;

void main(){
    //out_color = vec4(ex_color, 1.0);
    //out_color = texture(sampler, ex_texCoord)*vec4(ex_color,1.0f);
      out_color = texture(sampler, ex_texCoord);
}