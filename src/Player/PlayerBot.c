/**
 * \file PlayerBot.c
 * \brief Joueur de type inteligence artificiel
 * \author LE GLEAU Yoann
 * \date 21/02/2022
 * \version 1
 */

/* ---------- Sub Declaration ---------- */

/**
 * \brief Fonction permettent à l'intelligence artificielle de jouer son tour
 * \param p joueur cible
 * \param board pllateu cible
 * \return Vrais si le joueur a joué
 */
bool playSmart(Player *p, Board * board);


//---------- Constructor ----------

Player * playerBotFactory( int id){
    //appel le constructeur supérieure
    Player * player = playerFactory(id);
    player->play = &playSmart;
    return player;
}

//---------- utilities ----------

bool playSmart(Player *p, Board * board) {
    const int minint = -2147483648;
    int idPlayer = p->idPlayer, maxh = minint, cardPlayIndex, maxLocation, h = minint, pownLocation;
    enum Card * maxCard;
    if(isWin(board,p->idPlayer))
        idPlayer = getIdTeamMember(board,idPlayer);
    Linkedlist * pownsLocations = getPlayerPawnsLocation(board, idPlayer);
    Board *boardCopy;
    bool played = false;
    printf("\tnbPown:%i nbCard:%i\n",length(pownsLocations),length(p->cards));

    for (int i = length(pownsLocations) ; i >= 0 ; i--) {
        if (get(pownsLocations, i) != NULL)
            pownLocation = *((int*) get(pownsLocations, i));
        else
            pownLocation = -1;
        if(i == 0)
            pownLocation = -1;
        for (int j = 0; j < length(p->cards); j++) {
            boardCopy = boardClone(board);
            //gestion des cartes composé
            if (isComposed(get(p->cards, j))) {
                Linkedlist *compose = getCardCompose(get(p->cards, j));
                int compMaxh = minint,compMaxLocation;
                bool compplayed = false;
                enum Card * compmaxCard = NULL;
                for (int k = 0; k < length(compose); k++){
                    boardCopy = boardClone(board);
                    compplayed = playCard(idPlayer, boardCopy, get(compose, k), pownLocation);
                    if (compplayed) {
                        h = heuristic(boardCopy, idPlayer);
                        //TODO ferifier si onOUt ne casse pas le choi des autres cartes de la main (7.8.9)(les cartes normal)
                        printf("\t\th:%i location:%i carte:%s (%s)\n", h, pownLocation, cardToString((enum Card*)get(p->cards, j)), cardToString(get(compose, k)));
                        if (h > compMaxh) {
                            compMaxh = h;
                            compMaxLocation = pownLocation;
                            compmaxCard = get(compose, k);
                            compplayed = false;
                        }
                    }
                }
                printf("\th:%i location:%i carte:%s (%s)\n",compMaxh, pownLocation, cardToString((enum Card*)get(p->cards, j)), cardToString(compmaxCard));
                if (compMaxh > maxh) {
                    maxh = compMaxh;
                    maxLocation = compMaxLocation;
                    cardPlayIndex = j;
                    maxCard = compmaxCard;
                    played = false;
                }
            } else{
                played = playCard(idPlayer, boardCopy, get(p->cards, j), pownLocation);
                if (played) {
                    h = heuristic(boardCopy, idPlayer);
                    printf("\th:%i location:%i carte:", h, pownLocation);

                    drawCard(get(p->cards, j));
                    if (h > maxh) {
                        maxh = h;
                        maxLocation = pownLocation;
                        maxCard = get(p->cards, j);
                        cardPlayIndex = j;
                        played = false;
                    }
                }
            }
        }
    }
    if (h == minint && !isEmpty(p->cards)){
        printf("player %i a jeter ",p->idPlayer);
        drawCard(getFirst(p->cards));
        pollFirst(p->cards);
        played = false;
    } else {
        playCard(idPlayer, board, maxCard, maxLocation);
        printf("jouer h:%i location:%i carte:",maxh,maxLocation);
        drawCard(get(p->cards, cardPlayIndex));
        removeElem(p->cards, cardPlayIndex);
        played = true;
    }
    return played;
}