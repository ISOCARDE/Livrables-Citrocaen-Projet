package com.isocarde.citrocaen.communicarde.beans;

import android.widget.SeekBar;

import com.isocarde.citrocaen.communicarde.configuration.Configuration;

/**
 * <b>BoostConverter est l'objet qui represente un boost converter au niveau de
 * l'application Android.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public class BoostConverter {
	/* CARACTÉRISTIQUES D'UN BOOST CONVERTER */
	private String id;
	private String vo;
	private String vi;
	private String vil;
	private String voStar;
	private SeekBar seekBar;

	/* CONSTRUCTEURS DE BOOST CONVERTER */
	/**
	 * Constructeur de boost converter par defaut
	 */
	public BoostConverter() {
		super();
	}

	/**
	 * Constructeur de boost converter par trame
	 * 
	 * @param trame
	 */
	public BoostConverter(String trame) {
		super();
		this.id = trame.substring(0, 4);
		this.vo = trame.substring(4, 8);
		this.vi = trame.substring(8, 12);
		this.vil = trame.substring(12, 16);
		this.voStar = Configuration.voStarParDefaut;
	}

	/* ACCESSEURS / MUTATEURS */
	/**
	 * @return the id
	 */
	public String getId() {
		return this.id;
	}

	/**
	 * @param id
	 *            the id to set
	 */
	public void setId(String id) {
		this.id = id;
	}

	/**
	 * @return the vo
	 */
	public String getVo() {
		return this.vo;
	}

	/**
	 * @param vo
	 *            the vo to set
	 */
	public void setVo(String vo) {
		this.vo = vo;
	}

	/**
	 * @return the vi
	 */
	public String getVi() {
		return this.vi;
	}

	/**
	 * @param vi
	 *            the vi to set
	 */
	public void setVi(String vi) {
		this.vi = vi;
	}

	/**
	 * @return the vil
	 */
	public String getVil() {
		return this.vil;
	}

	/**
	 * @param vil
	 *            the vil to set
	 */
	public void setVil(String vil) {
		this.vil = vil;
	}

	/**
	 * @return the voStar
	 */
	public String getVoStar() {
		return this.voStar;
	}

	/**
	 * @param voStar
	 *            the voStar to set
	 */
	public void setVoStar(String voStar) {
		this.voStar = voStar;
	}

	/**
	 * @return the seekBar
	 */
	public SeekBar getSeekBar() {
		return this.seekBar;
	}

	/**
	 * @param seekBar
	 *            the seekBar to set
	 */
	public void setSeekBar(SeekBar seekBar) {
		this.seekBar = seekBar;
	}

	/* HASHCODE / EQUALS */
	/**
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((this.id == null) ? 0 : this.id.hashCode());
		result = prime * result + ((this.vi == null) ? 0 : this.vi.hashCode());
		result = prime * result
				+ ((this.vil == null) ? 0 : this.vil.hashCode());
		result = prime * result + ((this.vo == null) ? 0 : this.vo.hashCode());
		result = prime * result
				+ ((this.voStar == null) ? 0 : this.voStar.hashCode());
		return result;
	}

	/**
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (!(obj instanceof BoostConverter))
			return false;
		BoostConverter other = (BoostConverter) obj;
		if (this.id == null) {
			if (other.id != null)
				return false;
		} else if (!this.id.equals(other.id))
			return false;
		if (this.vi == null) {
			if (other.vi != null)
				return false;
		} else if (!this.vi.equals(other.vi))
			return false;
		if (this.vil == null) {
			if (other.vil != null)
				return false;
		} else if (!this.vil.equals(other.vil))
			return false;
		if (this.vo == null) {
			if (other.vo != null)
				return false;
		} else if (!this.vo.equals(other.vo))
			return false;
		if (this.voStar == null) {
			if (other.voStar != null)
				return false;
		} else if (!this.voStar.equals(other.voStar))
			return false;
		return true;
	}

	/* MÉTHODES POUR CONVERTIR PROGRESSIONS ET VALEURS DE VO_STAR */
	/**
	 * Donne l'equivalent voltaïque de la barre de progression
	 * 
	 * @param progress
	 * @return le voltage associe
	 */
	public static int voStarPourcentageToVolts(int progress) {
		return progress == 100 ? 36 : progress == 75 ? 30 : progress == 50 ? 24
				: 18;
	}

	/**
	 * Donne l'equivalent de la tension en pourcentage de progression
	 * 
	 * @param voStar
	 * @return le pourcentage associe
	 */
	public static int voStarVoltsToPourcentage(Float voStar) {
		return voStar == 36f ? 100 : voStar == 30f ? 75 : voStar == 24f ? 50
				: voStar == 18f ? 25 : 50;
	}

	/* MÉTHODES D'ESTIMATION DES PARAMÈTRES NON TRANSMIS */
	/**
	 * @return la representation de Il estime
	 */
	public String getIl() {
		return Float.toString(Math.round(Math.abs(Float.parseFloat(this.vi)
				- Float.parseFloat(this.vil))
				/ (Configuration.resSh)) / 100f);
	}

	/**
	 * @return la representation de Pi estime
	 */
	public String getPi() {
		Float vi = Float.parseFloat(this.vi) / 100f;
		Float vil = Float.parseFloat(this.vil) / 100f;
		Float terme1 = Math.abs(vi - vil) / Configuration.resSh;
		Float terme2 = Float.parseFloat(this.vi) / 100f;
		return Float.toString(Math.round(terme1 * terme2 * 100) / 100f);
	}

	/**
	 * @return la representation de Io estime
	 */
	public String getIo() {
		return Float.toString(Math.round(Float.parseFloat(this.vo) * 10f
				/ Configuration.resCh));
	}

	/* MÉTHODES D'AFFICHAGE */
	/**
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return this.id + this.voStar;
	}

	/**
	 * @return la representation des statistiques du boost
	 */
	public String toStats() {
		return "BoostConverter [id=" + this.id + ", vo=" + this.vo + ", vi="
				+ this.vi + ", vil=" + this.vil + ", voStar=" + this.voStar
				+ "]";
	}
}
