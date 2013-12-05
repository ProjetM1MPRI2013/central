package pg;

import java.util.List;

import org.jfugue.Pattern;
import org.jfugue.Player;

import musique.Accompagnement;
import musique.Accord;
import musique.Basse;
import musique.GrilleHarmonique;
import musique.Melodie;
import musique.Parametres;

public class Program {
	public static void main(String[] args) {
		System.out.println("debut");
		Accord a = new Accord("Amaj");
		Parametres p = new Parametres(0);
		Player player = new Player(); 

		GrilleHarmonique G = new GrilleHarmonique(p, "C");
		//	for(int i=0;i<10;i++)
		//		System.out.println(G.randomAccord());
		Accord[] tabAccord  = G.tabGrille(); 
		Basse basse= new Basse(tabAccord,G.dominante,20); 
		Accompagnement accompagnement = new Accompagnement(tabAccord,G.dominante,10);
		Melodie melodie = new Melodie(tabAccord,G.dominante);
		String basseP = basse.generePiste();
		String accompagnementP = accompagnement.generePiste();
		Pattern p1 = new Pattern("V1"+basseP+basseP+basseP+basseP);
		Pattern p2 = new Pattern("V2"+accompagnementP+accompagnementP+accompagnementP+accompagnementP);
		Pattern p3 = new Pattern("V3"+melodie.generePiste()+melodie.generePiste()+melodie.generePiste()+melodie.generePiste());
		
		Pattern tout = new Pattern();
		tout.add(p1);
		tout.add(p2);
		tout.add(p3);
		player.play(tout) ;
	}

}
