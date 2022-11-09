#include "CollisionSystem.hpp"

void CollisionSystem::update(entt::registry &registry)
{
    // registry.view<Collision, PlayerController, Position>().each(
    //     [&registry](auto entity1, auto &collision1, auto &position1)
    //     {
    //         registry.view<Collision>().each(
    //             [](auto entity2, auto &collision2)
    //             {
    //                 if (entity1 != entity2)
    //                 // handleCollision(collision1, collision2);
    //             });
    //     });
}

// void handleCollision(Collision e1, Collision e2, Position p1)
// {
//     auto e1Box = e1->getHitBox();
//     auto e2Box = e2->getHitBox();
//     if (e2Box.intersects(e1Box))
//     {
//         auto eTop = e2Box.top;
//         auto eBottom = e2Box.top + e2Box.height;
//         auto eLeft = e2Box.left;
//         auto eRight = e2Box.left + e2Box.width;
//         auto pTop = e1Box.top;
//         auto pBottom = e1Box.top + e1Box.height;
//         auto pLeft = e1Box.left;
//         auto pRight = e1Box.left + e1Box.width;

//         auto BTOverlap = eBottom - pTop;
//         auto TBOverlap = pBottom - eTop;
//         auto RLOverlap = eRight - pLeft;
//         auto LROverlap = pRight - eLeft;

//         auto currentPos = e1->getPosition();
//         float newX = currentPos.x;
//         float newY = currentPos.y;

//         // TODO: The direction of the collision is defined by which Overlap is
//         // the minimum overlap greater than 0.

//         if (BTOverlap > 0 && BTOverlap < RLOverlap && BTOverlap < LROverlap && BTOverlap < TBOverlap) // Coming mainly up, even if some diagonal movement is involved
//         {
//             // std::cout << "Collision moving up\n";
//             newY = e2Box.top + e2Box.height - 0.7f * constants::player_height /**Diff between hitbox top and bounding box top*/
//                    - 12 /**Diff between top of sprite bounds and top of player bounds*/;

//             e1->setPosition({currentPos.x, newY});
//         }
//         else if (TBOverlap > 0 && TBOverlap < RLOverlap && TBOverlap < LROverlap && TBOverlap < BTOverlap) // Coming mainly down
//         {
//             // std::cout << "Collision moving down\n";
//             newY = e2Box.top - 32;
//             e1->setPosition({currentPos.x, newY});
//         }
//         else if (RLOverlap > 0 && RLOverlap < TBOverlap && RLOverlap < LROverlap && RLOverlap < BTOverlap) // Coming mainly left
//         {
//             // std::cout << "Collision moving left\n";
//             newX = e2Box.left + e2Box.width - 16 * 0.1f;
//             e1->setPosition({newX, currentPos.y});
//         }
//         else if (LROverlap > 0 && LROverlap < TBOverlap && LROverlap < RLOverlap && LROverlap < BTOverlap) // Coming mainly right
//         {
//             // std::cout << "Collision moving right\n";
//             newX = e2Box.left - e1Box.width - /**Diff between player x position and left hitbox */ 16 * 0.1f;
//             e1->setPosition({newX, currentPos.y});
//         }
//     }
// }