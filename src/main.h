#include "pebble.h"

#pragma once

static const int line_points_left_x[] = {40, 88, 40, 40, 88, 40};

static const int line_points_left_y[] = {24, 44, 64, 104, 124, 144};

static const int line_points_right_x[] = {104, 56, 104, 104, 56, 104};

static const int line_points_right_y[] = {24, 44, 64, 104, 124, 144};

static const GPathInfo LEFT_POINTS = {
	6,
	(GPoint []) {
		{0, 0},
		{35, 0},
		{35, 18},
		{25, 18},
		{25, 8},
		{0, 8}
	}
};

static const GPathInfo RIGHT_POINTS = {
	6,
	(GPoint []) {
		{35, 0},
		{0, 0},
		{0, 18},
		{10, 18},
		{10, 8},
		{35, 8}
	}
};
