package com.isocarde.citrocaen.communicarde.configuration;

import java.util.LinkedList;
import java.util.concurrent.ScheduledExecutorService;

import com.isocarde.citrocaen.communicarde.R;
import com.isocarde.citrocaen.communicarde.beans.BoostConverter;
import com.isocarde.citrocaen.communicarde.reseau.ClientAndroid;
import com.isocarde.citrocaen.communicarde.ui.BoostConverterAdapter;

import android.app.Dialog;
import android.widget.Button;
import android.widget.ListView;

/**
 * <b>Configuration permet de regrouper l'ensemble des parametres de
 * l'application Android.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public class Configuration {
	/* PARAMÈTRES PHYSIQUES */
	/**
	 * Resistance shunt
	 */
	public static final float resSh = (float) 0.22 / 4; // (Ohm)
	/**
	 * Resistance de charge
	 */
	public static final float resCh = (float) 100; // (Ohm)

	/* BOOSTS CONVERTERS */
	/**
	 * La liste doublement chainee des boosts converters connectes
	 */
	public static LinkedList<BoostConverter> listeDeBoostsConverters;
	/**
	 * La valeur par defaut de la consigne voStar
	 */
	public static final String voStarParDefaut = "2400";

	/* OBJETS IHM */
	// Boutons toujours visibles :
	/**
	 * Le bouton permettant l'affichage global de tous les boosts connectes
	 */
	public static Button boutonVueGlobale;
	/**
	 * Le bouton permettant l'affichage des statistiques sur tous les boosts
	 * connectes ou deconnectes
	 */
	public static Button boutonStatistiques;
	/**
	 * Le bouton permettant l'affichage de l'interface graphique de generation
	 * de sequence de consignes
	 */
	public static Button boutonScripts;
	// Boutons de la boîte de dialogue pour validation de changement de tension
	// :
	/**
	 * La boîte de dialogue utilisee pour la validation d'un changement de
	 * tension
	 */
	public static Dialog boiteDeDialogue;
	/**
	 * Le bouton de la boîte de dialogue permettant d'annuler le changement de
	 * consigne qui a ete demande
	 */
	public static Button boiteDeDialogueBoutonAnnulerChangementDeVoStar;
	/**
	 * Le bouton de la boîte de dialogue permettant de valider le changement de
	 * consigne qui a ete demande
	 */
	public static Button boiteDeDialogueBoutonValiderChangementDeVoStar;
	// Progression par defaut de chaque voStar et de chaque SeekBar (correspond
	// a 24V) :
	/**
	 * La valeur (en pourcentage) de la progression avant que le changement de
	 * consigne ait ete demande
	 */
	public static Integer progressionAvantDemandeDeChangement = 50;
	// La liste visuelle des boosts converters :
	/**
	 * La liste visuelle des boosts converters connectes
	 */
	public static ListView listViewDeBoostsConverters;
	// L'adaptateur pour lier la liste de boosts converters a son affichage
	// graphique :
	/**
	 * L'adaptateur permettant de synchroniser l'application fonctionnelle et
	 * l'interface graphique
	 */
	public static BoostConverterAdapter adaptateurDeBoostsConverters;
	// Les images d'un boost converter :
	/**
	 * L'image symbolisant le boost converter (une batterie provenant des
	 * specifications de CITROCAEN)
	 */
	public static final int icon = R.drawable.icon_boost_converter;
	/**
	 * L'image symbolisant les statistiques propres a un boost et qui sera
	 * utilise en tant que bouton (afin d'afficher les statistiques du boost)
	 */
	public static final int iconStats = R.drawable.stats_image_button;

	/* INTERFACE DE COMMUNICATION */
	// Le client android :
	/**
	 * Le client Android permettant la communication avec le serveur
	 */
	public static ClientAndroid clientAndroid;
	// Parametres de connection :
	/**
	 * L'adresse IPv4 du serveur
	 */
	public static final String ipServeur = "192.168.0.14";
	/**
	 * Le port associe sur le serveur
	 */
	public static final int portServeur = 0001;
	/**
	 * La trame qui sera envoyee lors de la connection
	 */
	public static final String trameDeConnexion = "Connectee.";
	/**
	 * Proposition logique de non connection
	 */
	public static boolean nonConnectee = true;
	/**
	 * Proposition logique de lancement de la communication
	 */
	public static boolean clientEtServeurEnRoute = false;

	// Parametres du cron logiciel :
	/**
	 * L'ordonnancement des requêtes periodiques d'acquisition de mesures
	 */
	public static ScheduledExecutorService scheduledExecutorService;
	/**
	 * Le retard precedent le declenchement de l'ordonnancement
	 */
	public static final int retard = 5000; // (ms)
	/**
	 * La periode de repetition de la requête d'acquisition de mesure :
	 */
	public static final int periode = 5000; // (ms)
	/**
	 * Proposition logique de demarrage de l'ordonnancement :
	 */
	public static boolean scheduledExecutorServiceNonLance = true;
}