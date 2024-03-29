#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include "../libmidi/MidiComm.h++"

#include "base_de_datos.h++"
#include "../dispositivos/teclas_luminosas.h++"
#include "../util/usuario.h++"
#include "../control/teclado_organo.h++"
#include "../elementos_graficos/notificacion.h++"

class Configuracion
{
private:
	//Base de datos
	Base_de_Datos m_datos;

	//Configuracion MIDI
	MidiCommIn *m_entrada;
	MidiCommOut *m_salida;
	TeclasLuminosas* m_teclas_luminosas;
	unsigned int m_id_entrada, m_id_entrada_original;
	unsigned int m_id_salida, m_id_salida_original;
	unsigned int m_id_teclas_luminosas_original;
	bool m_entrada_notificacion, m_salida_notificacion;

	//Configuracion General
	bool m_pantalla_completa, m_pantalla_completa_original;

	//Configuracion Archivo
	std::string m_carpeta_inicial, m_carpeta_inicial_original;
	std::string m_carpeta_activa, m_carpeta_activa_original;

	//Configuracion Reproduccion
	double m_volumen, m_volumen_original;
	double m_velocidad, m_velocidad_original;
	unsigned int m_duracion_nota, m_duracion_nota_original;
	bool m_subtitulos, m_subtitulos_original;
	Teclado_Organo m_teclado_visible, m_teclado_visible_original;
	Teclado_Organo m_teclado_util, m_teclado_util_original;

	std::string leer(std::string atributo, std::string predeterminado);
	unsigned int leer(std::string atributo, unsigned int predeterminado);
	double leer(std::string atributo, double predeterminado);
	bool leer(std::string atributo, bool predeterminado);

public:
	Configuracion();
	~Configuracion();

	//Base de datos
	Base_de_Datos* base_de_datos();
	//std::string leer(std::string atributo);
	//bool escribir(std::string atributo, std::string valor);
	void guardar_configuracion();

	//Configuracion MIDI
	void dispositivo_entrada(unsigned int id_entrada);
	void dispositivo_salida(unsigned int id_salida);
	void teclas_luminosas(unsigned int identificador);

	unsigned int id_dispositivo_entrada();
	unsigned int id_dispositivo_salida();

	MidiCommIn *dispositivo_entrada();
	MidiCommOut *dispositivo_salida();
	TeclasLuminosas *teclas_luminosas();

	//Configuracion General
	void pantalla_completa(bool estado);
	bool pantalla_completa();

	//Configuracion Archivo
	void carpeta_inicial(const std::string& carpeta);
	void carpeta_activa(const std::string& carpeta);
	std::string carpeta_inicial();
	std::string carpeta_activa();

	//Configuracion Reproduccion
	void volumen(double valor);
	void velocidad(double valor);
	void duracion_nota(unsigned int duracion);
	void subtitulos(bool estado);
	void teclado_visible(unsigned int inicial, unsigned int largo);
	void teclado_util(unsigned int inicial, unsigned int largo);
	double volumen();
	double velocidad();
	unsigned int duracion_nota();
	bool subtitulos();
	Teclado_Organo teclado_visible();
	Teclado_Organo teclado_util();
};

#endif
