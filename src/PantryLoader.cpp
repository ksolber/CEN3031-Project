#include "PantryLoader.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

namespace
{
    std::string readEntireFile(const std::string& filename)
    {
        std::ifstream inFile(filename);
        if (!inFile.is_open())
        {
            return "";
        }

        std::ostringstream buffer;
        buffer << inFile.rdbuf();
        return buffer.str();
    }

    std::string extractStringValue(const std::string& block, const std::string& key)
    {
        std::regex pattern("\"" + key + "\"\\s*:\\s*(None|\"([^\"]*)\")");
        std::smatch match;

        if (std::regex_search(block, match, pattern))
        {
            if (match[1] == "None")
            {
                return "";
            }

            if (match.size() >= 3)
            {
                return match[2].str();
            }
        }

        return "";
    }

    double extractDoubleValue(const std::string& block, const std::string& key)
    {
        std::regex pattern("\"" + key + "\"\\s*:\\s*(-?\\d+(?:\\.\\d+)?)");
        std::smatch match;

        if (std::regex_search(block, match, pattern))
        {
            return std::stod(match[1].str());
        }

        return 0.0;
    }

    bool extractBoolValue(const std::string& block, const std::string& key)
    {
        std::regex pattern("\"" + key + "\"\\s*:\\s*(true|false)");
        std::smatch match;

        if (std::regex_search(block, match, pattern))
        {
            return match[1].str() == "true";
        }

        return false;
    }

    std::string extractDescription(const std::string& block)
    {
        std::regex pattern("\"description\"\\s*:\\s*\\(([\\s\\S]*?)\\)\\s*,");
        std::smatch match;

        if (!std::regex_search(block, match, pattern))
        {
            return "";
        }

        std::string descriptionBlock = match[1].str();
        std::regex stringPattern("\"([^\"]*)\"");
        std::sregex_iterator begin(descriptionBlock.begin(), descriptionBlock.end(), stringPattern);
        std::sregex_iterator end;

        std::string description;
        for (std::sregex_iterator it = begin; it != end; ++it)
        {
            description += (*it)[1].str();
        }

        return description;
    }

    std::vector<std::string> splitIntoObjectBlocks(const std::string& fileContents)
    {
        std::vector<std::string> blocks;
        bool insideObject = false;
        int braceDepth = 0;
        std::string current;

        for (char ch : fileContents)
        {
            if (ch == '{')
            {
                if (!insideObject)
                {
                    insideObject = true;
                    current.clear();
                }
                braceDepth++;
            }

            if (insideObject)
            {
                current += ch;
            }

            if (ch == '}')
            {
                braceDepth--;

                if (insideObject && braceDepth == 0)
                {
                    blocks.push_back(current);
                    current.clear();
                    insideObject = false;
                }
            }
        }

        return blocks;
    }

    Pantry parsePantryBlock(const std::string& block)
    {
        Pantry pantry;

        pantry.name = extractStringValue(block, "name");
        pantry.address = extractStringValue(block, "address");
        pantry.latitude = extractDoubleValue(block, "latitude");
        pantry.longitude = extractDoubleValue(block, "longitude");
        pantry.description = extractDescription(block);
        pantry.hours = extractStringValue(block, "hours");
        pantry.eligibility = extractStringValue(block, "eligibility");
        pantry.phone = extractStringValue(block, "phone");
        pantry.email = extractStringValue(block, "email");
        pantry.website = extractStringValue(block, "website");
        pantry.notes = pantry.description;

        pantry.halal = extractBoolValue(block, "halal");
        pantry.kosher = extractBoolValue(block, "kosher");
        pantry.vegan = extractBoolValue(block, "vegan");
        pantry.vegetarian = extractBoolValue(block, "vegetarian");
        pantry.carnivore = extractBoolValue(block, "carnivore");
        pantry.handicapAccessible = extractBoolValue(block, "handicapAccessible");

        return pantry;
    }
}

std::vector<Pantry> loadPantriesFromLocationFile(const std::string& filename)
{
    std::vector<Pantry> pantries;
    std::string fileContents = readEntireFile(filename);

    if (fileContents.empty())
    {
        std::cerr << "Error: Could not open or read file: " << filename << '\n';
        return pantries;
    }

    std::vector<std::string> blocks = splitIntoObjectBlocks(fileContents);

    for (const std::string& block : blocks)
    {
        Pantry pantry = parsePantryBlock(block);

        if (!pantry.name.empty())
        {
            pantries.push_back(pantry);
        }
    }

    return pantries;
}
