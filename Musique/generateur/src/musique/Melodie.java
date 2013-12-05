package musique;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class Melodie extends Base implements Piste{
	//String[] tabNotes = new String[64];
	Random generateur = new Random();
	String instrument = "[10]";

	public Melodie (Accord[] tabAccord,String dominante){
		super (tabAccord,dominante);
	}
	public String generePiste(){
		LinkedList<String> listeGamme = new LinkedList<String>();
		List<String> gamme = (new Gamme(dominante+"maj")).nomNotes();
		for(String note:gamme)
			listeGamme.add(note+"4");
		for(String note:gamme)
			listeGamme.add(note+"5");
		listeGamme.add(dominante+"6");


		int indiceNote = 7;
		StringBuffer S = new StringBuffer();
		S.append(" I"+instrument);
		for(int temps = 0; temps < 64; temps ++) {
			int de = generateur.nextInt(5);
			if (de ==0){
				LinkedList<Integer> liste = new LinkedList<Integer>();
				
				for(int i=indiceNote-2;i<=indiceNote+2;i++)
					if (i>=0 && i< listeGamme.size())
						liste.add(i);
				int dede = generateur.nextInt(liste.size());
				S.append(" "+listeGamme.get(dede)+"i");
			}
			if (de == 1){
				int dede = generateur.nextInt(listeGamme.size());
				S.append(" "+listeGamme.get(dede)+"i");
			}
			if (de > 1) {
				S.append(" Ri");
			}
		}
		return S.toString();
	}
}

