#pragma once

#include <string>
#include <cryptopp/hex.h>
#include <cryptopp/md5.h>
#include <cryptopp/osrng.h>

using namespace std;

string salt();
string md5(string &data);
