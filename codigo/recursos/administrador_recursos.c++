#include "administrador_recursos.h++"

Administrador_Recursos::Administrador_Recursos()
{
	matriz_proyeccion = glm::ortho(0.0f, (float)this->ancho, (float)this->alto, 0.0f, -1.0f, 1.0f);

	archivo_texturas[T_Titulo] = "../texturas/titulo.tga";
	archivo_texturas[T_Boton] = "../texturas/boton.tga";

	archivo_sombreador_vertice[Rectangulo_Textura] = "../sombreadores/rectangulo_textura_sv.glsl";
	archivo_sombreador_fragmento[Rectangulo_Textura] = "../sombreadores/rectangulo_textura_sf.glsl";

	archivo_sombreador_vertice[Rectangulo_SinTextura] = "../sombreadores/rectangulo_sin_textura_sv.glsl";
	archivo_sombreador_fragmento[Rectangulo_SinTextura] = "../sombreadores/rectangulo_sin_textura_sf.glsl";

	archivo_sombreador_vertice[Rectangulo_Texto] = "../sombreadores/texto_sv.glsl";
	archivo_sombreador_fragmento[Rectangulo_Texto] = "../sombreadores/texto_sf.glsl";

	Sombreador *sombreador_letras = obtener_sombreador(Rectangulo_Texto);
	sombreador_letras->e_int("textura_texto", 0);
	sombreador_letras->e_vector3f("color_texto", 0.0, 0.0, 0.0);

	formato_letras[LetraTitulo] = new Texto(Normal, 16, sombreador_letras);
	formato_letras[LetraGrande] = new Texto(Normal, 26, sombreador_letras);
	formato_letras[LetraMediana] = new Texto(Normal, 14, sombreador_letras);
	formato_letras[LetraChica] = new Texto(Normal, 12, sombreador_letras);
	formato_letras[LetraMuyChica] = new Texto(Normal, 8, sombreador_letras);
}

Administrador_Recursos::~Administrador_Recursos()
{
	//glDeleteTextures(1, &indice);
	//glDeleteProgram(indice);
}

Textura2D *Administrador_Recursos::obtener_textura(Textura valor)
{
	Textura2D *temporal = lista_texturas[valor];
	if(!temporal)
	{
		//Generar la textura
		Archivo::Tga textura_nueva(archivo_texturas[valor]);

		temporal = new Textura2D();
		temporal->generar(textura_nueva.ancho(), textura_nueva.alto(), textura_nueva.bytes(), GL_BGR, textura_nueva.imagen());

		lista_texturas[valor] = temporal;

		Registro::nota("Se cargo la textura del archivo: " + std::string(archivo_texturas[valor]));
	}

	return temporal;
}

void Administrador_Recursos::activar_textura(Textura valor)
{
	Textura2D *temporal = obtener_textura(valor);
	temporal->activar();
}

Sombreador *Administrador_Recursos::obtener_sombreador(SombreadorVF valor)
{
	Sombreador *temporal = lista_sombreadores[valor];
	if(!temporal)
	{
		std::string texto_vertice = Archivo::leer_archivo(archivo_sombreador_vertice[valor]);
		std::string texto_fragmento = Archivo::leer_archivo(archivo_sombreador_fragmento[valor]);

		const char* codigo_vertice = texto_vertice.c_str();
		const char* codigo_fragmento = texto_fragmento.c_str();

		temporal = new Sombreador(codigo_vertice, codigo_fragmento);
		temporal->e_matriz4("proyeccion", this->matriz_proyeccion);

		lista_sombreadores[valor] = temporal;

		Registro::nota("Se cargo el sombreador de vertices del archivo: " + std::string(archivo_sombreador_vertice[valor]));
		Registro::nota("Se cargo el sombreador de fragmentos del archivo: " + std::string(archivo_sombreador_fragmento[valor]));
	}

	return temporal;
}

void Administrador_Recursos::activar_sombreador(SombreadorVF valor)
{
	Sombreador *temporal = obtener_sombreador(valor);
	temporal->activar();
}

Texto *Administrador_Recursos::obtener_tipografia(ModeloLetra tipo)
{
	return formato_letras[tipo];
}

int Administrador_Recursos::mostrar_texto(int x, int y, ModeloLetra tipo, std::string texto)
{
	Texto *texto_actual = formato_letras[tipo];
	return texto_actual->dibujar_texto(x, y, texto);
}

int Administrador_Recursos::mostrar_texto(int x, int y, ModeloLetra tipo, std::string texto, bool centrado)
{
	Texto *texto_actual = formato_letras[tipo];
	return texto_actual->dibujar_texto(x, y, texto, centrado);
}

int Administrador_Recursos::mostrar_texto(int x, int y, ModeloLetra tipo, std::string texto, Color color)
{
	Texto *texto_actual = formato_letras[tipo];
	return texto_actual->dibujar_texto(x, y, texto, color);
}

int Administrador_Recursos::mostrar_texto(int x, int y, ModeloLetra tipo, std::string texto, Color color, bool centrado)
{
	Texto *texto_actual = formato_letras[tipo];
	return texto_actual->dibujar_texto(x, y, texto, color, centrado);
}

void Administrador_Recursos::actualizar_pantalla(int nuevo_ancho, int nuevo_alto)
{
	this->ancho = nuevo_ancho;
	this->alto = nuevo_alto;

	matriz_proyeccion = glm::ortho(0.0f, (float)this->ancho, (float)this->alto, 0.0f, -1.0f, 1.0f);

	for(std::map<SombreadorVF, Sombreador*>::iterator e=lista_sombreadores.begin(); e != lista_sombreadores.end(); e++)
	{
		e->second->e_matriz4("proyeccion", this->matriz_proyeccion);
	}
}