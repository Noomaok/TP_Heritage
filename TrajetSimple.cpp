//------------- Realisation de la classe <TrajetSimple> ( fichier TrajetSimple.cpp ) -----------------

//------------- Include système ------------------------------------------------------------
#include <iostream>
#include <cstring>

using namespace std;

//------------- Include personnel ----------------------------------------------------------
#include "TrajetSimple.h"

int TrajetSimple::compteurTs = 0;
//------------- Constantes -----------------------------------------------------------------


//------------- Methodes publiques ---------------------------------------------------------

void TrajetSimple::Affichage() const
{
	cout << "TS" << TrajetSimple::numTrajet << " = de "  << villeDepart << " à " << villeArrivee << " en " << moyenTransport;
}//------- Fin de Affichage

Trajet* TrajetSimple::Clone() const
{
	return new TrajetSimple(*this);
}//------- Fin de Clone

//------------- Surcharge d'opérateurs -----------------------------------------------------


//------------- Constructeurs - Desctructeur -----------------------------------------------
TrajetSimple::TrajetSimple(const char *villeDep,const char *villeArr,const char *moyenTp)
: Trajet(villeDep, villeArr), moyenTransport(new char[100])
{
#ifdef MAP
	cout << "Appel du constructeur de <Trajet Simple>" << endl;
#endif
	strcpy(moyenTransport,moyenTp);
	numTrajet = ++TrajetSimple::compteurTs;
}//-------- Fin du constructeur

TrajetSimple::TrajetSimple(TrajetSimple const& trajetSimpleACopier)
: Trajet(trajetSimpleACopier.villeDepart,trajetSimpleACopier.villeArrivee), moyenTransport(new char[100])
{
#ifdef MAP
	cout << "Appel du constructeur de Copie de <Trajet Simple>" << endl;
#endif
	strcpy(moyenTransport,trajetSimpleACopier.moyenTransport);
	numTrajet = ++TrajetSimple::compteurTs;
}//--------- Fin du constructeur de copie

TrajetSimple::~TrajetSimple()
{
#ifdef MAP
	cout << "Appel du destructeur de <Trajet Simple>" << endl;
#endif
	delete[] moyenTransport;
}//--------- Fin du destructeur

//------------- Methodes protégées ---------------------------------------------------------
