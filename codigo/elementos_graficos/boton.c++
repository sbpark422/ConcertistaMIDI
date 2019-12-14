#include "boton.h++"

Boton::Boton(int x, int y, int ancho, int alto, std::string texto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto)
{
	m_rectangulo = recursos->obtener_figura(F_Rectangulo);
	m_textura_boton = recursos->obtener_textura(T_Boton);

	m_sobre_boton = false;
	m_boton_pre_activado = false;
	m_boton_activado = false;

	Color color(1.0f, 1.0f, 1.0f);
	m_color_boton_normal = color;
	m_color_boton_actual = color;
	m_color_boton_sobre.e_color(color.o_rojo()-0.1f, color.o_verde()-0.1f, color.o_azul()-0.1f);

	m_texto.texto(texto);
	m_texto.tipografia(recursos->obtener_tipografia(LetraMediana));
	m_texto.posicion(this->posicion_x()+this->dx(), this->posicion_y()+this->dy());
	m_texto.dimension(ancho, alto);
	m_texto.centrado(true);
}

Boton::~Boton()
{
}

void Boton::textura(Textura2D *textura)
{
	m_textura_boton = textura;
}

void Boton::color_boton(Color color)
{
	m_color_boton_normal = color;
	m_color_boton_actual = color;
	m_color_boton_sobre.e_color(color.o_rojo()-0.1f, color.o_verde()-0.1f, color.o_azul()-0.1f);
}

void Boton::color_texto(Color color)
{
	m_texto.color(color);
}

void Boton::tipografia(Texto *texto)
{
	m_texto.tipografia(texto);
}

void Boton::centrado(bool centrado)
{
	bool centrado_actual = m_centrado;
	m_centrado = centrado;
	if(m_centrado)
	{
		if(!centrado_actual)//Centra el objeto
			this->m_x = this->posicion_x() - (this->ancho() / 2.0);
	}
	else
	{
		if(centrado_actual)//Revierte el centrado
			this->m_x = this->posicion_x() + (this->ancho() / 2.0);
	}
	m_texto.posicion(this->posicion_x()+this->dx(), this->posicion_y()+this->dy());
}

void Boton::actualizar(unsigned int diferencia_tiempo)
{
}

void Boton::dibujar()
{
	m_textura_boton->activar();
	m_rectangulo->textura(true);
	m_rectangulo->dibujar(this->posicion_x()+this->dx(), this->posicion_y()+this->dy(), this->ancho(), this->alto(), m_color_boton_actual);
	m_texto.dibujar();
}

void Boton::evento_raton(Raton *raton)
{
	if(raton->x() >= this->posicion_x()+this->dx() && raton->x() <= this->posicion_x()+this->dx() + this->ancho() &&
		raton->y() >= this->posicion_y()+this->dy() && raton->y() <= this->posicion_y()+this->dy() + this->alto())
	{
		if(raton->activado(BotonIzquierdo) && m_sobre_boton)
			m_boton_pre_activado = true;
		else if(!raton->activado(BotonIzquierdo))
		{
			m_color_boton_actual = m_color_boton_sobre;
			m_sobre_boton = true;
			if(m_boton_pre_activado)
			{
				m_boton_activado = true;
				m_boton_pre_activado = false;
			}
		}
	}
	else
	{
		m_color_boton_actual = m_color_boton_normal;
		m_sobre_boton = false;
		m_boton_pre_activado = false;
		m_boton_activado = false;
	}
}

void Boton::evento_pantalla(int ancho, int alto)
{
	m_texto.posicion(this->posicion_x()+this->dx(), this->posicion_y()+this->dy());
}

bool Boton::esta_activado()
{
	bool estado = m_boton_activado;
	m_boton_activado = false;
	return estado;
}
