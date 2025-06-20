#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

std::string expandHome(const std::string& path) {
    const char* home = getenv("HOME");
    if (!home) {
        std::cerr << "Erro: variável HOME não definida.\n";
        exit(1);
    }
    return std::string(home) + path;
}

int main() {
    std::string baseDir = expandHome("/ocrpipe_output/");
    fs::path saidaPath = baseDir + "saida.txt";

    std::ofstream ofs(saidaPath, std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        std::cerr << "Erro ao abrir arquivo de saída: " << saidaPath << "\n";
        return 1;
    }

    int count = 1;
    while (true) {
        fs::path inputPath = baseDir + "texto" + std::to_string(count) + ".txt";
        if (!fs::exists(inputPath)) {
            break;
        }

        std::ifstream ifs(inputPath);
        if (!ifs.is_open()) {
            std::cerr << "Erro ao abrir arquivo: " << inputPath << ", pulando.\n";
            count++;
            continue;
        }

        ofs << ifs.rdbuf();
        ofs << "\n";

        ifs.close();
        count++;
    }

    ofs.close();
    std::cout << "Juntou os arquivos texto1.txt até texto" << (count-1) << ".txt em: " << saidaPath << "\n";
    return 0;
}
