#version 150 core
uniform vec2 size;
uniform float scale;
uniform vec2 location;
in vec4 position;
void main(){
//    vec4 pos = vec4(position.x,position.y+  sin(position.y * 0.1) * 10, position.z, position.a);
    gl_Position = vec4(2.0 * scale / size, 1.0, 1.0) * position
    +vec4(location, 0.0, 0.0);
}
