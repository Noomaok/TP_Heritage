//------------- Realisation de la classe <Catalogue> ( fichier Catalogue.cpp ) -----------------

//------------- Include système ------------------------------------------------------------
#include <iostream>
#include <cstring>

//------------- Include personnel ----------------------------------------------------------
#include "Catalogue.h"

using namespace std;

//------------- Constantes -----------------------------------------------------------------


//------------- Methodes publiques ---------------------------------------------------------

void Catalogue::RechercheSimple(const char *villeDepart, const char *villeArrivee) const
{
	cout << endl << "Trajet(s) trouves : " << endl;
	bool aucun = true;
	for(int i = 0; i < GetNbElement(); i++)
	{
		Trajet *trajet = listeTrajet[i];
		if(strcmp(villeDepart,trajet->GetVilleDepart()) == 0 && strcmp(villeArrivee,trajet->GetVilleArrivee()) == 0)
		{
			aucun = false;
			cout << *trajet << endl;
		}
	}

	if(aucun)
	{
		cout << "Aucun." << endl;
	}
}//------- Fin de RechercheSimple

void Catalogue::RechercheAvancee(const char *villeDepart, const char *villeArrivee) const
{
	TableauTrajet listeTrajetPotentiel[100];
	int nbTrajetPotentiel = 0;
	int tour = 0;
	int nombreAssociationTrajet = 0;
	bool premierTour = true;
	cout << "Trajet(s) trouves : " << endl;
	while (tour >= 0)
	{
		for (int i = 0; i < nbElement; i++)
		{
			if (!strcmp(listeTrajet[i]->GetVilleDepart(), villeDepart) && premierTour)
			{
				listeTrajetPotentiel[nbTrajetPotentiel].Add(listeTrajet[i]);
				tour++;
				nbTrajetPotentiel++;
				if (!strcmp(listeTrajet[i]->GetVilleArrivee(), villeArrivee))
				{
					nombreAssociationTrajet++;
					cout << endl << "Association de trajet possible n°" << nombreAssociationTrajet << " : " << endl;
					cout << *listeTrajet[i] << endl;
				}
			}
			for (int j = 0; j < nbTrajetPotentiel; j++)
			{
				if (!strcmp(listeTrajetPotentiel[j][listeTrajetPotentiel[j].GetNbElement() - 1]->GetVilleArrivee(), listeTrajet[i]->GetVilleDepart()) && !listeTrajetPotentiel[j].DejaAjoute(listeTrajet[i]))
				{
					listeTrajetPotentiel[j].Add(listeTrajet[i]);
					tour++;
					if (!strcmp(listeTrajet[i]->GetVilleArrivee(), villeArrivee))
					{
						nombreAssociationTrajet++;
						cout << endl << "Association de trajet possible n°" << nombreAssociationTrajet << " : " << endl;
						cout << listeTrajetPotentiel[j] << endl;
					}
				}
			}
		}
		tour--;
		premierTour = false;
	}
	for (int i = 0; i < nbTrajetPotentiel; i++)
	{
		for (int j = 0; j < listeTrajetPotentiel[i].GetNbElement(); j++)
		{
			listeTrajetPotentiel[i][j] = nullptr;
			//On remplace tous les pointeurs vers les trajets par des poiteurs null car sinon à la destruction de listeTrajetPotentielle 
			//on perdrait tous les trajets originaux de notre catalogue (on ne copie pas les objets pour la recherche)
		}
	}

}//------- Fin de RechercheAvancee

//------------- Surcharge d'opérateurs -----------------------------------------------------

std::ostream& operator<<(std::ostream& output, Catalogue const & catal)
{
	cout << "Contenu du Catalogue :" << endl;
	cout << "{";
	if (catal.nbElement > 0)
	{
		for (int i = 0; i < catal.nbElement - 1; i++)
		{
			output << *catal[i] << "; " << std::endl;
		}
		output << *catal[catal.nbElement - 1];
	}
	output << " }";
	return output;
}//------- Fin de surcharge de <<


//------------- Constructeurs - Desctructeur -----------------------------------------------

Catalogue::Catalogue() : TableauTrajet()
{
#ifdef MAP
	cout << "Appel du constructeur de <Catalogue>" << endl;
#endif
}//------- Fin du constructeur

Catalogue::~Catalogue()
{
#ifdef MAP
	cout << "Appel du destructeur de <Catalogue>" << endl;
#endif
}//------- Fin du destructeur

//------------- Methodes protégées ---------------------------------------------------------
