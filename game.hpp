#include <allegro5/allegro5.h>
#include "Character.hpp"
#include "Object.hpp"
#include "map.hpp"
#include "ui.hpp"
#include <functional>
#pragma once

class Game
{
public:
    Game();
    ~Game();
    void Run();
private:
    void Draw() const;
    void Update_aim_center(float x, float y);
    void Update_aim_direction(float x, float y);
    void Play_again_or_quit(bool& done);

    bool exit;
    Vector mouse_position;
    std::function<void()>* what_to_do;

    std::function<void()> aiming;
    std::function<void()> shooting;

    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_FONT* font;

    Fence fence;
    Clipper clipper;
    Aim aim;
    Player_magenta player_magenta;
    Player_cyan player_cyan;

    Player* active_player;
    Player* passive_player;

    End_dialog_box* pointer_to_end_dialog_box;
    // std::vector<Line> trail;

    Map_1 map_1;
};