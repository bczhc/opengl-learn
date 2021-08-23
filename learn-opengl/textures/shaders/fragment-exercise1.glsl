#version 330 core

out vec4 color;

in vec2 tex_coords;
in vec2 tex2_coords;
in vec3 f_color;

uniform sampler2D texture_sampler;
uniform sampler2D texture2_sampler;

void main() {
    //    color = vec4(0.1F, 0.3F, 0.5F, 1.0F);
    vec4 f_color_vec4 = vec4(f_color.rgb, 1.0F);
    //    color = mix(texture(texture_sampler, tex_coords), texture(texture2_sampler, tex2_coords), 0.3F);
    vec4 tex_color1 = texture(texture_sampler, tex_coords);
    vec4 tex_color2 = texture(texture2_sampler, vec2(1.0F - tex2_coords.x, tex2_coords.y));

    if (tex_color2.a == 0.0F) {
        color = tex_color1 * f_color_vec4;
    } else {
        color = mix(tex_color1, tex_color2, 0.4F) * f_color_vec4;
    }
}
