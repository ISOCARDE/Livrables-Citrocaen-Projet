package com.isocarde.citrocaen.communicarde.reseau;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import com.isocarde.citrocaen.communicarde.configuration.Configuration;

/**
 * <b>ClientAndroid est la classe qui gere les communications TCP/IP via wifi
 * entre l'interface Android et le serveur.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public class ClientAndroid {
	/* CARACTÉRISTIQUES D'UN CLIENT ANDROID */
	private String messagePourLeServeur;
	private PrintWriter bufferD_Emission;
	private BufferedReader bufferDeReception;
	private TraitementDesAcquisitionsListener TraitementDesAcquisitionsListener = null;

	/* CONSTRUCTEURS DE CLIENT ANDROID */
	/**
	 * Constructeur par defaut
	 */
	public ClientAndroid() {
		super();
	}

	/**
	 * Constructeur avec parametre
	 * 
	 * @param TraitementDesAcquisitionsListener
	 */
	public ClientAndroid(
			TraitementDesAcquisitionsListener TraitementDesAcquisitionsListener) {
		super();
		this.TraitementDesAcquisitionsListener = TraitementDesAcquisitionsListener;
	}

	/**
	 * Envoie les consignes au serveur pour tous les boosts converters connectes
	 * 
	 * @param consigne
	 */
	public void sendConsignes(String consigne) {
		if (bufferD_Emission != null && !bufferD_Emission.checkError()) {
			bufferD_Emission.println(consigne);
			bufferD_Emission.flush();
		}
	}

	/**
	 * Stoppe la communication
	 */
	public void finCommunication() {
		Configuration.clientEtServeurEnRoute = false;
	}

	/**
	 * Lance l'ordonnancement de l'envoie periodique des requêtes d'acquisition
	 * de mesures
	 */
	public void run() {
		Configuration.clientEtServeurEnRoute = true;
		try {
			Socket socketAndroid = new Socket(
					InetAddress.getByName(Configuration.ipServeur),
					Configuration.portServeur);
			try {
				bufferD_Emission = new PrintWriter(
						new BufferedWriter(new OutputStreamWriter(
								socketAndroid.getOutputStream())), true);
				bufferDeReception = new BufferedReader(new InputStreamReader(
						socketAndroid.getInputStream()));
				sendConsignes(Configuration.trameDeConnexion);
				if (Configuration.scheduledExecutorServiceNonLance) {
					Configuration.scheduledExecutorServiceNonLance = false;
					Configuration.scheduledExecutorService = Executors
							.newSingleThreadScheduledExecutor();
					Configuration.scheduledExecutorService.scheduleAtFixedRate(
							new Runnable() {
								public void run() {
									if (!Configuration.nonConnectee) {
										String trame = Configuration.listeDeBoostsConverters
												.toString().replace("[", "")
												.replace("]", "")
												.replaceAll(",", "")
												.replaceAll(" ", "");
										if (trame.length() >= 4) {
											Configuration.clientAndroid
													.sendConsignes(trame);
										}
									}
								}
							}, Configuration.retard, Configuration.periode,
							TimeUnit.MILLISECONDS);
				}
				while (Configuration.clientEtServeurEnRoute) {
					messagePourLeServeur = bufferDeReception.readLine();
					if (messagePourLeServeur != null
							&& TraitementDesAcquisitionsListener != null) {
						TraitementDesAcquisitionsListener
								.traitementDesAcquisitions(messagePourLeServeur);
					}
				}
			} catch (Exception e) {
			} finally {
				socketAndroid.close();
			}
		} catch (Exception e) {
		}

	}

	/**
	 * <b>TraitementDesAcquisitionsListener est l'interface de reception des
	 * mesures.</b>
	 * 
	 * @author TOMA
	 * @version 3.0
	 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
	 */
	public interface TraitementDesAcquisitionsListener {
		/**
		 * @param trameD_Acquisition
		 */
		public void traitementDesAcquisitions(String trameD_Acquisition);
	}
}