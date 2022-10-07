#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 1000
#define MAX_PLAYERS 1000

struct team {
  char country[MAX_STRING];     // pais
  char **players;               // todos os jogadores da equipa
  int nplayers;                 // nr de jogadores
  int ndraws;
};

struct match {
    struct team *teams[2];       // referencia para as equipas do jogo
    int ngoals[2];               // nr de golos por equipa
    char *players[MAX_PLAYERS];   // para cada golo, nome do jogador
};

// adiciona um jogador à equipa
void add_player(struct team *_team, char *_player)
{
    _team->nplayers++;
    _team->players = (char **) realloc (_team->players, sizeof(char *)*_team->nplayers);
    if ( _team->players == NULL ) {
        printf("Memory realloc error\n");
        exit(EXIT_FAILURE);
    }
    _team->players[_team->nplayers-1] = (char *)malloc (sizeof(char)*(strlen(_player)+1));
    if ( _team->players[_team->nplayers-1] == NULL ) {
        printf("Memory realloc error\n");
        exit(EXIT_FAILURE);
    }
    strcpy(_team->players[_team->nplayers-1], _player);
}

void printTeams(struct team *_team, int _nteams)
{
    int j = 0, i = 0;

    for ( i = 0 ; i < _nteams ; i++ ) {
        printf("%s:", _team[i].country);
        for ( j = 0 ; j < _team[i].nplayers ; j++ ) {
            printf(" %s ", _team[i].players[j]);
        }
        printf("\n");
    }
}

// cria um match
struct match create_match(struct team *_team1, struct team *_team2, int _goal1, int _goal2, char *_players[]){
    int i = 0;
    struct match *new_match;
    new_match = (struct match *) calloc (1, sizeof(struct match));
    if ( new_match == NULL )
    {
        printf("Memory realloc error\n");
        exit(EXIT_FAILURE);
    }
    new_match->teams[0] = _team1;  // use ref, 
    new_match->teams[1] = _team2;
    new_match->ngoals[0] = _goal1;
    new_match->ngoals[1] = _goal2;

    for ( i = 0 ; i < (_goal1+_goal2) ; i++ )
    {
        new_match->players[i] = (char *)malloc(sizeof(char)*(strlen(_players[i])+1));
        strcpy(new_match->players[i], _players[i]);
    }
    return *new_match;  // loses memory: to be improved
}

void printMatches(struct match _matches[], int _nmatches)
{
    int j = 0, i = 0;

    for ( i = 0 ; i < _nmatches ; i++ ) {
        printf("%s-%s \t ", _matches[i].teams[0]->country,  _matches[i].teams[1]->country);
        printf("%d-%d \t ", _matches[i].ngoals[0],  _matches[i].ngoals[1]);

        for ( j = 0 ; j < (_matches[i].ngoals[0] + _matches[i].ngoals[1]) ; j++ ) {
            printf("%s - ", _matches[i].players[j]);
        }
        printf("\n");
    }
}

// No jogo com mais golos do mundial imprima o nome das jogadores que marcaram. 
void goals(struct match _matches[], int _nmatches){

    int i=0, idxmin = 0, maxgoals = -1;

    for ( i = 0; i < _nmatches; i++ ) {
        if ( (_matches[i].ngoals[0]+_matches[i].ngoals[1]) > maxgoals ){
            maxgoals = _matches[i].ngoals[0]+_matches[i].ngoals[1];
            idxmin = i;
        }
    }
    printf("%s-%s\n", _matches[idxmin].teams[0]->country, _matches[idxmin].teams[1]->country);
    for ( i = 0; i < maxgoals; i++ )
        printf(" %s", _matches[idxmin].players[i]); 
    printf("\n");
}

// encontrar a equipa que empatou mais jogos, se for conveniente pode mudar as 
// estruturas acima definidas.
void team_more_draws(struct match _matches[], int _nmatches){
    int i = 0, j = 0, idx_match = 0, idx_team = 0;
    int maxdraws = -1;

    for ( i = 0; i < _nmatches; i++ ) 
    {
        if ( _matches[i].ngoals[0] == _matches[i].ngoals[1] ) 
        {
            _matches[i].teams[0]->ndraws++;
            _matches[i].teams[1]->ndraws++;
        }
    }

    for ( i = 0; i < _nmatches; i++ ) {
        for ( j = 0; j < 2; j++ ) {
            if ( _matches[i].teams[j]->ndraws > maxdraws){
                maxdraws = _matches[i].teams[j]->ndraws;
                idx_match = i;
                idx_team = j;
            }
        }
    }
    printf("A %s empatou mais jogos (%d)\n", _matches[idx_match].teams[idx_team]->country, 
        _matches[idx_match].teams[idx_team]->ndraws);
}

int main (void)
{
    struct match matches[10];
    struct team tm[] = {{"Portugal"},{"Uruguai"},{"Germany"},{"South Korea"},{"Brasil"}, {"France"}};
    char *player_goals[] = {"P1","P2","P3", "P4", "P5"};  // just to fill

    add_player(&tm[0], "Ronaldo");
    add_player(&tm[0], "William");
    add_player(&tm[0], "Moutinho");
    add_player(&tm[0], "Quaresma");
    // and so on... for other teams !
    printTeams(tm, 1);

    matches[0] = create_match(&tm[0], &tm[1], 2, 1, player_goals); // POR-URU
    matches[1] = create_match(&tm[0], &tm[5], 5, 0, player_goals); // POR-FRA
    matches[2] = create_match(&tm[0], &tm[2], 2, 2, player_goals); // POR-GER
    matches[3] = create_match(&tm[3], &tm[2], 1, 1, player_goals); // SK-GER

    printMatches(matches, 4);
    goals(matches, 4);
    team_more_draws(matches, 4);

    // and so on... for other matches !

    return EXIT_SUCCESS;
}
