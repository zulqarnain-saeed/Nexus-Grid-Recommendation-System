#pragma once 
#include <iostream>
#include <string>
using namespace std;
class HuffmanNode
{
public:
    unsigned char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(unsigned char ch, int freq)
    {
        character = ch;
        frequency = freq;
        left = NULL;
        right = NULL;
    }
};
class Huffman
{
private:
    HuffmanNode* root;
    string codes[256];
    int frequencies[256];
    void clearTree(HuffmanNode* node)
    {
        if (node != NULL)
        {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }
    void makeCodes(HuffmanNode* node, string code)
    {
        if (node == NULL)
        {
            return;
        }
        if (node->left == NULL && node->right == NULL)
        {
            if (code == "")
            {
                code = "0";
            }
            codes[(int)node->character] = code;
            return;
        }
        makeCodes(node->left, code + "0");
        makeCodes(node->right, code + "1");
    }

    int findSmallest(HuffmanNode* nodes[], int count, int skip)
    {
        int best = -1;
        for (int i = 0; i < count; i++)
        {
            if (i == skip)
            {
                continue;
            }
            if (nodes[i] == NULL)
            {
                continue;
            }
            if (best == -1 || nodes[i]->frequency < nodes[best]->frequency)
            {
                best = i;
            }
        }

        return best;
    }

public:

    Huffman()
    {
        root = NULL;

        for (int i = 0; i < 256; i++)
        {
            codes[i] = "";
            frequencies[i] = 0;
        }
    }
    ~Huffman()
    {
        clear();
    }

    void clear()
    {
        clearTree(root);
        root = NULL;

        for (int i = 0; i < 256; i++)
        {
            codes[i] = "";
            frequencies[i] = 0;
        }
    }
    bool buildFromFrequencies(const int inputFrequencies[])
    {
        clearTree(root);
        root = NULL;

        for (int i = 0; i < 256; i++)
        {
            codes[i] = "";
            frequencies[i] = inputFrequencies[i];
        }
        HuffmanNode* nodes[512];
        int count = 0;

        for (int i = 0; i < 256; i++)
        {
            if (frequencies[i] > 0)
            {
                nodes[count] = new HuffmanNode((unsigned char)i, frequencies[i]);
                count++;
            }
        }

        if (count == 0)
        {
            return false;
        }

        while (count > 1)
        {
            int first = findSmallest(nodes, count, -1);
            int second = findSmallest(nodes, count, first);

            HuffmanNode* parent = new HuffmanNode(0, nodes[first]->frequency + nodes[second]->frequency);
            parent->left = nodes[first];
            parent->right = nodes[second];

            if (first > second)
            {
                int temp = first;
                first = second;
                second = temp;
            }

            nodes[first] = parent;
            nodes[second] = nodes[count - 1];
            count--;
        }
        root = nodes[0];
        makeCodes(root, "");
        return true;
    }

    bool buildFromText(string text)
    {
        int tempFrequencies[256];

        for (int i = 0; i < 256; i++)
        {
            tempFrequencies[i] = 0;
        }
        for (int i = 0; i < (int)text.length(); i++)
        {
            unsigned char ch = (unsigned char)text[i];
            tempFrequencies[(int)ch]++;
        }
        return buildFromFrequencies(tempFrequencies);
    }
    string encodeText(string text)
    {
        string encoded = "";

        if (root == NULL)
        {
            if (buildFromText(text) == false)
            {
                return encoded;
            }
        }
        for (int i = 0; i < (int)text.length(); i++)
        {
            unsigned char ch = (unsigned char)text[i];
            encoded += codes[(int)ch];
        }
        return encoded;
    }

    string decodeBits(string bits)
    {
        string decoded = "";

        if (root == NULL)
        {
            return decoded;
        }

        if (root->left == NULL && root->right == NULL)
        {
            for (int i = 0; i < (int)bits.length(); i++)
            {
                decoded += (char)root->character;
            }

            return decoded;
        }

        HuffmanNode* current = root;

        for (int i = 0; i < (int)bits.length(); i++)
        {
            if (bits[i] == '0')
            {
                current = current->left;
            }
            else if (bits[i] == '1')
            {
                current = current->right;
            }
            else
            {
                return "";
            }

            if (current == NULL)
            {
                return "";
            }

            if (current->left == NULL && current->right == NULL)
            {
                decoded += (char)current->character;
                current = root;
            }
        }

        return decoded;
    }

    int getFrequency(int index) const
    {
        if (index < 0 || index >= 256)
        {
            return 0;
        }

        return frequencies[index];
    }
};


