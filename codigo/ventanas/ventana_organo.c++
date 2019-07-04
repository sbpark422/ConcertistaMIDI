#include "ventana_organo.h++"

VentanaOrgano::VentanaOrgano(Administrador_Recursos *recursos) : Ventana()
{
	//musica = new Midi(Midi::ReadFromFile("../musica/Ven Señor no tardes propia.midi"));
	musica = new Midi(Midi::ReadFromFile("../musica/Navidad_Jingle_Bells_1.midi"));
	//musica = new Midi(Midi::ReadFromFile("../musica/Escala_musícal.midi"));
	musica->Reset(3000000, 3000000);
	MidiCommDescriptionList dispositivos_entrada = MidiCommIn::GetDeviceList();
	MidiCommDescriptionList dispositivos_salida = MidiCommOut::GetDeviceList();

	Teclado *teclado = Tipo_Teclado::obtener_teclado(Teclas88);

	barra = new Barra_Progreso(0, 0, Pantalla::ancho, 40, musica->GetSongLengthInMicroseconds(), musica->GetBarLines(), recursos);
	organo = new Organo(0, Pantalla::alto, Pantalla::ancho, teclado, recursos);
	tablero = new Tablero_Notas(0, barra->o_alto(), Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()), teclado, recursos);

	this->velocidad_musica = 1.0;
	this->texto = recursos->obtener_tipografia(LetraChica);

	Registro::aviso("Dispositivos de entrada:");
	for(int x=0; x<dispositivos_entrada.size(); x++)
	{
		Registro::aviso("\tNombre: " + dispositivos_entrada[x].name);
	}

	Registro::aviso("Dispositivos de salida:");
	for(int x=0; x<dispositivos_salida.size(); x++)
	{
		Registro::aviso("\tNombre: " + dispositivos_salida[x].name);
	}

	midi_entrada = new MidiCommIn(3);//Deberia seleccionarse el id del dispositivo (Teclado)
	midi_salida = new MidiCommOut(1);//Deberia seleccionarse el id del dispositivo (Timidity 0)

	pistas[0] = new Pista(Color(0.0, 0.598, 0.0), Automatico);
	pistas[1] = new Pista(Color(0.0, 0.598, 1.0), Automatico);
	pistas[2] = new Pista(Color(1.0, 0.598, 1.0), Automatico);
	pistas[3] = new Pista(Color(1.0, 0.424, 0.0), Automatico);
	pistas[4] = new Pista(Color(1.0, 0.0, 0.467), Automatico);
	pistas[5] = new Pista(Color(0.587, 0.0, 0.467), Automatico);
	pistas[6] = new Pista(Color(0.261, 0.0, 0.467), Automatico);
	pistas[7] = new Pista(Color(0.0, 0.0, 0.467), Automatico);
	pistas[8] = new Pista(Color(0.0, 0.761, 0.467), Automatico);
	pistas[9] = new Pista(Color(0.0, 0.761, 1.0), Automatico);
	pistas[10] = new Pista(Color(1.0, 0.761, 0.609), Automatico);
	pistas[11] = new Pista(Color(1.0, 0.761, 0.0), Automatico);
	pistas[12] = new Pista(Color(0.489, 0.587, 0.489), Automatico);
	pistas[13] = new Pista(Color(0.489, 0.0, 0.489), Automatico);
	pistas[14] = new Pista(Color(1.0, 0.0, 0.489), Automatico);
	pistas[15] = new Pista(Color(0.407, 0.348, 0.408), Automatico);
	pistas[16] = new Pista(Color(0.407, 0.348, 0.0), Automatico);
	pistas[17] = new Pista(Color(0.407, 0.348, 1.0), Automatico);
	pistas[18] = new Pista(Color(0.0, 0.348, 1.0), Automatico);
	pistas[19] = new Pista(Color(0.0, 0.348, 0.0), Automatico);

	tablero->e_notas(musica->Notes());
	tablero->e_pistas(&pistas);
	tablero->e_lineas(musica->GetBarLines());
	organo->e_blancas_presionadas(tablero->o_blancas_presionadas());
	organo->e_negras_presionadas(tablero->o_negras_presionadas());
}

VentanaOrgano::~VentanaOrgano()
{
	delete barra;
	delete tablero;
	delete organo;
	delete musica;
	delete midi_entrada;
	delete midi_salida;
}

void VentanaOrgano::actualizar(Raton *raton)
{
	if(musica->IsSongOver())
	{
		musica->Reset(3000000, 3000000);
		tablero->reiniciar();
	}
	MidiEventListWithTrackId evs = musica->Update((Fps::obtener_nanosegundos() / 1000.0) * velocidad_musica);

	for (MidiEventListWithTrackId::const_iterator i = evs.begin(); i != evs.end(); ++i)
	{
		midi_salida->Write(i->second);
	}

	if(barra->o_tiempo_seleccionado() > 0)
	{
		musica->GoTo(barra->o_tiempo_seleccionado());
		tablero->reiniciar();
	}

	barra->e_tiempo(musica->GetSongPositionInMicroseconds());
	tablero->e_tiempo(musica->GetSongPositionInMicroseconds());

	barra->actualizar(raton);
	tablero->actualizar(raton);
	organo->actualizar(raton);
}

void VentanaOrgano::dibujar()
{
	tablero->dibujar();
	barra->dibujar();
	organo->dibujar();
	this->texto->imprimir(10, 80, "Velocidad: " + std::to_string((int)(velocidad_musica*100)) + "%", Color(0.0, 0.0, 0.0));
}

void VentanaOrgano::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_FLECHA_ARRIBA && estado)
		tablero->c_velocidad_caida(1);
	else if(tecla == TECLA_FLECHA_ABAJO && estado)
		tablero->c_velocidad_caida(-1);
	else if(tecla == TECLA_FLECHA_IZQUIERDA && estado)
	{
		velocidad_musica-=0.01;
		if(velocidad_musica < 0.01)
			velocidad_musica = 0.01;
	}
	else if(tecla == TECLA_FLECHA_DERECHA && estado)
	{
		velocidad_musica+=0.01;
		if(velocidad_musica > 2)
			velocidad_musica = 2;
	}
	else if(tecla == TECLA_F5 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas37));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas37));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()));
	}
	else if(tecla == TECLA_F6 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas49));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas49));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()));
	}
	else if(tecla == TECLA_F7 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas61));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas61));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()));
	}
	else if(tecla == TECLA_F8 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas76));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas76));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()));
	}
	else if(tecla == TECLA_F9 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas88));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas88));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()));
	}
}

void VentanaOrgano::evento_pantalla(int ancho, int alto)
{
	barra->e_ancho(ancho);
	organo->e_y(alto);
	organo->e_ancho(ancho);
	tablero->e_dimension(ancho, alto - (organo->o_alto() + barra->o_alto()));
}
