#include <allegro5/allegro5.h>
#include <functional>
#include "Character.hpp"
#include "Object.hpp"
#include "UI.hpp"
#pragma once

class Game
{
public:
    Game();
    ~Game();
    void Run();
private:
    void Draw() const;
    void Move();
    std::function<void()> aiming;
    std::function<void()> moving;
    std::function<void()> ending;

    bool al_init_is_success;
    bool al_init_primitives_addon_is_success;
    bool al_install_keyboard_is_success;
    bool al_install_mouse_is_success;

    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_FONT* font;
    ALLEGRO_EVENT event;

    Map_1 map_1;

    Aim aim;
    Player_magenta player_magenta;
    Player_cyan player_cyan;
    
    End_dialog_box end_dialog_box;

    Player* active_player;
    Player* passive_player;
    std::function<void()>* what_to_do;
    
    Vector mouse_position;
    bool exit;
};