#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

#define PI 3.141592653589793238462643383279L

const long double a = 6378137.0L;
const long double f = 1.0L / 298.257223563L;
const long double k0 = 0.9996L;

void utmToLatLon(long double easting, long double northing, int zone, bool isNorthernHemisphere, long double& lat, long double& lon) {
    long double e = std::sqrt(f * (2 - f));
    long double e1sq = e * e / (1 - e * e);

    long double x = easting - 500000.0L;
    long double y = northing;
    if (!isNorthernHemisphere) {
        y -= 10000000.0L;
    }

    long double M = y / k0;
    long double mu = M / (a * (1 - e * e / 4 - 3 * std::pow(e, 4) / 64 - 5 * std::pow(e, 6) / 256));

    long double e1 = (1 - std::sqrt(1 - e * e)) / (1 + std::sqrt(1 - e * e));

    long double phi1Rad = mu
        + (3 * e1 / 2 - 27 * std::pow(e1, 3) / 32) * std::sin(2 * mu)
        + (21 * std::pow(e1, 2) / 16 - 55 * std::pow(e1, 4) / 32) * std::sin(4 * mu)
        + (151 * std::pow(e1, 3) / 96) * std::sin(6 * mu);

    long double N1 = a / std::sqrt(1 - std::pow(e * std::sin(phi1Rad), 2));
    long double T1 = std::pow(std::tan(phi1Rad), 2);
    long double C1 = e1sq * std::pow(std::cos(phi1Rad), 2);
    long double R1 = a * (1 - e * e) / std::pow(1 - std::pow(e * std::sin(phi1Rad), 2), 1.5);
    long double D = x / (N1 * k0);

    long double latRad = phi1Rad - (N1 * std::tan(phi1Rad) / R1) *
        (D * D / 2 - (5 + 3 * T1 + 10 * C1 - 4 * C1 * C1 - 9 * e1sq) * std::pow(D, 4) / 24
        + (61 + 90 * T1 + 298 * C1 + 45 * T1 * T1 - 252 * e1sq - 3 * C1 * C1) * std::pow(D, 6) / 720);
    lat = latRad * 180.0L / PI;

    long double lonOrigin = (zone - 1) * 6.0L - 180.0L + 3.0L;
    long double lonRad = (D - (1 + 2 * T1 + C1) * std::pow(D, 3) / 6
        + (5 - 2 * C1 + 28 * T1 - 3 * std::pow(C1, 2) + 8 * e1sq + 24 * std::pow(T1, 2)) * std::pow(D, 5) / 120)
        / std::cos(phi1Rad);
    lon = lonOrigin + lonRad * 180.0L / PI;
}

int main() {
    long double x, y;
    int zone;
    std::string hemisphere;

    std::cout << "Enter Easting (X): ";
    std::cin >> x;

    std::cout << "Enter Northing (Y): ";
    std::cin >> y;

    std::cout << "Enter UTM Zone (1–60): ";
    std::cin >> zone;

    std::cout << "Enter Hemisphere (N/S): ";
    std::cin >> hemisphere;

    if (zone < 1 || zone > 60 || (hemisphere != "N" && hemisphere != "S" && hemisphere != "n" && hemisphere != "s")) {
        std::cerr << "Invalid input. Zone must be 1–60. Hemisphere must be 'N' or 'S'.\n";
        return 1;
    }

    bool isNorthernHemisphere = (hemisphere == "N" || hemisphere == "n");

    long double lat, lon;
    utmToLatLon(x, y, zone, isNorthernHemisphere, lat, lon);

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "Latitude: " << lat << ", Longitude: " << lon << std::endl;

    return 0;
}