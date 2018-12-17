//-------------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ---------------------
#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H

//-------------- Interfaces utilisées -----------------------------
#include "Trajet.h"
#include "TableauTrajet.h"

//-------------- Constantes ---------------------------------------
//-------------- Types --------------------------------------------

//-----------------------------------------------------------------
//           Rôle de la classe <TrajetCompose>:
// Gerer les informations d'un trajet compose d'autre trajets, qui
// peuvent etre simple ou composes.
//
// TOUT POINTEUR PASSE A CETTE CLASS EST ENTIEREMENT GERER PAS CETTE
// DERNIERE. LA LIBERATION DE LA MEMOIRE EST À LA CHARGE DE LA CLASSE
// ET DE SES ATTRIBUTS.
//-----------------------------------------------------------------

class TrajetCompose : public Trajet
{
public:
//----- Methodes publiques -----

	virtual void Affichage() const;
	// Mode d'emploi :
	// Affiche le contenu du TrajetCompose courant

	virtual int GetType() const;

	bool AjouterTrajet(Trajet *nouveauTrajet);
	// Mode d'emploi :
	// Ajouter le trajet à la liste si il est compatible avec ceux déjà présent. Renvoie true si le trajet été corectement ajouté. Sinon renvoie false.

	bool RemoveLast();

	virtual Trajet* Clone() const;
	// Mode d'emploi :
	// Renvoie une copie du trajet compose courant

//---- Surchage d'opérateurs ----
//--- Constructeurs - Desctructeurs ---

	TrajetCompose(Trajet** listeTrajet, int nbElement);
	// Mode d'emploi :
	// Cree un trajet compose a partir d'un tableau de Trajet listeTrajet, sachant le nombre d'element nbElement.

	TrajetCompose(Trajet* trajetIni = nullptr);
	// Mode d'emploi :
	// Cree un trajet compose a partir d'un unique trajet initiale trajetIni.

	TrajetCompose(TableauTrajet* tabTrajet);
	// Mode d'emploi :
	// Cree un trajet compose a partir d'une structure TableauTrajet tabTrajet.

	TrajetCompose(TrajetCompose const& trajetACopier);
	// Mode d'emploi :
	// Constructeur de copie de trajet compose. Cree une copie du trajet compose passe en parametre.

	virtual ~TrajetCompose();
	// Mode d'emploi :
	// Desctructeur de trajet compose. Libere la memoire allouer au trajet compose.

protected:
//----- Methodes protégées -----
//----- Attributs protégés -----

	static int compteurTc;			//Compteur de trajet composes
	TableauTrajet* listeTrajet;

};
//------------ Autres définitions dépendantes de TrajetCompose ----------

#endif