// Name: Dominic McElroy
// Date: 9/14/2024
// Project - Program Assignment One || Decimal, Binary , Hexidecimal converter.

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <limits>
#include <cctype>

//  Binary
bool isValidBinary(const std::string& binary) {
    for (char ch : binary) {
        if (ch != '0' && ch != '1') return false;
    }
    return !binary.empty();
}

// Hexidecimal
bool isValidHex(const std::string& hex) {
    for (char ch : hex) {
        if (!((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))) {
            return false;
        }
    }
    return !hex.empty();
}

// Deci to Bin
void decimalToBinary(int decimal) {
    if (decimal < 0) {
        std::cerr << "Error: Negative decimal values are not supported.\n";
        return;
    }

    std::bitset<64> binary(decimal); // 64 bits for safety
    std::string binaryStr = binary.to_string();

    // Remove leading zeros
    size_t pos = binaryStr.find('1');
    if (pos != std::string::npos) {
        binaryStr = binaryStr.substr(pos);
    } else {
        binaryStr = "0";
    }

    std::cout << "Binary: " << binaryStr << std::endl;
}

// Deci to Hex
void decimalToHex(int decimal) {
    if (decimal < 0) {
        std::cerr << "Error: Negative decimal values are not supported.\n";
        return;
    }

    std::stringstream ss;
    ss << std::hex << std::uppercase << decimal;
    std::string hex = ss.str();

    std::cout << "Hexadecimal: " << hex << std::endl;
}

// Bin to Deci
void binaryToDecimal(const std::string& binary) {
    if (!isValidBinary(binary)) {
        std::cerr << "Error: Invalid binary number.\n";
        return;
    }

    try {
        int decimal = std::stoi(binary, nullptr, 2);
        std::cout << "Decimal: " << decimal << std::endl;
    } catch (const std::invalid_argument&) {
        std::cerr << "Error: Invalid binary input.\n";
    } catch (const std::out_of_range&) {
        std::cerr << "Error: Binary value out of range.\n";
    }
}

// Bin to Hex
void binaryToHex(const std::string& binary) {
    if (!isValidBinary(binary)) {
        std::cerr << "Error: Invalid binary number.\n";
        return;
    }

    try {
        int decimal = std::stoi(binary, nullptr, 2);
        std::stringstream ss;
        ss << std::hex << std::uppercase << decimal;
        std::string hex = ss.str();

        std::cout << "Hexadecimal: " << hex << std::endl;
    } catch (const std::invalid_argument&) {
        std::cerr << "Error: Invalid binary input.\n";
    } catch (const std::out_of_range&) {
        std::cerr << "Error: Binary value out of range.\n";
    }
}

// Hex to Deci
void hexToDecimal(const std::string& hex) {
    if (!isValidHex(hex)) {
        std::cerr << "Error: Invalid hexadecimal number.\n";
        return;
    }

    try {
        unsigned long long decimal;
        std::stringstream ss;
        ss << std::hex << hex;
        ss >> decimal;

        if (decimal > std::numeric_limits<int>::max()) {
            std::cerr << "Error: Decimal value overflow.\n";
        } else {
            std::cout << "Decimal: " << static_cast<int>(decimal) << std::endl;
        }
    } catch (const std::invalid_argument&) {
        std::cerr << "Error: Invalid hexadecimal input.\n";
    } catch (const std::out_of_range&) {
        std::cerr << "Error: Hexadecimal value out of range.\n";
    }
}

// Hex to Bin
void hexToBinary(const std::string& hex) {
    if (!isValidHex(hex)) {
        std::cerr << "Error: Invalid hexadecimal number.\n";
        return;
    }

    try {
        unsigned long long decimal;
        std::stringstream ss;
        ss << std::hex << hex;
        ss >> decimal;

        std::bitset<64> binary(decimal);
        std::string binaryStr = binary.to_string();

        // Remove leading zeros
        size_t pos = binaryStr.find('1');
        if (pos != std::string::npos) {
            binaryStr = binaryStr.substr(pos);
        } else {
            binaryStr = "0";
        }

        std::cout << "Binary: " << binaryStr << std::endl;
    } catch (const std::invalid_argument&) {
        std::cerr << "Error: Invalid hexadecimal input.\n";
    } catch (const std::out_of_range&) {
        std::cerr << "Error: Hexadecimal value out of range.\n";
    }
}

// Triggers and Conversions
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " -[d|b|h] [number]\n";
        std::cerr << "Options:\n";
        std::cerr << "-d [decimal]     Convert decimal to binary and hexadecimal\n";
        std::cerr << "-b [binary]      Convert binary to decimal and hexadecimal\n";
        std::cerr << "-h [hexadecimal] Convert hexadecimal to decimal and binary\n";
        return 1;
    }

    std::string flag = argv[1];
    std::string number = argv[2];

    if (flag == "-d") {
        try {
            int decimal = std::stoi(number);
            decimalToBinary(decimal);
            decimalToHex(decimal);
        } catch (const std::invalid_argument&) {
            std::cerr << "Error: Invalid decimal number.\n";
            return 1;
        } catch (const std::out_of_range&) {
            std::cerr << "Error: Decimal value out of range.\n";
            return 1;
        }
    } else if (flag == "-b") {
        binaryToDecimal(number);
        binaryToHex(number);
    } else if (flag == "-h") {
        hexToDecimal(number);
        hexToBinary(number);
    } else {
        std::cerr << "Error: Invalid flag '" << flag << "'.\n";
        return 1;
    }

    return 0;
}