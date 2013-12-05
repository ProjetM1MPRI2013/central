package fenetre;

import org.jfugue.Pattern;
import org.jfugue.Player;

public class GenereMusique {
	public static void main(String[] args) {
		//Fenetre f = new Fenetre ();
		//f.dessine();
		
		
		Player player = new Player(); 
		Pattern pattern1 = new Pattern("V0  A3q B3q C3q B3q"); 
		Pattern pattern2 = new Pattern("V1  I[Flute] A5h C5h");
		Pattern tout = new Pattern();
		tout.add(pattern1);
		tout.add(pattern2);
		//player.play(tout);
		//player.play("V0 I[Piano] C5q D5q V1 I[Flute] G5q F5q");  
		//player.play("V0  A3q B3q C3q B3q V1  A2h C2h");
		//player.play("C3q Rs Rs Rs C Rs Ab7q Bb2i");
		player.play("T[Presto] Cmaj5q F#min2h Bbmin13^^^");
		//System.exit(0); //
	}

}
