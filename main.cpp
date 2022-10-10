#include <iostream>
#include <algorithm>

#include "RedBlackTree.h"

void addWordToDictionary(RedBlackTree<std::string> &tree){

    int choice = 0;
    std::string buf;

    std::cout << "Enter a word:" << std::endl;
    std::cin >> buf;
    std::transform(buf.begin(), buf.end(), buf.begin(), toupper);
    tree.insert(buf);

    std::cout << "1 - Add translation of the word." << std::endl;
    std::cout << "0 - exit." << std::endl;
    std::cin >> choice;

    if(!std::cin) {
        throw WrongIntegerNumber();
    }

    if(choice){
        std::cout << "Add translation:" << std::endl;
        std::string transl;
        std::cin >> transl;

        tree.addTranslate(buf, transl);
    }
}

void addTranslationToDictionary(RedBlackTree<std::string> &tree){

    std::string buf;
    std::cout << "Enter the word to which you want to add a translation:" << std::endl;
    std::cin >> buf;
    std::transform(buf.begin(), buf.end(), buf.begin(), toupper);

    std::cout << "Add translation:" << std::endl;
    std::string transl;
    std::cin >> transl;

    if(!tree.addTranslate(buf, transl)){
        std::cout << "Translation was not added because the word was not in the dictionary!" << std::endl;
    }
}

void removeWordFromDictionary(RedBlackTree<std::string> &tree){
    std::string buf;
    std::cout << "Enter the word you want to remove from the dictionary:" << std::endl;
    std::cin >> buf;
    std::transform(buf.begin(), buf.end(), buf.begin(), toupper);

    if(!tree.remove(buf)){
        std::cout << "This word is not in the dictionary!" << std::endl;
    }
}

void removeTranslationFromDictionary(RedBlackTree<std::string> &tree){
    std::string buf;
    std::cout << "Enter the word where you want to remove the translation:" << std::endl;
    std::cin >> buf;
    std::transform(buf.begin(), buf.end(), buf.begin(), toupper);

    std::size_t num;
    std::cout << "Choose the translation number of the word" << std::endl;
    std::cin >> num;

    if(!std::cin) {
        throw WrongUnsignedNumber();
    }

    if(!tree.deleteTranslate(buf,num)){
        std::cout << "This word is not in the dictionary!" << std::endl;
    }
}

void findTranslation(RedBlackTree<std::string> &tree) {
    std::string buf;
    std::cout << "Enter the word whose translation you want to see:" << std::endl;
    std::cin >> buf;
    std::transform(buf.begin(), buf.end(), buf.begin(), toupper);

    if(!tree.searchTranslate(buf)){
        std::cout << "This word is not in the dictionary!" << std::endl;
    }
}

int selectAction(){
    int choice = 0;

    std::cout << "1 - Add word to dictionary" << std::endl;
    std::cout << "2 - Enter a translation into an existing word" << std::endl;
    std::cout << "3 - Remove word from dictionary" << std::endl;
    std::cout << "4 - Remove translation from dictionary" << std::endl;
    std::cout << "5 - Find translation" << std::endl;
    std::cout << "6 - Show dictionary" << std::endl;
    std::cout << "7 - Exit" << std::endl;
    std::cin >> choice;

    if (!std::cin) {
        throw WrongUnsignedNumber();
    }

    std::cout << std::endl;

    return choice;
}

int main() {
    try {
        RedBlackTree<std::string> dictionary;
        int choice = selectAction();

        while (choice != 7) {
            switch (choice) {
                case 1:
                    addWordToDictionary(dictionary);
                    break;
                case 2:
                    addTranslationToDictionary(dictionary);
                    break;
                case 3:
                    removeWordFromDictionary(dictionary);
                    break;
                case 4:
                    removeTranslationFromDictionary(dictionary);
                    break;
                case 5:
                    findTranslation(dictionary);
                    break;
                case 6:
                    dictionary.inOrder();
                    break;
                case 7:
                    break;
                default:
                    throw WrongCommand();
            }

            choice = selectAction();
        }
    }
    catch (std::exception &exception) {
        std::cerr << std::endl << exception.what() << std::endl;
    }

    return 0;
}
