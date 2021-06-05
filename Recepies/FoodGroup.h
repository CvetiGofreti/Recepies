#pragma once
#include <string>
enum class FoodGrup {
	vegetables = 1,
	fruits = 2,
	cereals = 4,
	meat = 8,
	seafood = 16,
	dairy = 32,
	eggs = 64
};

static std::string groups[7] = {
	"vegetables",
	"fruits",
	"cereals",
	"meat",
	"seafood",
	"dairy",
	"eggs"
};