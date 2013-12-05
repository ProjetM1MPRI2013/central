package musique;

import java.util.List;
import java.util.Random;

public class Basse extends Base implements Piste{
	String[] tabNotes = new String[32];
	Random generateur = new Random();
	int nbNotesAjoutes;
	String instrument = "[33]";
	
	public Basse (Accord[] tabAccord,String dominante, int nbNotesAjoutes ){
		super (tabAccord,dominante);
		this.nbNotesAjoutes = nbNotesAjoutes;
	}

	public String generePiste(){
		// au debut de chaque accord, on joue la tonique de l'accord

		for(int i = 0; i<4; i++){
			tabNotes[8*i]= tabAccord[i].noteDominante +"2";
			System.out.println("==="+tabNotes[8*i]+"==="+tabAccord[i]);
		}
		//puis on rajoute peu de note (k)  au pif:on tire au sort k entre 2 et 8,
		// k  =  le nombre de notes qu'on rajoute en tout; 
		// on tire au sort une case du tableau k fois, 
		//   si la case n'est pas remplie, on  met une note de l'accord dedans 

		int nbNotes = generateur.nextInt(nbNotesAjoutes/2)+nbNotesAjoutes/2;
		for (int i = 0 ; i<nbNotes; i++){
			int cases = generateur.nextInt(32);

			if (tabNotes[cases]== null) {
				Accord accord = tabAccord[cases/8];
				List <String> notesAccord = accord.nomNotes();
				int numNote = generateur.nextInt(notesAccord.size());
				tabNotes[cases] = notesAccord.get(numNote)+"3";
			}
		}

		//  le choix des octaves: si la case modulo 8 est 0, c'est 2 sinon c'est 3
		// pour la duré des notes 


		// si j'ai do vide vide vide mi, le do doit durer trois croches

		StringBuffer S = new StringBuffer();
		S.append(" I"+instrument);
		for (int i = 0; i<tabNotes.length; i++){
			if (tabNotes[i] == null){
				S.append("q");

			}
			else {
				S.append(" " + tabNotes[i]+"q");
			}

		}
		return S.toString();

	}


	public void affiche(){
		for (String s :tabNotes) {
			if (s!=null){
				System.out.println(s);
			}
		}
	}
	//	instrument
	//	grilleHarmonque

	//	base = new basse '"picolo", grilleHamrmique12
	//	base.generatePattern
}
