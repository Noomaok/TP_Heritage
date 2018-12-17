//-------------- Interface de la classe <Trajet> (fichier Trajet.h) ---------------------
#if ! defined ( TRAJET_H )
#define TRAJET_H

//-------------- Interfaces utilisées -----------------------------
#include <fstream>

using namespace std;

//-------------- Constantes ---------------------------------------
//-------------- Types --------------------------------------------

//-----------------------------------------------------------------
//               Rôle de la classe <Trajet>:
// Gerer les informations d'un trajet, c'est a dire les villes de
// depart et d'arrive.
// Cette classe fournie egalement des methodes pour traiter ces 
// donnees
//
// TOUT POINTEUR PASSE A CETTE CLASS EST ENTIEREMENT GERER PAS CETTE
// DERNIERE. LA LIBERATION DE LA MEMOIRE EST À LA CHARGE DE LA CLASSE
// ET DE SES ATTRIBUTS.
//-----------------------------------------------------------------

class Trajet
{
public:
//----- Methodes publiques -----
	
	virtual void Affichage() const = 0;
	// Methode virtuelle pur destine a gerer l'affichage des trajets

	virtual int GetType() const = 0;

	virtual void SaveTrajet(ofstream &fichier) const = 0;

	static bool TestCompatible(Trajet const &  trajet1, const Trajet & trajet2);
	// Mode d'emploi :
	// Test la compatibilite de deux trajet. Renvoie true si l'arrive de trajet1 est identique au depart de trajet2

	const char* GetVilleDepart() const;
	// Mode d'emploi :
	// Renvoie la valeur actuelle de villeDepart

	const char* GetVilleArrivee() const;
	// Mode d'emploi :
	// Renvoie la valeur actuelle de villeArrivee

	virtual Trajet* Clone() const = 0;
	// Methode virtuelle pur destine a dupliquer le trajet courant

//---- Surchage d'opérateurs ----
	
	friend std::ostream& operator<<(std::ostream& output, Trajet const & trajet);
	//Surcharge de l'operateur << pour simplifier l'affichage des trajets

//--- Constructeurs - Desctructeurs ---
	
	Trajet(const char *villeDep = "",const char *villeArr = "");
	// Mode d'emploi :
	// Cree un trajet avec villeDep comme ville de depart et villeArr comme ville d'arrivee
	
	virtual ~Trajet();
	// Mode d'emploi :
	// Supprime le trajet courant et libere la memoire

protected:
//----- Methodes protégées -----
	
	Trajet(Trajet const & trajetACopier) {};

//----- Attributs protégés -----
	
	char *villeDepart;
	char *villeArrivee;
	int numTrajet;

};
//------------ Autres définitions dépendantes de Trajet ----------

#endif