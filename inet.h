#pragma once

#include <Windows.h>
#include <Wininet.h>
#include <random>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>


namespace inet
{
    std::string read_url(std::string url);
    DWORD post_request(std::string url, std::string request, DWORD* code, std::string* response);
    bool webstatus_check(const std::string& szAddress, DWORD* pdwWebStat);
}