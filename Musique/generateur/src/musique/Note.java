package musique;

public class Note {
	public static String[] notes = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B",};
	
	public static int indNote(String note){
		for( int i = 0; i<12; i++){
			if( notes[i].equals(note)){
				return i;
			}
		}
		return -1;
	}
	
	public static String decalage( String note, int decalage){
		return  notes[(indNote(note)+ decalage) % 12];
	}
	
	
}
