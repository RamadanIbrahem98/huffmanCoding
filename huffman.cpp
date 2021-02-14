#include "huffman.hpp"

HuffmanCoding::HuffmanCoding(std::string fileName)
{
    IO.setTargetName(fileName);
}

void HuffmanCoding::constructFreqTable()
{
    for (auto value : input)
    {
        freqTable[value]++;
    }
}

void HuffmanCoding::constructTree()
{
    struct freqCompare
    {
        bool operator()(Node *l, Node *r)
        {
            return (l->freq > r->freq);
        }
    };

    std::priority_queue<Node *, std::vector<Node *>, freqCompare> pq;

    for (auto pixel : freqTable)
    {
        Node *n = new Node{pixel.first, pixel.second};
        pq.push(n);
    }

    Node *parent;

    while (pq.size() != 1)
    {
        Node *left = pq.top();
        pq.pop();

        Node *right = pq.top();
        pq.pop();

        parent = new Node;
        parent->freq = left->freq + right->freq;
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    builtTree = parent;

    char word[255];
    constructCodeWords(builtTree, word, 0);
}

void HuffmanCoding::constructCodeWords(Node *parent, char *word, int index)
{
    if (parent->left)
    {
        word[index] = '0';
        constructCodeWords(parent->left, word, index + 1);
    }

    if (parent->right)
    {
        word[index] = '1';
        constructCodeWords(parent->right, word, index + 1);
    }

    if (!(parent->right || parent->left))
    {
        std::string codeWord(word, word + index);
        leafCodeWord[parent->greyScaleValue] = codeWord;
    }
}

void HuffmanCoding::createEncoded()
{
    for (auto element : input)
    {
        std::string binary = leafCodeWord[element];
        strEncoded += binary;
    }
    encodedLength = strEncoded.length();
}

void HuffmanCoding::toDecimal()
{
    decimalPacked.clear();
    std::string str = "";
    for (auto e : strEncoded)
    {
        str.push_back(e);
        if (str.size() == 8)
        {
            decimalPacked.push_back(std::bitset<8>(str).to_ulong());
            str = "";
        }
    }
    int numOfZeros = strEncoded.length() % 8;
    if (numOfZeros != 0)
    {
        for (int i = 0; i < 8 - numOfZeros; ++i)
        {
            str.push_back('0');
        }
        if (str.size() == 8)
        {
            decimalPacked.push_back(std::bitset<8>(str).to_ulong());
        }
    }
}

void HuffmanCoding::traverseDown()
{
    for (int i = 0; i < encodedLength;)
    {
        Node *current = builtTree;
        while (current->left != nullptr && current->right != nullptr)
        {
            if (strToDecode[i] == '0')
                current = current->left;
            else
                current = current->right;
            i++;
        }
        decoded.push_back(current->greyScaleValue);
    }
}

void HuffmanCoding::encode(std::string filePath)
{
    IO.pgmRead(filePath, filetype, rows, cols, greyscaleMax, size, input);
    constructFreqTable();
    constructTree();
    createEncoded();
    toDecimal();
    IO.freqWrite(filetype, rows, cols, greyscaleMax, encodedLength, freqTable);
    IO.hufWrite(decimalPacked);
}

void HuffmanCoding::decode(std::string hufDestination, std::string freqDestination)
{
    IO.freqRead(freqDestination, filetype, rows, cols, greyscaleMax, size, encodedLength, freqTable);
    constructTree();
    IO.hufRead(hufDestination, strToDecode);
    traverseDown();
    IO.pgmWrite(filetype, rows, cols, greyscaleMax, decoded);
}