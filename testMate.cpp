#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "funkcijos.hpp"

bool Islaike (double Vidurkis)
{
    if (Vidurkis >= 5)
        return true;
    else return false;
}
bool Skolininkas (double Vidurkis)
{
    if (Vidurkis < 5)
        return true;
    else return false;
}

double Galutinis_Balas (double Vidurkis, int Egzamino)
{
    return 0.4 * Vidurkis + 0.6 * Egzamino;
}

TEST_CASE("Galutinis_Balas") {

	REQUIRE(Galutinis_Balas(5.1, 7) == 6.24);
	REQUIRE(Galutinis_Balas(4.1, 10) == 7.64);
	REQUIRE(Galutinis_Balas(9.2, 4) == 6.08);
	REQUIRE(Galutinis_Balas(8.5, 9) == 8.8);
	REQUIRE(Galutinis_Balas(8.5, 3) == 5.2);

}

TEST_CASE("Islaike") {

	REQUIRE(Islaike(8) == true);
	REQUIRE(Islaike(2) == false);
	REQUIRE(Islaike(10) == true);
	REQUIRE(Islaike(7) == true);
	REQUIRE(Islaike(4) == false);

}
TEST_CASE("Skolininkas") {

	REQUIRE(Skolininkas(9) == false);
    REQUIRE(Skolininkas(5) == false);
	REQUIRE(Skolininkas(10) == false);
	REQUIRE(Skolininkas(1) == true);
	REQUIRE(Skolininkas(3) == true);

}