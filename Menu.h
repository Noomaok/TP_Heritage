//-------------- Interface de la classe <Menu> (fichier Menu.h) ---------------------
#if ! defined ( MENU_H )
#define MENU_H

//-------------- Interfaces utilis�es -----------------------------
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "TableauTrajet.h"
#include "Catalogue.h"
#include <string>

//-------------- Constantes ---------------------------------------
#define DIR "save/"
//-------------- Types --------------------------------------------

//-----------------------------------------------------------------
//               Rôle de la classe <Menu>:
// Gere le fonctionnement du menu pour l'ajout de trajet, l'affichage
// du catalogue ainsi que la recherche de trajet.
//-----------------------------------------------------------------
typedef enum CritereType { NONE, ON_TYPE, ON_DEPART, ON_ARRIVEE, ON_BOTH, ON_INTER} CritereType;

class Menu
{
public:
	//----- Methodes publiques -----

	void run();
	// Mode d'emploi :
	// Execute le debut du menu

	TrajetCompose* creerTrajetCompose(const Catalogue & catalogue);
	// Mode d'emploi :
	// Lance la procedure de creation d'un trajet compose. Renvoie un pointeur sur le nouveau trajet.
	// Le parametre formel catalogue est utilisé pour l'ajout d'un trajet existant dans le trajet compose.

	TrajetSimple* creerTrajetSimple();
	// Mode d'emploi :
	// Lance la procedure de creation d'un trajet simple. Renvoie un pointeur sur le nouveau trajet.

	bool checkExists(string file) const;
	// Mode d'emploi :
	// Verifie l'existence du fichier de nom file dans le dossier de sauvegarde. Renvoie true si le fichier existe.

	void Sauvegarde(CritereType type, ...) const;
	// Mode d'emploi :
	// Lance la procédure de sauvegarde ayant pour critère type.

	void Chargement(CritereType type, ...);
	// Mode d'emploi :
	// Lance la procédure de chargement ayant pour critère type.

	//---- Surchage d'op�rateurs ----
	//--- Constructeurs - Desctructeurs ---

	Menu();
	// Mode d'emploi :
	// Creer le menu et lance son deroulement

	~Menu();
	// Mode d'emploi :
	// Detruit le menu et libere la memoire

protected:
	//----- Methodes prot�g�es -----
	//----- Attributs prot�g�s -----

	enum SelectionMenu { M_MENU, CT_MENU, RP_MENU, TC_MENU, DELETE_TRAJET, SAVE, LOAD};
	SelectionMenu currentMenu;
	Catalogue catal;
};
//------------ Autres d�finitions d�pendantes de %class% ----------

#endif // ! defined ( Menu_H )
