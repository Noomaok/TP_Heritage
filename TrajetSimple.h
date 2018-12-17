//-------------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ---------------------
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H

//-------------- Interfaces utilisées -----------------------------
#include "Trajet.h"

//-------------- Constantes ---------------------------------------
//-------------- Types --------------------------------------------

//-----------------------------------------------------------------
//             Rôle de la classe <TrajetSimple>:
// Gerer les informations d'un trajet simple, c'est a dire sa ville
// de depart, sa ville d'arrivee et son moyen de transport.
//
// TOUT POINTEUR PASSE A CETTE CLASS EST ENTIEREMENT GERER PAS CETTE
// DERNIERE. LA LIBERATION DE LA MEMOIRE EST À LA CHARGE DE LA CLASSE
// ET DE SES ATTRIBUTS.
//-----------------------------------------------------------------

class TrajetSimple : public Trajet
{
public:
//----- Methodes publiques -----
	
	virtual void Affichage() const;
	// Mode d'emploi :
	// Affiche la ville de depart, la ville d'arrivee et le moyen de transport dans la sortie par defaut du systeme

	virtual Trajet* Clone() const;
	// Mode d'emploi :
	// Renvoie une copie du trajet simple courant

//---- Surchage d'opérateurs ----
//--- Constructeurs - Desctructeurs ---

	TrajetSimple(const char *villeDep, const char *villeArr,const char *moyenTp);
	// Mode d'emploi :
	// Cree un Trajet simple avec villeDep comme ville de depart, villeArr comme ville d'arrivee et moyenTp comme moyen de transport

	TrajetSimple(TrajetSimple const& trajetSimpleACopier);
	// Mode d'emploi :
	// Cree une copie du Trajet simple passee en parametre

	virtual ~TrajetSimple();
	// Mode d'emploi :
	// Supprime le trajet simple courant

protected:
//----- Methodes protégées -----
//----- Attributs protégés -----

	static int compteurTs;      //Compteur des trajets simple
	char *moyenTransport;


};
//------------ Autres définitions dépendantes de TrajetSimple ----------

#endif