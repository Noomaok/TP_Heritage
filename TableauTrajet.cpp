//------------- Realisation de la classe <TableauTrajet> ( fichier TableauTrajet.cpp ) -----------------

//------------- Include système ------------------------------------------------------------
#include <iostream>

using namespace std;

//------------- Include personnel ----------------------------------------------------------
#include "TableauTrajet.h"

//------------- Constantes -----------------------------------------------------------------

//------------- Methodes publiques ---------------------------------------------------------

void TableauTrajet::Add(Trajet* trajetAjout)
{
	if(nbElement == size)
	{
		Trajet** extendedListeTrajet = new Trajet*[size+10];
		for(int i=0;i<nbElement;i++)
		{
			extendedListeTrajet[i] = listeTrajet[i];
		}
		Trajet** oldList = listeTrajet;
		listeTrajet = extendedListeTrajet;
		delete[] oldList;
	}
	listeTrajet[nbElement] = trajetAjout;
	nbElement++;
}//-------- Fin de Add

bool TableauTrajet::DejaAjoute(Trajet const * ptrTrajet) const
{
	for (int i = 0; i < nbElement; i++)
	{
		if (ptrTrajet == listeTrajet[i])
		{
			return true;
		}
	}
	return false;
}//-------- Fin de DejaAJoute


void TableauTrajet::DeleteElement(int indice)
{
	if (indice >= 0 && indice < nbElement)
	{
		delete listeTrajet[indice];
		for (int i = indice; i < nbElement - 1; i++)
		{
			listeTrajet[i] = listeTrajet[i + 1];
		}
		nbElement--;
	}
	else
	{
		cerr << "Erreur : indice non valide" << endl;
	}

}//--------- Fin de DeleteElement

int TableauTrajet::GetNbElement() const
{
	return nbElement;
}//-------- Fin de GetNbElement

//------------- Surcharge d'opérateurs -----------------------------------------------------

std::ostream& operator<<(std::ostream& output, const TableauTrajet& tabTrajet) 
{
	output << "Tableau : " << "{ ";
	if (tabTrajet.nbElement > 0)
	{
		for (int i = 0; i < tabTrajet.nbElement - 1; i++)
		{
			output << *tabTrajet[i] << "; " << std::endl;
		}
		output << *tabTrajet[tabTrajet.nbElement - 1];
	}
	output << " }";
	return output;
}//-------- Fin de la surchage de <<

Trajet* & TableauTrajet::operator[](int indice)
{
	return listeTrajet[indice];
}//-------- Fin de la surcharge de []

Trajet* & TableauTrajet::operator[](int indice) const
{
	return listeTrajet[indice];
}//-------- Fin de la surcharge de [] const

//------------- Constructeurs - Desctructeur -----------------------------------------------

TableauTrajet::TableauTrajet(Trajet** listeTrajetIni, int nbElementIni) 
: listeTrajet(listeTrajetIni), nbElement(nbElementIni)
{
#ifdef MAP
	cout << "Appel du constructeur de <TableauTrajet>" << endl;
#endif

	if (nbElement == 0) {
		size = 10;
	}
}//-------- Fin du constructeur

TableauTrajet::TableauTrajet(TableauTrajet const& tableauTrajetACopier)
: nbElement(tableauTrajetACopier.nbElement)
{
#ifdef MAP
	cout << "Appel du constructeur de copie de <TableauTrajet>" << endl;
#endif
	listeTrajet = new Trajet*[nbElement];
	for (int i = 0; i < nbElement; i++)
	{
		listeTrajet[i] = tableauTrajetACopier.listeTrajet[i]->Clone();
	}
}//-------- Fin du constructeur de copie

TableauTrajet::~TableauTrajet()
{
#ifdef MAP
	cout << "Appel du destructeur de <TableauTrajet>" << endl;
#endif

	for (int i=0;i<nbElement;i++)
	{
		delete listeTrajet[i];
	}
	delete[] listeTrajet;
}//-------- Fin du destructeur

//------------- Methodes protégées ---------------------------------------------------------
