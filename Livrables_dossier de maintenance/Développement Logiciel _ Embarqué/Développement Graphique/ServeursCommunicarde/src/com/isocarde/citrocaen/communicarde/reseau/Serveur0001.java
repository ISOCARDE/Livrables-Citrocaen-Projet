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
public class Serveur0001 extends Thread {
	/* CARACTÉRISTIQUES DU SERVEUR */
	private int port = 0001;
	private boolean ecouteDemarree = false;
	private PrintWriter bufferD_Emission;
	private OnConsignesReceived consignesListener;
	private ServerSocket serveur0001;
	private Socket clientAndroid;

	/* CONSTRUCTEURS */
	/**
	 * Constructeur par defaut
	 */
	public Serveur0001() {
	}

	/**
	 * Constructeur avec parametre
	 * 
	 * @param consignesListener
	 */
	public Serveur0001(OnConsignesReceived consignesListener) {
		this.consignesListener = consignesListener;
	}

	/**
	 * Envoie les mesures au clientAndroid pour tous les boosts converters
	 * connectes
	 * 
	 * @param mesures
	 */
	public void sendMesures(String mesures) {
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
			serveur0001 = new ServerSocket(port);
			clientAndroid = serveur0001.accept();
			try {
				bufferD_Emission = new PrintWriter(
						new BufferedWriter(new OutputStreamWriter(
								clientAndroid.getOutputStream())), true);
				BufferedReader in = new BufferedReader(new InputStreamReader(
						clientAndroid.getInputStream()));
				while (ecouteDemarree) {
					String message = null;
					try {
						message = in.readLine();
					} catch (IOException e) {
					}
					if (message != null && consignesListener != null) {
						consignesListener
								.traitementDesConsignesDeL_Android(message);
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
	public interface OnConsignesReceived {
		/**
		 * @param consignes
		 */
		public void traitementDesConsignesDeL_Android(String consignes);
	}

}