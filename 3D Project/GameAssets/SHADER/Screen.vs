#version 140
in vec2 pos;

out vec2 uv;
void main()
{
	uv = pos + vec2(1.0,1.0);
	uv /=2.0;
	gl_Position = vec4(pos,0.0,1.0);
}