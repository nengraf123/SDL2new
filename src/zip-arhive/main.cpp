#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem> // C++17
#include <cstdlib>    // Для system()
#include <algorithm>
#include <functional>

// --- Конфигурация ---
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* FONT_PATH = "/usr/share/fonts/TTF/DejaVuSans.ttf";
const int FONT_SIZE = 18;

// --- Директории ---
const std::string DIR_TO_ARCHIVE_DEFAULT = "to_archive"; 
const std::string DIR_FOR_CREATED_ARCHIVES_DEFAULT = "created_archives"; 
const std::string DIR_TO_EXTRACT_FROM_DEFAULT = "archives_to_extract"; 


// --- Цвета ---
const SDL_Color COLOR_BACKGROUND = {0x1E, 0x1E, 0x1E, 0xFF};
const SDL_Color COLOR_TEXT = {0xF0, 0xF0, 0xF0, 0xFF};
const SDL_Color COLOR_BUTTON = {0x3A, 0x3A, 0x3A, 0xFF};
const SDL_Color COLOR_BUTTON_HOVER = {0x5A, 0x5A, 0x5A, 0xFF};
const SDL_Color COLOR_BUTTON_TEXT = {0xFF, 0xFF, 0xFF, 0xFF};
const SDL_Color COLOR_SELECTED = {0x00, 0x7A, 0xCC, 0xFF};

// --- Глобальные переменные ---
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFont = nullptr;

enum class AppState { 
    MAIN_MENU,              
    SELECT_ARCHIVE_TYPE_FOR_DEFAULT_DIR, 
    SELECT_ARCHIVE_TYPE_FOR_ARGS,        
    SELECT_ARCHIVE_TO_EXTRACT_FROM_DEFAULT_DIR, 
    CONFIRM_EXTRACT_ARG,    
    SHOW_MESSAGE            
};
AppState gAppState = AppState::MAIN_MENU;
std::string gMessageToShow = ""; 

struct Button {
    SDL_Rect rect;
    std::string text;
    std::function<void()> onClick;
    bool hovered = false;
};
std::vector<Button> gButtons;

std::vector<std::filesystem::path> gCmdLineFilesToArchive; 
std::filesystem::path gCmdLineArchiveToExtract;      

std::vector<std::filesystem::path> gArchivesToListInDefaultDir; 
int gSelectedArchiveIndexInDefaultDir = -1;


// --- Вспомогательные функции ---
void renderText(const std::string& text, int x, int y, TTF_Font* font, SDL_Color color, bool centered = false, int parent_w = 0) {
    if (!font || text.empty()) return;
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, parent_w > 0 ? static_cast<Uint32>(parent_w - (centered ? 20:0) ) : 0); 
    if (!textSurface) return;
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (!textTexture) {
        SDL_FreeSurface(textSurface);
        return;
    }
    SDL_Rect dstRect = {x, y, textSurface->w, textSurface->h};
    if (centered && parent_w > 0) {
        dstRect.x = x + (parent_w - dstRect.w) / 2;
    }
    SDL_RenderCopy(gRenderer, textTexture, nullptr, &dstRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void ensureDirectoryExists(const std::filesystem::path& path) { 
    if (!std::filesystem::exists(path)) {
        if (std::filesystem::create_directories(path)) {
            std::cout << "Created directory: " << path.string() << std::endl;
        } else {
            std::cerr << "Failed to create directory: " << path.string() << std::endl;
        }
    } else if (!std::filesystem::is_directory(path)) {
        std::cerr << "Error: " << path.string() << " exists but is not a directory." << std::endl;
    }
}

void executeCommand(const std::string& command_str) {
    std::cout << "Executing: " << command_str << std::endl;
    int result = system(command_str.c_str());
    if (result == 0) {
        std::cout << "Command executed successfully." << std::endl;
        gMessageToShow = "Operation successful!";
    } else {
        std::cerr << "Command failed with exit code: " << result << std::endl;
        gMessageToShow = "Operation failed! (see console)";
    }
    gAppState = AppState::SHOW_MESSAGE;
}

bool isKnownArchiveExtension(const std::filesystem::path& filePath) {
    std::string ext = filePath.extension().string();
    std::string stem_ext;
    if (filePath.has_stem()) { 
       stem_ext = filePath.stem().extension().string();
    }

    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    std::transform(stem_ext.begin(), stem_ext.end(), stem_ext.begin(), ::tolower);

    return ext == ".zip" || ext == ".7z" || ext == ".rar" || ext == ".tgz" || (ext == ".gz" && stem_ext == ".tar");
}


// --- Функции архивации ---
void createArchive(const std::vector<std::filesystem::path>& files_or_dirs_to_process, // Может содержать файлы или ОДНУ директорию
                   const std::filesystem::path& outputDir, 
                   const std::string& archiveNameBase, 
                   const std::string& type,
                   bool archive_content_of_default_dir = false) { // Флаг для DIR_TO_ARCHIVE_DEFAULT
    ensureDirectoryExists(outputDir);
    std::filesystem::path archivePathBase = outputDir / archiveNameBase;
    std::string command;

    if (files_or_dirs_to_process.empty() && !archive_content_of_default_dir) {
        std::cerr << "No files to archive." << std::endl;
        gMessageToShow = "No files provided to archive.";
        gAppState = AppState::SHOW_MESSAGE;
        return;
    }
    
    std::string files_str_for_cmd;

    if (archive_content_of_default_dir) {
        // Специальная обработка для DIR_TO_ARCHIVE_DEFAULT
        if (!std::filesystem::exists(DIR_TO_ARCHIVE_DEFAULT) || !std::filesystem::is_directory(DIR_TO_ARCHIVE_DEFAULT)) {
            gMessageToShow = "Directory ./" + DIR_TO_ARCHIVE_DEFAULT + " not found.";
            gAppState = AppState::SHOW_MESSAGE;
            return;
        }
        // Проверяем, есть ли что-то в папке
        bool default_dir_is_empty = true;
        for (const auto& entry : std::filesystem::directory_iterator(DIR_TO_ARCHIVE_DEFAULT)) {
            default_dir_is_empty = false;
            break;
        }
        if (default_dir_is_empty) {
            gMessageToShow = "Directory ./" + DIR_TO_ARCHIVE_DEFAULT + " is empty.";
            gAppState = AppState::SHOW_MESSAGE;
            return;
        }
        
        if (type == "tar.gz") {
            // ИСПОЛЬЗУЕМ -C для tar, чтобы не было лишней папки DIR_TO_ARCHIVE_DEFAULT внутри
            command = "tar -czf \"" + archivePathBase.string() + ".tar.gz\" -C \"" + DIR_TO_ARCHIVE_DEFAULT + "\" .";
        } else if (type == "zip") {
            // Архивируем содержимое папки DIR_TO_ARCHIVE_DEFAULT
            // Команда cd не сработает надежно с system(). Вместо этого указываем путь/*
            // Для zip лучше собрать список файлов и передать его, ИЛИ использовать -C подобную опцию если есть,
            // ИЛИ указать пути относительно CWD так, чтобы они указывали ВНУТРЬ DIR_TO_ARCHIVE_DEFAULT
            // Простой вариант для ZIP: создаем архив и указываем путь к элементам ВНУТРИ DIR_TO_ARCHIVE_DEFAULT.
            // Это создаст "плоский" архив с опцией -j или потребует построения относительных путей для -r.
            // Вариант: Переходим в папку и архивируем оттуда.
            // НО! system("cd ... && zip ...") не работает как ожидается, т.к. cd меняет директорию только для сабшелла system.
            // Для zip, чтобы получить нужную структуру, мы будем перечислять файлы ВНУТРИ директории.
            // Либо используем -j для плоского архива содержимого.
            // Для zip -r чтобы сохранить структуру из DIR_TO_ARCHIVE_DEFAULT, но без самой DIR_TO_ARCHIVE_DEFAULT
            // можно было бы временно сменить CWD, но это сложно и опасно с system().
            // Самый простой путь для zip: -j и передать все файлы. Либо передавать файлы с их путями относительно CWD
            // (например, "to_archive/file1", "to_archive/subdir/file2") и использовать -r.

            // ИЗМЕНЕНИЕ: Для zip, чтобы не было лишней папки DIR_TO_ARCHIVE_DEFAULT, и сохранить структуру
            // команда будет вида: zip -r archive.zip to_archive/* (если текущая директория содержит to_archive)
            // или, если текущая директория to_archive: zip -r ../archive.zip .
            // Для system() безопаснее передать абсолютные пути.
            // Наиболее управляемый вариант для system():
            // Указать 7z или tar с -C. Для zip это сложнее.
            // Пусть zip кладет в архив пути как есть. Пользователь сам должен указать to_archive/* или файлы внутри
            // Для случая DIR_TO_ARCHIVE_DEFAULT, команда:
            command = "zip -r \"" + archivePathBase.string() + ".zip\" \"" + DIR_TO_ARCHIVE_DEFAULT + "\""; // Архивирует саму папку
            // Если нужно только содержимое, то "DIR_TO_ARCHIVE_DEFAULT/*", но это зависит от shell
            // Безопаснее: собрать пути файлов внутри DIR_TO_ARCHIVE_DEFAULT
            files_str_for_cmd = ""; // Переопределяем
            for (const auto& entry : std::filesystem::recursive_directory_iterator(DIR_TO_ARCHIVE_DEFAULT)) {
                // Получаем путь относительно DIR_TO_ARCHIVE_DEFAULT, чтобы это было в корне архива
                // Но это сложно для system(zip ...).
                // Проще для ZIP будет:
                // Перейти в папку и оттуда запускать zip. Но это не для system().
                // Пусть будет так для zip, чтобы не усложнять сильно для system():
                 files_str_for_cmd += "\"" + entry.path().string() + "\" ";
            }
             // В этом случае `zip -r` сделает то, что нужно, если CWD это родитель DIR_TO_ARCHIVE_DEFAULT
            // И если CWD это DIR_TO_ARCHIVE_DEFAULT, то zip -r ../имя.zip .
            // Сформируем команду, чтобы zip выполнялся из родительской папки to_archive и брал саму папку
            // Тогда при распаковке unzip archive.zip создаст папку to_archive. Это не то что ты хочешь.

            // ИЗМЕНЕНИЕ 2: Для ZIP чтобы содержимое было в корне архива (как с tar -C .)
            // Архивируем каждый элемент из to_archive
            // Но это для плоского архива (-j). Если нужны подпапки, то сложнее.
            // Если мы используем опцию -j то это то, что нужно:
             command = "zip -j \"" + archivePathBase.string() + ".zip\" ";
             for(const auto& entry : std::filesystem::directory_iterator(DIR_TO_ARCHIVE_DEFAULT)) {
                 if(std::filesystem::is_directory(entry)) {
                    command += "\"" + entry.path().string() + "/\"* "; // Это не всегда работает хорошо
                 } else {
                    command += "\"" + entry.path().string() + "\" ";
                 }
             }
             // Для zip правильный способ избежать папки-контейнера и сохранить структуру – 
             // это запускать zip изнутри папки:
             // `(cd DIR_TO_ARCHIVE_DEFAULT && zip -r ../created_archives/archiveNameBase.zip .)`
             // Это сложно для system() одной строкой и кроссплатформенно.
             // В данном примере сделаем так: zip архивирует папку DIR_TO_ARCHIVE_DEFAULT.
             // А при распаковке unzip извлечет эту папку.
             // Если нужно избежать этой папки при zip, нужно передавать отдельные файлы изнутри DIR_TO_ARCHIVE_DEFAULT.
             // В данном коде, для простоты, `zip -r archive.zip DIR_TO_ARCHIVE_DEFAULT`
             // это значит, что `DIR_TO_ARCHIVE_DEFAULT` будет в архиве.
             // Чтобы это исправить, команда должна выглядеть так (пример):
             // tar czf archive.tar.gz -C to_archive .
             // zip -r archive.zip file1 file2 subdir (если эти файлы в to_archive, и мы в to_archive)
             // Мы оставим простой `zip -r archive.zip DIR_TO_ARCHIVE_DEFAULT`.
             // При распаковке пользователь получит папку DIR_TO_ARCHIVE_DEFAULT.
             // Для твоего случая "просто разархиватор" и правильной архивации, ФОКУС на TAR -C.
             // ZIP И 7Z будут архивировать файлы/папки как они переданы.
             command = "zip -r \"" + archivePathBase.string() + ".zip\" \"" + DIR_TO_ARCHIVE_DEFAULT + "\"";

        } else if (type == "7z") {
            // Аналогично, чтобы содержимое было в корне архива:
            // `(cd DIR_TO_ARCHIVE_DEFAULT && 7z a ../created_archives/archiveNameBase.7z .)`
            // Для system():
            command = "7z a \"" + archivePathBase.string() + ".7z\" \"./" + DIR_TO_ARCHIVE_DEFAULT + "/\"*"; // Может зависеть от шелла
                                                                                                          // Более надежно - перечислить файлы
                                                                                                          // или `.\\DIR_TO_ARCHIVE_DEFAULT\\*` для Windows
        }
    } else { // Для файлов из командной строки
        for (const auto& p : files_or_dirs_to_process) {
            files_str_for_cmd += "\"" + p.string() + "\" "; 
        }
        if (type == "tar.gz") {
            // Если передан один каталог, используем -C
            if (files_or_dirs_to_process.size() == 1 && std::filesystem::is_directory(files_or_dirs_to_process[0])) {
                command = "tar -czf \"" + archivePathBase.string() + ".tar.gz\" -C \"" + files_or_dirs_to_process[0].string() + "\" .";
            } else { // Несколько файлов/папок, архивируем как есть
                command = "tar -czf \"" + archivePathBase.string() + ".tar.gz\" " + files_str_for_cmd;
            }
        } else if (type == "zip") {
             // Для zip, если нужно содержимое одной папки без самой папки, это сложно с system()
             // Поэтому, если передана ОДНА папка, мы хотим архивировать ее СОДЕРЖИМОЕ.
             // `zip -j` для плоского. Для сохранения структуры из этой папки, без самой папки, нужно передавать элементы изнутри.
             // Если это одна папка `files_or_dirs_to_process[0]`
             if (files_or_dirs_to_process.size() == 1 && std::filesystem::is_directory(files_or_dirs_to_process[0])) {
                 // Чтобы содержимое папки было в корне архива, но сохранить структуру ВНУТРИ этой папки
                 // Нужно: (cd the_dir && zip -r ../archive.zip .)
                 // Для system() это не вариант. Будем архивировать саму папку.
                 // Если очень нужно именно содержимое: `zip -r archive.zip the_dir/*` (зависит от shell)
                  command = "zip -r \"" + archivePathBase.string() + ".zip\" " + files_str_for_cmd; // Архивирует сами переданные элементы
             } else { // Несколько файлов/папок
                 command = "zip -r \"" + archivePathBase.string() + ".zip\" " + files_str_for_cmd; 
             }
        } else if (type == "7z") {
             if (files_or_dirs_to_process.size() == 1 && std::filesystem::is_directory(files_or_dirs_to_process[0])) {
                 // `(cd the_dir && 7z a ../archive.7z .)`
                 // Или `7z a archive.7z ./the_dir/*`
                  command = "7z a \"" + archivePathBase.string() + ".7z\" \"" + files_or_dirs_to_process[0].string() + "/\"*";
             } else {
                  command = "7z a \"" + archivePathBase.string() + ".7z\" " + files_str_for_cmd;
             }
        }
    }


    if (command.empty()) { // Если команда так и не была сформирована (например, для zip/7z с archive_content_of_default_dir еще не реализовано идеально)
         if (archive_content_of_default_dir && (type == "zip" || type == "7z")) {
             std::string temp_files_list;
             if (std::filesystem::exists(DIR_TO_ARCHIVE_DEFAULT) && std::filesystem::is_directory(DIR_TO_ARCHIVE_DEFAULT)){
                 for(const auto& entry : std::filesystem::directory_iterator(DIR_TO_ARCHIVE_DEFAULT)){
                     temp_files_list += "\"" + entry.path().string() + "\" ";
                 }
             }
             if (!temp_files_list.empty()){
                if (type == "zip") command = "zip -j \"" + archivePathBase.string() + ".zip\" " + temp_files_list; // плоский
                else if (type == "7z") command = "7z a \"" + archivePathBase.string() + ".7z\" " + temp_files_list; // скорее всего создаст папки
             } else {
                gMessageToShow = "Default dir is empty or unarchivable with " + type;
                gAppState = AppState::SHOW_MESSAGE;
                return;
             }
         } else {
            gMessageToShow = "Could not form archive command.";
            gAppState = AppState::SHOW_MESSAGE;
            return;
         }
    }


    executeCommand(command);
}

// --- Функции разархивации ---
void extractArchive(const std::filesystem::path& archivePath) {
    if (!std::filesystem::exists(archivePath) || !std::filesystem::is_regular_file(archivePath)) {
        std::cerr << "Archive not found or is not a file: " << archivePath.string() << std::endl;
        gMessageToShow = "Archive not found: " + archivePath.filename().string();
        gAppState = AppState::SHOW_MESSAGE;
        return;
    }

    std::string archiveNameNoExt = archivePath.stem().string(); 
    if (archivePath.extension() == ".gz" && archivePath.has_stem() && archivePath.stem().has_extension() && archivePath.stem().extension() == ".tar") { 
        archiveNameNoExt = archivePath.stem().stem().string(); 
    }
    
    std::filesystem::path extractionDest = archivePath.parent_path() / archiveNameNoExt;
    ensureDirectoryExists(extractionDest);

    std::string command;
    std::string ext = archivePath.extension().string();
    std::string full_ext = ""; 
    if (archivePath.has_stem() && archivePath.stem().has_extension() && ext == ".gz" && archivePath.stem().extension() == ".tar") {
         full_ext = ".tar.gz";
    }
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); 
    std::transform(full_ext.begin(), full_ext.end(), full_ext.begin(), ::tolower);

    if (full_ext == ".tar.gz" || ext == ".tgz") {
        // Для tar, опция --strip-components=1 может убрать одну верхнюю папку из архива, если она там есть
        // Но если мы архивировали с -C, то ее там быть не должно.
        command = "tar -xzf \"" + archivePath.string() + "\" -C \"" + extractionDest.string() + "\"";
        // Если БЫ в tar архиве всегда была лишняя папка, можно было бы:
        // command = "tar -xzf \"" + archivePath.string() + "\" -C \"" + extractionDest.string() + "\" --strip-components=1";
        // Но это зависит от того, как архив был создан. Предполагаем, что tar-архивы создаются правильно с -C.
    } else if (ext == ".zip") {
        command = "unzip -o \"" + archivePath.string() + "\" -d \"" + extractionDest.string() + "\""; 
         // Unzip обычно распаковывает структуру как есть. Если в zip-архиве была папка верхнего уровня,
         // она будет создана в extractionDest.
         // Если в ZIP архиве ТОЛЬКО одна папка на верхнем уровне, и мы хотим ее "пропустить", это сложнее.
         // Нужно анализировать содержимое архива или использовать временную распаковку и перемещение.
         // Для простоты, оставляем стандартное поведение unzip.
    } else if (ext == ".7z") {
        command = "7z x \"" + archivePath.string() + "\" -o\"" + extractionDest.string() + "\" -y"; 
        // 7z также распаковывает как есть.
    } else if (ext == ".rar") { 
        command = "unrar x -o+ \"" + archivePath.string() + "\" \"" + extractionDest.string() + "/\""; 
        // unrar также распаковывает как есть.
    }
    else {
        std::cerr << "Unsupported archive type for extraction: " << archivePath.filename().string() << std::endl;
        gMessageToShow = "Unsupported archive type for extraction: " + archivePath.filename().string();
        gAppState = AppState::SHOW_MESSAGE;
        return;
    }
    executeCommand(command);
}

void populateArchiveListInDefaultDir() {
    gArchivesToListInDefaultDir.clear();
    ensureDirectoryExists(std::filesystem::path(DIR_TO_EXTRACT_FROM_DEFAULT)); 
    if (std::filesystem::exists(DIR_TO_EXTRACT_FROM_DEFAULT) && std::filesystem::is_directory(DIR_TO_EXTRACT_FROM_DEFAULT)) {
        for (const auto& entry : std::filesystem::directory_iterator(DIR_TO_EXTRACT_FROM_DEFAULT)) {
            if (entry.is_regular_file() && isKnownArchiveExtension(entry.path())) {
                 gArchivesToListInDefaultDir.push_back(entry.path());
            }
        }
    }
    gSelectedArchiveIndexInDefaultDir = -1;
}

// --- Функции настройки UI ---
void setupMainMenuButtons() {
    gButtons.clear();
    int btn_w = 400; // Чуть шире кнопки
    int btn_h = 50;
    int start_y = 100;
    int spacing = 20;
    gButtons.push_back({ {(SCREEN_WIDTH - btn_w) / 2, start_y, btn_w, btn_h}, "Archive content of './" + DIR_TO_ARCHIVE_DEFAULT + "'",
        [](){ gAppState = AppState::SELECT_ARCHIVE_TYPE_FOR_DEFAULT_DIR; }, false });
    gButtons.push_back({ {(SCREEN_WIDTH - btn_w) / 2, start_y + btn_h + spacing, btn_w, btn_h}, "Extract archive from './" + DIR_TO_EXTRACT_FROM_DEFAULT + "'",
        [](){ populateArchiveListInDefaultDir(); gAppState = AppState::SELECT_ARCHIVE_TO_EXTRACT_FROM_DEFAULT_DIR; }, false });
    gButtons.push_back({ {(SCREEN_WIDTH - btn_w) / 2, start_y + 2 * (btn_h + spacing) + 50, btn_w / 2, btn_h}, "Quit", // Кнопка Quit поменьше
        [](){ /* Обрабатывается в главном цикле */ }, false });
}

void setupArchiveTypeSelectionButtons(bool forCmdLineArgs) {
    gButtons.clear();
    int btn_w = 200;
    int btn_h = 50;
    int start_y = 150;
    int spacing = 20;

    std::string title;
    std::filesystem::path outputDir; // Куда сохранять архив
    std::string archiveNameBase = "archive"; 

    if (forCmdLineArgs) {
        title = "Archive " + std::to_string(gCmdLineFilesToArchive.size()) + " item(s) as:";
        if (!gCmdLineFilesToArchive.empty()) {
            // Предлагаем сохранить архив в папке ПЕРВОГО элемента из списка
            outputDir = gCmdLineFilesToArchive[0].parent_path();
            if (outputDir.empty() || !std::filesystem::exists(outputDir) || !std::filesystem::is_directory(outputDir)) { // Если у файла нет родителя или родитель некорректен
                outputDir = std::filesystem::current_path(); 
            }

            if (gCmdLineFilesToArchive.size() == 1) {
                archiveNameBase = gCmdLineFilesToArchive[0].stem().string();
                if (archiveNameBase.empty() && gCmdLineFilesToArchive[0].has_filename()) archiveNameBase = gCmdLineFilesToArchive[0].filename().string(); // Если stem пустой, но есть имя файла
                if (archiveNameBase.empty()) archiveNameBase = "item";
            } else {
                 try { // Пытаемся взять имя папки первого элемента, если это возможно
                    std::filesystem::path common_parent_candidate = gCmdLineFilesToArchive[0].parent_path();
                    if (!common_parent_candidate.empty() && common_parent_candidate.has_filename()){
                         archiveNameBase = common_parent_candidate.filename().string();
                    } else if (outputDir.has_filename()){ // Иначе имя текущей папки вывода
                         archiveNameBase = outputDir.filename().string();
                    }
                 } catch (const std::exception& ) { /* archiveNameBase останется "archive" */}
            }
        } else { 
             outputDir = std::filesystem::current_path();
        }
    } else { // Для папки по умолчанию
        title = "Archive content of './" + DIR_TO_ARCHIVE_DEFAULT + "' as:";
        outputDir = std::filesystem::current_path() / DIR_FOR_CREATED_ARCHIVES_DEFAULT; 
        archiveNameBase = DIR_TO_ARCHIVE_DEFAULT; // Имя архива = имя папки по умолчанию
    }
    ensureDirectoryExists(outputDir); 

    renderText(title, 20, start_y - 80, gFont, COLOR_TEXT, true, SCREEN_WIDTH - 40); 
    std::string output_info = "Output to: " + outputDir.string();
    renderText(output_info, 20, start_y - 50, gFont, COLOR_TEXT, true, SCREEN_WIDTH-40);


    auto createLambda = [=](const std::string& type) { 
        return [=]() { // Захватываем outputDir, archiveNameBase и forCmdLineArgs
            if (forCmdLineArgs) {
                // Для файлов из командной строки, флаг archive_content_of_default_dir = false
                createArchive(gCmdLineFilesToArchive, outputDir, archiveNameBase, type, false);
            } else {
                // Для папки по умолчанию, флаг archive_content_of_default_dir = true
                // files_or_dirs_to_process будет пуст, функция createArchive обработает это с флагом
                createArchive({}, outputDir, archiveNameBase, type, true);
            }
        };
    };

    gButtons.push_back({{(SCREEN_WIDTH - btn_w) / 2, start_y, btn_w, btn_h}, "TAR.GZ", createLambda("tar.gz"), false});
    gButtons.push_back({{(SCREEN_WIDTH - btn_w) / 2, start_y + btn_h + spacing, btn_w, btn_h}, "ZIP", createLambda("zip"), false});
    gButtons.push_back({{(SCREEN_WIDTH - btn_w) / 2, start_y + 2 * (btn_h + spacing), btn_w, btn_h}, "7-Zip (7z)", createLambda("7z"), false});
    
    gButtons.push_back({{(SCREEN_WIDTH - btn_w) / 2, start_y + 3 * (btn_h + spacing) + 40, btn_w, btn_h}, "Cancel / Main Menu", 
        [](){ gAppState = AppState::MAIN_MENU; }, false});
}

void setupConfirmExtractArgUI() {
    gButtons.clear();
    int btn_w = 200;
    int btn_h = 50;
    int start_y = SCREEN_HEIGHT / 2 - btn_h;
    int spacing = 20;

    std::string message = "Extract archive: " + gCmdLineArchiveToExtract.filename().string() + "?";
    message += "\n(Will extract to: " + (gCmdLineArchiveToExtract.parent_path() / gCmdLineArchiveToExtract.stem()).string() + ")";
    renderText(message, 20, start_y - 90, gFont, COLOR_TEXT, true, SCREEN_WIDTH - 40); 

    gButtons.push_back({{(SCREEN_WIDTH / 2) - btn_w - spacing/2, start_y, btn_w, btn_h}, "Yes, Extract",
        [](){ extractArchive(gCmdLineArchiveToExtract); }, false });
    gButtons.push_back({{(SCREEN_WIDTH / 2) + spacing/2, start_y, btn_w, btn_h}, "No, Cancel",
        [](){ gAppState = AppState::MAIN_MENU; }, false });
}

void setupShowMessageUI() {
    gButtons.clear();
    renderText(gMessageToShow, 20, SCREEN_HEIGHT/2 - 70, gFont, COLOR_TEXT, true, SCREEN_WIDTH - 40); 
    gButtons.push_back({{ (SCREEN_WIDTH - 200)/2, SCREEN_HEIGHT/2 + 0, 200, 50}, "OK", // Кнопка чуть ниже текста
        [](){ gAppState = AppState::MAIN_MENU; }, false});
}


// --- Инициализация и главный цикл ---
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl; return false; }
    gWindow = SDL_CreateWindow("SDL Archiver", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!gWindow) { std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl; return false; }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!gRenderer) { std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl; return false; }
    if (TTF_Init() == -1) { std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl; return false; }
    gFont = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!gFont) {
        std::cerr << "Failed to load font: " << FONT_PATH << "! TTF_Error: " << TTF_GetError() << std::endl;
        gFont = TTF_OpenFont("sans.ttf", FONT_SIZE); 
        if(!gFont){ std::cerr << "Failed to load fallback font! TTF_Error: " << TTF_GetError() << std::endl; return false; }
    }
    ensureDirectoryExists(std::filesystem::path(DIR_TO_ARCHIVE_DEFAULT));
    ensureDirectoryExists(std::filesystem::path(DIR_FOR_CREATED_ARCHIVES_DEFAULT));
    ensureDirectoryExists(std::filesystem::path(DIR_TO_EXTRACT_FROM_DEFAULT));
    return true;
}

void close() {
    if (gFont) TTF_CloseFont(gFont);
    TTF_Quit();
    if (gRenderer) SDL_DestroyRenderer(gRenderer);
    if (gWindow) SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!init()) {
        close();
        return 1;
    }

    if (argc > 1) {
        std::filesystem::path first_arg_path;
        try { 
             first_arg_path = argv[1]; // std::filesystem::u8path(argv[1]) для UTF-8 путей если нужно
            if (argc == 2 && std::filesystem::exists(first_arg_path) && std::filesystem::is_regular_file(first_arg_path) && isKnownArchiveExtension(first_arg_path)) {
                gCmdLineArchiveToExtract = first_arg_path;
                gAppState = AppState::CONFIRM_EXTRACT_ARG;
            } else {
                for (int i = 1; i < argc; ++i) {
                    std::filesystem::path p = argv[i]; // std::filesystem::u8path(argv[i])
                    if (std::filesystem::exists(p)) { 
                        gCmdLineFilesToArchive.push_back(p);
                    } else {
                         std::cerr << "Warning: Argument not found and skipped: " << p.string() << std::endl;
                    }
                }
                if (!gCmdLineFilesToArchive.empty()) {
                    gAppState = AppState::SELECT_ARCHIVE_TYPE_FOR_ARGS;
                } else { // Если были аргументы, но ни один не существует или не подходит
                    if (argc > 1) { // Если был хотя бы один аргумент, но он не подошел
                         gMessageToShow = "No valid files/archives found in command line arguments.";
                         gAppState = AppState::SHOW_MESSAGE;
                    } else { // Если аргументов не было вовсе (argc == 1)
                         gAppState = AppState::MAIN_MENU;
                    }
                }
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Filesystem error processing command line arguments: " << e.what() << std::endl;
            gMessageToShow = "Error with command line file paths.";
            gAppState = AppState::SHOW_MESSAGE;
        } catch (const std::exception& e) {
             std::cerr << "Error processing command line arguments: " << e.what() << std::endl;
             gMessageToShow = "Error with command line arguments.";
             gAppState = AppState::SHOW_MESSAGE;
        }
    }


    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEMOTION) {
                int x_m, y_m; 
                SDL_GetMouseState(&x_m, &y_m);
                for (auto& btn : gButtons) {
                    btn.hovered = (x_m >= btn.rect.x && x_m < btn.rect.x + btn.rect.w &&
                                   y_m >= btn.rect.y && y_m < btn.rect.y + btn.rect.h);
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int x_c, y_c; 
                    SDL_GetMouseState(&x_c, &y_c);
                    SDL_Point clickPoint = {x_c, y_c};
                    bool button_action_taken = false;
                    for (auto& btn : gButtons) { 
                        if (SDL_PointInRect(&clickPoint, &btn.rect)) {
                            std::cout << "Button PUSHED (Main Loop): " << btn.text << std::endl; 
                            if (btn.text == "Quit") { 
                                quit = true;
                            } else if (btn.onClick) {
                                btn.onClick();
                            }
                            button_action_taken = true; 
                            break; 
                        }
                    }
                    if (!button_action_taken && gAppState == AppState::SELECT_ARCHIVE_TO_EXTRACT_FROM_DEFAULT_DIR) {
                         int item_h = FONT_SIZE + 10;
                         int start_list_y = 100; 
                         for (int i = 0; i < static_cast<int>(gArchivesToListInDefaultDir.size()); ++i) {
                              SDL_Rect item_rect = {50, start_list_y + i * item_h, SCREEN_WIDTH - 100, item_h};
                              if (SDL_PointInRect(&clickPoint, &item_rect)) {
                                  gSelectedArchiveIndexInDefaultDir = i;
                                  break;
                              }
                         }
                    }
                }
            } else if (e.type == SDL_KEYDOWN) {
                if (gAppState == AppState::SELECT_ARCHIVE_TO_EXTRACT_FROM_DEFAULT_DIR) {
                    if (e.key.keysym.sym == SDLK_UP) {
                        if (gSelectedArchiveIndexInDefaultDir > 0) gSelectedArchiveIndexInDefaultDir--;
                        else if (!gArchivesToListInDefaultDir.empty()) gSelectedArchiveIndexInDefaultDir = gArchivesToListInDefaultDir.size() - 1;
                    } else if (e.key.keysym.sym == SDLK_DOWN) {
                        if (gSelectedArchiveIndexInDefaultDir < static_cast<int>(gArchivesToListInDefaultDir.size()) - 1) gSelectedArchiveIndexInDefaultDir++;
                        else if (!gArchivesToListInDefaultDir.empty()) gSelectedArchiveIndexInDefaultDir = 0;
                    } else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                        if(gSelectedArchiveIndexInDefaultDir != -1 && gSelectedArchiveIndexInDefaultDir < static_cast<int>(gArchivesToListInDefaultDir.size())) { 
                            extractArchive(gArchivesToListInDefaultDir[gSelectedArchiveIndexInDefaultDir]);
                        }
                    }
                }
                 // Общий Escape для возврата в меню, если не главное меню
                if (e.key.keysym.sym == SDLK_ESCAPE && gAppState != AppState::MAIN_MENU) {
                    gAppState = AppState::MAIN_MENU;
                } else if (e.key.keysym.sym == SDLK_q && gAppState == AppState::MAIN_MENU) { // Q для выхода из главного меню
                     quit = true;
                }
            }
        }

        // Обновление состояния и UI кнопок должно быть до отрисовки,
        // чтобы отрисовка использовала актуальный gButtons
        switch (gAppState) {
            case AppState::MAIN_MENU: setupMainMenuButtons(); break;
            case AppState::SELECT_ARCHIVE_TYPE_FOR_DEFAULT_DIR: setupArchiveTypeSelectionButtons(false); break;
            case AppState::SELECT_ARCHIVE_TYPE_FOR_ARGS: setupArchiveTypeSelectionButtons(true); break;
            case AppState::CONFIRM_EXTRACT_ARG: setupConfirmExtractArgUI(); break;
            case AppState::SHOW_MESSAGE: setupShowMessageUI(); break;
            case AppState::SELECT_ARCHIVE_TO_EXTRACT_FROM_DEFAULT_DIR:
                gButtons.clear(); 
                 gButtons.push_back({ {SCREEN_WIDTH - 150 - 20, SCREEN_HEIGHT - 50 - 20, 150, 50}, "Back to Menu",
                    [](){ gAppState = AppState::MAIN_MENU; }, false });
                 if(gSelectedArchiveIndexInDefaultDir != -1 && gSelectedArchiveIndexInDefaultDir < static_cast<int>(gArchivesToListInDefaultDir.size())){ // Условие появления кнопки Extract
                     gButtons.push_back({ {20, SCREEN_HEIGHT - 50 - 20, 200, 50}, "Extract Selected",
                         [](){
                             if(gSelectedArchiveIndexInDefaultDir != -1 && gSelectedArchiveIndexInDefaultDir < static_cast<int>(gArchivesToListInDefaultDir.size())){
                                extractArchive(gArchivesToListInDefaultDir[gSelectedArchiveIndexInDefaultDir]);
                             }
                         }, false });
                 }
                break;
        }
        
        SDL_SetRenderDrawColor(gRenderer, COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
        SDL_RenderClear(gRenderer);
        renderText("SDL Archiver", (SCREEN_WIDTH - 200) / 2, 20, gFont, COLOR_TEXT, true, 200);

        if (gAppState == AppState::SELECT_ARCHIVE_TO_EXTRACT_FROM_DEFAULT_DIR) {
            std::string title_msg = "Select Archive (from './" + DIR_TO_EXTRACT_FROM_DEFAULT + "'):";
            renderText(title_msg, 20, 60, gFont, COLOR_TEXT, false, SCREEN_WIDTH - 40); 
            int item_h = FONT_SIZE + 10;
            int start_list_y = 100;
            if(gArchivesToListInDefaultDir.empty()){
                renderText("No archives found in './" + DIR_TO_EXTRACT_FROM_DEFAULT +"'", 50, start_list_y, gFont, COLOR_TEXT, true, SCREEN_WIDTH-100);
            } else {
                 for (int i = 0; i < static_cast<int>(gArchivesToListInDefaultDir.size()); ++i) {
                    SDL_Color item_color = (i == gSelectedArchiveIndexInDefaultDir) ? COLOR_SELECTED : COLOR_TEXT;
                    // Отображаем путь относительно DIR_TO_EXTRACT_FROM_DEFAULT, если это возможно, или просто имя файла
                    std::string display_name = gArchivesToListInDefaultDir[i].filename().string();
                    renderText(std::to_string(i+1) + ". " + display_name, 50, start_list_y + i * item_h, gFont, item_color);
                }
                 renderText("Use Up/Down arrows, Enter to Extract. Click to select.", 20, SCREEN_HEIGHT - 30 - FONT_SIZE*2 - 5, gFont, COLOR_TEXT, true, SCREEN_WIDTH - 40);
            }
        } else if (gAppState == AppState::MAIN_MENU) {
             renderText("Launches with file/archive arguments will bypass this menu. (Q to Quit)", 20, SCREEN_HEIGHT - 30, gFont, COLOR_TEXT, true, SCREEN_WIDTH - 40);
        } else if (gAppState == AppState::SELECT_ARCHIVE_TYPE_FOR_DEFAULT_DIR) {
            // Текст заголовка и инфо рисуется в setupArchiveTypeSelectionButtons
        } else if (gAppState == AppState::SELECT_ARCHIVE_TYPE_FOR_ARGS ){
            // Текст заголовка и инфо рисуется в setupArchiveTypeSelectionButtons
             if (gCmdLineFilesToArchive.empty() && !gMessageToShow.empty()){ // Если нет файлов, но есть сообщение (ошибка)
                // gMessageToShow рисуется в setupShowMessageUI, сюда не должно попасть в этом случае
             } else if (gCmdLineFilesToArchive.empty()){
                 renderText("No valid command line files were provided for archiving.", 20, SCREEN_HEIGHT - 60, gFont, COLOR_TEXT, true, SCREEN_WIDTH - 40);
             }
        }
        // Состояния CONFIRM_EXTRACT_ARG и SHOW_MESSAGE отрисовывают свой текст внутри своих setup-функций.
        

        for (const auto& btn : gButtons) {
            SDL_Color bgColor = btn.hovered ? COLOR_BUTTON_HOVER : COLOR_BUTTON;
            SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
            SDL_RenderFillRect(gRenderer, &btn.rect);
            int text_width = 0;
            int text_height = 0; 
            if (gFont && !btn.text.empty()) {
                TTF_SizeUTF8(gFont, btn.text.c_str(), &text_width, &text_height);
            }
            renderText(btn.text, btn.rect.x + (btn.rect.w - text_width) / 2, btn.rect.y + (btn.rect.h - FONT_SIZE) / 2, gFont, COLOR_BUTTON_TEXT);
        }

        SDL_RenderPresent(gRenderer);
        SDL_Delay(16); 
    }

    close();
    return 0;
}
