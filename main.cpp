#include "Game.hpp"
#include "Game_run.hpp"
#include "Game_update_aim.hpp"
#include "Game_update_pawn.hpp"

int main()
{
    Game game = Game();

    game.run();
    
    return 0;
}