#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal; // Keep this even if unused to match Vertex Shader

// These MUST match what the C++ code sets
uniform sampler2D u_Texture;
uniform sampler2D texture_specular1; // Added to stop the warning "texture_specular1 doesn't exist"
uniform float alpha;                // Added to stop the warning "alpha doesn't exist"

void main()
{
    // Sample the diffuse texture
    vec4 texColor = texture(u_Texture, TexCoords);
    
    // Apply the alpha transparency
    float finalAlpha = texColor.a * alpha;
    
    FragColor = vec4(texColor.rgb, finalAlpha);
}