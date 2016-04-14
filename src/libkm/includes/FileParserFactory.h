/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileParserFactory.h
 * Author: veraalva
 *
 * Created on April 11, 2016, 12:50 PM
 */

#ifndef FILEPARSERFACTORY_H
#define FILEPARSERFACTORY_H

#include "Exceptions.h"


namespace parsers {

    class FileParserFactory {
    public:
        FileParserFactory();
        FileParserFactory(FILE *fileToParse);
        FileParserFactory(std::string fileToParseName);
        virtual ~FileParserFactory();

        FILE* getFileToParse() {
            return fileToParse;
        }

        void setFileToParse(FILE* fileToParse) {
            this->fileToParse = fileToParse;
            this->closeFile = false;
        }

        void setFileToParse(std::string fileToParseName) {
            this->fileToParse = (FILE *) fopen(fileToParseName.c_str(), "r");
            if (!this->fileToParse) {
                throw exceptions::FileNotFoundException("Can't open file: " + fileToParseName);
            }
            this->closeFile = true;
        }

        size_t getNWords() {
            return nWords;
        }

        char** getWords() {
            return words;
        }

        char *getLine() {
            return line;
        }

        size_t getLineLength() {
            return lineLength;
        }

        void setBufferSize(size_t bufferSize) {
            this->bufferSize = bufferSize;
        }

        bool iterate(const char dontStartWith);
        bool iterate(const char dontStartWith, const char *delimiter);
        void wordsToVector(std::vector<std::string>& v);
        void clean();

    private:
        FILE *fileToParse;
        char **words;
        size_t wordsSize;
        size_t nWords;
        char *buffer;
        char *bufferEndPtr;
        char *str;
        char *line;
        char *backup;
        size_t bufferSize;
        size_t backupSize;
        size_t backupTotalSize;
        size_t read;
        size_t lineLength;
        bool closeFile;
    };

}

#endif /* FILEPARSERFACTORY_H */
