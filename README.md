# TP_Heritage

Si tu charges le fichier 

0 A B X

0 B C X

1 D F 2

0 D E X

0 E F X

0 G H X

3

et que tu le save avec le critère NONE, le fichier de sauvegarde aura cette allure :

0 A B X

0 B C X

1  2

0 D E X

0 E F X

0 G H X

3

C'est parce que dans la méthode TrajetCompose::loadTrajetCompose, tu avais mis 
listeTrajet->Add(nouveauTrajet); 
et pas 
AjouterTrajet(nouveauTrajet);
