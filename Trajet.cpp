//------------- Realisation de la classe <Trajet> ( fichier Trajet.cpp ) -----------------

//------------- Include système ------------------------------------------------------------
#include <iostream>
#include <cstring>

using namespace std;

//------------- Include personnel ----------------------------------------------------------
#include "Trajet.h"

//------------- Constantes -----------------------------------------------------------------


//------------- Methodes publiques ---------------------------------------------------------

bool Trajet::TestCompatible(const Trajet & trajet1, const Trajet & trajet2)
{
	if (strcmp(trajet1.villeArrivee,trajet2.villeDepart) == 0)
	{
		return true;
	}

	return false;
}//-------- Fin de TestCompatible

const char* Trajet::GetVilleDepart() const
{
	return villeDepart;
}//-------- Fin de GetVilleDepart

const char* Trajet::GetVilleArrivee() const
{
	return villeArrivee;
}//-------- Fin de GetVilleArrivee

//------------- Surcharge d'opérateurs -----------------------------------------------------

std::ostream& operator<<(std::ostream& output, Trajet const & trajet)
{
	trajet.Affichage();
	return std::cout;
}//-------- Fin de la surcharge de <<

//------------- Constructeurs - Desctructeur -----------------------------------------------
Trajet::Trajet(const char *villeDep,const char *villeArr)
: villeDepart(new char[100]), villeArrivee(new char[100]), numTrajet(0) //initialisation pour le strcpy, taille max 100 caracteres
{ 
	strcpy(villeDepart, villeDep);
	strcpy(villeArrivee, villeArr);
#ifdef MAP
	cout << "Appel du constructeur de <Trajet>" << endl;
#endif
}//------- Fin du constructeur

Trajet::~Trajet()
{
#ifdef MAP
	cout << "Appel du destructeur de <Trajet>" << endl;
#endif
	delete[] villeArrivee;
	delete[] villeDepart;
}//------- Fin du destructeur

//------------- Methodes protégées ---------------------------------------------------------
