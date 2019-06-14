#version 460
layout (location = 0) in vec2 posicion_vertice;
layout (location = 1) in vec2 coordenadas_textura;

out vec2 textura_posicion;

uniform mat4 modelo;
uniform mat4 proyeccion;

void main()
{
	gl_Position = proyeccion * modelo * vec4(posicion_vertice, 0.0, 1.0);
	textura_posicion = coordenadas_textura;
}
