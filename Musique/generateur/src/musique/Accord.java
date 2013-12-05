package musique;

import java.util.ArrayList;
import java.util.List;

public class Accord {
	public String noteDominante ;// exemple C (do)
	 public String typeAccord;// exemple maj
	
	 public Accord (String accord){  // exemple Cmin7
		  noteDominante = accord.substring(0,1);
		  typeAccord = accord.substring(1);
		  
	 }
	 

	//methode qui renvoie la liste de notes de l'accord
	 public List <String> nomNotes(){
		 List<String> liste = new ArrayList<String>();
		 if( typeAccord.equals("min")){
			 liste.add(noteDominante);
			 liste.add( Note.decalage(noteDominante, 3));
			 liste.add( Note.decalage(noteDominante, 7));			 
		 }
		 if( typeAccord.equals("maj")){
			 liste.add(noteDominante);
			 liste.add( Note.decalage(noteDominante, 4));
			 liste.add( Note.decalage(noteDominante, 7));			 
		 }
		 return liste;
	 }



	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((noteDominante == null) ? 0 : noteDominante.hashCode());
		result = prime * result
				+ ((typeAccord == null) ? 0 : typeAccord.hashCode());
		return result;
	}



	public boolean equals(Object obj) {
		if (this == obj)
			return true;

		if (getClass() != obj.getClass())
			return false;
		Accord other = (Accord) obj;
		if (noteDominante == null) {
			if (other.noteDominante != null)
				return false;
		} else if (!noteDominante.equals(other.noteDominante))
			return false;
		if (typeAccord == null) {
			if (other.typeAccord != null)
				return false;
		} else if (!typeAccord.equals(other.typeAccord))
			return false;
		return true;
	}



	public String toString() {
		return noteDominante + typeAccord;
	} 
	 
}
