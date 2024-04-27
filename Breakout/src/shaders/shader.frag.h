#pragma once

const char* FRAGMENT_SHADER_SOURCE = R"(#version 330

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main() {
    color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
}
)";
