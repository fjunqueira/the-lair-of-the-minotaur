//
// Created by fabio on 12/12/15.
//

#include <GL/glu.h>
#include <GL/freeglut.h>
#include "pathfinding/pathfinding_graph.h"
#include "tile_map.h"
#include "asset_manager.h"
#include "gameobject/game_object_drawer.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "player.h"
#include "opengl_extensions/pixel_2_world.h"
#include "opengl_extensions/text.h"


AssetManager* asset_manager;
pathfinding::PathfindingGraph* pathfinding_graph;
TileMap* tile_map;
gameobject::SimpleGameObject* entrance;
Player* player;

std::vector<Enemy*> enemies;
bool game_over = false;
int points = 0;

void post_redisplay()
{
    glutPostRedisplay();
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void mouse(int button, int state, int x, int y)
#pragma clang diagnostic pop
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !game_over)
    {
        auto point = opengl_extensions::Pixel2World(x, y);

        auto index = tile_map->GetTileIndexByPosition(point);

        if (!tile_map->IndexInBounds(index))
            return;

        auto node1 = player->current_node();

        auto node2 = pathfinding_graph->GetNodeByIndex(index);

        auto path = pathfinding_graph->FindPath(*node1, *node2);

        player->ChangePath(path);

        glutPostRedisplay();
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void keyboard(unsigned char key, int x, int y)
#pragma clang diagnostic pop
{
    if (key == '\r' && game_over)
    {
        game_over = false;
        points = 0;

        std::for_each(enemies.begin(), enemies.end(), [&](Enemy* enemy)
        { delete enemy; });

        enemies.clear();

        player->MoveToCenter();
    }
}

void DisplayGameOver()
{
    opengl_extensions::DisplayText(0, 250, 1, 0, 0, "GAMEOVER");

    auto points_text = "SCORE: " + std::to_string(points);
    opengl_extensions::DisplayText(0, 200, 1, 0, 0, points_text);

    opengl_extensions::DisplayText(0, 150, 1, 0, 0, "PRESS ENTER TO RESTART");
}

int last_elapsed_time = 0;
int total_elapsed_time = 0;

void Display()
{
    int elapsed_time = glutGet(GLUT_ELAPSED_TIME);
    int delta_time = elapsed_time - last_elapsed_time;

    last_elapsed_time = elapsed_time;

    auto enemies_count = enemies.size();

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](Enemy* enemy)
    {
        auto enemy_is_dead = enemy->dead();

        if (enemy_is_dead) delete enemy;

        return enemy_is_dead;
    }), enemies.end());

    points += enemies_count - enemies.size();

    glClear(GL_COLOR_BUFFER_BIT);
    {
        gameobject::DrawGameObjects((gameobject::GameObject**) tile_map->GetTiles(), tile_map->size());
        gameobject::DrawGameObject(*entrance);

        std::for_each(enemies.begin(), enemies.end(), [&](Enemy* enemy)
        {
            gameobject::DrawGameObject(*enemy);

            if (!game_over)
            {
                enemy->Update(delta_time);
                game_over = enemy->GetCurrentNode()->index == math::Vector2<int>(16, 13);
            }
        });

        gameobject::DrawGameObject(*player);

        if (!game_over)
            player->Update(delta_time);
        else
            DisplayGameOver();
    }
    glFlush();

    total_elapsed_time += delta_time;

    if (total_elapsed_time > 1000 && !game_over)
    {
        total_elapsed_time = 0;
        enemy_manager::AddEnemy(*tile_map, *asset_manager, *pathfinding_graph, enemies);
    }
}

void init_game_data()
{
    asset_manager = new AssetManager();

    pathfinding_graph = new pathfinding::PathfindingGraph(math::Vector2<int>(30, 30));

    tile_map = new TileMap(math::Vector2<float>(20, 20), math::Vector2<int>(30, 30),
                           asset_manager->get_asset("cave_floor")->textureid);

    entrance = new gameobject::SimpleGameObject(tile_map->GetTilePositionByIndex(math::Vector2<int>(16, 13)),
                                                math::Vector2<float>(100, 100),
                                                asset_manager->get_asset("entrance")->textureid);

    auto minotaur_spritesheet = asset_manager->get_asset("minotaur");

    player = new Player(tile_map,
                        pathfinding_graph,
                        &enemies,
                        animation::Running(minotaur_spritesheet, 192, directions::SOUTH),
                        animation::Idle(minotaur_spritesheet, 192, directions::SOUTH),
                        animation::Attacking(minotaur_spritesheet, 192, directions::SOUTH),
                        math::Vector2<float>(40, 80),
                        minotaur_spritesheet->textureid);

    player->MoveToCenter();
}

void cleanup_game_data()
{
    delete pathfinding_graph;
    delete tile_map;
    delete asset_manager;
    delete entrance;
    delete player;

    std::for_each(enemies.begin(), enemies.end(), [&](Enemy* enemy)
    { delete enemy; });
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 590, -300, 300, -1, 1);
    glViewport(0, 0, 1000, 600);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("The Lair of the Minotaur");
    glutDisplayFunc(Display);
    glutIdleFunc(post_redisplay);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    init_game_data();

    glutMainLoop();

    cleanup_game_data();
    return 0;   /* ISO C requires main to return int. */
}