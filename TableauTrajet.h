//-------------- Interface de la classe <TableauTrajet> (fichier TableauTrajet.h) ---------------------
#if ! defined ( TABLEAUTRAJET_H )
#define TABLEAUTRAJET_H

//-------------- Interfaces utilisées -----------------------------
#include "Trajet.h"

//-------------- Constantes ---------------------------------------
//-------------- Types --------------------------------------------

//-----------------------------------------------------------------
//             Rôle de la classe <TableauTrajet>:
// Gerer une liste de trajet, l'ajout de nouvelle elements et leur
// acces.
//
// TOUT POINTEUR PASSE A CETTE CLASS EST ENTIEREMENT GERER PAS CETTE
// DERNIERE. LA LIBERATION DE LA MEMOIRE EST À LA CHARGE DE LA CLASSE
// ET DE SES ATTRIBUTS.
//-----------------------------------------------------------------

class TableauTrajet
{
public:
//----- Methodes publiques -----

	int GetNbElement() const;
	// Mode d'emploi :
	// Renvoie un entier correspondant au nombre d'elements present dans le tableau

	bool DejaAjoute(Trajet const *) const;
	// Mode d'emploi :
	// Regarde si le pointeur passé en paramètre a déja été ajouté au tableau, si c'est le ca renvoie true

	void Add(Trajet* trajetAjout);
	// Mode d'emploi :
	// Ajoute le trajet trajetAjout à la liste des trajets

	void DeleteElement(int indice);

//---- Surchage d'opérateurs ----

	Trajet * &operator[](int indice);
	// Surcharge de l'operateur []

	Trajet * &operator[](int indice) const;
	// Surcharge de l'operateur [] const

	friend std::ostream& operator<<(std::ostream& output, TableauTrajet const & tabTrajet);
	// Surcharge de l'operateur <<

//--- Constructeurs - Desctructeurs ---

	TableauTrajet(Trajet** listeTrajetIni = new Trajet*[10],int nbElementIni = 0);
	// Mode d'emploi :
	// Creer un nouveau TableauTrajet avec un tableau de trajet listeTrajetIni et un nombre nbElementIni d'element

	TableauTrajet(TableauTrajet const& tableauTrajetACopier);
	// Mode d'emploi :
	// Constructeur de copie de TableauTrajet. Creer une copie de l'element tableauTrajetACopier

	~TableauTrajet();
	// Mode d'emploi : 
	// Destructeur de TableauTrajet. Libere la memoire de l'objet.

protected:
//----- Methodes protégées -----
//----- Attributs protégés -----

	Trajet** listeTrajet;
	int size;
	int nbElement;

};
//------------ Autres définitions dépendantes de TableauTrajet ----------

#endif