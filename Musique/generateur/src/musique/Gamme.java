package musique;

import java.util.ArrayList;
import java.util.List;

public class Gamme {
	public String noteDominante ;// exemple C (do)
	 public String typeGamme;// exemple maj
	
	 public Gamme (String gamme){  // exemple Cmin7
		  noteDominante = gamme.substring(0,1);
		  typeGamme = gamme.substring(1);
		  
	 }
	 public List <String> nomNotes(){
		 List<String> liste = new ArrayList<String>();
		 if( typeGamme.equals("maj")){
			 liste.add(noteDominante);
			 liste.add( Note.decalage(noteDominante, 2));
			 liste.add( Note.decalage(noteDominante, 4));
			 liste.add( Note.decalage(noteDominante, 5));
			 liste.add( Note.decalage(noteDominante, 7));
			 liste.add( Note.decalage(noteDominante, 9));
			 liste.add( Note.decalage(noteDominante, 11));
			 	 
		 }
		 
		 return liste;
	 }



}

