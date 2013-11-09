package com.isocarde.citrocaen.communicarde.reseau;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * <b>CoServeur0001 definie le serveur relie a la tablette Android.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public class Serveur0000 extends Thread {
	/* CARACTÉRISTIQUES DU SERVEUR */
	private int port = 0000;
	private boolean ecouteDemarree = false;
	private PrintWriter bufferD_Emission;
	private OnMesuresReceived mesuresListener;
	private ServerSocket serveur0000;
	private Socket clientPic;

	/* CONSTRUCTEURS */
	/**
	 * Constructeur par defaut
	 */
	public Serveur0000() {
	}

	/**
	 * Constructeur avec parametre
	 * 
	 * @param mesuresListener
	 */
	public Serveur0000(OnMesuresReceived mesuresListener) {
		this.mesuresListener = mesuresListener;
	}

	/**
	 * Envoie les mesures au clientPic pour tous les boosts converters connectes
	 * 
	 * @param mesures
	 */
	public void sendConsignes(String mesures) {
		if (bufferD_Emission != null && !bufferD_Emission.checkError()) {
			bufferD_Emission.println(mesures);
			bufferD_Emission.flush();
		}
	}

	/**
	 * Lance le processus d'ecoute du port
	 */
	private void runServeur0001() {
		ecouteDemarree = true;
		try {
			serveur0000 = new ServerSocket(port);
			clientPic = serveur0000.accept();
			try {
				bufferD_Emission = new PrintWriter(new BufferedWriter(
						new OutputStreamWriter(clientPic.getOutputStream())),
						true);
				BufferedReader in = new BufferedReader(new InputStreamReader(
						clientPic.getInputStream()));
				while (ecouteDemarree) {
					String message = null;
					try {
						message = in.readLine();
					} catch (IOException e) {
					}
					if (message != null && mesuresListener != null) {
						mesuresListener.traitementDesMesuresDuPic(message);
					}
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * @see java.lang.Thread#run()
	 */
	@Override
	public void run() {
		super.run();
		runServeur0001();

	}

	/**
	 * <b>TraitementDesAcquisitionsListener est l'interface de reception des
	 * mesures.</b>
	 * 
	 * @author TOMA
	 * @version 3.0
	 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
	 */
	public interface OnMesuresReceived {
		/**
		 * @param mesures
		 */
		public void traitementDesMesuresDuPic(String mesures);
	}

}