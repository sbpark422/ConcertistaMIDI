#include "administrador_recursos.h++"

Administrador_Recursos::Administrador_Recursos()
{
	m_ancho = 800;
	m_alto = 600;
	m_matriz_proyeccion = glm::ortho(0.0f, m_ancho, m_alto, 0.0f, -1.0f, 1.0f);

	std::string ruta = RUTA_ARCHIVOS;
	m_archivo_texturas[T_FondoTitulo] = ruta + "/texturas/fondo_titulo.tga";
	m_archivo_texturas[T_Titulo] = ruta + "/texturas/titulo.tga";
	m_archivo_texturas[T_Boton] = ruta + "/texturas/boton.tga";
	m_archivo_texturas[T_TeclaBlanca] = ruta + "/texturas/tecla_blanca.tga";
	m_archivo_texturas[T_TeclaNegra] = ruta + "/texturas/tecla_negra.tga";
	m_archivo_texturas[T_TeclaBlancaPresionada] = ruta + "/texturas/tecla_blanca_presionada.tga";
	m_archivo_texturas[T_TeclaBlancaPresionadaDoble] = ruta + "/texturas/tecla_blanca_presionada_doble.tga";
	m_archivo_texturas[T_TeclaNegraPresionada] = ruta + "/texturas/tecla_negra_presionada.tga";
	m_archivo_texturas[T_Circulo] = ruta + "/texturas/circulo.tga";
	m_archivo_texturas[T_BordeOrganoRojo] = ruta + "/texturas/borde_organo_rojo.tga";
	m_archivo_texturas[T_BordeOrganoNegro] = ruta + "/texturas/borde_organo_negro.tga";
	m_archivo_texturas[T_Nota] = ruta + "/texturas/nota.tga";
	m_archivo_texturas[T_NotaResaltada] = ruta + "/texturas/nota_resaltada.tga";
	m_archivo_texturas[T_Sombra] = ruta + "/texturas/sombra.tga";
	m_archivo_texturas[T_FrenteBarraProgreso] = ruta + "/texturas/frente_barra_progreso.tga";
	m_archivo_texturas[T_ParticulaNota] = ruta + "/texturas/particula_nota.tga";
	m_archivo_texturas[T_Barra] = ruta + "/texturas/barra.tga";
	m_archivo_texturas[T_ConfiguracionPista] = ruta + "/texturas/configuracion_pista.tga";
	m_archivo_texturas[T_SonidoActivado] = ruta + "/texturas/sonido_activado.tga";
	m_archivo_texturas[T_SonidoDesactivado] = ruta + "/texturas/sonido_desactivado.tga";
	m_archivo_texturas[T_Reproducir] = ruta + "/texturas/reproducir.tga";
	m_archivo_texturas[T_Pausar] = ruta + "/texturas/pausar.tga";
	m_archivo_texturas[T_TituloMusica] = ruta + "/texturas/titulo_musica.tga";
	m_archivo_texturas[T_Color_1] = ruta + "/texturas/color_1.tga";
	m_archivo_texturas[T_Color_2] = ruta + "/texturas/color_2.tga";
	m_archivo_texturas[T_Color_3] = ruta + "/texturas/color_3.tga";
	m_archivo_texturas[T_Color_4] = ruta + "/texturas/color_4.tga";
	m_archivo_texturas[T_Color_5] = ruta + "/texturas/color_5.tga";
	m_archivo_texturas[T_Color_6] = ruta + "/texturas/color_6.tga";
	m_archivo_texturas[T_Color_7] = ruta + "/texturas/color_7.tga";
	m_archivo_texturas[T_Color_8] = ruta + "/texturas/color_8.tga";
	m_archivo_texturas[T_Color_9] = ruta + "/texturas/color_9.tga";
	m_archivo_texturas[T_Color_Invisible] = ruta + "/texturas/color_invisible.tga";
	m_archivo_texturas[T_Tocar] = ruta + "/texturas/tocar.tga";
	m_archivo_texturas[T_Aprender] = ruta + "/texturas/aprender.tga";
	m_archivo_texturas[T_MusicaFondo] = ruta + "/texturas/musica_fondo.tga";
	m_archivo_texturas[T_CasillaInactiva] = ruta + "/texturas/casilla_verificacion_inactiva.tga";
	m_archivo_texturas[T_CasillaActiva] = ruta + "/texturas/casilla_verificacion_activa.tga";
	m_archivo_texturas[T_CasillaSombra] = ruta + "/texturas/casilla_verificacion_sombra.tga";
	m_archivo_texturas[T_FlechaIzquierda] = ruta + "/texturas/flecha_izquierda.tga";
	m_archivo_texturas[T_FlechaDerecha] = ruta + "/texturas/flecha_derecha.tga";

	m_archivo_sombreador_vertice[S_Rectangulo] = ruta + "/sombreadores/rectangulo_sv.glsl";
	m_archivo_sombreador_fragmento[S_Rectangulo] = ruta + "/sombreadores/rectangulo_sf.glsl";

	m_archivo_sombreador_vertice[S_Texto] = ruta + "/sombreadores/texto_sv.glsl";
	m_archivo_sombreador_fragmento[S_Texto] = ruta + "/sombreadores/texto_sf.glsl";

	m_archivo_sombreador_vertice[S_Particula] = ruta + "/sombreadores/particula_sv.glsl";
	m_archivo_sombreador_fragmento[S_Particula] = ruta + "/sombreadores/particula_sf.glsl";

	m_lista_figuras[F_Rectangulo] = new Rectangulo(this->sombreador(S_Rectangulo));

	Sombreador *sombreador_letras = this->sombreador(S_Texto);
	sombreador_letras->uniforme_int("textura_texto", 0);
	sombreador_letras->uniforme_vector3f("color_texto", 0.0, 0.0, 0.0);

	m_formato_letras[LetraTituloGrande] = new Tipografia(Normal, 35);
	m_formato_letras[LetraTitulo] = new Tipografia(Normal, 20);
	m_formato_letras[LetraGrande] = new Tipografia(Normal, 16);
	m_formato_letras[LetraMediana] = new Tipografia(Normal, 14);
	m_formato_letras[LetraChica] = new Tipografia(Normal, 12);
	m_formato_letras[LetraMuyChica] = new Tipografia(Normal, 8);
}

Administrador_Recursos::~Administrador_Recursos()
{
	for(std::map<Textura, Textura2D*>::iterator i = m_lista_texturas.begin(); i != m_lista_texturas.end(); i++)
		delete i->second;
	m_lista_texturas.clear();

	for(std::map<SombreadorVF, Sombreador*>::iterator i = m_lista_sombreadores.begin(); i != m_lista_sombreadores.end(); i++)
		delete i->second;
	m_lista_sombreadores.clear();

	for(std::map<FiguraGeometrica, Rectangulo*>::iterator i = m_lista_figuras.begin(); i != m_lista_figuras.end(); i++)
		delete i->second;
	m_lista_figuras.clear();

	for(std::map<ModeloLetra, Tipografia*>::iterator i = m_formato_letras.begin(); i != m_formato_letras.end(); i++)
		delete i->second;
	m_formato_letras.clear();
}

Textura2D *Administrador_Recursos::textura(Textura valor)
{
	Textura2D *temporal = m_lista_texturas[valor];
	if(!temporal)
	{
		//Generar la textura
		Archivo::Tga textura_nueva(m_archivo_texturas[valor]);

		temporal = new Textura2D();
		temporal->generar(static_cast<int>(textura_nueva.ancho()), static_cast<int>(textura_nueva.alto()), textura_nueva.bytes(), textura_nueva.imagen());

		m_lista_texturas[valor] = temporal;

		if(!textura_nueva.hay_error())
			Registro::Depurar("Se cargo la textura del archivo: " + std::string(m_archivo_texturas[valor]));
	}

	return temporal;
}

Sombreador *Administrador_Recursos::sombreador(SombreadorVF valor)
{
	Sombreador *temporal = m_lista_sombreadores[valor];
	if(!temporal)
	{
		std::string texto_vertice = Archivo::leer_archivo(m_archivo_sombreador_vertice[valor].c_str());
		std::string texto_fragmento = Archivo::leer_archivo(m_archivo_sombreador_fragmento[valor].c_str());

		const char* codigo_vertice = texto_vertice.c_str();
		const char* codigo_fragmento = texto_fragmento.c_str();

		temporal = new Sombreador(codigo_vertice, codigo_fragmento);
		temporal->uniforme_matriz4("proyeccion", m_matriz_proyeccion);

		m_lista_sombreadores[valor] = temporal;

		Registro::Depurar("Se cargo el sombreador de vertices del archivo: " + std::string(m_archivo_sombreador_vertice[valor]));
		Registro::Depurar("Se cargo el sombreador de fragmentos del archivo: " + std::string(m_archivo_sombreador_fragmento[valor]));
	}

	return temporal;
}

Rectangulo *Administrador_Recursos::figura(FiguraGeometrica valor)
{
	return m_lista_figuras[valor];
}

Tipografia *Administrador_Recursos::tipografia(ModeloLetra tipo)
{
	return m_formato_letras[tipo];
}

void Administrador_Recursos::actualizar_pantalla(float nuevo_ancho, float nuevo_alto)
{
	m_ancho = nuevo_ancho;
	m_alto = nuevo_alto;

	m_matriz_proyeccion = glm::ortho(0.0f, m_ancho, m_alto, 0.0f, -1.0f, 1.0f);

	for(std::map<SombreadorVF, Sombreador*>::iterator e=m_lista_sombreadores.begin(); e != m_lista_sombreadores.end(); e++)
	{
		e->second->uniforme_matriz4("proyeccion", m_matriz_proyeccion);
	}
}
