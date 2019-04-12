#version 150 core
uniform float aspect;
in vec4 position;
void main(){
//    vec4 pos = vec4(position.x,position.y+  sin(position.y * 0.1) * 10, position.z, position.a);
    gl_Position = vec4(1.0 / aspect, 1.0, 1.0, 1.0) * position;
}
