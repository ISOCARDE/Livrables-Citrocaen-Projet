package com.isocarde.citrocaen.communicarde.ui;

import android.content.Context;
import android.graphics.Typeface;
import android.util.AttributeSet;
import android.widget.TextView;

/**
 * <b>IsocardeTextView definie un type de texte propre a ISOCARDE.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public class IsocardeTextView extends TextView {

	Context context;
	String ttfName;

	String TAG = getClass().getName();

	/**
	 * @param context
	 * @param attrs
	 */
	public IsocardeTextView(Context context, AttributeSet attrs) {
		super(context, attrs);
		this.context = context;

		for (int i = 0; i < attrs.getAttributeCount(); i++) {
			this.ttfName = attrs
					.getAttributeValue(
							"http://schemas.android.com/apk/res/com.isocarde.citrocaen.communicarde",
							"ttf_name");
			init();
		}

	}

	private void init() {
		Typeface font = Typeface.createFromAsset(context.getAssets(), ttfName);
		setTypeface(font);
	}

	/**
	 * @see android.widget.TextView#setTypeface(android.graphics.Typeface)
	 */
	@Override
	public void setTypeface(Typeface tf) {
		super.setTypeface(tf);
	}

}