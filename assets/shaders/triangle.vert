#version 330 core

// Output varying structure to pass color to the fragment shader
out Varyings {
    vec3 color;
} vs_out;

// Uniforms for transformation
uniform vec2 translation = vec2(0.0, 0.0); // Default (0,0)
uniform vec2 scale = vec2(1.0, 1.0);       // Default (1,1)

// Vertex data defined inside the shader
const vec3 positions[3] = vec3[3](
    vec3(-0.5, -0.5, 0.0),  // Vertex 0
    vec3( 0.5, -0.5, 0.0),  // Vertex 1
    vec3( 0.0,  0.5, 0.0)   // Vertex 2
);

const vec3 colors[3] = vec3[3](
    vec3(1.0, 0.0, 0.0),  // Red (Vertex 0)
    vec3(0.0, 1.0, 0.0),  // Green (Vertex 1)
    vec3(0.0, 0.0, 1.0)   // Blue (Vertex 2)
);

void main() {
    // Use gl_VertexID (0, 1, 2) to pick the corresponding vertex
    vec3 aPos = positions[gl_VertexID];
    vec3 aColor = colors[gl_VertexID];

    // Apply transformation: scale * v + translation
    vec2 transformedPos = scale * aPos.xy + translation;

    // Assign transformed position to gl_Position (with z=0 and w=1)
    gl_Position = vec4(transformedPos, aPos.z, 1.0);

    // Pass the color to the fragment shader
    vs_out.color = aColor;
}