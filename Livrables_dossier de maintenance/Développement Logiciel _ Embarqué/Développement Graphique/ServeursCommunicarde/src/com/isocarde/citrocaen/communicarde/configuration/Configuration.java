package com.isocarde.citrocaen.communicarde.configuration;

import java.util.ArrayList;

/**
 * <b>Configuration permet de regrouper l'ensemble des parametres de
 * l'application serveur.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public class Configuration {
	/* SAUVEGARDE DES INFORMATIONS */
	/**
	 * Nombre de donnees (trames) conservees en memoire pour les statistiques
	 */
	public static int nombreDeDataSauvegardees = 480;
	/**
	 * Structure de sauvegarde pour les trames issues du terminal Android
	 */
	public static ArrayList<String> arrayOfTrameFromTablette = new ArrayList<String>(
			Configuration.nombreDeDataSauvegardees);
	/**
	 * Structure de sauvegarde pour les trames issues du pic
	 */
	public static ArrayList<String> arrayOfTrameFromPic = new ArrayList<String>(
			Configuration.nombreDeDataSauvegardees);
	/**
	 * Indique le nombre de donnees issues du terminal Android actuellement
	 * sauvegardees
	 */
	public static int pointeurDeDataSauvegardeesFromTablette = 0;
	/**
	 * Indique le nombre de donnees issues du pic actuellement sauvegardees
	 */
	public static int pointeurDeDataSauvegardeesFromPic = 0;
	/**
	 * Permet de classifier les entrees/sorties des serveurs
	 */
	public static int indexLigne = 1;

	/* TESTS */
	// Consignes :
	/**
	 * 
	 */
	public static String trameDesConsignesIdVoStarHumanReadable = "0001 0036   0021 0030   0142 0018";
	/**
	 * 
	 */
	public static String trameDesConsignesIdVoStar = trameDesConsignesIdVoStarHumanReadable
			.replaceAll(" ", "");
	// Mesures :
	/**
	 * 
	 */
	public static String trameDesMesuresIdVoViVilHumanReadable1 = "0001 1806 1210 1201   0002 1773 1197 1203";
	/**
	 * 
	 */
	public static String trameDesMesuresIdVoViVilHumanReadable2 = "0001 1795 1198 1183   0002 1806 1210 1201   0255 1773 1197 1203";
	/**
	 * 
	 */
	public static String trameDesMesuresIdVoViVilHumanReadable3 = "0001 1773 1197 1203   0002 1795 1198 1183   0132 1792 1230 1231   0255 1806 1210 1201";
	/**
	 * 
	 */
	public static String trameDesMesuresIdVoViVil1 = trameDesMesuresIdVoViVilHumanReadable1
			.replaceAll(" ", "");
	/**
	 * 
	 */
	public static String trameDesMesuresIdVoViVil2 = trameDesMesuresIdVoViVilHumanReadable2
			.replaceAll(" ", "");
	/**
	 * 
	 */
	public static String trameDesMesuresIdVoViVil3 = trameDesMesuresIdVoViVilHumanReadable3
			.replaceAll(" ", "");
}