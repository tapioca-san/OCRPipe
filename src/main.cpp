#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <unistd.h>

namespace fs = std::filesystem;

std::string expandHome(const std::string& path) {
    const char* home = getenv("HOME");
    return std::string(home) + path;
}

int main() {
    std::string baseDir = expandHome("/ocrpipe_output/");
    fs::create_directories(baseDir);  

    int count = 1;

    while (true) {
        std::string imagePath = baseDir + "imageTexto" + std::to_string(count) + ".png";
        std::string textPathBase = baseDir + "texto" + std::to_string(count);
        std::string textPath = textPathBase + ".txt";

        std::cout << "[Captura #" << count << "] Selecione a área da tela...\n";

        // Captura com grim + slurp
        std::string grimCommand = "grim -g \"$(slurp)\" \"" + imagePath + "\"";
        if (std::system(grimCommand.c_str()) != 0) {
            std::cerr << "Erro ao capturar a tela. Saindo...\n";
            break;
        }

        // OCR com Tesseract
        std::string tesseractCommand = "tesseract \"" + imagePath + "\" \"" + textPathBase + "\" -l por";
        if (std::system(tesseractCommand.c_str()) != 0) {
            std::cerr << "Erro ao executar OCR. Saindo...\n";
            break;
        }

        std::cout << "Texto salvo em: " << textPath << "\n";

        std::cout << "\nDeseja capturar mais? (s/n): ";
        char resp;
        std::cin >> resp;
        if (resp != 's' && resp != 'S') break;

        count++;
    }

    std::cout << "Finalizado.\n";
    return 0;
}
