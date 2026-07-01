#ifndef ARCHIVE_SYSTEM_H
#define ARCHIVE_SYSTEM_H
#include <iostream>
#include <fstream>
#include <string>
#include "Huffman.h"
using namespace std;
class ArchiveSystem
{
private:
    Huffman huffman;
public:
    bool compressLogs(string inputFileName, string outputFileName)
    {
        ifstream inputFile(inputFileName.c_str());
        if (!inputFile)
        {
            cout << "Log file not found: " << inputFileName << endl;
            return false;
        }
        string text = "";
        string line;

        while (getline(inputFile, line))
        {
            text += line;
            text += '\n';
        }
        inputFile.close();
        if (text == "")
        {
            cout << "Log file is empty. Nothing to compress." << endl;
            return false;
        }
        huffman.clear();
        huffman.buildFromText(text);
        string encoded = huffman.encodeText(text);

        ofstream outputFile(outputFileName.c_str());
        if (!outputFile)
        {
            cout << "Unable to create compressed file." << endl;
            return false;
        }
        for (int i = 0; i < 256; i++)
        {
            outputFile << huffman.getFrequency(i) << " ";
        }

        outputFile << endl;
        outputFile << encoded << endl;
        outputFile.close();
        cout << "Logs compressed successfully " << endl;
        cout << "Original characters: " << text.length() << endl;
        cout << "Compressed bit characters: " << encoded.length() << endl;
        return true;
    }
    bool decompressLogs(string inputFileName, string outputFileName)
    {
        ifstream inputFile(inputFileName.c_str());
        if (!inputFile)
        {
            cout << "Compressed file not found: " << inputFileName << endl;
            return false;
        }
        int frequencies[256];
        for (int i = 0; i < 256; i++)
        {
            if (!(inputFile >> frequencies[i]))
            {
                cout << "Compressed file is damaged." << endl;
                inputFile.close();
                return false;
            }
        }

        string encoded;
        inputFile >> encoded;
        inputFile.close();
        huffman.clear();
        if (huffman.buildFromFrequencies(frequencies) == false)
        {
            cout << "Could not rebuild Huffman tree." << endl;
            return false;
        }
        string decoded = huffman.decodeBits(encoded);

        if (decoded == "")
        {
            cout << "Could not decode compressed file." << endl;
            return false;
        }
        ofstream outputFile(outputFileName.c_str());
        if (!outputFile)
        {
            cout << "Unable to create restored log file." << endl;
            return false;
        }

        outputFile << decoded;
        outputFile.close();
        cout << "Logs decompressed successfully." << endl;
        return true;
    }
};
#endif
