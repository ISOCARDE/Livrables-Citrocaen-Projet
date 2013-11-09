package com.isocarde.citrocaen.communicarde.ui;

import java.util.LinkedList;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import android.widget.Toast;

import com.isocarde.citrocaen.communicarde.R;
import com.isocarde.citrocaen.communicarde.beans.BoostConverter;
import com.isocarde.citrocaen.communicarde.configuration.Configuration;

/**
 * <b>BoostConverterAdapter est l'adaptateur qui parametre l'affichage graphique
 * des boosts converters.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public class BoostConverterAdapter extends ArrayAdapter<BoostConverter>
		implements SeekBar.OnSeekBarChangeListener {
	/* CARACTÉRISTIQUES DE L'ADAPTATEUR */
	private Context context;
	private int layoutResourceId;
	private LinkedList<BoostConverter> data = new LinkedList<BoostConverter>();

	/* CONSTRUCTEUR DE BOOST CONVERTER ADAPTER */
	/**
	 * Constructeur de l'adaptateur avec parametres
	 * 
	 * @param context
	 * @param layoutResourceId
	 * @param data
	 */
	public BoostConverterAdapter(Context context, int layoutResourceId,
			LinkedList<BoostConverter> data) {
		super(context, layoutResourceId, data);
		this.layoutResourceId = layoutResourceId;
		this.context = context;
		this.data = data;
	}

	/* MÉTHODES DE L'ADAPTATEUR */
	/**
	 * @see android.widget.ArrayAdapter#getView(int, android.view.View,
	 *      android.view.ViewGroup)
	 */
	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		View row = convertView;
		BoostConverterHolder holder = null;
		if (row == null) {
			LayoutInflater inflater = ((Activity) context).getLayoutInflater();
			row = inflater.inflate(layoutResourceId, parent, false);
			holder = new BoostConverterHolder();
			holder.imgIcon = (ImageView) row.findViewById(R.id.imgIcon);
			holder.iconStats = (ImageButton) row.findViewById(R.id.iconStats);
			holder.seekBar = (SeekBar) row.findViewById(R.id.seekBar);
			holder.txtId = (TextView) row.findViewById(R.id.txtId);
			holder.txtVi = (TextView) row.findViewById(R.id.txtVi);
			holder.txtIl = (TextView) row.findViewById(R.id.txtIl);
			holder.txtPi = (TextView) row.findViewById(R.id.txtPi);
			holder.txtVo = (TextView) row.findViewById(R.id.txtVo);
			holder.txtIo = (TextView) row.findViewById(R.id.txtIo);
			row.setTag(holder);
		} else {
			holder = (BoostConverterHolder) row.getTag();
		}
		final BoostConverter boostConverter = data.get(position);
		boostConverter.setSeekBar(holder.seekBar);
		Float voStar = Float.parseFloat(boostConverter.getVoStar()) / 100f;
		int progress = com.isocarde.citrocaen.communicarde.beans.BoostConverter
				.voStarVoltsToPourcentage(voStar);
		holder.seekBar.setProgress(progress);
		holder.imgIcon.setImageResource(Configuration.icon);
		holder.iconStats.setImageResource(Configuration.iconStats);
		holder.iconStats.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {

				Toast.makeText(context, boostConverter.toStats(),
						Toast.LENGTH_LONG).show();

			}

		});
		holder.seekBar.setOnSeekBarChangeListener(this);
		holder.seekBar
				.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
					BoostConverter BoostConverterTemp;
					Integer progressTemp;

					public void onProgressChanged(SeekBar seekBar,
							int progress, boolean fromUser) {
						progressTemp = ((int) Math.round(progress / 25)) * 25;
						BoostConverterTemp = boostConverter;
						seekBar.setProgress(progressTemp);
					}

					public void onStartTrackingTouch(SeekBar seekBar) {
					}

					public void onStopTrackingTouch(SeekBar seekBar) {
						Configuration.progressionAvantDemandeDeChangement = progressTemp;
						showDialog(
								context,
								BoostConverterTemp,
								com.isocarde.citrocaen.communicarde.beans.BoostConverter
										.voStarPourcentageToVolts(progressTemp));
					}
				});
		holder.txtId.setText("" + Integer.parseInt(boostConverter.getId()));
		holder.txtVi.setText("" + Float.parseFloat(boostConverter.getVi())
				/ 100);
		holder.txtIl.setText("" + Float.parseFloat(boostConverter.getIl()));
		holder.txtPi.setText("" + Float.parseFloat(boostConverter.getPi()));
		holder.txtVo.setText("" + Float.parseFloat(boostConverter.getVo())
				/ 100);
		holder.txtIo.setText("" + Float.parseFloat(boostConverter.getIo()));
		return row;
	}

	/**
	 * @see android.widget.SeekBar.OnSeekBarChangeListener#onProgressChanged(android.widget.SeekBar,
	 *      int, boolean)
	 */
	public void onProgressChanged(SeekBar seekBar, int progress,
			boolean fromTouch) {
	}

	/**
	 * @see android.widget.SeekBar.OnSeekBarChangeListener#onStartTrackingTouch(android.widget.SeekBar)
	 */
	public void onStartTrackingTouch(SeekBar seekBar) {
	}

	/**
	 * @see android.widget.SeekBar.OnSeekBarChangeListener#onStopTrackingTouch(android.widget.SeekBar)
	 */
	@Override
	public void onStopTrackingTouch(SeekBar arg0) {
	}

	/* HOLDER */
	private static class BoostConverterHolder {
		ImageView imgIcon;
		ImageButton iconStats;
		SeekBar seekBar;
		TextView txtId;
		TextView txtVi;
		TextView txtIl;
		TextView txtPi;
		TextView txtVo;
		TextView txtIo;
	}

	/* BOÎTE DE DIALOGUE */
	private void showDialog(Context context,
			final BoostConverter boostConverter, final Integer volts) {
		Configuration.boiteDeDialogue = new Dialog(context);
		Configuration.boiteDeDialogue
				.setContentView(R.layout.dialog_box_valider_consigne);
		Configuration.boiteDeDialogue.setTitle("Demander  " + volts
				+ "V en sortie pour le boost "
				+ Integer.parseInt(boostConverter.getId()) + "?");
		Configuration.boiteDeDialogue
				.setOnCancelListener(new DialogInterface.OnCancelListener() {
					@Override
					public void onCancel(DialogInterface dialog) {
						boostConverter.setVoStar(Integer.toString(volts * 100));
					}
				});
		Configuration.boiteDeDialogueBoutonAnnulerChangementDeVoStar = (Button) Configuration.boiteDeDialogue
				.findViewById(R.id.cancelPosition);
		Configuration.boiteDeDialogueBoutonAnnulerChangementDeVoStar
				.setOnClickListener(new OnClickListener() {
					@Override
					public void onClick(View v) {
						boostConverter
								.getSeekBar()
								.setProgress(
										Configuration.progressionAvantDemandeDeChangement);
						notifyDataSetChanged();
						Configuration.boiteDeDialogue.hide();
					}
				});
		Configuration.boiteDeDialogueBoutonValiderChangementDeVoStar = (Button) Configuration.boiteDeDialogue
				.findViewById(R.id.validatePosition);
		Configuration.boiteDeDialogueBoutonValiderChangementDeVoStar
				.setOnClickListener(new OnClickListener() {
					@Override
					public void onClick(View v) {
						boostConverter.setVoStar(Integer.toString(volts * 100));
						Configuration.boiteDeDialogue.hide();
					}
				});
		Configuration.boiteDeDialogue.show();
	}

}
