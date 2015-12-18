//
// Created by fabio on 12/12/15.
//

#include <GL/glu.h>
#include <GL/freeglut.h>
#include "pathfinding/pathfinding_graph.h"
#include "tile_map.h"
#include "asset_manager.h"
#include "animation/attacking.h"
#include "animation/dying.h"
#include "animation/idle.h"
#include "gameobject/game_object_drawer.h"


AssetManager* asset_manager;
pathfinding::PathfindingGraph* pathfinding_graph;
TileMap* tile_map;

gameobject::SimpleGameObject* entrance;

void post_redisplay()
{
    glutPostRedisplay();
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void mouse(int button, int state, int x, int y)
#pragma clang diagnostic pop
{

}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void keyboard(unsigned char key, int x, int y)
#pragma clang diagnostic pop
{

}

void display()
{
    glClear(0);
    {
        gameobject::DrawGameObjects((gameobject::GameObject**) tile_map->GetTiles(), tile_map->size());
        gameobject::DrawGameObject(*entrance);
    }
    glFlush();
}

void init_game_data()
{
    asset_manager = new AssetManager();

    pathfinding_graph = new pathfinding::PathfindingGraph(math::Vector2<int>(30, 30));

    pathfinding_graph->FindPath(*pathfinding_graph->GetNodeByIndex(math::Vector2<int>(0, 0)),
                                *pathfinding_graph->GetNodeByIndex(math::Vector2<int>(10, 20)));

    pathfinding_graph->FindPath(*pathfinding_graph->GetNodeByIndex(math::Vector2<int>(10, 0)),
                                *pathfinding_graph->GetNodeByIndex(math::Vector2<int>(15, 15)));

    pathfinding_graph->FindPath(*pathfinding_graph->GetNodeByIndex(math::Vector2<int>(25, 12)),
                                *pathfinding_graph->GetNodeByIndex(math::Vector2<int>(13, 27)));

    tile_map = new TileMap(math::Vector2<float>(20, 20), math::Vector2<int>(30, 30),
                           asset_manager->get_asset("cave_floor")->textureid);

    entrance = new gameobject::SimpleGameObject(tile_map->GetTilePositionByIndex(math::Vector2<int>(16, 13)),
                                                math::Vector2<float>(100, 100),
                                                asset_manager->get_asset("entrance")->textureid);

    animation::Attacking attacking(asset_manager->get_asset("minotaur"), 192, 1);

    attacking.MoveToNextFrame(2, 4);
    attacking.MoveToNextFrame(2, 4);
    attacking.MoveToNextFrame(2, 4);
    attacking.MoveToNextFrame(2, 4);

    attacking.GetCurrentFrameCoords();

    animation::Dying dying(asset_manager->get_asset("minotaur"), 192, 1);

    dying.MoveToNextFrame(2, 4);
    dying.MoveToNextFrame(2, 4);
    dying.MoveToNextFrame(2, 4);
    dying.MoveToNextFrame(2, 4);

    dying.GetCurrentFrameCoords();

    animation::Idle idle(asset_manager->get_asset("minotaur"), 192, 1);

    idle.MoveToNextFrame(2, 4);
    idle.MoveToNextFrame(2, 4);
    idle.MoveToNextFrame(2, 4);
    idle.MoveToNextFrame(2, 4);

    idle.GetCurrentFrameCoords();

    animation::Attacking running(asset_manager->get_asset("minotaur"), 192, 1);

    running.MoveToNextFrame(2, 4);
    running.MoveToNextFrame(2, 4);
    running.MoveToNextFrame(2, 4);
    running.MoveToNextFrame(2, 4);

    running.GetCurrentFrameCoords();

    gameobject::DrawGameObjects((gameobject::GameObject**) tile_map->GetTiles(), tile_map->size());
}

void cleanup_game_data()
{
    delete pathfinding_graph;
    delete tile_map;
    delete asset_manager;
    delete entrance;
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
    glutDisplayFunc(display);
    glutIdleFunc(post_redisplay);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    init_game_data();

    glutMainLoop();

    cleanup_game_data();
    return 0;   /* ISO C requires main to return int. */
}