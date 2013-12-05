package musique;

import java.util.List;
import java.util.Random;

public class Accompagnement extends Base implements Piste{

	String[] tabAcc = new String[16];
	Random generateur = new Random();
	int nbNotesAjoutes;
	String instrument = "[53]";

	public Accompagnement (Accord[] tabAccord,String dominante,int nbNotesAjoutes ){
		super (tabAccord,dominante);
		this.nbNotesAjoutes = nbNotesAjoutes;
	}
	public String generePiste(){

		// au debut de chaque accord, on joue  l'accord
		for(int i = 0; i<4; i++){
			tabAcc[4*i]= tabAccord[i].noteDominante+tabAccord[i].typeAccord;
			System.out.println("==="+tabAcc[4*i]+"==="+tabAccord[i]);
		}

		int nbNotes = generateur.nextInt(nbNotesAjoutes/2)+nbNotesAjoutes/2;
		for (int i = 0 ; i<nbNotes; i++){
			int cases = generateur.nextInt(16);

			if (tabAcc[cases]== null) {
				Accord accord = tabAccord[cases/4];
				tabAcc[cases] = accord.noteDominante+accord.typeAccord;
			}
		}
		StringBuffer S = new StringBuffer();
		S.append(" I"+instrument);
		for (int i = 0; i<tabAcc.length; i++){
			if (tabAcc[i] == null){
				S.append("h");

			}
			else {
				S.append(" " + tabAcc[i]+"h");
			}

		}
		return S.toString();

	}
}
