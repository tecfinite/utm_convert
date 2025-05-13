# UTM to Lat/Lon Converter (C++ High Precision)

A simple C++ utility to convert UTM (Universal Transverse Mercator) coordinates to WGS84 geographic coordinates (latitude and longitude) with long double precision. Designed for accuracy-critical geospatial applications.

## 🔧 Features

- ✅ High-precision output using `long double`
- ✅ Supports UTM zones (default: Zone 37)
- ✅ Cross-platform: macOS (Apple Silicon) & Linux
- ✅ CLI-based for integration with Laravel, Bash, or APIs

## 🧪 Example

**Input:**
Easting: 632862.6012
Northing: 2364981.2945

**Output:**
## 🛠️ Build Instructions

### On Linux or macOS

```bash
g++ -std=c++17 -o utm_convert main.cpp
./utm_convert