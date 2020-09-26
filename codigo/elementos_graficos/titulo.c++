#include "titulo.h++"

Titulo::Titulo(float x, float y, float ancho, float alto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_titulo(recursos), m_autor(recursos)
{
	m_rectangulo = recursos->figura(F_Rectangulo);
	m_fondo = recursos->textura(T_TituloMusica);

	m_titulo.tipografia(recursos->tipografia(LetraTituloGrande));
	m_titulo.dimension(ancho, 0);
	m_titulo.color(Color(1.0f, 1.0f, 1.0f));
	m_titulo.centrado(true);

	m_autor.tipografia(recursos->tipografia(LetraTitulo));
	m_autor.dimension(ancho, 0);
	m_autor.color(Color(1.0f, 1.0f, 1.0f));
	m_autor.centrado(true);

	m_alfa = 0;
	m_estado = 0;
}

Titulo::~Titulo()
{
}

void Titulo::actualizar(unsigned int diferencia_tiempo)
{
	if(m_estado == 5)//Invisible y no se actualiza mas
		return;

	float valocidad_alfa = diferencia_tiempo*3.0/1000000000.0f;//0.05 a 60 fps
	float velocidad_pixeles = diferencia_tiempo*18.0/10000000.0f;//1800 = 60 fps * 30 px

	if(m_estado == 0)//Aparecer
	{
		m_alfa +=valocidad_alfa;
		if(m_alfa >= 1.0)
		{
			m_alfa = 1.0;
			m_estado = 1;
		}
	}
	else if(m_estado == 1)//Entrada
	{
		m_posicion_texto -= velocidad_pixeles;
		if(m_posicion_texto <= 0)
		{
			m_posicion_texto = 0;
			m_estado = 2;
		}
	}
	else if(m_estado == 2)//Espera 3 segundo
	{
		m_tiempo += diferencia_tiempo;
		if(m_tiempo >= 2000000000)
			m_estado = 3;
	}
	else if(m_estado == 3)//Salida
	{
		m_posicion_texto -= velocidad_pixeles;
		if(m_posicion_texto < -(this->ancho() / 2 + m_titulo.largo_texto() / 2))
			m_estado = 4;
	}
	else if(m_estado == 4)//Desaparecer
	{
		m_alfa -=valocidad_alfa;
		if(m_alfa < 0.0)
		{
			m_alfa = 0.0;
			m_estado = 5;
		}
	}

	m_titulo.posicion(this->x()+m_posicion_texto, this->y()+this->alto()/2-m_titulo.alto_texto());
	m_autor.posicion(this->x()-m_posicion_texto, this->y()+this->alto()/2+20);
}

void Titulo::dibujar()
{
	if(m_estado == 5)//Invisible
		return;
	m_fondo->activar();
	m_rectangulo->textura(true);
	m_rectangulo->dibujar(this->x(), this->y()+this->alto()/2-100, this->ancho(), 200, Color(1.0f, 1.0f, 1.0f, m_alfa));

	m_titulo.dibujar();
	m_autor.dibujar();
}

void Titulo::evento_raton(Raton */*raton*/)
{
}

void Titulo::dimension(float ancho, float alto)
{
	this->_dimension(ancho, alto);

	m_titulo.posicion(this->x(), this->y()+alto/2-m_titulo.alto_texto());
	m_titulo.dimension(ancho, 0);

	m_autor.posicion(this->x(), this->y()+alto/2+20);
	m_autor.dimension(ancho, 0);
}

void Titulo::datos(Datos_Musica *datos_musica)
{
	m_datos = datos_musica;
	m_titulo.texto(m_datos->nombre_musica());
	m_autor.texto(m_datos->autor());
	m_posicion_texto = this->ancho() / 2 + m_titulo.largo_texto() / 2;
}
