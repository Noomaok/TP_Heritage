//------------- Realisation de la classe <TrajetCompose> ( fichier TrajetCompose.cpp ) -----------------

//------------- Include système ------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//------------- Include personnel ----------------------------------------------------------
#include "TrajetCompose.h"
#include "TrajetSimple.h"

int TrajetCompose::compteurTc = 0;

//------------- Constantes -----------------------------------------------------------------


//------------- Methodes publiques ---------------------------------------------------------

void TrajetCompose::SaveTrajet(ofstream & fichier) const
{
	fichier << listeTrajet->GetNbElement() << endl;
	for(int i = 0; i < listeTrajet->GetNbElement(); i++)
	{
		Trajet * unTrajet = (*listeTrajet)[i];
		int typeTrajet =  unTrajet->GetType();
		fichier << typeTrajet << " " << unTrajet->GetVilleDepart() << " " << unTrajet->GetVilleArrivee() << " ";
		unTrajet->SaveTrajet(fichier);
	}
}

streampos TrajetCompose::loadTrajetCompose(ifstream &file, streampos currentPos, int nbAdd)
{
	file.seekg(currentPos);
	char categorie;
	string villeDep, villeArr, moyTransport;
	for(int i = 0; i < nbAdd; i++)
	{
		file >> categorie >> villeDep >> villeArr;
		if(categorie == '0')
		{
			file >> moyTransport;
			TrajetSimple *nouveauTrajet = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyTransport.c_str());
			AjouterTrajet(nouveauTrajet);
		}
		else if(categorie == '1')
		{
			int nbTrajet;
			file >> nbTrajet;
			TrajetCompose *nouveauTrajet = new TrajetCompose();
			file.seekg(nouveauTrajet->loadTrajetCompose(file, file.tellg(), nbTrajet));
			AjouterTrajet(nouveauTrajet);
		}
	}
	return file.tellg();
}

int TrajetCompose::GetType() const
{
	return 1;
}

void TrajetCompose::Affichage() const
{
	cout << "TC" << numTrajet << " : " << endl << "{" << endl;
	for(int i=0;i<listeTrajet->GetNbElement();i++)
	{
		cout << "\t";
		(*listeTrajet)[i]->Affichage();
		cout << endl;
	}
	cout << "}";
}//--------- Fin de Affichage

bool TrajetCompose::AjouterTrajet(Trajet* nouveauTrajet)
{
	if(listeTrajet->GetNbElement() == 0) //Si il n'y a pas d'elements dans la listeTrajet
	{
		listeTrajet->Add(nouveauTrajet);

		strcpy(villeArrivee,nouveauTrajet->GetVilleArrivee());
		strcpy(villeDepart,nouveauTrajet->GetVilleDepart());
		return true;
	}
	else if(Trajet::TestCompatible(*(*listeTrajet)[listeTrajet->GetNbElement()-1],*nouveauTrajet)) //Si l'element peut etre ajouter
	{
		listeTrajet->Add(nouveauTrajet);
		strcpy(villeArrivee,nouveauTrajet->GetVilleArrivee());
		return true;
	}
	delete nouveauTrajet;
	return false;
}//--------- Fin de AjouterTrajet

Trajet* TrajetCompose::Clone() const
{
	return new TrajetCompose(*this);
}//--------- Fin de Clone

//------------- Surcharge d'opérateurs -----------------------------------------------------

//------------- Constructeurs - Desctructeur -----------------------------------------------
TrajetCompose::TrajetCompose(Trajet* trajetIni)
: Trajet("","")
{
#ifdef MAP
	cout << "Appel du constructeur de <TrajetCompose1>" << endl;
#endif
	listeTrajet = new TableauTrajet();
	if(trajetIni != nullptr){
		AjouterTrajet(trajetIni);
	}
	numTrajet = ++TrajetCompose::compteurTc;
}//-------- Fin du constructeur 1

TrajetCompose::TrajetCompose(Trajet** listeTrajetIni, int nbElement)
: Trajet("","")
{
#ifdef MAP
	cout << "Appel du constructeur de <TrajetCompose2>" << endl;
#endif
	listeTrajet = new TableauTrajet();
	int nombreAjoute = nbElement;
	if(nbElement > 0){
		for(int i = 0;i<nbElement;i++)
		{
			if(!(AjouterTrajet(listeTrajetIni[i])))
			{
				#ifdef MAP
					cout << "Erreur : trajets non compatibles" << endl;
				#endif
				nombreAjoute = i;
				break;
			}
		}
		for(int i = nombreAjoute + 1;i<nbElement;i++) // i = nb + 1 car le premier element mauvais est deja delete dans AjouterTrajet();
		{
			delete listeTrajetIni[i];
		}
	}
	else
	{
		TrajetCompose();
	}
	delete[] listeTrajetIni;
	numTrajet = ++TrajetCompose::compteurTc;
}//-------- Fin du constructeur 2

TrajetCompose::TrajetCompose(TableauTrajet* tabTrajet)
: Trajet("",""), listeTrajet(tabTrajet)
{
#ifdef MAP
	cout << "Appel du constructeur de <TrajetCompose3>" << endl;
#endif
	strcpy(villeDepart,(*tabTrajet)[0]->GetVilleDepart()); //initialisation des valeurs des villes de départs et d'arrivee
	strcpy(villeArrivee,(*tabTrajet)[tabTrajet->GetNbElement()-1]->GetVilleArrivee());
	numTrajet = ++TrajetCompose::compteurTc;
}//-------- Fin du constructeur 3

TrajetCompose::TrajetCompose(TrajetCompose const& trajetACopier)
: Trajet("","")
{
#ifdef MAP
	cout << "Appel du constructeur de copie de <TrajetCompose>" << endl;
#endif
	listeTrajet = new TableauTrajet(*(trajetACopier.listeTrajet));
	strcpy(villeDepart,(*listeTrajet)[0]->GetVilleDepart()); //initialisation des valeurs des villes de départs et d'arrivee
	strcpy(villeArrivee,(*listeTrajet)[listeTrajet->GetNbElement()-1]->GetVilleArrivee());
	numTrajet = ++TrajetCompose::compteurTc;
}//-------- Fin du constructeur de copie

TrajetCompose::~TrajetCompose()
{
#ifdef MAP
	cout << "Appel du destructeur de <TrajetCompose>" << endl;
#endif
	delete listeTrajet;
}//-------- Fin du destructeur

//------------- Methodes protégées ---------------------------------------------------------
