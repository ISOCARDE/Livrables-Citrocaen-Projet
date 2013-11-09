package com.isocarde.citrocaen.communicarde.ui;

import android.app.Activity;
import android.graphics.Typeface;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

/**
 * <b>IsocardeActivity definie un type d'activite propre a ISOCARDE.</b>
 * 
 * @author TOMA
 * @version 3.0
 * @see <a href="http://isocarde.fr.ht">ISOCARDE</a>
 */
public abstract class IsocardeActivity extends Activity {

	@Override
	protected void onResume() {
		super.onResume();
		ViewGroup root = ((ViewGroup) findViewById(android.R.id.content));
		setAllTypeface(root);
	}

	protected void setAllTypeface(View view) {
		if (view instanceof ViewGroup
				&& ((ViewGroup) view).getChildCount() != 0) {
			for (int i = 0; i < ((ViewGroup) view).getChildCount(); i++) {
				setAllTypeface(((ViewGroup) view).getChildAt(i));
			}
		} else {
			if (view instanceof TextView && !(view instanceof IsocardeTextView)) {
				((TextView) view).setTypeface(Typeface.createFromAsset(
						getAssets(), "fonts/trebucbd.ttf"));
			}
		}
	}
}