package musique;


import java.util.HashMap;
import java.util.Random;




public class GrilleHarmonique {
	final static int GAMME_MAJEURE = 0; // constantes
	int nbMesures;
	public String dominante;
	Parametres parametres;
	HashMap<Accord, Integer> accords;
	Random generateur = new Random();
	
	
	public GrilleHarmonique ( Parametres p, String dom){
		dominante = dom;
		parametres=p;
		accords = new HashMap<Accord, Integer>();
		
		if (p.harmonie == GrilleHarmonique.GAMME_MAJEURE){
			accords.put(new Accord(dominante+"maj"), 4);
			accords.put(new Accord(Note.decalage(dominante, 2)+"min"), 1);
			accords.put(new Accord(Note.decalage(dominante, 4)+"min"), 1);
			accords.put(new Accord(Note.decalage(dominante, 5)+"maj"), 2);
			accords.put(new Accord(Note.decalage(dominante, 7)+"maj"), 2);
			accords.put(new Accord(Note.decalage(dominante, 9)+"min"), 1);
		}
	
		//System.out.println(accords);
	}
	//fonction next pour avoir le suivant avec boucle
	public Accord randomAccord (){
		int somme = 0;
		for(int i:accords.values())
			somme += i;
		int de = generateur.nextInt(somme);
		for(Accord ac:accords.keySet()){
			if(de < accords.get(ac))
				return ac;
			de= de-accords.get(ac);
		}
		return null;	
	}
	
	public Accord[] tabGrille (){
		Accord[] tab = new Accord[4];
		for (int i = 0; i<4; i++){
			tab[i]= randomAccord();
		}
	// TODO il faudra verifier qu'on pas quatre fois le meme accord. mais p=1/64	
		return tab;
	}
	
}
