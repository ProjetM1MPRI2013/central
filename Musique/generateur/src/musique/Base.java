package musique;

public class Base {
	public Accord[] tabAccord;
	public String dominante;
	
	public Base(Accord[] tabAccord,String dominante){
		this.tabAccord = tabAccord ;
		this.dominante = dominante;
	}
	
	
	
	//pattern = Base ( grilleHarminique)
		//generer un tab en interne 
		//factory qui cr�er un pattern en fonction de parametre
}
