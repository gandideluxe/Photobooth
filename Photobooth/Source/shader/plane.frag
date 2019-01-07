#version 140
#extension GL_ARB_shading_language_420pack : require
#extension GL_ARB_explicit_attrib_location : require
                                                            
uniform sampler2D image_texture;

in vec3 vColor;
in vec2 fTexCoord;
layout(location = 0) out vec4 FragColor;

void main()
{
    //FragColor = vec4(fTexCoord.x, fTexCoord.y*2.0 , 0.0, 1.0);\n\
    //FragColor = vec4(fTexCoord, 0.0, 1.0);\n\
    //FragColor = vec4(fTexCoord , 0.0, 1.0);
    //FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    FragColor= texture(image_texture, vec2(1.0 - fTexCoord.x, fTexCoord.y));
}