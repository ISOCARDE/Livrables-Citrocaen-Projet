package com.isocarde.citrocaen.communicarde.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import com.isocarde.citrocaen.communicarde.configuration.Configuration;
import com.isocarde.citrocaen.communicarde.reseau.Serveur0000;
import com.isocarde.citrocaen.communicarde.reseau.Serveur0001;

/**
 * <b>Console represente l'interface du serveur.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public class Console extends JFrame {
	/* CARACTÉRISTIQUES DE LA FENÊTRE */
	private static final long serialVersionUID = -804851251240220536L;
	private JTextArea jTextArea;
	private JButton demarrerServeur;
	private Serveur0001 serveurPourAndroid;
	private Serveur0000 serveurPourPic;

	/* CONSTRUCTEURS */
	/**
	 * Constructeur par defaut
	 */
	public Console() {
		super("Console");
		JPanel panelFields = new JPanel();
		panelFields.setLayout(new BoxLayout(panelFields, BoxLayout.X_AXIS));
		JPanel panelFields2 = new JPanel();
		panelFields2.setLayout(new BoxLayout(panelFields2, BoxLayout.X_AXIS));
		jTextArea = new JTextArea();
		jTextArea.setColumns(30);
		jTextArea.setRows(10);
		jTextArea.setEditable(false);
		demarrerServeur = new JButton("Demarrer le serveur");
		demarrerServeur.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				serveurPourAndroid = new Serveur0001(
						new Serveur0001.OnConsignesReceived() {

							@Override
							public void traitementDesConsignesDeL_Android(
									String consignes) {
								Configuration.arrayOfTrameFromTablette
										.add(Configuration.pointeurDeDataSauvegardeesFromTablette
												% Configuration.nombreDeDataSauvegardees,
												consignes);
								jTextArea.append("\n("
										+ Configuration.indexLigne
										+ ") Tablette :\n\t" + consignes);
								Configuration.indexLigne++;
								serveurPourPic.sendConsignes(consignes);
								String reponse;
								int random = (int) (Math.random() * 3);
								reponse = random == 0 ? Configuration.trameDesMesuresIdVoViVil1
										: random == 1 ? Configuration.trameDesMesuresIdVoViVil3
												: Configuration.trameDesMesuresIdVoViVil2;
								serveurPourAndroid.sendMesures(reponse);
								jTextArea.append("\n("
										+ Configuration.indexLigne
										+ ") Pic :\n\t" + reponse);
								Configuration.indexLigne++;
							}
						});
				serveurPourAndroid.start();
				serveurPourPic = new Serveur0000(
						new Serveur0000.OnMesuresReceived() {

							@Override
							public void traitementDesMesuresDuPic(String mesures) {
								Configuration.arrayOfTrameFromPic
										.add(Configuration.pointeurDeDataSauvegardeesFromPic
												% Configuration.nombreDeDataSauvegardees,
												mesures);
								serveurPourAndroid.sendMesures(mesures);
								jTextArea.append("\n("
										+ Configuration.indexLigne
										+ ") Pic :\n\t" + mesures);
								Configuration.indexLigne++;
							}
						});
				serveurPourPic.start();
				demarrerServeur.setEnabled(false);
			}
		});
		panelFields.add(jTextArea);
		panelFields.add(demarrerServeur);
		getContentPane().add(panelFields);
		getContentPane().add(panelFields2);
		getContentPane().setLayout(
				new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
		setSize(1000, 700);
		setVisible(true);
	}

	/**
	 * Programme principal
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		Console frame = new Console();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);

	}
}