#include "fila.h++"
Fila::Fila(int x, int y, int ancho, int alto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_color_fondo(0.95f, 0.95f, 0.95f)
{
	m_rectangulo = recursos->figura(F_Rectangulo);

	m_sobre_boton = false;
	m_boton_pre_activado = false;
	m_boton_seleccionado = false;

	m_color_actual = m_color_fondo;
	m_color_seleccion = Color(m_color_fondo.rojo()-0.045f, m_color_fondo.verde()-0.045f, m_color_fondo.azul()-0.045f);
}

Fila::~Fila()
{
	for(Etiqueta* e : m_celda)
		delete e;
}

void Fila::actualizar(unsigned int /*diferencia_tiempo*/)
{
	if(m_boton_seleccionado)
		m_color_actual = m_color_seleccion;
	else
		m_color_actual = m_color_fondo;

	if(m_sobre_boton)
		m_color_actual = Color(m_color_actual.rojo()-0.08f, m_color_actual.verde()-0.08f, m_color_actual.azul()-0.08f);
}

void Fila::dibujar()
{
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->x(), this->y(), this->ancho(), this->alto(), m_color_actual);
	for(unsigned int x=0; x<m_celda.size(); x++)
	{
		m_celda.at(x)->dibujar();
	}
	m_rectangulo->dibujar(this->x(), this->y()+this->alto()-1, this->ancho(), 1, Color(0.9f, 0.9f, 0.9f));
}

void Fila::evento_raton(Raton *raton)
{
	if(raton->esta_sobre(this->x(), this->y(), this->ancho(), this->alto()))
	{
		if(raton->activado(BotonIzquierdo) && m_sobre_boton)
			m_boton_pre_activado = true;
		else if(!raton->activado(BotonIzquierdo))
		{
			m_sobre_boton = true;
			if(m_boton_pre_activado)
			{
				m_boton_seleccionado = true;
				m_boton_pre_activado = false;
			}
		}
	}
	else
	{
		m_sobre_boton = false;
		m_boton_pre_activado = false;
	}
}

void Fila::posicion(int x, int y)
{
	this->_posicion(x, y);
	for(Etiqueta* e : m_celda)
		e->posicion(e->x(), this->y());
}

void Fila::agregar_celda(Etiqueta *celda)
{
	m_celda.push_back(celda);
}

std::vector<Etiqueta *> *Fila::celdas()
{
	return &m_celda;
}

bool Fila::esta_seleccionado()
{
	return m_boton_seleccionado;
}

void Fila::seleccionar()
{
	m_boton_seleccionado = true;
}

void Fila::deseleccionar()
{
	m_boton_seleccionado = false;
}
