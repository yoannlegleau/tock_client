/**
 * \file board.h
 * \brief Gestion du plateau de jeu et des pions
 * \author LE GLEAU Yoann
 * \date 10/03/2022
 * \version 1
 */
#ifndef TOCK_CLIENT_BOARD_H
#define TOCK_CLIENT_BOARD_H


/* ---------- Includes ---------- */

#include <SDL.h>
#include "linkedlist.h"
#include "card.h"


/* ---------- Structure ---------- */

/**
 * \brief Structure représentent le plateau
 */
typedef struct Board Board;
struct Board {
    /**
        * \brief Se tableux represente toutes les cases du plateu
        * \details la longeur varie selon le nombre de joueur car chaque jouer posed 18 plus 4 donc pour 4j 88 et 132 pour 6.
        * Les int represantes les ID de chaques jouers
        * \image html assets/img/Tock.io-BoardArray.jpg
    */
    int * board;

    /** \brief Nombre de joueurs sur le plateau (4 ou 6 ou 8) */
    int nbPlayer;
};


/* ---------- Constructor ---------- */

/**
 * \brief Constructeur de Board
 * \param nbPlayer Nombre de joueurs autour du plateau (4 ou 6 ou 8)
 * \return Board nouveau plateau
 */
Board * boardFactory(int nbPlayer);

/**
 * \brief Duplique un plateau
 * \param board plateau source
 * \return Board copie
 */
Board * boardClone(Board * board);

/**
 * \brief Remet a 0 tout le plateau
 * \param board cible
 */
void initBoard(Board * board);

/**
 * \brief libere toutes les variables du plateau
 */
void destroyBoard(Board ** board);


/* ---------- Getters ---------- */

/**
 * \brief Retourne le nombre de jouer autour du plateau
 * \param board context
 * \return int
 */
int getNbPlayer(Board * board);

/**
 * \brief Retourne la longueur du plateau en comptent les maisons des joueurs
 * \param board context
 * \return int
 */
int getLen(Board * board);

/**
 * \brief Retourne la longueur du plateau sans comptent les maisons des joueurs
 * \param board context
 * \return int
 */
int getBoardLen(Board * board);

/**
 * \brief Retourn la liste des coordonnés (int) des pions d'un joueur
 * \param board context
 * \param playerId id du joueur
 * \return Linkedlist of int*
 */
Linkedlist * getPlayerPawnsLocation(Board * board, int playerId );

/**
 * \brief Retourne les coordonnées de la case de sortie des pions d'un joueur
 * \param pId Identifient du joueur
 * \return int coordonnée
 */
int getStart(int pId);

/**
 * \brief Retourne les coordonnées de la case qui permet au pion de ranter des pions d'un joueur
 * \param pId Identifient du joueur
 * \return int coordonnée
 */
int getHomeEntry(int pId);

/**
 * \brief Retourne les coordonnées de premiere case de la maison d'un joueur
 * \param pId Identifient du joueur
 * \return int coordonnée
 */
int getHomeStart(Board * board, int pId);

/**
 * \brief Retourne la position d'une coordoner dans la la maison
 * \param pId Identifient du joueur
 * \return int [1-4] position, -1 si la localisation n'est pas dans une maison
 */
int getInHomePosition(Board * board, int location);

/**
 * \brief Retourne la distance qu'il rest à parcourir a un pion pour rentrer à la maison
 * \param board context
 * \param location position
 * \param pId Identifient du joueur
 * \return
 */
int getStepToHome(Board * board, int location, int pId);

/**
 * \brief Retourne l'identifient du coéquipier
 * \param board context
 * \param idPlayer Identifient du joueur
 * \return int identifient du coéquipier
 */
int getIdTeamMember(Board * board,int idPlayer);


/* ---------- Tests ---------- */

/**
 * \brief Verifier que la position est bien sur le plateau les maisons ne sont pas incluse
 * \param board context
 * \param location position
 * \return Vrais si la position est sur le plateau
 */
bool isOnBoard(Board * board, int location);

/**
 * \brief Verifier si il y a des pion sur le chemin
 * \param board context
 * \param location coordonnée de depart
 * \param step distance
 * \return Vrais s'il y a un pion ou plus
 */
bool pawnOnPath(Board * board, int location, int step);

/**
 * \brief Verifier si le joueur a gagner (4 pion dans la maison). Ne prend pas en compte la réussite de l'équipier
 * \param board context
 * \param pId Identifient du joueur
 * \return vrais si gagner
 */
bool isWin(Board * board, int pId);


/* ---------- Utilities ---------- */

/**
 * \brief Fais avancer un pion sur le plateau
 * \param board context
 * \param location Position du pion à faire avancer
 * \param step Distance à parcourir
 * \return true si le pion a bien pue avencer
 */
bool forward(Board * board, int location, int step);

/**
* \brief Fais reculer un pion sur le plateau
* \param board Context
* \param location Position du pion à faire avancer
* \param step Distance à parcourir
* \return true si le pion a bien pue reculer
*/
bool backward(Board * board, int location, int step);

/**
 * \brief Fonction de déplacement basic
 * \param board context
 * \param from départ
 * \param to destination
 */
void move(Board * board, int from, int to);

/**
 * \brief Fais sortir un pion a un joueur (ajouter un pion)
 * \param board context
 * \param pId Identifient du joueur
 * \return Vrais si le pion a bien pue aitre sorti
 */
bool outPawn(Board * board, int pId);

/**
 * \brief Calcule une estimation de la position. l'estimation est representative de l'envencement et des chance de victoire d'un joueur dans la partie a un instant t
 * \param board context
 * \param IdPlayer Idantifient du jour de reference
 * \return Int estimation
 */
int heuristic(Board * board,int IdPlayer);


/* ---------- Displays ---------- */

/**
 * \brief Afficher le plateau ses pions et les reserve de pion
 * \param board context
 */
void drawBoard(Board * board);

/**
 * \brief met en evidence la case selectioner
 * \param location Position selectinée
 */
void highlightLocation(int location);

#endif //TOCK_CLIENT_BOARD_H
