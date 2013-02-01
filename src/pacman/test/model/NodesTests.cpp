/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "NodesTests.h"
#include <pacman/model/PacmanNodes.h>
#include <pacman/model/GhostNodes.h>

using std::cout;
using std::endl;
using std::vector;

using namespace ::PACMAN::MODEL;
using namespace ::PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

void NodesTests::test_pacman_nodes() {
    // generated with PACMAN_NODES.print_code after manual checking the graph for correctness
    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(57);
    neighbour_ids.push_back(33);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(30, FPoint(67.200000000000002842, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(62);
    neighbour_ids.push_back(35);
    neighbour_ids.push_back(30);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(33, FPoint(124.79999999999999716, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(62);
    neighbour_ids.push_back(33);
    neighbour_ids.push_back(39);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(35, FPoint(187.19999999999998863, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(68);
    neighbour_ids.push_back(35);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(39, FPoint(268.80000000000001137, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(71);
    neighbour_ids.push_back(48);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(44, FPoint(403.19999999999998863, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(77);
    neighbour_ids.push_back(50);
    neighbour_ids.push_back(44);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(48, FPoint(484.80000000000001137, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(77);
    neighbour_ids.push_back(48);
    neighbour_ids.push_back(53);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(50, FPoint(547.20000000000004547, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(82);
    neighbour_ids.push_back(50);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(53, FPoint(604.79999999999995453, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(30);
    neighbour_ids.push_back(113);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(57, FPoint(36, 67.200000000000002842), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(35);
    neighbour_ids.push_back(33);
    neighbour_ids.push_back(118);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(62, FPoint(156, 67.200000000000002842), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(39);
    neighbour_ids.push_back(124);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(68, FPoint(300, 67.200000000000002842), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(44);
    neighbour_ids.push_back(127);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(71, FPoint(372, 67.200000000000002842), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(50);
    neighbour_ids.push_back(48);
    neighbour_ids.push_back(133);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(77, FPoint(516, 67.200000000000002842), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(53);
    neighbour_ids.push_back(138);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(82, FPoint(636, 67.200000000000002842), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(169);
    neighbour_ids.push_back(142);
    neighbour_ids.push_back(57);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(113, FPoint(36, 100.79999999999999716), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(174);
    neighbour_ids.push_back(147);
    neighbour_ids.push_back(145);
    neighbour_ids.push_back(62);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(118, FPoint(156, 100.79999999999999716), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(153);
    neighbour_ids.push_back(151);
    neighbour_ids.push_back(68);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(124, FPoint(300, 100.79999999999999716), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(156);
    neighbour_ids.push_back(154);
    neighbour_ids.push_back(71);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(127, FPoint(372, 100.79999999999999716), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(189);
    neighbour_ids.push_back(162);
    neighbour_ids.push_back(160);
    neighbour_ids.push_back(77);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(133, FPoint(516, 100.79999999999999716), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(194);
    neighbour_ids.push_back(165);
    neighbour_ids.push_back(82);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(138, FPoint(636, 100.79999999999999716), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(113);
    neighbour_ids.push_back(169);
    neighbour_ids.push_back(145);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(142, FPoint(67.200000000000002842, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(118);
    neighbour_ids.push_back(174);
    neighbour_ids.push_back(147);
    neighbour_ids.push_back(142);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(145, FPoint(124.79999999999999716, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(148);
    neighbour_ids.push_back(118);
    neighbour_ids.push_back(174);
    neighbour_ids.push_back(145);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(147, FPoint(187.19999999999998863, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(147);
    neighbour_ids.push_back(177);
    neighbour_ids.push_back(150);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(148, FPoint(196.80000000000001137, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(151);
    neighbour_ids.push_back(177);
    neighbour_ids.push_back(148);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(150, FPoint(259.19999999999998863, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(150);
    neighbour_ids.push_back(124);
    neighbour_ids.push_back(153);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(151, FPoint(268.80000000000001137, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(154);
    neighbour_ids.push_back(124);
    neighbour_ids.push_back(151);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(153, FPoint(331.19999999999998863, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(153);
    neighbour_ids.push_back(127);
    neighbour_ids.push_back(156);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(154, FPoint(340.80000000000001137, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(157);
    neighbour_ids.push_back(127);
    neighbour_ids.push_back(154);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(156, FPoint(403.19999999999998863, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(156);
    neighbour_ids.push_back(186);
    neighbour_ids.push_back(159);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(157, FPoint(412.80000000000001137, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(160);
    neighbour_ids.push_back(186);
    neighbour_ids.push_back(157);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(159, FPoint(475.19999999999998863, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(159);
    neighbour_ids.push_back(133);
    neighbour_ids.push_back(189);
    neighbour_ids.push_back(162);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(160, FPoint(484.80000000000001137, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(133);
    neighbour_ids.push_back(189);
    neighbour_ids.push_back(160);
    neighbour_ids.push_back(165);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(162, FPoint(547.20000000000004547, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(138);
    neighbour_ids.push_back(194);
    neighbour_ids.push_back(162);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(165, FPoint(604.79999999999995453, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(197);
    neighbour_ids.push_back(113);
    neighbour_ids.push_back(142);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(169, FPoint(36, 163.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(202);
    neighbour_ids.push_back(118);
    neighbour_ids.push_back(147);
    neighbour_ids.push_back(145);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(174, FPoint(156, 163.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(205);
    neighbour_ids.push_back(150);
    neighbour_ids.push_back(148);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(177, FPoint(228, 163.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(214);
    neighbour_ids.push_back(159);
    neighbour_ids.push_back(157);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(186, FPoint(444, 163.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(217);
    neighbour_ids.push_back(133);
    neighbour_ids.push_back(162);
    neighbour_ids.push_back(160);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(189, FPoint(516, 163.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(222);
    neighbour_ids.push_back(138);
    neighbour_ids.push_back(165);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(194, FPoint(636, 163.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(169);
    neighbour_ids.push_back(226);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(197, FPoint(36, 172.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(174);
    neighbour_ids.push_back(258);
    neighbour_ids.push_back(229);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(202, FPoint(156, 172.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(177);
    neighbour_ids.push_back(234);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(205, FPoint(228, 172.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(186);
    neighbour_ids.push_back(241);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(214, FPoint(444, 172.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(189);
    neighbour_ids.push_back(273);
    neighbour_ids.push_back(246);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(217, FPoint(516, 172.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(194);
    neighbour_ids.push_back(249);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(222, FPoint(636, 172.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(197);
    neighbour_ids.push_back(229);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(226, FPoint(67.200000000000002842, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(202);
    neighbour_ids.push_back(258);
    neighbour_ids.push_back(226);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(229, FPoint(124.79999999999999716, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(235);
    neighbour_ids.push_back(205);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(234, FPoint(259.19999999999998863, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(234);
    neighbour_ids.push_back(264);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(235, FPoint(268.80000000000001137, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(241);
    neighbour_ids.push_back(267);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(240, FPoint(403.19999999999998863, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(240);
    neighbour_ids.push_back(214);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(241, FPoint(412.80000000000001137, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(217);
    neighbour_ids.push_back(273);
    neighbour_ids.push_back(249);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(246, FPoint(547.20000000000004547, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(222);
    neighbour_ids.push_back(246);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(249, FPoint(604.79999999999995453, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(202);
    neighbour_ids.push_back(229);
    neighbour_ids.push_back(370);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(258, FPoint(156, 235.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(292);
    neighbour_ids.push_back(235);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(264, FPoint(300, 235.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(295);
    neighbour_ids.push_back(240);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(267, FPoint(372, 235.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(217);
    neighbour_ids.push_back(246);
    neighbour_ids.push_back(385);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(273, FPoint(516, 235.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(264);
    neighbour_ids.push_back(321);
    neighbour_ids.push_back(319);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(292, FPoint(300, 244.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(267);
    neighbour_ids.push_back(324);
    neighbour_ids.push_back(322);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(295, FPoint(372, 244.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(319);
    neighbour_ids.push_back(345);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(318, FPoint(259.19999999999998863, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(318);
    neighbour_ids.push_back(292);
    neighbour_ids.push_back(321);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(319, FPoint(268.80000000000001137, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(322);
    neighbour_ids.push_back(292);
    neighbour_ids.push_back(319);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(321, FPoint(331.19999999999998863, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(321);
    neighbour_ids.push_back(295);
    neighbour_ids.push_back(324);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(322, FPoint(340.80000000000001137, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(325);
    neighbour_ids.push_back(295);
    neighbour_ids.push_back(322);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(324, FPoint(403.19999999999998863, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(324);
    neighbour_ids.push_back(354);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(325, FPoint(412.80000000000001137, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(373);
    neighbour_ids.push_back(318);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(345, FPoint(228, 307.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(382);
    neighbour_ids.push_back(325);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(354, FPoint(444, 307.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(426);
    neighbour_ids.push_back(399);
    neighbour_ids.push_back(397);
    neighbour_ids.push_back(258);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(370, FPoint(156, 316.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(345);
    neighbour_ids.push_back(429);
    neighbour_ids.push_back(400);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(373, FPoint(228, 316.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(354);
    neighbour_ids.push_back(438);
    neighbour_ids.push_back(411);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(382, FPoint(444, 316.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(441);
    neighbour_ids.push_back(414);
    neighbour_ids.push_back(412);
    neighbour_ids.push_back(273);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(385, FPoint(516, 316.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(370);
    neighbour_ids.push_back(426);
    neighbour_ids.push_back(399);
    neighbour_ids.push_back(414);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(397, FPoint(124.79999999999999716, 348), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(400);
    neighbour_ids.push_back(370);
    neighbour_ids.push_back(426);
    neighbour_ids.push_back(397);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(399, FPoint(187.19999999999998863, 348), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(399);
    neighbour_ids.push_back(373);
    neighbour_ids.push_back(429);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(400, FPoint(196.80000000000001137, 348), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(412);
    neighbour_ids.push_back(382);
    neighbour_ids.push_back(438);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(411, FPoint(475.19999999999998863, 348), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(411);
    neighbour_ids.push_back(385);
    neighbour_ids.push_back(441);
    neighbour_ids.push_back(414);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(412, FPoint(484.80000000000001137, 348), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(385);
    neighbour_ids.push_back(441);
    neighbour_ids.push_back(412);
    neighbour_ids.push_back(397);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(414, FPoint(547.20000000000004547, 348), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(370);
    neighbour_ids.push_back(399);
    neighbour_ids.push_back(397);
    neighbour_ids.push_back(538);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(426, FPoint(156, 379.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(457);
    neighbour_ids.push_back(373);
    neighbour_ids.push_back(400);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(429, FPoint(228, 379.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(466);
    neighbour_ids.push_back(382);
    neighbour_ids.push_back(411);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(438, FPoint(444, 379.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(385);
    neighbour_ids.push_back(414);
    neighbour_ids.push_back(412);
    neighbour_ids.push_back(553);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(441, FPoint(516, 379.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(429);
    neighbour_ids.push_back(513);
    neighbour_ids.push_back(486);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(457, FPoint(228, 388.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(438);
    neighbour_ids.push_back(522);
    neighbour_ids.push_back(493);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(466, FPoint(444, 388.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(457);
    neighbour_ids.push_back(513);
    neighbour_ids.push_back(493);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(486, FPoint(259.19999999999998863, 420), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(466);
    neighbour_ids.push_back(522);
    neighbour_ids.push_back(486);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(493, FPoint(412.80000000000001137, 420), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(541);
    neighbour_ids.push_back(457);
    neighbour_ids.push_back(486);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(513, FPoint(228, 451.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(550);
    neighbour_ids.push_back(466);
    neighbour_ids.push_back(493);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(522, FPoint(444, 451.19999999999998863), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(594);
    neighbour_ids.push_back(567);
    neighbour_ids.push_back(565);
    neighbour_ids.push_back(426);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(538, FPoint(156, 460.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(513);
    neighbour_ids.push_back(570);
    neighbour_ids.push_back(568);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(541, FPoint(228, 460.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(522);
    neighbour_ids.push_back(579);
    neighbour_ids.push_back(577);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(550, FPoint(444, 460.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(609);
    neighbour_ids.push_back(582);
    neighbour_ids.push_back(580);
    neighbour_ids.push_back(441);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(553, FPoint(516, 460.80000000000001137), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(589);
    neighbour_ids.push_back(565);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(562, FPoint(67.200000000000002842, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(538);
    neighbour_ids.push_back(594);
    neighbour_ids.push_back(567);
    neighbour_ids.push_back(562);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(565, FPoint(124.79999999999999716, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(568);
    neighbour_ids.push_back(538);
    neighbour_ids.push_back(594);
    neighbour_ids.push_back(565);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(567, FPoint(187.19999999999998863, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(567);
    neighbour_ids.push_back(541);
    neighbour_ids.push_back(570);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(568, FPoint(196.80000000000001137, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(571);
    neighbour_ids.push_back(541);
    neighbour_ids.push_back(568);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(570, FPoint(259.19999999999998863, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(570);
    neighbour_ids.push_back(600);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(571, FPoint(268.80000000000001137, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(577);
    neighbour_ids.push_back(603);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(576, FPoint(403.19999999999998863, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(576);
    neighbour_ids.push_back(550);
    neighbour_ids.push_back(579);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(577, FPoint(412.80000000000001137, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(580);
    neighbour_ids.push_back(550);
    neighbour_ids.push_back(577);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(579, FPoint(475.19999999999998863, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(579);
    neighbour_ids.push_back(553);
    neighbour_ids.push_back(609);
    neighbour_ids.push_back(582);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(580, FPoint(484.80000000000001137, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(553);
    neighbour_ids.push_back(609);
    neighbour_ids.push_back(580);
    neighbour_ids.push_back(585);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(582, FPoint(547.20000000000004547, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(614);
    neighbour_ids.push_back(582);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(585, FPoint(604.79999999999995453, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(617);
    neighbour_ids.push_back(562);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(589, FPoint(36, 523.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(622);
    neighbour_ids.push_back(538);
    neighbour_ids.push_back(567);
    neighbour_ids.push_back(565);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(594, FPoint(156, 523.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(628);
    neighbour_ids.push_back(571);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(600, FPoint(300, 523.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(631);
    neighbour_ids.push_back(576);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(603, FPoint(372, 523.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(637);
    neighbour_ids.push_back(553);
    neighbour_ids.push_back(582);
    neighbour_ids.push_back(580);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(609, FPoint(516, 523.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(642);
    neighbour_ids.push_back(585);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(614, FPoint(636, 523.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(589);
    neighbour_ids.push_back(646);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(617, FPoint(36, 532.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(594);
    neighbour_ids.push_back(678);
    neighbour_ids.push_back(651);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(622, FPoint(156, 532.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(600);
    neighbour_ids.push_back(657);
    neighbour_ids.push_back(655);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(628, FPoint(300, 532.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(603);
    neighbour_ids.push_back(660);
    neighbour_ids.push_back(658);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(631, FPoint(372, 532.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(609);
    neighbour_ids.push_back(693);
    neighbour_ids.push_back(664);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(637, FPoint(516, 532.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(614);
    neighbour_ids.push_back(669);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(642, FPoint(636, 532.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(617);
    neighbour_ids.push_back(675);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(646, FPoint(60, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(652);
    neighbour_ids.push_back(622);
    neighbour_ids.push_back(678);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(651, FPoint(187.19999999999998863, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(651);
    neighbour_ids.push_back(681);
    neighbour_ids.push_back(654);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(652, FPoint(196.80000000000001137, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(655);
    neighbour_ids.push_back(681);
    neighbour_ids.push_back(652);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(654, FPoint(259.19999999999998863, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(654);
    neighbour_ids.push_back(628);
    neighbour_ids.push_back(657);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(655, FPoint(268.80000000000001137, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(658);
    neighbour_ids.push_back(628);
    neighbour_ids.push_back(655);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(657, FPoint(331.19999999999998863, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(657);
    neighbour_ids.push_back(631);
    neighbour_ids.push_back(660);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(658, FPoint(340.80000000000001137, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(661);
    neighbour_ids.push_back(631);
    neighbour_ids.push_back(658);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(660, FPoint(403.19999999999998863, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(660);
    neighbour_ids.push_back(690);
    neighbour_ids.push_back(663);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(661, FPoint(412.80000000000001137, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(664);
    neighbour_ids.push_back(690);
    neighbour_ids.push_back(661);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(663, FPoint(475.19999999999998863, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(663);
    neighbour_ids.push_back(637);
    neighbour_ids.push_back(693);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(664, FPoint(484.80000000000001137, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(696);
    neighbour_ids.push_back(642);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(669, FPoint(612, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(703);
    neighbour_ids.push_back(646);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(675, FPoint(84, 595.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(706);
    neighbour_ids.push_back(622);
    neighbour_ids.push_back(651);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(678, FPoint(156, 595.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(709);
    neighbour_ids.push_back(654);
    neighbour_ids.push_back(652);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(681, FPoint(228, 595.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(718);
    neighbour_ids.push_back(663);
    neighbour_ids.push_back(661);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(690, FPoint(444, 595.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(721);
    neighbour_ids.push_back(637);
    neighbour_ids.push_back(664);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(693, FPoint(516, 595.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(724);
    neighbour_ids.push_back(669);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(696, FPoint(588, 595.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(675);
    neighbour_ids.push_back(732);
    neighbour_ids.push_back(730);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(703, FPoint(84, 604.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(678);
    neighbour_ids.push_back(733);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(706, FPoint(156, 604.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(681);
    neighbour_ids.push_back(738);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(709, FPoint(228, 604.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(690);
    neighbour_ids.push_back(745);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(718, FPoint(444, 604.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(693);
    neighbour_ids.push_back(750);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(721, FPoint(516, 604.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(696);
    neighbour_ids.push_back(753);
    neighbour_ids.push_back(751);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(724, FPoint(588, 604.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(757);
    neighbour_ids.push_back(703);
    neighbour_ids.push_back(732);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(730, FPoint(60, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(733);
    neighbour_ids.push_back(703);
    neighbour_ids.push_back(730);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(732, FPoint(115.20000000000000284, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(732);
    neighbour_ids.push_back(706);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(733, FPoint(124.79999999999999716, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(739);
    neighbour_ids.push_back(709);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(738, FPoint(259.19999999999998863, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(738);
    neighbour_ids.push_back(768);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(739, FPoint(268.80000000000001137, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(745);
    neighbour_ids.push_back(771);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(744, FPoint(403.19999999999998863, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(744);
    neighbour_ids.push_back(718);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(745, FPoint(412.80000000000001137, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(751);
    neighbour_ids.push_back(721);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(750, FPoint(547.20000000000004547, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(750);
    neighbour_ids.push_back(724);
    neighbour_ids.push_back(753);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(751, FPoint(556.79999999999995453, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(724);
    neighbour_ids.push_back(751);
    neighbour_ids.push_back(782);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(753, FPoint(612, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(785);
    neighbour_ids.push_back(730);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(757, FPoint(36, 667.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(796);
    neighbour_ids.push_back(739);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(768, FPoint(300, 667.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(799);
    neighbour_ids.push_back(744);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(771, FPoint(372, 667.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(810);
    neighbour_ids.push_back(753);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(782, FPoint(636, 667.20000000000004547), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(757);
    neighbour_ids.push_back(814);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(785, FPoint(36, 676.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(768);
    neighbour_ids.push_back(825);
    neighbour_ids.push_back(823);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(796, FPoint(300, 676.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(771);
    neighbour_ids.push_back(828);
    neighbour_ids.push_back(826);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(799, FPoint(372, 676.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(782);
    neighbour_ids.push_back(837);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(810, FPoint(636, 676.79999999999995453), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(785);
    neighbour_ids.push_back(823);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(814, FPoint(67.200000000000002842, 708), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(796);
    neighbour_ids.push_back(825);
    neighbour_ids.push_back(814);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(823, FPoint(268.80000000000001137, 708), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(826);
    neighbour_ids.push_back(796);
    neighbour_ids.push_back(823);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(825, FPoint(331.19999999999998863, 708), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(825);
    neighbour_ids.push_back(799);
    neighbour_ids.push_back(828);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(826, FPoint(340.80000000000001137, 708), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(799);
    neighbour_ids.push_back(826);
    neighbour_ids.push_back(837);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(828, FPoint(403.19999999999998863, 708), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(810);
    neighbour_ids.push_back(828);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(837, FPoint(604.79999999999995453, 708), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(658);
    ASSERT(PACMAN_NODES.has_node_equivalent_to(-1, FPoint(336, 564), neighbour_ids));
    }
}

void NodesTests::test_ghost_nodes() {
    // generated with GHOST_NODES.print_code after manual checking the graph for correctness
    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(282);
    neighbour_ids.push_back(68);
    ASSERT(GHOST_NODES.has_node_equivalent_to(58, FPoint(36, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(292);
    neighbour_ids.push_back(58);
    neighbour_ids.push_back(80);
    ASSERT(GHOST_NODES.has_node_equivalent_to(68, FPoint(156, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(304);
    neighbour_ids.push_back(68);
    ASSERT(GHOST_NODES.has_node_equivalent_to(80, FPoint(300, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(310);
    neighbour_ids.push_back(98);
    ASSERT(GHOST_NODES.has_node_equivalent_to(86, FPoint(372, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(322);
    neighbour_ids.push_back(86);
    neighbour_ids.push_back(108);
    ASSERT(GHOST_NODES.has_node_equivalent_to(98, FPoint(516, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(332);
    neighbour_ids.push_back(98);
    ASSERT(GHOST_NODES.has_node_equivalent_to(108, FPoint(636, 36), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(58);
    neighbour_ids.push_back(450);
    neighbour_ids.push_back(292);
    ASSERT(GHOST_NODES.has_node_equivalent_to(282, FPoint(36, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(68);
    neighbour_ids.push_back(460);
    neighbour_ids.push_back(282);
    neighbour_ids.push_back(298);
    ASSERT(GHOST_NODES.has_node_equivalent_to(292, FPoint(156, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(466);
    neighbour_ids.push_back(292);
    neighbour_ids.push_back(304);
    ASSERT(GHOST_NODES.has_node_equivalent_to(298, FPoint(228, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(80);
    neighbour_ids.push_back(298);
    neighbour_ids.push_back(310);
    ASSERT(GHOST_NODES.has_node_equivalent_to(304, FPoint(300, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(86);
    neighbour_ids.push_back(304);
    neighbour_ids.push_back(316);
    ASSERT(GHOST_NODES.has_node_equivalent_to(310, FPoint(372, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(484);
    neighbour_ids.push_back(310);
    neighbour_ids.push_back(322);
    ASSERT(GHOST_NODES.has_node_equivalent_to(316, FPoint(444, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(98);
    neighbour_ids.push_back(490);
    neighbour_ids.push_back(316);
    neighbour_ids.push_back(332);
    ASSERT(GHOST_NODES.has_node_equivalent_to(322, FPoint(516, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(108);
    neighbour_ids.push_back(500);
    neighbour_ids.push_back(322);
    ASSERT(GHOST_NODES.has_node_equivalent_to(332, FPoint(636, 132), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(282);
    neighbour_ids.push_back(460);
    ASSERT(GHOST_NODES.has_node_equivalent_to(450, FPoint(36, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(292);
    neighbour_ids.push_back(796);
    neighbour_ids.push_back(450);
    ASSERT(GHOST_NODES.has_node_equivalent_to(460, FPoint(156, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(298);
    neighbour_ids.push_back(472);
    ASSERT(GHOST_NODES.has_node_equivalent_to(466, FPoint(228, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(640);
    neighbour_ids.push_back(466);
    ASSERT(GHOST_NODES.has_node_equivalent_to(472, FPoint(300, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(646);
    neighbour_ids.push_back(484);
    ASSERT(GHOST_NODES.has_node_equivalent_to(478, FPoint(372, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(316);
    neighbour_ids.push_back(478);
    ASSERT(GHOST_NODES.has_node_equivalent_to(484, FPoint(444, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(322);
    neighbour_ids.push_back(826);
    neighbour_ids.push_back(500);
    ASSERT(GHOST_NODES.has_node_equivalent_to(490, FPoint(516, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(332);
    neighbour_ids.push_back(490);
    ASSERT(GHOST_NODES.has_node_equivalent_to(500, FPoint(636, 204), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(802);
    neighbour_ids.push_back(640);
    ASSERT(GHOST_NODES.has_node_equivalent_to(634, FPoint(228, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(472);
    neighbour_ids.push_back(634);
    neighbour_ids.push_back(646);
    ASSERT(GHOST_NODES.has_node_equivalent_to(640, FPoint(300, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(478);
    neighbour_ids.push_back(640);
    neighbour_ids.push_back(652);
    ASSERT(GHOST_NODES.has_node_equivalent_to(646, FPoint(372, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(820);
    neighbour_ids.push_back(646);
    ASSERT(GHOST_NODES.has_node_equivalent_to(652, FPoint(444, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(460);
    neighbour_ids.push_back(1132);
    neighbour_ids.push_back(802);
    neighbour_ids.push_back(826);
    ASSERT(GHOST_NODES.has_node_equivalent_to(796, FPoint(156, 348), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(634);
    neighbour_ids.push_back(970);
    neighbour_ids.push_back(796);
    ASSERT(GHOST_NODES.has_node_equivalent_to(802, FPoint(228, 348), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(652);
    neighbour_ids.push_back(988);
    neighbour_ids.push_back(826);
    ASSERT(GHOST_NODES.has_node_equivalent_to(820, FPoint(444, 348), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(490);
    neighbour_ids.push_back(1162);
    neighbour_ids.push_back(820);
    neighbour_ids.push_back(796);
    ASSERT(GHOST_NODES.has_node_equivalent_to(826, FPoint(516, 348), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(802);
    neighbour_ids.push_back(1138);
    neighbour_ids.push_back(988);
    ASSERT(GHOST_NODES.has_node_equivalent_to(970, FPoint(228, 420), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(820);
    neighbour_ids.push_back(1156);
    neighbour_ids.push_back(970);
    ASSERT(GHOST_NODES.has_node_equivalent_to(988, FPoint(444, 420), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1290);
    neighbour_ids.push_back(1132);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1122, FPoint(36, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(796);
    neighbour_ids.push_back(1300);
    neighbour_ids.push_back(1122);
    neighbour_ids.push_back(1138);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1132, FPoint(156, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(970);
    neighbour_ids.push_back(1132);
    neighbour_ids.push_back(1144);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1138, FPoint(228, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1312);
    neighbour_ids.push_back(1138);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1144, FPoint(300, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1318);
    neighbour_ids.push_back(1156);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1150, FPoint(372, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(988);
    neighbour_ids.push_back(1150);
    neighbour_ids.push_back(1162);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1156, FPoint(444, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(826);
    neighbour_ids.push_back(1330);
    neighbour_ids.push_back(1156);
    neighbour_ids.push_back(1172);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1162, FPoint(516, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1340);
    neighbour_ids.push_back(1162);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1172, FPoint(636, 492), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1122);
    neighbour_ids.push_back(1294);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1290, FPoint(36, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1462);
    neighbour_ids.push_back(1290);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1294, FPoint(84, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1132);
    neighbour_ids.push_back(1468);
    neighbour_ids.push_back(1306);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1300, FPoint(156, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1474);
    neighbour_ids.push_back(1300);
    neighbour_ids.push_back(1312);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1306, FPoint(228, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1144);
    neighbour_ids.push_back(1306);
    neighbour_ids.push_back(1318);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1312, FPoint(300, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1150);
    neighbour_ids.push_back(1312);
    neighbour_ids.push_back(1324);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1318, FPoint(372, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1492);
    neighbour_ids.push_back(1318);
    neighbour_ids.push_back(1330);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1324, FPoint(444, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1162);
    neighbour_ids.push_back(1498);
    neighbour_ids.push_back(1324);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1330, FPoint(516, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1504);
    neighbour_ids.push_back(1340);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1336, FPoint(588, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1172);
    neighbour_ids.push_back(1336);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1340, FPoint(636, 564), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1626);
    neighbour_ids.push_back(1462);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1458, FPoint(36, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1294);
    neighbour_ids.push_back(1458);
    neighbour_ids.push_back(1468);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1462, FPoint(84, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1300);
    neighbour_ids.push_back(1462);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1468, FPoint(156, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1306);
    neighbour_ids.push_back(1480);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1474, FPoint(228, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1648);
    neighbour_ids.push_back(1474);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1480, FPoint(300, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1654);
    neighbour_ids.push_back(1492);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1486, FPoint(372, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1324);
    neighbour_ids.push_back(1486);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1492, FPoint(444, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1330);
    neighbour_ids.push_back(1504);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1498, FPoint(516, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1336);
    neighbour_ids.push_back(1498);
    neighbour_ids.push_back(1508);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1504, FPoint(588, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1676);
    neighbour_ids.push_back(1504);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1508, FPoint(636, 636), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1458);
    neighbour_ids.push_back(1648);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1626, FPoint(36, 708), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1480);
    neighbour_ids.push_back(1626);
    neighbour_ids.push_back(1654);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1648, FPoint(300, 708), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1486);
    neighbour_ids.push_back(1648);
    neighbour_ids.push_back(1676);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1654, FPoint(372, 708), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1508);
    neighbour_ids.push_back(1654);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1676, FPoint(636, 708), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(640);
    neighbour_ids.push_back(646);
    ASSERT(GHOST_NODES.has_node_equivalent_to(1, FPoint(336, 276), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(1);
    ASSERT(GHOST_NODES.has_node_equivalent_to(3, FPoint(336, 336), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(3);
    ASSERT(GHOST_NODES.has_node_equivalent_to(5, FPoint(288, 336), neighbour_ids));
    }

    {
    vector<int> neighbour_ids;
    neighbour_ids.push_back(3);
    ASSERT(GHOST_NODES.has_node_equivalent_to(7, FPoint(384, 336), neighbour_ids));
    }
}

}}}
