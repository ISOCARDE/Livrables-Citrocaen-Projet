package com.isocarde.citrocaen.communicarde.beans;

/**
 * <b>BoostConverter est l'objet representant un boost converter pour le
 * serveur.</b>
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

	/* CONSTRUCTEURS */
	/**
	 * Constructeur par defaut
	 */
	public BoostConverter() {
		super();
	}

	/**
	 * Constructeur avec parametres
	 * 
	 * @param id
	 * @param vo
	 * @param vi
	 * @param vil
	 */
	public BoostConverter(String id, String vo, String vi, String vil) {
		super();
		this.id = id;
		this.vo = vo;
		this.vi = vi;
		this.vil = vil;
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
		return true;
	}

	/**
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "BoostConverter [id=" + this.id + ", vo=" + this.vo + ", vi="
				+ this.vi + ", vil=" + this.vil + "]";
	}

}
