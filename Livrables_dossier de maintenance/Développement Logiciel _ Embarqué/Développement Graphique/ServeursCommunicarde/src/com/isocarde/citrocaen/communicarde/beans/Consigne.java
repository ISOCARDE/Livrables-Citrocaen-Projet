package com.isocarde.citrocaen.communicarde.beans;

/**
 * <b>Consigne est l'objet representant une consigne pour le serveur.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public class Consigne {
	/* CARACTÉRISTIQUES D'UNE CONSIGNE */
	private String id;
	private String voStar;

	/* CONSTRUCTEURS */
	/**
	 * Constructeur par defaut
	 */
	public Consigne() {
		super();
	}

	/**
	 * Construteur avec parametres
	 * 
	 * @param id
	 * @param voStar
	 */
	public Consigne(String id, String voStar) {
		super();
		this.id = id;
		this.voStar = voStar;
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
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "Consigne [id=" + this.id + ", voStar=" + this.voStar + "]";
	}

	/**
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((this.id == null) ? 0 : this.id.hashCode());
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
		if (!(obj instanceof Consigne))
			return false;
		Consigne other = (Consigne) obj;
		if (this.id == null) {
			if (other.id != null)
				return false;
		} else if (!this.id.equals(other.id))
			return false;
		if (this.voStar == null) {
			if (other.voStar != null)
				return false;
		} else if (!this.voStar.equals(other.voStar))
			return false;
		return true;
	}
}