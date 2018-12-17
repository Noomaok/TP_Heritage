//-------------- Interface de la classe <Catalogue> (fichier Catalogue.h) ---------------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//-------------- Interfaces utilisées -----------------------------
#include "Trajet.h"
#include "TableauTrajet.h"
//-------------- Constantes ---------------------------------------
//-------------- Types --------------------------------------------

//-----------------------------------------------------------------
//              Rôle de la classe <Catalogue>:
// Gerer un tableau de trajet, effectuer la recherche simle et
// avancee avec ce tableau.
// Cette classe est destinee a etre utilisee par le main du projet
//
// TOUT POINTEUR PASSE A CETTE CLASS EST ENTIEREMENT GERER PAS CETTE
// DERNIERE. LA LIBERATION DE LA MEMOIRE EST À LA CHARGE DE LA CLASSE
// ET DE SES ATTRIBUTS.
//-----------------------------------------------------------------

class Catalogue : public TableauTrajet
{
public:
//----- Methodes publiques -----

	void RechercheSimple(const char *villeDepart, const char *villeArrivee) const;
	// Mode d'emploi :
	// Effectue une recherche simple sur le catalogue.

	void RechercheAvancee(const char *villeDepart, const char *villeArrivee) const;
	// Mode d'emploi :
	// Effectue une recherche avancee sur le catalogue.

//---- Surchage d'opérateurs ----
/*
	Trajet * &operator[](int indice);
	// Surcharge de l'operateur []

	Trajet * &operator[](int indice) const;
	// Surcharge de l'operateur [] const
	*/
	friend std::ostream& operator<<(std::ostream& output, Catalogue const & catal);
	// Surchage de l'operateur <<
	
//--- Constructeurs - Desctructeurs ---

	Catalogue();
	// Mode d'emploi :
	// Cree un catalogue de trajet vide

	virtual ~Catalogue();
	// Mode d'emploi :
	// Supprime le catalogue courant

protected:
//----- Methodes protégées -----
//----- Attributs protégés -----

};
//------------ Autres définitions dépendantes de Catalogue ----------

#endif