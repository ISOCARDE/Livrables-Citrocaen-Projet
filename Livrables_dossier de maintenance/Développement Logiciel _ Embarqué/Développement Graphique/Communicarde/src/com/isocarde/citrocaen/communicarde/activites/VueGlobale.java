package com.isocarde.citrocaen.communicarde.activites;

import java.util.Iterator;
import java.util.LinkedList;

import android.os.AsyncTask;
import android.os.Bundle; 
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ListView;

import com.isocarde.citrocaen.communicarde.R;
import com.isocarde.citrocaen.communicarde.beans.BoostConverter;
import com.isocarde.citrocaen.communicarde.configuration.Configuration;
import com.isocarde.citrocaen.communicarde.reseau.ClientAndroid;
import com.isocarde.citrocaen.communicarde.ui.BoostConverterAdapter;
import com.isocarde.citrocaen.communicarde.ui.IsocardeActivity;

/**
 * <b>VueGlobale est l'activite principale de l'application Android.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public class VueGlobale extends IsocardeActivity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		/* UI */
		// La liaison avec le layout principal :
		setContentView(R.layout.activity_main);

		// La definition des boutons presents :
		Configuration.boutonVueGlobale = (Button) findViewById(R.id.button1);
		Configuration.boutonStatistiques = (Button) findViewById(R.id.button2);
		Configuration.boutonScripts = (Button) findViewById(R.id.button3);

		// La definition de la liste visuelle des boosts converters :
		Configuration.listViewDeBoostsConverters = (ListView) findViewById(R.id.listView1);

		// La definition de la legende de la liste visuelle de boosts converters
		// :
		View header = (View) getLayoutInflater().inflate(
				R.layout.listview_header_row, null);

		// La definition de la liste doublement chaînee des BoostConverter :
		Configuration.listeDeBoostsConverters = new LinkedList<BoostConverter>();

		// La definition de l'adaptateur entre le visuel et le fonctionnel :
		Configuration.adaptateurDeBoostsConverters = new BoostConverterAdapter(
				this, R.layout.listview_item_row,
				Configuration.listeDeBoostsConverters);

		// L'ajout de la legende a la liste visuelle de boost converters :
		Configuration.listViewDeBoostsConverters.addHeaderView(header);

		// La mise en place de l'adaptateur entre le visuel et le fonctionnel :
		Configuration.listViewDeBoostsConverters
				.setAdapter(Configuration.adaptateurDeBoostsConverters);

		/* GESTION DES ACTIONS */
		Configuration.boutonVueGlobale
				.setOnClickListener(new View.OnClickListener() {
					@Override
					public void onClick(View v) {
						Configuration.adaptateurDeBoostsConverters
								.notifyDataSetChanged();
					}
				});
		Configuration.boutonStatistiques
				.setOnClickListener(new View.OnClickListener() {
					@Override
					public void onClick(View v) {
						Configuration.adaptateurDeBoostsConverters
								.notifyDataSetChanged();
					}
				});
		Configuration.boutonScripts
				.setOnClickListener(new View.OnClickListener() {
					@Override
					public void onClick(View v) {
					}
				});

	}

	@Override
	protected void onResume() {
		super.onResume();
		Configuration.adaptateurDeBoostsConverters.notifyDataSetChanged();
	}

	@Override
	protected void onPause() {
		super.onPause();
	}
 
	@Override
	protected void onRestart() {
		super.onRestart();
	}

	@Override
	protected void onStop() {
		super.onStop();
	}
 
	@Override
	protected void onDestroy() {
		super.onDestroy();
	}

	/**
	 * @see android.app.Activity#onCreateOptionsMenu(android.view.Menu)
	 */
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.main_menu, menu);
		return true;
	}

	/**
	 * @see android.app.Activity#onPrepareOptionsMenu(android.view.Menu)
	 */
	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		if (!Configuration.nonConnectee) {
			// if the client is Configuration.nonConnectee, enable the connect
			// button and disable
			// the disconnect one
			menu.getItem(1).setEnabled(true);
			menu.getItem(0).setEnabled(false);
		} else {
			// if the client is disconnected, enable the disconnect button and
			// disable the connect one
			menu.getItem(1).setEnabled(false);
			menu.getItem(0).setEnabled(true);
		}

		return super.onPrepareOptionsMenu(menu);
	}

	/**
	 * @see android.app.Activity#onOptionsItemSelected(android.view.MenuItem)
	 */
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle item selection
		switch (item.getItemId()) {
		case R.id.connexion:
			new Cron().execute("");
			Configuration.nonConnectee = false;
			return true;
		case R.id.deconnexion:
			// // disconnect
			Configuration.nonConnectee = true;
			return true;
		default:
			return super.onOptionsItemSelected(item);
		}
	}

	/**
	 * <b>Cron est la tâche gerant l'ordonnancement des requêtes.</b>
	 * 
	 * @author TOMA
	 * @version 3.0
	 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
	 */
	public class Cron extends AsyncTask<String, String, ClientAndroid> {

		@Override
		protected ClientAndroid doInBackground(String... message) {
			Configuration.clientAndroid = new ClientAndroid(
					new ClientAndroid.TraitementDesAcquisitionsListener() {
						@Override
						public void traitementDesAcquisitions(String message) {
							publishProgress(message);
						}
					});
			Configuration.clientAndroid.run();
			return null;
		}

		@Override
		protected void onProgressUpdate(String... values) {
			super.onProgressUpdate(values);
			if (Configuration.listeDeBoostsConverters != null) {
				trameToBoostsConverters(values[0]);
			}
			if (Configuration.adaptateurDeBoostsConverters != null) {
				Configuration.adaptateurDeBoostsConverters
						.notifyDataSetChanged();
			}
		}

		private void trameToBoostsConverters(String trame) {
			LinkedList<BoostConverter> list = new LinkedList<BoostConverter>();
			String tramePourUnBoost;
			boolean found;
			String id;
			BoostConverter boostConverter;
			// Parcours de chaque "sous-trame", propre a un unique boost
			// converter :
			for (int i = 0; i < trame.length(); i += 16) {
				found = false;
				id = trame.substring(i, i + 4);
				Iterator<BoostConverter> it = Configuration.listeDeBoostsConverters
						.iterator();
				// Verifie la pre-existence :
				while (it.hasNext()) {
					boostConverter = it.next();
					// Si le boost converter etait deja connecte, mise a jour :
					if (Integer.parseInt(boostConverter.getId()) == Integer
							.parseInt(id)) {
						boostConverter.setVo(trame.substring(i + 4, i + 8));
						boostConverter.setVi(trame.substring(i + 8, i + 12));
						boostConverter.setVil(trame.substring(i + 12, i + 16));
						list.add(boostConverter);
						found = true;
						break;
					}
				}
				// Si le boost converter n'etait pas encore connecte, creation :
				if (!found) {
					tramePourUnBoost = trame.substring(i, i + 16);
					list.add(new BoostConverter(tramePourUnBoost));
				}
			}
			// Re-initialisation de la liste :
			Configuration.listeDeBoostsConverters.clear();

			// Actualisation de la liste :
			Configuration.listeDeBoostsConverters.addAll(list);
		}
	}
}