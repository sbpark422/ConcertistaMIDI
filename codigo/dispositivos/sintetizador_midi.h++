#ifndef SINTETIZADOR_MIDI
#define SINTETIZADOR_MIDI

#include "../libmidi/MidiComm.h++"
#include "../registro.h++"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

class Sintetizador_Midi
{
private:
	int m_pid;
public:
	void iniciar();
	void esperar_conexion();
	void detener();
};

#endif
