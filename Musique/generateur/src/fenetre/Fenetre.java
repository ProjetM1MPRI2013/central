package fenetre;

import java.awt.BorderLayout;
import java.awt.Checkbox;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;

public class Fenetre {
	
	String[] typeFichier = {"MIDI","MP3"} ;
	String[] rock = {"batterie", "basse", "guitare", "guitare"};
	String[] instruments = {"batterie", "basse", "guitare", "piano", "violon", "harpe", "ukulele"};
//	jazz
//	pop
//	classique
//	assenceur
	
	
	public void dessine (){
		JFrame fen = new JFrame ("Music Generator");
		BorderLayout disposeur = new BorderLayout(40,40);
		fen.setLayout(disposeur);
//nord
		JPanel nord = new  JPanel();
		BorderLayout gnord = new BorderLayout();
		nord.setLayout(gnord);
			JPanel nordhaut = new JPanel();
			Font maFont = new Font("serif",Font.BOLD,24);
			JLabel titre = new JLabel("Universal Music Generator for Games",JLabel.CENTER) ;
			titre.setFont(maFont);
			nordhaut.add(titre,BorderLayout.NORTH);
			nord.add(nordhaut,BorderLayout.NORTH);
			
			JPanel panelduree = new JPanel() ;
			JLabel duree = new JLabel ("Duree de la musique ");
			GridLayout dispoHaut = new GridLayout(1,4);
			panelduree.setLayout(dispoHaut);
			panelduree.add(duree);
			JTextField heures = new JTextField("heure",8);
			heures.setPreferredSize(new Dimension(200, 30));
			panelduree.add(heures);
			JTextField minutes = new JTextField("minutes",8);
			panelduree.add(minutes);
			JTextField secondes = new JTextField("secondes",8);
			panelduree.add(secondes);
		
			nord.add(panelduree,BorderLayout.SOUTH);
		fen.add(nord,BorderLayout.NORTH);
	

		
//sud		
		JPanel sud = new JPanel();
		BorderLayout disposeSud = new BorderLayout(30, 30);
		sud.setLayout(disposeSud);
		
		JPanel sudCentre = new JPanel();
			JLabel fichier = new JLabel ("Type de ficher de sortie : ");
			sudCentre.add(fichier);
			JComboBox<String> typeF = new JComboBox<String>(this.typeFichier);
			sudCentre.add(typeF);
		sud.add(sudCentre, BorderLayout.CENTER);
		
		JButton boutonGenere = new JButton("generate the file");	
		boutonGenere.setPreferredSize(new Dimension(200, 30));			
		sud.add(boutonGenere,BorderLayout.EAST);	
		fen.add(sud,BorderLayout.SOUTH);
		
		// centre
		JPanel centre = new JPanel() ;	
		GridLayout dispoCentre = new GridLayout(5,4);
		centre.setLayout(dispoCentre);
		centre.add(new JLabel(""));
		centre.add(new JLabel("Pistes....", JLabel.RIGHT));
		JLabel pistes = new JLabel("") ;
		centre.add(pistes);
		
		centre.add(new JLabel("Harmonie"));
		
		centre.add(new JLabel("Piste 1 : ", JLabel.RIGHT));
		JComboBox<String> piste1 = new JComboBox<String>(instruments);
		centre.add(piste1);
		
		JSlider volume1 = new JSlider(0, 10, 5);
		centre.add(volume1);
	
		JCheckBox majeure = new JCheckBox("Majeure");
		centre.add(majeure);
		
		centre.add(new JLabel("Piste 2 : " , JLabel.RIGHT));
		JComboBox<String> piste2 = new JComboBox<String>(instruments);
		centre.add(piste2);
		
		
		
		JSlider volume2 = new JSlider(0, 10, 5);
		centre.add(volume2);
		
		
		JCheckBox mineureH = new JCheckBox("Mineure harmonique");
		centre.add(mineureH);
		
		
		
		centre.add(new JLabel("Piste 3 : " , JLabel.RIGHT));
		JComboBox<String> piste3 = new JComboBox<String>(instruments);
		centre.add(piste3);
		
		JSlider volume3 = new JSlider(0, 10, 5);
		centre.add(volume3);
		
	
		JCheckBox mineureM = new JCheckBox("Mineure mélodique");
		centre.add(mineureM);
		
		centre.add(new JLabel("Piste 4 : ", JLabel.RIGHT));
		JComboBox<String> piste4 = new JComboBox<String>(instruments);
		centre.add(piste4);
		
		JSlider volume4 = new JSlider(0, 10, 5);
		centre.add(volume4);
		
		
		JCheckBox blues = new JCheckBox("Blues");
		centre.add(blues);
		
		ButtonGroup harmonies = new ButtonGroup();
		harmonies.add(majeure);
		harmonies.add(mineureH);
		harmonies.add(mineureM);
		harmonies.add(blues);
		
		
		fen.add(centre,BorderLayout.CENTER);

		
		
		//ouest 
		JPanel ouest = new JPanel() ;
		GridLayout dispoOuest = new GridLayout(7,1);
		ouest.setLayout(dispoOuest);
		JLabel style = new JLabel("Style : ") ;
		ouest.add(style);
		JCheckBox melodie = new JCheckBox("Ascenceur");
		ouest.add(melodie);
		JCheckBox zen = new JCheckBox("Rock");
		ouest.add(zen);
		JCheckBox oriental = new JCheckBox("Oriental");
		ouest.add(oriental);
		JCheckBox asiatique = new JCheckBox("Jazz");
		ouest.add(asiatique);
		JCheckBox classique = new JCheckBox("Classique");
		ouest.add(classique);
		JCheckBox chefPolice = new JCheckBox("Chef de la police");
		ouest.add(chefPolice);
		ButtonGroup styles = new ButtonGroup();
		styles.add(melodie);
		styles.add(zen);
		styles.add(oriental);
		styles.add(asiatique);
		styles.add(chefPolice);
		
		fen.add(ouest,BorderLayout.WEST);

		// Est
		JPanel est = new JPanel() ;
		GridLayout dispoEst = new GridLayout(9,1);
		est.setLayout(dispoEst);
		JLabel tempo = new JLabel("Tempo : ") ;
		est.add(tempo);
		JCheckBox lent = new JCheckBox("Lent");
		est.add(lent);
		JCheckBox normal = new JCheckBox("Normal");
		est.add(normal);
		JCheckBox rapide = new JCheckBox("Rapide");
		est.add(rapide);
		
		
		ButtonGroup tempos = new ButtonGroup();
		tempos.add(lent);
		tempos.add(normal);
		tempos.add(rapide);
		
		JLabel trou = new JLabel("") ;
		est.add(trou);
		JLabel densite = new JLabel("Densite de notes") ;
		est.add(densite);
		JCheckBox peu = new JCheckBox("peu");
		est.add(peu);
		JCheckBox normalnote = new JCheckBox("Normal");
		est.add(normalnote);
		JCheckBox beaucoup = new JCheckBox("beaucoup");
		est.add(beaucoup);
		
		ButtonGroup densites = new ButtonGroup();
		densites.add(peu);
		densites.add(normalnote);
		densites.add(beaucoup);
		
		
		
		fen.add(est,BorderLayout.EAST);

		
		
		
		
		
		
		
		
		fen.pack();
		fen.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fen.setVisible(true);
	}

}
