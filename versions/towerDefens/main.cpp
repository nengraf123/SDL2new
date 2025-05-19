#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_pixels.h>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <algorithm> // Для std::min/max, std::remove_if
#include <chrono>
#include <iostream>
#include <locale>
#include <set>      // Для отслеживания врагов, пораженных AoE

// --- Константы ---
const int SCREEN_WIDTH = 1920; // Изменено на Full HD
const int SCREEN_HEIGHT = 1080; // Изменено на Full HD
const char* WINDOW_TITLE = "Simple Tower Defense";
const char* FONT_PATH = "arial.ttf"; // Файл шрифта

const int TOWER_SELECTION_BAR_HEIGHT = 80; // Уменьшена высота верхней панели
const int TOWER_CARD_WIDTH = 70; // Уменьшена ширина карточки башни
const int TOWER_CARD_PADDING = 10; // Отступы между карточками и от краев панели
const int TOWER_SLOT_TOTAL_WIDTH = TOWER_CARD_WIDTH + TOWER_CARD_PADDING; // Общая ширина, занимаемая слотом (карточка + отступ)
const int TOWER_CARD_HEIGHT = TOWER_SELECTION_BAR_HEIGHT - 2 * TOWER_CARD_PADDING; // Высота карточки

const int BASE_LIVES = 10;
const int STARTING_MONEY = 750; // Немного больше стартовых денег

const float TIME_BETWEEN_WAVES = 15.0f; // Увеличено время между волнами

// Простой путь для врагов (последовательность точек) - АДАПТИРОВАНО для 1080p
// Эти точки - пример. Для идеального пути на вашем экране может потребоваться ручная настройка.
const SDL_Point PATH_POINTS[] = {
    {-50, 540},       // Start off-screen left (примерно по центру по Y)
    {300, 540},
    {300, 840},
    {1000, 840},
    {1000, 240},
    {SCREEN_WIDTH + 50, 240} // End off-screen right
};
const int PATH_POINT_COUNT = sizeof(PATH_POINTS) / sizeof(PATH_POINTS[0]);

// Цвета
const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
const SDL_Color COLOR_BLACK = {0, 0, 0, 255};
const SDL_Color COLOR_RED = {255, 0, 0, 255};
const SDL_Color COLOR_GREEN = {0, 255, 0, 255};
const SDL_Color COLOR_BLUE = {0, 0, 255, 255};
const SDL_Color COLOR_GRAY = {128, 128, 128, 255};
const SDL_Color COLOR_YELLOW = {255, 255, 0, 255};
const SDL_Color COLOR_TRANSPARENT_GREEN = {0, 255, 0, 100}; // Для радиуса башни
const SDL_Color COLOR_TRANSPARENT_RED = {255, 0, 0, 100};   // Для невозможного размещения
const SDL_Color COLOR_TRANSPARENT_BLUE = {0, 0, 255, 80}; // Для радиуса замедления
const SDL_Color COLOR_TRANSPARENT_YELLOW = {255, 255, 0, 80}; // Для радиуса баффа

// Цвет фона (светло-оливково-серый)
const SDL_Color COLOR_BACKGROUND = {192, 208, 192, 255}; // Пример спокойного цвета

// Время для отображения информации о башне при наведении (в секундах)
const float TOWER_HOVER_TIME_THRESHOLD = 0.7f; // Уменьшим для более быстрого срабатывания

// Коэффициенты усиления врагов по волнам (уменьшены для более плавного прироста)
const float ENEMY_HEALTH_BASE_SCALE = 1.04f; // Увеличение здоровья на 4% за волну после первой
const float ENEMY_REWARD_BASE_SCALE = 1.02f; // Увеличение награды на 2% за волну после первой
const float ENEMY_WAVE_1_HEALTH_MULTIPLIER = 0.25f; // Здоровье в первой волне - 25% от базового


// --- Глобальные переменные SDL и менеджеры ---
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFont = nullptr;
TTF_Font* gFontSmall = nullptr; // Меньший шрифт для некоторого текста

// Простой менеджер текстур (для этого примера просто map)
std::map<std::string, SDL_Texture*> gTextures;

SDL_Texture* loadTexture(const std::string& path) {
    if (path.empty()) return nullptr; // Не пытаемся загрузить из пустой строки

    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        SDL_Log("Unable to load image %s! SDL_image Error: %s", path.c_str(), IMG_GetError());
    } else {
        // Определяем формат окна
        Uint32 windowPixelFormat = SDL_GetWindowPixelFormat(gWindow);
        SDL_PixelFormat* windowFormatDetails = SDL_AllocFormat(windowPixelFormat);
        bool windowHasAlpha = (windowFormatDetails && windowFormatDetails->Amask > 0);
        if (windowFormatDetails) SDL_FreeFormat(windowFormatDetails);


        // Определяем формат исходной поверхности
        SDL_PixelFormat* loadedFormatDetails = loadedSurface->format;
        bool loadedSurfaceHasAlpha = (loadedFormatDetails && loadedFormatDetails->Amask > 0);

        Uint32 targetFormat = windowPixelFormat; // Пытаемся конвертировать в формат окна

        // Если формат окна не поддерживает альфа, но исходная поверхность имеет альфа-канал,
        // пытаемся конвертировать в 32-битный формат с альфой, чтобы сохранить прозрачность.
        if (!windowHasAlpha && loadedSurfaceHasAlpha) {
             targetFormat = SDL_PIXELFORMAT_RGBA32; // Fallback to a known 32-bit RGBA format
        }


        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, targetFormat, 0);

        if (formattedSurface == nullptr) {
             SDL_Log("Unable to convert surface format for %s! SDL Error: %s", path.c_str(), SDL_GetError());
             formattedSurface = loadedSurface; // Используем исходную поверхность, если конвертация не удалась
        } else {
             SDL_FreeSurface(loadedSurface); // Освобождаем исходную поверхность, если конвертация удалась
        }

        // Устанавливаем цветовой ключ (например, пурпурный) для прозрачности, если нет альфа-канала
        // Это опционально и зависит от ваших изображений. PNG с альфой лучше.
        // SDL_SetColorKey(formattedSurface, SDL_TRUE, SDL_MapRGB(formattedSurface->format, 0xFF, 0, 0xFF));


        newTexture = SDL_CreateTextureFromSurface(gRenderer, formattedSurface);
        if (newTexture == nullptr) {
            SDL_Log("Unable to create texture from %s! SDL Error: %s", path.c_str(), SDL_GetError());
        } else {
             // Включаем смешивание для текстур, если они могут быть полупрозрачными
             SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
        }
        SDL_FreeSurface(formattedSurface); // Освобождаем поверхность после создания текстуры
    }
    return newTexture;
}

void freeTextures() {
    for (auto const& [key, val] : gTextures) {
        SDL_DestroyTexture(val);
    }
    gTextures.clear();
}

// Хелпер для рендеринга текста с указанием шрифта
SDL_Texture* renderText(const std::string& text, SDL_Color color, TTF_Font* font) {
    if (font == nullptr) {
        // SDL_Log("Font not loaded for rendering text!"); // Не спамить лог каждый кадр
        return nullptr;
    }
    // Обработка пустой строки текста
    if (text.empty()) return nullptr;

    // Важно: TTF_RenderUTF8_Blended работает с альфа-каналом, что нужно для прозрачности текста
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (textSurface == nullptr) {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s", TTF_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (texture == nullptr) {
        SDL_Log("Unable to create texture from rendered text! SDL Error: %s", SDL_GetError());
    }
    SDL_FreeSurface(textSurface);
    return texture;
}


// --- Структуры данных для игры ---

struct Vector2 {
    float x, y;
};

struct Projectile {
    Vector2 position;
    Vector2 velocity;
    float speed;
    float damage; // Урон при попадании (или урон в секунду, если снаряд "живет"?)
    int targetEnemyId; // ID врага, в которого летит снаряд
    SDL_Texture* texture = nullptr; // Текстура снаряда
    SDL_Rect srcRect = {0, 0, 8, 8}; // Размер снаряда (пример)

    // Для AoE/Piercing
    bool isAreaDamage = false;
    float areaRadius = 0.0f;
    // bool isPiercing = false; // Пробивающий снаряд (пока не реализовано)
    // int piercingCount = 0;   // Сколько еще врагов может пробить

    std::set<int> hitEnemiesIds; // ID врагов, уже пораженных этим снарядом (для AoE - за попадание снаряда; для DoT/continuous AoE - за тик урона)


    // Для замедления
    float slowAmount = 1.0f; // Множитель скорости (1.0 = нет замедления, 0.5 = 50% скорость)
    float slowDuration = 0.0f; // Длительность замедления при попадании (секунды)

    // Для непрерывного урона (например, лазер, огнемет?) - возможно, лучше реализовать в логике башни
    // float duration = 0.0f; // Длительность жизни снаряда (для непрерывного урона)
};

// Информация о типе врага (базовые характеристики)
struct EnemyInfo {
    std::string name;
    float baseMaxHealth; // Базовое здоровье без учета волны
    float baseSpeed;     // Базовая скорость без учета волны
    int baseReward;      // Базовая награда без учета волны
    std::string texturePath; // Путь к текстуре
    SDL_Texture* texture = nullptr; // Загруженная текстура

    // Явный конструктор
    EnemyInfo(std::string name, float baseMaxHealth, float baseSpeed, int baseReward, std::string texturePath)
        : name(name), baseMaxHealth(baseMaxHealth), baseSpeed(baseSpeed), baseReward(baseReward), texturePath(texturePath) {}

};

// Информация о типе башни (базовые характеристики и множители прокачки)
struct TowerInfo {
    std::string name;
    std::string description;
    int cost;
    float baseRange;        // Базовый радиус атаки (или радиус эффекта для утилит)
    float baseDamage;       // Базовый урон за выстрел (или урон в секунду для DoT/AoE зон)
    float baseFireRate;     // Базовая скорость выстрелов (выстрелов в секунду), 0 для утилит

    // Параметры специфических атак/эффектов
    bool isProjectile = true; // Стреляет снарядами? (false для лазера, огнемета зоны, болота, шипов)
    bool isContinuous = false; // Наносит урон непрерывно (Лазер)? (true для лазера)
    bool isAreaOfEffect = false; // Урон или эффект по области (Огнемет, Болото, Миномет)?
    float areaOfEffectRadius = 0.0f; // Радиус AoE/зоны

    float slowAmount = 1.0f; // Множитель замедления (1.0 = нет, 0.5 = 50% скорость)
    float slowDuration = 0.0f; // Длительность замедления (для снарядов) ИЛИ время обновления эффекта (для зон)

    std::string texturePath; // Путь к текстуре
    SDL_Texture* texture = nullptr; // Загруженная текстура

    // Параметры прокачки
    int upgradeCost;
    float rangeUpgradeMultiplier;
    float damageUpgradeMultiplier;
    float fireRateUpgradeMultiplier; // Меньше 1.0 для ускорения
    int maxLevel; // Максимальный уровень прокачки

    // Явный конструктор с полным набором параметров
    TowerInfo(std::string name, std::string description, int cost, float baseRange, float baseDamage, float baseFireRate,
              std::string texturePath, int upgradeCost, float rangeUpgradeMultiplier, float damageUpgradeMultiplier,
              float fireRateUpgradeMultiplier, int maxLevel = 5,
              bool isProjectile = true, bool isContinuous = false, bool isAreaOfEffect = false, float areaOfEffectRadius = 0.0f,
              float slowAmount = 1.0f, float slowDuration = 0.0f)
        : name(name), description(description), cost(cost), baseRange(baseRange), baseDamage(baseDamage), baseFireRate(baseFireRate),
          texturePath(texturePath), upgradeCost(upgradeCost), rangeUpgradeMultiplier(rangeUpgradeMultiplier),
          damageUpgradeMultiplier(damageUpgradeMultiplier), fireRateUpgradeMultiplier(fireRateUpgradeMultiplier),
          maxLevel(maxLevel), isProjectile(isProjectile), isContinuous(isContinuous), isAreaOfEffect(isAreaOfEffect), areaOfEffectRadius(areaOfEffectRadius),
          slowAmount(slowAmount), slowDuration(slowDuration) {}

};

// Активный враг на поле (текущее состояние и *масштабированные* характеристики для этой волны)
struct ActiveEnemy {
    int typeIndex;
    float currentHealth;
    Vector2 position;
    int currentPathPointIndex;
    float distanceAlongSegment; // Прогресс от начала текущего сегмента пути
    bool alive; // Используется для пометки на удаление
    int id; // Уникальный ID для надежной ссылки из снарядов

    // Масштабированные характеристики для этой конкретной сущности
    float maxScaledHealth;
    float scaledSpeed; // Скорость может тоже масштабироваться
    int scaledReward;

    // Состояние эффектов на враге
    float currentSlowMultiplier; // Текущий множитель скорости (самый сильный примененный)
    float slowDurationTimer;     // Оставшееся время замедления

    // Конструктор, который рассчитывает масштабированные статы
    ActiveEnemy(int typeIndex, Vector2 position, int id, int waveNumber);

    static int nextId; // Для генерации уникальных ID
};
int ActiveEnemy::nextId = 0; // Инициализация статического члена

// Поставленная башня на поле (текущее состояние и *масштабированные* характеристики от прокачки)
struct PlacedTower {
    int typeIndex;
    Vector2 position;
    int level;
    float currentRange;
    float currentDamage; // Урон за выстрел ИЛИ урон в секунду
    float currentFireRate; // Выстрелов в секунду
    float fireCooldown; // Таймер до следующего выстрела

    // Текущие эффекты от башни (для утилит или AoE)
    float currentSlowAmount; // Множитель замедления для этой башни
    float currentAreaOfEffectRadius; // Радиус AoE/зоны этой башни

    // Для непрерывного урона (Лазер): отслеживаем текущую цель
    int currentTargetEnemyId = -1;
    float timeSinceLastTargetSearch = 0.0f; // Таймер для поиска цели (Лазер)
    const float LASER_TARGET_SEARCH_INTERVAL = 0.5f; // Как часто лазер ищет новую цель (секунды)


    // Конструктор, который копирует базовые статы и эффекты из TowerInfo
     PlacedTower(int typeIndex, Vector2 position, int level, const TowerInfo& info)
         : typeIndex(typeIndex), position(position), level(level),
           currentRange(info.baseRange),
           currentDamage(info.baseDamage), // При постройке - базовый урон (DPS для непрерывных/AoE зон)
           currentFireRate(info.baseFireRate), // При постройке - базовая скорость (0 для нестреляющих)
           fireCooldown(0.0f), // Готова стрелять сразу
           currentSlowAmount(info.slowAmount), // При постройке - базовое замедление
           currentAreaOfEffectRadius(info.areaOfEffectRadius) // При постройке - базовый радиус AoE
     {
         // Специальная инициализация для лазера или других типов, если нужно
     }
};

// Состояние игры
struct GameState {
    int money;
    int lives;
    int currentWave; // Текущая волна (начинается с 1 для первой игры, или > gWaves.size() для бесконечных)
    int enemiesSpawnedInWave; // Сколько врагов уже выпустили в текущей волне
    float waveTimer;          // Таймер до следующей волны или до следующего спавна врага
    bool waveInProgress;      // Идет ли текущая волна (выпускаются враги)
    float timeSinceWaveStart; // Время с начала текущей волны

    std::vector<ActiveEnemy> activeEnemies;
    std::vector<PlacedTower> placedTowers;
    std::vector<Projectile> projectiles; // Теперь только для снарядов, которые ЛЕТЯТ

    bool isPaused = false; // Состояние паузы
};

// Состояние UI
struct UIState {
    int selectedTowerIndex = -1; // Индекс выбранной башни для постройки (-1 = ничего)
    int hoveredTowerIndex = -1;  // Индекс башни, на которую наведен курсор
    float towerHoverTimer = 0.0f; // Таймер наведения для инфо окна
    Vector2 mousePosition;
    Vector2 placementPreviewPos; // Позиция голограммы башни
    bool canPlaceTower = false;

    int selectedPlacedTowerIndex = -1; // Индекс поставленной башни для прокачки (-1 = ничего)
    SDL_Rect upgradeWindowRect;       // Прямоугольник окна прокачки
    bool isUpgradeWindowOpen = false;
};

// --- Данные игры (типы врагов, башен, волны) ---

// Определение типов врагов
std::vector<EnemyInfo> gEnemyTypes;

// Определение типов башен (10 штук)
std::vector<TowerInfo> gTowerTypes;

// Определение волн (пример)
struct WaveData {
    struct SpawnEvent {
        int enemyTypeIndex;
        float timeIntoWave; // Время в секундах с начала волны для спавна этого врага
    };
    std::vector<SpawnEvent> spawns;
};
std::vector<WaveData> gWaves;


// --- Глобальные экземпляры состояния ---
GameState gGameState;
UIState gUIState;


// Реализация конструктора ActiveEnemy, который вычисляет масштабированные статы
ActiveEnemy::ActiveEnemy(int typeIndex, Vector2 position, int id, int waveNumber)
    : typeIndex(typeIndex), position(position), id(id),
      currentPathPointIndex(0), distanceAlongSegment(0.0f), alive(true),
      currentSlowMultiplier(1.0f), slowDurationTimer(0.0f) // Инициализация эффектов
{
    // Убедимся, что typeIndex валиден
     if (typeIndex < 0 || typeIndex >= gEnemyTypes.size()) {
         SDL_Log("Error: ActiveEnemy created with invalid typeIndex: %d", typeIndex);
         // Установим минимальные безопасные значения
         maxScaledHealth = 1.0f;
         currentHealth = 1.0f;
         scaledSpeed = 1.0f;
         scaledReward = 1;
         return; // Прерываем конструктор
     }

    // Получаем базовые статы из типа
    const EnemyInfo& info = gEnemyTypes[typeIndex];

    // Рассчитываем множители здоровья и награды в зависимости от номера волны
    float healthMultiplier = 1.0f;
    float rewardMultiplier = 1.0f;

    if (waveNumber == 1) {
         // Специальный множитель для первой волны (4x слабее по здоровью, 25%)
         healthMultiplier = ENEMY_WAVE_1_HEALTH_MULTIPLIER; // 0.25f
         // Награда в первой волне остается базовой
         rewardMultiplier = 1.0f;
    } else if (waveNumber > 1) {
         // Прогрессивное усиление с волны 2 и далее
         // Множитель = (Базовый Множитель) ^ (номер волны - 1)
         // Используем static_cast<float> для pow, чтобы избежать ошибок с целыми типами
         healthMultiplier = std::pow(ENEMY_HEALTH_BASE_SCALE, static_cast<float>(waveNumber - 1));
         rewardMultiplier = std::pow(ENEMY_REWARD_BASE_SCALE, static_cast<float>(waveNumber - 1));
    }
    // Для waveNumber <= 0 (состояние до старта), множители останутся 1.0f

    // Применяем масштабированные статы
    maxScaledHealth = info.baseMaxHealth * healthMultiplier;
    // Убедимся, что здоровье не становится слишком низким из-за множителя первой волны
     if (maxScaledHealth < 1.0f) maxScaledHealth = 1.0f; // Минимальное здоровье

    currentHealth = maxScaledHealth; // Враг появляется с полным здоровьем

    // Скорость может тоже масштабироваться (сейчас просто копируется)
    scaledSpeed = info.baseSpeed;

    scaledReward = static_cast<int>(info.baseReward * rewardMultiplier);
    if (scaledReward <= 0) scaledReward = 1; // Убедимся, что награда не меньше 1
}


// --- Вспомогательные функции ---

// Расчет дистанции между точками
float distance(Vector2 p1, Vector2 p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx*dx + dy*dy);
}

// Нормализация вектора
Vector2 normalize(Vector2 v) {
    float len = std::sqrt(v.x*v.x + v.y*v.y);
    if (len > 0) {
        return {v.x / len, v.y / len};
    }
    return {0, 0};
}

// Получение позиции врага на пути
Vector2 getEnemyPositionOnPath(int pathPointIndex, float distanceAlongSegment) {
    if (pathPointIndex < 0 || pathPointIndex >= PATH_POINT_COUNT) {
        // Некорректный индекс, вернуть последнюю точку или точку начала
         if (PATH_POINT_COUNT > 0) return {(float)PATH_POINTS[std::min(pathPointIndex, PATH_POINT_COUNT - 1)].x, (float)PATH_POINTS[std::min(pathPointIndex, PATH_POINT_COUNT - 1)].y};
         return {0, 0}; // Fallback
    }
     if (pathPointIndex >= PATH_POINT_COUNT - 1) {
        // Враг достиг конца пути или прошел его
        return {(float)PATH_POINTS[PATH_POINT_COUNT - 1].x, (float)PATH_POINTS[PATH_POINT_COUNT - 1].y};
    }


    SDL_Point p1 = PATH_POINTS[pathPointIndex];
    SDL_Point p2 = PATH_POINTS[pathPointIndex + 1];

    Vector2 segmentVector = {(float)(p2.x - p1.x), (float)(p2.y - p1.y)};
    Vector2 segmentDirection = normalize(segmentVector);

    return {p1.x + segmentDirection.x * distanceAlongSegment, p1.y + segmentDirection.y * distanceAlongSegment};
}

// Получение полной длины пройденного пути врагом
float getEnemyPathProgress(const ActiveEnemy& enemy) {
    float totalDistance = 0;
    // Суммируем длины всех завершенных сегментов
    for (int i = 0; i < enemy.currentPathPointIndex; ++i) {
        if (i < PATH_POINT_COUNT - 1) { // Убедиться, что i+1 не выходит за границы
            totalDistance += distance({(float)PATH_POINTS[i].x, (float)PATH_POINTS[i].y}, {(float)PATH_POINTS[i+1].x, (float)PATH_POINTS[i+1].y});
        }
    }
    // Добавляем дистанцию по текущему сегменту
    totalDistance += enemy.distanceAlongSegment;
    return totalDistance;
}

// Рисование круга (для радиуса башни) - только контур
void drawCircle(SDL_Renderer* renderer, Vector2 center, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int x = radius;
    int y = 0;
    int err = 0; // Decision parameter

    while (x >= y) {
        // Draw points in all 8 octants
        SDL_RenderDrawPoint(renderer, (int)center.x + x, (int)center.y + y);
        SDL_RenderDrawPoint(renderer, (int)center.x + y, (int)center.y + x);
        SDL_RenderDrawPoint(renderer, (int)center.x - y, (int)center.y + x);
        SDL_RenderDrawPoint(renderer, (int)center.x - x, (int)center.y + y);
        SDL_RenderDrawPoint(renderer, (int)center.x - x, (int)center.y - y);
        SDL_RenderDrawPoint(renderer, (int)center.x - y, (int)center.y - x);
        SDL_RenderDrawPoint(renderer, (int)center.x + y, (int)center.y - x);
        SDL_RenderDrawPoint(renderer, (int)center.x + x, (int)center.y - y);

        y++;
        err += 1 + 2*y;
        if (2*(err - x) + 1 > 0) {
            x--;
            err += 1 - 2*x;
        }
    }
}


// Рисование заполненного круга (для радиуса башни)
void drawFilledCircle(SDL_Renderer* renderer, Vector2 center, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int dy = -radius; dy <= radius; dy++) { // Iterate from -radius to +radius
        // Ensure dx is non-negative
        int dx = static_cast<int>(std::sqrt(std::max(0.0, (double)radius*radius - dy*dy)));
        // Draw horizontal line segment for this y
        SDL_RenderDrawLine(renderer, (int)center.x - dx, (int)center.y + dy, (int)center.x + dx, (int)center.y + dy);
    }
}


// Проверка, можно ли поставить башню в данную точку (очень упрощенно)
bool isValidPlacement(Vector2 pos) {
    // Проверка, что не на полосе выбора башен
    if (pos.y < TOWER_SELECTION_BAR_HEIGHT) return false;

     // Проверка, что находится в пределах игровой области (ниже UI бара)
     if (pos.x < 0 || pos.x > SCREEN_WIDTH || pos.y > SCREEN_HEIGHT) return false;


    // Проверка, что не слишком близко к точкам пути (можно сделать более точную проверку столкновения с сегментами)
    for (int i = 0; i < PATH_POINT_COUNT; ++i) {
        if (distance(pos, {(float)PATH_POINTS[i].x, (float)PATH_POINTS[i].y}) < 30) { // Магическое число 30 - радиус вокруг точки пути
            return false;
        }
    }

    // Проверка, что не пересекается с другими башнями (тоже грубо, по центрам)
    for (const auto& tower : gGameState.placedTowers) {
         if (distance(pos, tower.position) < 40) { // Магическое число 40 - радиус башни
             return false;
         }
    }

    // TODO: Более сложная проверка: не накладывается ли на сегменты пути, не блокирует ли проход.
    // Для этого примера это пропущено.

    return true;
}


// --- Инициализация игры ---
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        SDL_Log("Warning: Linear texture filtering not enabled!");
    }

    // Create window (Fullscreen)
    gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (gWindow == nullptr) {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    // Create renderer with VSync
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    // Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND); // Для прозрачности

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_Log("SDL_image could not initialize! SDL_image Error: %s", IMG_GetError());
        return false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s", TTF_GetError());
        return false;
    }

    // Load font
    gFont = TTF_OpenFont(FONT_PATH, 20); // Основной шрифт
    if (gFont == nullptr) {
        SDL_Log("Failed to load font %s! SDL_ttf Error: %s", FONT_PATH, TTF_GetError());
        // Не фатальная ошибка для этого примера, но текст не будет отображаться
    }
    gFontSmall = TTF_OpenFont(FONT_PATH, 16); // Меньший шрифт
     if (gFontSmall == nullptr) {
         SDL_Log("Failed to load small font %s! SDL_ttf Error: %s", FONT_PATH, TTF_GetError());
          // Если маленький шрифт не загрузился, используем основной
         gFontSmall = gFont;
     }


    // setlocale(LC_NUMERIC, "C"); // Опционально: гарантировать десятичную точку в to_string для float

    return true;
}

// Загрузка игровых ресурсов (текстур и определение данных)
void loadGameData() {
    // Очищаем предыдущие данные и текстуры перед загрузкой (если init вызывается повторно)
    // Но в этой структуре main, init и loadGameData вызываются только один раз
    // Очистка текстур происходит в close()

    // Определение типов врагов (базовые характеристики)
    gEnemyTypes.emplace_back("Медленный Танк", 200.0f, 50.0f, 20, "enemy_slow.png"); // Медленный, живучий
    gEnemyTypes.emplace_back("Быстрый Жук", 50.0f, 150.0f, 10, "enemy_fast.png");   // Быстрый, слабый

    // Загрузка текстур врагов после их определения
    for (auto& enemyInfo : gEnemyTypes) {
        enemyInfo.texture = loadTexture(enemyInfo.texturePath);
         if (enemyInfo.texture == nullptr) {
              SDL_Log("Warning: Failed to load texture for enemy %s from %s. Using placeholder.", enemyInfo.name.c_str(), enemyInfo.texturePath.c_str());
         }
    }

    // Загрузка текстуры снаряда (пример)
    gTextures["projectile"] = loadTexture("projectile.png");
     if (gTextures["projectile"] == nullptr) {
         SDL_Log("Warning: Failed to load projectile texture. Using placeholder.");
          // Создаем простую текстуру для примера (если нет файла)
          SDL_Surface* surf_projectile = SDL_CreateRGBSurface(0, 8, 8, 32, 0, 0, 0, 0);
          SDL_FillRect(surf_projectile, NULL, SDL_MapRGBA(surf_projectile->format, 255, 255, 0, 255)); // Используем MapRGBA для альфа
          gTextures["projectile"] = SDL_CreateTextureFromSurface(gRenderer, surf_projectile);
          SDL_FreeSurface(surf_projectile);
     }
     // Загрузка текстуры для лазера (например, тонкая белая линия?) - рисовать будем линией
     gTextures["laser_beam"] = nullptr;


    // Определение типов башен (10 штук)
    // TowerInfo(name, description, cost, baseRange, baseDamage, baseFireRate, texturePath, upgradeCost, rangeMult, damageMult, fireRateMult, maxLevel, isProjectile, isContinuous, isAreaOfEffect, areaOfEffectRadius, slowAmount, slowDuration)
    gTowerTypes.emplace_back("Пушка", "Базовая башня с хорошим уроном.", 100, 150.0f, 20.0f, 1.0f, "tower_gun.png", 50, 1.1f, 1.2f, 0.9f); // Проектил, одиночная
    gTowerTypes.emplace_back("Пулемет", "Высокая скорость атаки, низкий урон.", 150, 120.0f, 8.0f, 5.0f, "tower_minigun.png", 70, 1.05f, 1.1f, 0.8f); // Проектил, одиночная
    gTowerTypes.emplace_back("Снайпер", "Высокий урон, низкая скорость, большая дальность.", 200, 250.0f, 50.0f, 0.5f, "tower_sniper.png", 100, 1.15f, 1.3f, 0.95f); // Проектил, одиночная
    gTowerTypes.emplace_back("Ледышка", "Наносит небольшой урон и замедляет врагов.", 120, 130.0f, 5.0f, 1.5f, "tower_ice.png", 60, 1.08f, 1.05f, 0.85f, 5, true, false, false, 0.0f, 0.6f, 2.0f); // Проектил, одиночная, замедление 60% (скорость * 0.6) на 2 секунды
    gTowerTypes.emplace_back("Огнемет", "Наносит урон огнем по области.", 180, 100.0f, 30.0f, 0.0f, "tower_flame.png", 90, 1.0f, 1.15f, 1.0f, 5, false, false, true, 40.0f); // НЕ Проектил, НЕ Непрерывный, AoE, радиус 40. baseDamage теперь DPS.
    gTowerTypes.emplace_back("Тесла", "Бьет молнией по нескольким целям.", 250, 160.0f, 30.0f, 0.8f, "tower_tesla.png", 120, 1.1f, 1.25f, 0.92f); // TODO: Multiple target logic needed (currently acts like gun)
    gTowerTypes.emplace_back("Миномет", "Медленно стреляет по дальней цели, урон по области.", 220, 300.0f, 40.0f, 0.4f, "tower_mortar.png", 110, 1.2f, 1.35f, 0.98f, 5, true, false, true, 50.0f); // Проектил, AoE радиус 50, TODO: Far target priority logic needed
    gTowerTypes.emplace_back("Шипы", "Наносит урон врагам, проходящим по ним. Ставится на путь.", 50, 0.0f, 10.0f, 0.0f, "tower_spikes.png", 30, 0.0f, 1.5f, 0.0f, 1, false, false, false, 0.0f); // НЕ Проектил, НЕ Непрерывный. TODO: Damage on contact logic
    gTowerTypes.emplace_back("Болото", "Сильно замедляет врагов в области.", 70, 60.0f, 0.0f, 0.0f, "tower_swamp.png", 40, 1.1f, 0.0f, 1.0f, 3, false, false, true, 60.0f, 0.4f, 0.5f); // НЕ Проектил, НЕ Непрерывный, AoE зона замедления 40% (скорость * 0.4), радиус 60. slowDuration - время обновления эффекта зоны.
    gTowerTypes.emplace_back("Лазер", "Непрерывно наносит высокий урон одиночной цели.", 400, 80.0f, 0.0f, 0.0f, "tower_laser.png", 200, 1.1f, 1.2f, 1.0f, 5, false, true, false, 0.0f); // НЕ Проектил, Непрерывный, одиночная цель. baseDamage теперь DPS. baseFireRate = 0.0f
    // Увеличим урон лазера при прокачке только damage
    gTowerTypes.back().rangeUpgradeMultiplier = 1.1f; // Лазер прокачивает дальность
    gTowerTypes.back().damageUpgradeMultiplier = 1.2f;
    gTowerTypes.back().fireRateUpgradeMultiplier = 1.0f; // Непрерывный урон не имеет скорости атаки

    // Загрузка текстур башен после их определения
    for (auto& towerInfo : gTowerTypes) {
        towerInfo.texture = loadTexture(towerInfo.texturePath);
         if (towerInfo.texture == nullptr) {
             SDL_Log("Warning: Failed to load texture for tower %s from %s. Using placeholder.", towerInfo.name.c_str(), towerInfo.texturePath.c_str());
         }
    }


    // Определение волн (пример) - Это *шаблоны* волн. После последней волны будем повторять последний шаблон.
    gWaves.resize(5); // Пример 5 стартовых волн

    // Волна 1: Медленные враги
    gWaves[0].spawns.push_back({0, 0.5f}); // type 0, 0.5 сек
    gWaves[0].spawns.push_back({0, 1.5f});
    gWaves[0].spawns.push_back({0, 2.5f});
    gWaves[0].spawns.push_back({0, 3.5f});
    gWaves[0].spawns.push_back({0, 4.5f});

    // Волна 2: Быстрые враги
    gWaves[1].spawns.push_back({1, 0.2f}); // type 1, 0.2 сек
    gWaves[1].spawns.push_back({1, 0.4f});
    gWaves[1].spawns.push_back({1, 0.6f});
    gWaves[1].spawns.push_back({1, 0.8f});
    gWaves[1].spawns.push_back({1, 1.0f});
    gWaves[1].spawns.push_back({1, 1.2f});
    gWaves[1].spawns.push_back({1, 1.4f});
    gWaves[1].spawns.push_back({1, 1.6f});
    gWaves[1].spawns.push_back({1, 1.8f});
    gWaves[1].spawns.push_back({1, 2.0f});

    // Волна 3: Смесь
    gWaves[2].spawns.push_back({0, 0.5f});
    gWaves[2].spawns.push_back({1, 1.0f});
    gWaves[2].spawns.push_back({0, 1.5f});
    gWaves[2].spawns.push_back({1, 2.0f});
    gWaves[2].spawns.push_back({0, 2.5f});
    gWaves[2].spawns.push_back({1, 3.0f});

    // Волна 4: Больше медленных
    gWaves[3].spawns.push_back({0, 0.5f});
    gWaves[3].spawns.push_back({0, 1.0f});
    gWaves[3].spawns.push_back({0, 1.5f});
    gWaves[3].spawns.push_back({0, 2.0f});
    gWaves[3].spawns.push_back({0, 2.5f});
    gWaves[3].spawns.push_back({0, 3.0f});
    gWaves[3].spawns.push_back({0, 3.5f});
    gWaves[3].spawns.push_back({0, 4.0f});
    gWaves[3].spawns.push_back({0, 4.5f});
    gWaves[3].spawns.push_back({0, 5.0f});

    // Волна 5: Больше быстрых и немного медленных
    gWaves[4].spawns.push_back({1, 0.2f});
    gWaves[4].spawns.push_back({1, 0.4f});
    gWaves[4].spawns.push_back({1, 0.6f});
    gWaves[4].spawns.push_back({1, 0.8f});
    gWaves[4].spawns.push_back({1, 1.0f});
    gWaves[4].spawns.push_back({1, 1.2f});
    gWaves[4].spawns.push_back({1, 1.4f});
    gWaves[4].spawns.push_back({1, 1.6f});
    gWaves[4].spawns.push_back({1, 1.8f});
    gWaves[4].spawns.push_back({1, 2.0f});
    gWaves[4].spawns.push_back({0, 2.5f});
    gWaves[4].spawns.push_back({0, 3.5f});

    // Характеристики врагов масштабируются при их создании в update(),
    // поэтому EnemyInfo содержит только базовые статы.
}

// Сброс состояния игры
void resetGame() {
    gGameState.money = STARTING_MONEY;
    gGameState.lives = BASE_LIVES;
    gGameState.currentWave = 0; // Начинаем с волны 0. Первая игра начнется с таймера до волны 1.
    gGameState.enemiesSpawnedInWave = 0;
    gGameState.waveTimer = TIME_BETWEEN_WAVES;
    gGameState.waveInProgress = false;
    gGameState.timeSinceWaveStart = 0.0f;
    gGameState.isPaused = false; // Сброс паузы при рестарте

    gGameState.activeEnemies.clear();
    gGameState.placedTowers.clear();
    gGameState.projectiles.clear();

    gUIState.selectedTowerIndex = -1;
    gUIState.hoveredTowerIndex = -1;
    gUIState.towerHoverTimer = 0.0f;
    gUIState.selectedPlacedTowerIndex = -1;
    gUIState.isUpgradeWindowOpen = false;

    ActiveEnemy::nextId = 0; // Сброс счетчика ID врагов

    // Типы врагов, башен и волн загружаются один раз в loadGameData и не сбрасываются здесь.
    // Если бы их характеристики менялись в процессе игры (не только масштабировались),
    // тогда пришлось бы их перезагружать или иметь копии.
    // Также нужно будет сбросить модификаторы характеристик врагов, если они менялись в EnemyInfo
    // Но сейчас они не меняются в loadGameData после первого определения.
}


// Очистка ресурсов
void close() {
    // Очищаем текстуры, загруженные вручную (например, снаряд)
    freeTextures();

    // Очищаем текстуры, загруженные в структурах типов врагов и башен
    // Делаем это в цикле, чтобы освободить каждую текстуру
    for(auto& enemyInfo : gEnemyTypes) {
        if (enemyInfo.texture) {
            SDL_DestroyTexture(enemyInfo.texture);
            enemyInfo.texture = nullptr; // Устанавливаем в nullptr после освобождения
        }
    }
    // gEnemyTypes.clear(); // Очищать сам вектор типов не нужно, он может понадобиться при следующем запуске игры

     for(auto& towerInfo : gTowerTypes) {
        if (towerInfo.texture) {
            SDL_DestroyTexture(towerInfo.texture);
            towerInfo.texture = nullptr; // Устанавливаем в nullptr после освобождения
        }
    }
    // gTowerTypes.clear(); // Очищать сам вектор типов не нужно

    // Теперь очищаем данные волн, если они были изменены (хотя в этом примере они константы)
    // gWaves.clear(); // Не нужно, если WaveData константы

    if (gFont) {
        TTF_CloseFont(gFont);
        gFont = nullptr;
    }
     if (gFontSmall) {
        TTF_CloseFont(gFontSmall);
        gFontSmall = nullptr;
    }


    TTF_Quit();
    IMG_Quit();

    if (gRenderer) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = nullptr;
    }
    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }

    SDL_Quit();
}

// --- Обработка ввода ---
void handleInput(SDL_Event& e) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    gUIState.mousePosition = {(float)mouseX, (float)mouseY};

    // Проверка, ушла ли мышка за пределы окна прокачки, чтобы закрыть его (при движении мыши)
    // Делаем это до обработки кликов, чтобы клик вне окна закрыл его.
    if (e.type == SDL_MOUSEMOTION) {
         if (gUIState.isUpgradeWindowOpen) {
             // Проверяем, находится ли курсор внутри прямоугольника окна прокачки.
             bool mouseInsideUpgradeWindow = (mouseX >= gUIState.upgradeWindowRect.x && mouseX < gUIState.upgradeWindowRect.x + gUIState.upgradeWindowRect.w &&
                                            mouseY >= gUIState.upgradeWindowRect.y && mouseY < gUIState.upgradeWindowRect.y + gUIState.upgradeWindowRect.h);
             if (!mouseInsideUpgradeWindow) {
                 gUIState.isUpgradeWindowOpen = false;
                 gUIState.selectedPlacedTowerIndex = -1;
             }
         }

         // Обновление позиции голограммы башни при движении мыши, если башня выбрана для постройки
         if (gUIState.selectedTowerIndex != -1) {
             gUIState.placementPreviewPos = {(float)mouseX, (float)mouseY};
             gUIState.canPlaceTower = isValidPlacement(gUIState.placementPreviewPos);
         }
    }


    // Проверка наведения на карточки башен (при движении мыши)
    if (e.type == SDL_MOUSEMOTION) {
         int oldHoveredIndex = gUIState.hoveredTowerIndex;
         gUIState.hoveredTowerIndex = -1; // Сброс наведения

         // Проверяем, находится ли мышь в области карточек башен
         if (mouseY >= TOWER_CARD_PADDING && mouseY < TOWER_CARD_PADDING + TOWER_CARD_HEIGHT) {
             for (int i = 0; i < gTowerTypes.size(); ++i) {
                 // Объявляем cardRect локально в этом цикле
                 SDL_Rect cardRect = {
                     TOWER_CARD_PADDING + i * (TOWER_SLOT_TOTAL_WIDTH), // Используем TOWER_SLOT_TOTAL_WIDTH
                     TOWER_CARD_PADDING,
                     TOWER_CARD_WIDTH, // Используем TOWER_CARD_WIDTH
                     TOWER_CARD_HEIGHT
                 };
                 // Проверяем, наведена ли мышь на конкретную карточку
                 if (mouseX >= cardRect.x && mouseX < cardRect.x + cardRect.w &&
                     mouseY >= cardRect.y && mouseY < cardRect.y + cardRect.h) {
                     gUIState.hoveredTowerIndex = i;
                     break; // Найдена карточка, на которую наведен курсор
                 }
             }
         }
          // Сброс таймера, если наведение изменилось или прекратилось
          if (gUIState.hoveredTowerIndex != oldHoveredIndex) {
              gUIState.towerHoverTimer = 0.0f;
          }
    }


    // Обработка кликов мыши
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {

            // Приоритет: если окно прокачки открыто, обрабатываем только клики внутри него
            if (gUIState.isUpgradeWindowOpen) {
                 // Проверка клика внутри прямоугольника окна прокачки.
                 if (mouseX >= gUIState.upgradeWindowRect.x && mouseX < gUIState.upgradeWindowRect.x + gUIState.upgradeWindowRect.w &&
                     mouseY >= gUIState.upgradeWindowRect.y && mouseY < gUIState.upgradeWindowRect.y + gUIState.upgradeWindowRect.h) {
                     // Клик внутри окна прокачки - просто ничего не делаем, окно остается открытым.
                     return;
                 }
                 // Клик вне окна прокачки уже обработан в MOUSEMOTION для закрытия.
                 // Если мы дошли сюда, значит окно было открыто, но клик был вне его,
                 // и оно УЖЕ закрылось в MOUSEMOTION. Теперь можно обрабатывать клик по полю.
            }


            // 1. Обработка клика по карточке башни для выбора постройки
            // Делаем это, только если НЕ выбрана башня для прокачки (или окно прокачки только что закрылось)
            if (!gUIState.isUpgradeWindowOpen) {
                if (mouseY >= TOWER_CARD_PADDING && mouseY < TOWER_CARD_PADDING + TOWER_CARD_HEIGHT) {
                     for (int i = 0; i < gTowerTypes.size(); ++i) {
                         SDL_Rect cardRect = { // Используем cardRect из рендеринга карточек
                             TOWER_CARD_PADDING + i * (TOWER_SLOT_TOTAL_WIDTH), // Используем TOWER_SLOT_TOTAL_WIDTH
                             TOWER_CARD_PADDING,
                             TOWER_CARD_WIDTH, // Используем TOWER_CARD_WIDTH
                             TOWER_CARD_HEIGHT
                         };
                         if (mouseX >= cardRect.x && mouseX < cardRect.x + cardRect.w &&
                             mouseY >= cardRect.y && mouseY < cardRect.y + cardRect.h) {

                             // Если уже выбрана та же башня, отменить выбор
                             if (gUIState.selectedTowerIndex == i) {
                                 gUIState.selectedTowerIndex = -1; // Сброс выбора
                             } else {
                                 // Сбрасываем предыдущий выбор, если был другой
                                 gUIState.selectedTowerIndex = -1;
                                 gUIState.selectedPlacedTowerIndex = -1; // Убедимся, что не выбрана placed башня


                                 if (gGameState.money >= gTowerTypes[i].cost) {
                                     gUIState.selectedTowerIndex = i; // Выбрали башню для постройки
                                     gUIState.placementPreviewPos = {(float)mouseX, (float)mouseY};
                                     gUIState.canPlaceTower = isValidPlacement(gUIState.placementPreviewPos);
                                 } else {
                                     SDL_Log("Not enough money to build %s! Cost: %d", gTowerTypes[i].name.c_str(), gTowerTypes[i].cost); // TODO: Отобразить в UI
                                     // Оставляем selectedTowerIndex = -1
                                 }
                             }
                             return; // Обработали клик по карточке
                         }
                     }
                }
            }


            // 2. Обработка клика для постройки башни (если башня выбрана)
            if (gUIState.selectedTowerIndex != -1 && !gUIState.isUpgradeWindowOpen) { // Убедимся, что башня выбрана И окно прокачки не открыто
                Vector2 placementPos = {(float)mouseX, (float)mouseY};
                // Проверка на то, что клик не на UI панели выбора башен
                if (placementPos.y >= TOWER_SELECTION_BAR_HEIGHT) {
                    if (isValidPlacement(placementPos)) {
                         // Проверка на выход за границы вектора gTowerTypes на всякий случай
                         if (gUIState.selectedTowerIndex >= 0 && gUIState.selectedTowerIndex < gTowerTypes.size()) {
                             const TowerInfo& selectedInfo = gTowerTypes[gUIState.selectedTowerIndex];
                            // Проверка денег уже была при клике на карточку, но делаем еще раз на всякий случай
                            if (gGameState.money >= selectedInfo.cost) {
                                gGameState.money -= selectedInfo.cost;
                                gGameState.placedTowers.push_back( // Используем push_back с явным конструктором PlacedTower
                                    PlacedTower(
                                        gUIState.selectedTowerIndex,
                                        placementPos,
                                        1, // level
                                        selectedInfo // Передаем TowerInfo для инициализации текущих статов
                                    )
                                );
                                 SDL_Log("Built %s at (%.0f, %.0f). Money: %d", selectedInfo.name.c_str(), placementPos.x, placementPos.y, gGameState.money);
                                gUIState.selectedTowerIndex = -1; // Сброс выбора после постройки
                            } else {
                                 SDL_Log("Error: Not enough money to build!"); // Должно было быть проверено раньше
                                 gUIState.selectedTowerIndex = -1; // Сброс выбора
                            }
                         } else {
                              SDL_Log("Error: Invalid selected tower index!");
                              gUIState.selectedTowerIndex = -1; // Сброс выбора
                         }
                    } else {
                         // Kликнули для постройки, но место не валидно. Отменить выбор?
                         // gUIState.selectedTowerIndex = -1; // Можно сбросить
                         SDL_Log("Invalid tower placement!"); // TODO: Отобразить в UI
                    }
                    return; // Обработали клик по полю (при попытке постройки)
                } // else: клик на верхней панели при выбранной башне - игнорируем или отменяем? Сейчас игнорируем.
            }

            // 3. Обработка клика по уже стоящей башне для открытия окна прокачки
            // Делаем это, только если НИЧЕГО не выбрано для постройки и окно прокачки закрыто
            if (gUIState.selectedTowerIndex == -1 && !gUIState.isUpgradeWindowOpen) {
                for (size_t i = 0; i < gGameState.placedTowers.size(); ++i) {
                    const auto& tower = gGameState.placedTowers[i];
                    // Простая проверка клика на радиус вокруг центра башни
                    if (distance(gUIState.mousePosition, tower.position) < 20) { // Магическое число 20 - радиус башни для клика
                        gUIState.selectedPlacedTowerIndex = i;
                        gUIState.isUpgradeWindowOpen = true;
                        // Определить позицию окна прокачки (например, справа от башни)
                        gUIState.upgradeWindowRect = {
                            (int)tower.position.x + 30, (int)tower.position.y - 50, // Примерное смещение
                            200, 200 // Размер окна увеличен
                        };
                        // Корректировка позиции окна, чтобы не выходило за границы экрана
                        if (gUIState.upgradeWindowRect.x + gUIState.upgradeWindowRect.w > SCREEN_WIDTH) {
                            gUIState.upgradeWindowRect.x = (int)tower.position.x - gUIState.upgradeWindowRect.w - 30;
                        }
                         if (gUIState.upgradeWindowRect.y < TOWER_SELECTION_BAR_HEIGHT) {
                            gUIState.upgradeWindowRect.y = TOWER_SELECTION_BAR_HEIGHT + 10;
                         }
                         if (gUIState.upgradeWindowRect.y + gUIState.upgradeWindowRect.h > SCREEN_HEIGHT) {
                            gUIState.upgradeWindowRect.y = SCREEN_HEIGHT - gUIState.upgradeWindowRect.h - 10;
                         }

                        return; // Обработали клик по башне
                    }
                }
            }
        } // End of left click
         else if (e.button.button == SDL_BUTTON_RIGHT) {
             // Отмена выбора башни для постройки
             if (gUIState.selectedTowerIndex != -1) {
                 gUIState.selectedTowerIndex = -1;
                 SDL_Log("Tower placement cancelled.");
             }
             // Отмена выбора башни для прокачки и закрытие окна (если открыто)
             if (gUIState.isUpgradeWindowOpen) {
                  gUIState.isUpgradeWindowOpen = false;
                  gUIState.selectedPlacedTowerIndex = -1;
                  SDL_Log("Upgrade window closed.");
             }
         }
    } // End of mouse button down

    // Обработка нажатия клавиш
    if (e.type == SDL_KEYDOWN) {
        // Пауза по клавише P
        if (e.key.keysym.sym == SDLK_p || e.key.keysym.sym == SDLK_ESCAPE) {
            gGameState.isPaused = !gGameState.isPaused;
            SDL_Log("Game Paused: %s", gGameState.isPaused ? "True" : "False");
            // При постановке на паузу, закрываем окна UI
            if (gGameState.isPaused) {
                 gUIState.selectedTowerIndex = -1;
                 gUIState.selectedPlacedTowerIndex = -1;
                 gUIState.isUpgradeWindowOpen = false;
                 gUIState.hoveredTowerIndex = -1; // Сброс наведения тоже
                 gUIState.towerHoverTimer = 0.0f;
            }
             // Если снимаем с паузы, может быть полезно сбросить таймер волны немного,
             // чтобы не спавнились сразу куча врагов, если игра долго стояла на паузе.
             // Не будем делать это пока для простоты.
        }

        // Прокачка по клавише Space, если окно прокачки открыто и мышь над окном
        if (e.key.keysym.sym == SDLK_SPACE) {
            SDL_Log("Space pressed."); // Debug log
            if (gUIState.isUpgradeWindowOpen && gUIState.selectedPlacedTowerIndex != -1 && gUIState.selectedPlacedTowerIndex < gGameState.placedTowers.size()) {
                SDL_Log("Upgrade window open, tower selected."); // Debug log
                // Проверяем, находится ли курсор над прямоугольником окна прокачки
                int mouseX_check, mouseY_check;
                SDL_GetMouseState(&mouseX_check, &mouseY_check);
                 SDL_Rect checkRect = gUIState.upgradeWindowRect; // Создаем копию для проверки

                if (mouseX_check >= checkRect.x && mouseX_check < checkRect.x + checkRect.w &&
                    mouseY_check >= checkRect.y && mouseY_check < checkRect.y + checkRect.h) {
                    SDL_Log("Mouse over upgrade window."); // Debug log

                    PlacedTower& tower = gGameState.placedTowers[gUIState.selectedPlacedTowerIndex];
                    if (tower.typeIndex >= 0 && tower.typeIndex < gTowerTypes.size()) {
                        const TowerInfo& info = gTowerTypes[tower.typeIndex];
                         SDL_Log("Tower type info valid."); // Debug log

                        if (tower.level < info.maxLevel) { // Проверка макс уровня
                             SDL_Log("Tower not max level (%d/%d).", tower.level, info.maxLevel); // Debug log
                            if (gGameState.money >= info.upgradeCost) {
                                SDL_Log("Enough money (%d) for upgrade cost (%d). Upgrading...", gGameState.money, info.upgradeCost); // Debug log
                                gGameState.money -= info.upgradeCost;
                                tower.level++;
                                // Применяем множители прокачки к текущим статам
                                tower.currentRange *= info.rangeUpgradeMultiplier;
                                tower.currentDamage *= info.damageUpgradeMultiplier; // Для DPS тоже умножаем
                                // fireRateUpgradeMultiplier < 1.0f ускоряет, значит, делим currentFireRate (только для стреляющих)
                                if (info.isProjectile && info.fireRateUpgradeMultiplier > 0) {
                                     tower.currentFireRate /= info.fireRateUpgradeMultiplier; // Увеличиваем скорость атаки
                                }
                                // Прокачка эффектов (если есть) - применяем множитель к текущим эффектам
                                // Замедление: множитель прокачки FireRateMult < 1.0f делает замедление сильнее
                                if (info.slowAmount < 1.0f && info.fireRateUpgradeMultiplier > 0) {
                                     tower.currentSlowAmount /= info.fireRateUpgradeMultiplier;
                                     // Убедимся, что замедление не становится слишком сильным (например, < 0.1f множитель)
                                     if (tower.currentSlowAmount < 0.1f) tower.currentSlowAmount = 0.1f; // Макс 90% замедление
                                }
                                // Радиус AoE/эффекта прокачивается множителем RangeMult
                                if (info.isAreaOfEffect && info.areaOfEffectRadius > 0 && info.rangeUpgradeMultiplier != 1.0f) {
                                     tower.currentAreaOfEffectRadius *= info.rangeUpgradeMultiplier;
                                }


                                SDL_Log("Tower %s upgraded to level %d!", info.name.c_str(), tower.level);
                            } else {
                                SDL_Log("Not enough money (%d) for upgrade cost (%d)!", gGameState.money, info.upgradeCost); // Debug log
                            }
                        } else {
                            SDL_Log("Tower is already max level (%d)!", tower.level); // Debug log
                        }
                    } else {
                         SDL_Log("Error: Invalid selected placed tower type index!"); // Debug log
                    }
                } else {
                     SDL_Log("Mouse not over upgrade window."); // Debug log
                }
            } else {
                 SDL_Log("Upgrade window not open or no tower selected."); // Debug log
            }
        }
    }
}


// --- Обновление состояния игры ---
void update(float deltaTime) {
    // Проверка проигрыша
    if (gGameState.lives <= 0) {
        SDL_Log("Game Over! You lost.");
        resetGame(); // Перезапуск или переход в другое состояние
        return;
    }
    // Условие победы убрано для бесконечных волн

    // Если игра на паузе, обновляем только UI таймеры (наведения), остальное пропускаем
    if (gGameState.isPaused) {
         // Обновление таймера наведения UI (остается активным на паузе)
         if (gUIState.hoveredTowerIndex != -1) {
             gUIState.towerHoverTimer += deltaTime;
         } else {
             gUIState.towerHoverTimer = 0.0f; // Сброс, если нет наведения
         }
         return; // Выходим из update, если на паузе
    }


    // Обновление таймера волны / Спавн врагов
    if (!gGameState.waveInProgress) {
        gGameState.waveTimer -= deltaTime;
        if (gGameState.waveTimer <= 0.0f) {
            // Начать новую волну
            gGameState.currentWave++; // Увеличиваем номер волны
            SDL_Log("Starting Wave %d", gGameState.currentWave);
            gGameState.waveInProgress = true;
            gGameState.timeSinceWaveStart = 0.0f; // Сброс таймера волны
            gGameState.enemiesSpawnedInWave = 0; // Сброс счетчика заспавненных врагов в этой волне
        }
    }

    // Логика спавна врагов по событиям из WaveData
    if (gGameState.waveInProgress) {
         // Определяем, какой шаблон волны использовать.
         // Для волн до gWaves.size(), используем соответствующий шаблон.
         // Для волн после, используем шаблон последней определенной волны (если есть)
         WaveData* currentWaveData = nullptr;
         if (!gWaves.empty()) {
             int waveIndex = (gGameState.currentWave > 0 && gGameState.currentWave <= gWaves.size()) ?
                             (gGameState.currentWave - 1) : // Для первых N волн используем индекс N-1
                             (gWaves.size() - 1);          // Для волн > N, используем индекс последней волны

             // Проверяем, что индекс шаблона валиден
             if (waveIndex >= 0 && waveIndex < gWaves.size()) {
                 currentWaveData = &gWaves[waveIndex];
             } else {
                 // Этого не должно произойти, если gWaves не пуст и логика выше корректна
                 SDL_Log("Error: Calculated invalid wave template index: %d for wave %d", waveIndex, gGameState.currentWave);
             }
         }

         if (currentWaveData != nullptr) {
             gGameState.timeSinceWaveStart += deltaTime;

             // Проверяем события спавна, которые должны произойти к текущему времени
             while(gGameState.enemiesSpawnedInWave < currentWaveData->spawns.size()) {
                 const auto& spawnEvent = currentWaveData->spawns[gGameState.enemiesSpawnedInWave];
                 if (gGameState.timeSinceWaveStart >= spawnEvent.timeIntoWave) {
                     // Время для спавна этого врага пришло
                     int enemyTypeIndex = spawnEvent.enemyTypeIndex;
                     if (enemyTypeIndex >= 0 && enemyTypeIndex < gEnemyTypes.size()) {
                         // Создаем врага с масштабированными статами на основе текущего номера волны
                         gGameState.activeEnemies.push_back( // Используем push_back с явным конструктором ActiveEnemy
                             ActiveEnemy(
                                 enemyTypeIndex,
                                 {(float)PATH_POINTS[0].x, (float)PATH_POINTS[0].y},
                                 ActiveEnemy::nextId++, // Уникальный ID для снарядов
                                 gGameState.currentWave // Передаем номер текущей волны для расчета статов
                             )
                         );
                         // SDL_Log("Spawning enemy type %d (ID %d) for wave %d", enemyTypeIndex, gGameState.activeEnemies.back().id, gGameState.currentWave);
                         gGameState.enemiesSpawnedInWave++;
                     } else {
                         SDL_Log("Error: Invalid enemy type index (%d) in wave data for wave %d", enemyTypeIndex, gGameState.currentWave);
                         gGameState.enemiesSpawnedInWave++; // Пропускаем некорректный спавн
                     }
                 } else {
                     // Следующий спавн еще не должен произойти
                     break; // Выходим из while, остальные спавны позже
                 }
             }

            // Проверка, завершен ли выпуск врагов из текущего шаблона волны И убиты ли все активные враги
            if (gGameState.enemiesSpawnedInWave >= currentWaveData->spawns.size() && gGameState.activeEnemies.empty()) {
                 // Все враги из этого *шаблона* волны выпущены И убиты
                 gGameState.waveInProgress = false;
                 gGameState.waveTimer = TIME_BETWEEN_WAVES; // Начать отсчет до следующей волны
                 SDL_Log("Wave %d finished. Next wave (%d) in %.1f seconds.", gGameState.currentWave, gGameState.currentWave + 1, TIME_BETWEEN_WAVES);
            } else if (gGameState.enemiesSpawnedInWave >= currentWaveData->spawns.size() && !gGameState.activeEnemies.empty()) {
                 // Все враги из этого шаблона волны выпущены, но еще не убиты
                 // Остаемся в waveInProgress = true и ждем, пока все враги умрут.
            }
         } else if (gGameState.activeEnemies.empty()) {
              // Нет определенных волн И нет врагов на поле (крайний случай)
              // Запустить следующую волну сразу? Или что-то еще?
              // Для простоты, если волн нет, ничего не спавним.
         }
    }

    // --- Обновление состояний врагов (движение, эффекты) ---
    // Удаляем мертвых врагов в начале, чтобы не обновлять их
    gGameState.activeEnemies.erase(
        std::remove_if(gGameState.activeEnemies.begin(), gGameState.activeEnemies.end(),
                       [](const ActiveEnemy& e){ return !e.alive; }),
        gGameState.activeEnemies.end()
    );

    for (auto& enemy : gGameState.activeEnemies) {
        // Обновление таймера замедления
        if (enemy.slowDurationTimer > 0) {
            enemy.slowDurationTimer -= deltaTime;
            if (enemy.slowDurationTimer <= 0) {
                enemy.currentSlowMultiplier = 1.0f; // Замедление закончилось
            }
        }

        // Скорость врага с учетом замедления
        float effectiveEnemySpeed = enemy.scaledSpeed * enemy.currentSlowMultiplier;

        // Движение по пути
        if (enemy.currentPathPointIndex < PATH_POINT_COUNT - 1) {
            SDL_Point p1 = PATH_POINTS[enemy.currentPathPointIndex];
            SDL_Point p2 = PATH_POINTS[enemy.currentPathPointIndex + 1];
            float segmentLength = distance({(float)p1.x, (float)p1.y}, {(float)p2.x, (float)p2.y});

            // Дистанция, которую враг может пройти за этот кадр
            float distanceThisFrame = effectiveEnemySpeed * deltaTime; // Используем эффективную скорость

            // Двигаемся по текущему сегменту
            enemy.distanceAlongSegment += distanceThisFrame;

            // Если прошли текущий сегмент, переходим к следующему (может проскочить несколько)
            while (enemy.distanceAlongSegment >= segmentLength && enemy.currentPathPointIndex < PATH_POINT_COUNT - 1) {
                enemy.distanceAlongSegment -= segmentLength; // Оставшаяся дистанция
                enemy.currentPathPointIndex++;               // Переход к следующей точке

                // Получаем новый сегмент
                if (enemy.currentPathPointIndex < PATH_POINT_COUNT - 1) {
                     p1 = PATH_POINTS[enemy.currentPathPointIndex];
                     p2 = PATH_POINTS[enemy.currentPathPointIndex + 1];
                     segmentLength = distance({(float)p1.x, (float)p1.y}, {(float)p2.x, (float)p2.y});
                     // Если новый сегмент нулевой длины (точки совпадают), переходим дальше сразу
                     if (segmentLength <= 0) {
                          enemy.currentPathPointIndex++;
                          enemy.distanceAlongSegment = 0; // Начинаем следующий сегмент с нуля
                          // Продолжаем цикл while
                     }
                } else {
                    // Достигли конца пути (после цикла while будет проверено)
                    enemy.distanceAlongSegment = 0; // Оставшаяся дистанция игнорируется у конца
                    break; // Выходим из цикла while
                }
            }

            // Обновление фактической позиции
            // Обновляем позицию только если не достигли конца пути в этом кадре
            if (enemy.currentPathPointIndex < PATH_POINT_COUNT - 1) {
                 enemy.position = getEnemyPositionOnPath(enemy.currentPathPointIndex, enemy.distanceAlongSegment);
            }


            // Проверка, достиг ли конца пути (после цикла while)
            if (enemy.currentPathPointIndex >= PATH_POINT_COUNT - 1) {
                gGameState.lives--;
                enemy.alive = false; // Помечаем на удаление
                 SDL_Log("Enemy (ID %d) reached end. Lives: %d", enemy.id, gGameState.lives);
            }
        }
         // TODO: Логика для Шипов - проверять столкновение врага с позициями башен Шипов и наносить урон.
         // Эта логика должна быть здесь, внутри цикла обновления врагов.
    }

    // --- Обновление башен (нацеливание, стрельба, AoE эффекты, непрерывный урон) ---
    for (auto& tower : gGameState.placedTowers) {
        // Проверка на выход за границы вектора gTowerTypes на всякий случай
        if (tower.typeIndex < 0 || tower.typeIndex >= gTowerTypes.size()) continue;
        const TowerInfo& info = gTowerTypes[tower.typeIndex];

        // --- Логика для стреляющих башен (isProjectile = true) ---
        if (info.isProjectile) {
            tower.fireCooldown -= deltaTime;

            if (tower.fireCooldown <= 0.0f) {
                // Найти цель (первого живого врага в радиусе, который ближе к концу пути)
                ActiveEnemy* targetEnemy = nullptr;
                float maxProgress = -1.0f; // Максимальный пройденный путь среди потенциальных целей

                // Ищем живого врага в радиусе
                for (auto& enemy : gGameState.activeEnemies) {
                    if (enemy.alive && distance(tower.position, enemy.position) <= tower.currentRange) {
                        float enemyProgress = getEnemyPathProgress(enemy);
                        if (targetEnemy == nullptr || enemyProgress > maxProgress) {
                            targetEnemy = &enemy;
                            maxProgress = enemyProgress;
                        }
                    }
                }

                // Если цель найдена, стрелять
                if (targetEnemy != nullptr) {
                     // Создаем снаряд, ссылаясь на врага по его уникальному ID
                     Vector2 direction = normalize({targetEnemy->position.x - tower.position.x, targetEnemy->position.y - tower.position.y});

                     Projectile newProjectile = {
                         tower.position, // start position
                         direction,      // velocity direction
                         400.0f,         // projectile speed (pixels per second) - Пример, можно добавить в TowerInfo
                         tower.currentDamage, // Урон снаряда берем из текущих статов башни
                         targetEnemy->id, // target ID
                         gTextures.count("projectile") ? gTextures["projectile"] : nullptr // projectile texture (check if loaded)
                     };

                     // Добавляем специфические параметры снаряда из TowerInfo
                     newProjectile.isAreaDamage = info.isAreaOfEffect; // Если тип башни AoE и стреляет снарядом (Миномет)
                     newProjectile.areaRadius = tower.currentAreaOfEffectRadius; // Радиус AoE от башни (для AoE снаряда)
                     // isPiercing не реализовано пока
                     newProjectile.slowAmount = info.slowAmount; // Замедление от снаряда (Ледышка)
                     newProjectile.slowDuration = info.slowDuration; // Длительность замедления от снаряда (Ледышка)
                     newProjectile.hitEnemiesIds.clear(); // Очищаем set для нового снаряда

                     gGameState.projectiles.push_back(newProjectile);

                     // Сброс кулдауна на основе текущей прокачанной скорости атаки башни
                     if (tower.currentFireRate > 0) { // Избежать деления на ноль
                         tower.fireCooldown = 1.0f / tower.currentFireRate;
                     } else {
                         tower.fireCooldown = 999.0f; // Не стреляет, если currentFireRate стал <= 0 после прокачки (не должно быть)
                     }
                }
            }
        }
        // --- Логика для нестреляющих или непрерывных башен (isProjectile = false) ---
        else {
            // --- Непрерывный урон (Лазер) ---
            if (info.isContinuous) {
                // Обновляем таймер поиска цели
                 tower.timeSinceLastTargetSearch += deltaTime;
                 if (tower.currentTargetEnemyId == -1 || tower.timeSinceLastTargetSearch >= tower.LASER_TARGET_SEARCH_INTERVAL) {
                     // Время искать новую цель или старая цель потеряна/умерла
                     tower.timeSinceLastTargetSearch = 0.0f; // Сброс таймера

                     ActiveEnemy* newTarget = nullptr;
                     float maxProgress = -1.0f; // Максимальный пройденный путь среди потенциальных целей

                     // Ищем живого врага в радиусе, который ближе к концу пути
                     for (auto& enemy : gGameState.activeEnemies) {
                         if (enemy.alive && distance(tower.position, enemy.position) <= tower.currentRange) {
                              float enemyProgress = getEnemyPathProgress(enemy);
                              if (newTarget == nullptr || enemyProgress > maxProgress) {
                                  newTarget = &enemy;
                                  maxProgress = enemyProgress;
                              }
                         }
                     }
                     // Устанавливаем новую цель (может быть nullptr)
                     tower.currentTargetEnemyId = (newTarget != nullptr) ? newTarget->id : -1;
                 }

                 // Если есть текущая цель, наносим урон
                 if (tower.currentTargetEnemyId != -1) {
                     // Найти цель по ID
                      ActiveEnemy* currentTarget = nullptr;
                      for(auto& enemy : gGameState.activeEnemies) {
                           if (enemy.id == tower.currentTargetEnemyId && enemy.alive) {
                               currentTarget = &enemy;
                               break;
                           }
                      }

                      if (currentTarget != nullptr) {
                           // Наносим урон в секунду, масштабированный по deltaTime
                           currentTarget->currentHealth -= tower.currentDamage * deltaTime;

                           // Проверяем смерть врага
                           if (currentTarget->currentHealth <= 0 && currentTarget->alive) {
                               currentTarget->alive = false;
                               gGameState.money += currentTarget->scaledReward;
                               SDL_Log("Enemy (ID %d) killed by Laser. Money: %d", currentTarget->id, gGameState.money);
                               tower.currentTargetEnemyId = -1; // Цель мертва, сбрасываем цель
                           }
                      } else {
                          // Цель, которую мы отслеживали по ID, больше не существует или мертва
                          tower.currentTargetEnemyId = -1; // Сбрасываем цель
                      }
                 }
            }
            // --- Постоянный AoE эффект (Огнемет, Болото) ---
            else if (info.isAreaOfEffect) { // Проверяем флаг AoE у типа башни
                // Огнемет и Болото: наносят урон/эффект врагам в радиусе каждый кадр
                float effectRange = tower.currentAreaOfEffectRadius; // Используем текущий прокачанный радиус эффекта
                float damagePerSecond = tower.currentDamage; // Для огнемета (DPS)
                float slowAmount = tower.currentSlowAmount; // Для болота (множитель)
                float effectDuration = info.slowDuration; // Время обновления эффекта для зоны (из TowerInfo)

                 // Применяем эффект ко всем живым врагам в радиусе
                 for (auto& enemy : gGameState.activeEnemies) {
                     if (enemy.alive && distance(tower.position, enemy.position) <= effectRange) {
                         // Наносим урон от AoE башни (Огнемет)
                         if (damagePerSecond > 0) {
                              enemy.currentHealth -= damagePerSecond * deltaTime;
                              // Проверяем смерть врага
                              if (enemy.currentHealth <= 0 && enemy.alive) {
                                  enemy.alive = false;
                                  gGameState.money += enemy.scaledReward;
                                  SDL_Log("Enemy (ID %d) killed by AoE. Money: %d", enemy.id, gGameState.money);
                              }
                         }

                         // Применяем замедление от AoE башни (Болото)
                         if (slowAmount < 1.0f && effectDuration > 0) {
                             // Применяем замедление. Если текущее замедление врага слабее ИЛИ оно закончилось, применяем новое.
                             // Используем std::min, потому что меньший множитель = сильнее замедление.
                             // Важно: если враг находится в нескольких зонах замедления, он должен получить самое сильное.
                             // Текущая логика просто перезаписывает замедление, если оно сильнее или таймер истек.
                             // Более правильная логика: отслеживать все замедляющие источники на враге и брать максимальное замедление.
                             // Для простоты: если это замедление сильнее или дольше, чем текущее активное замедление врага, применяем его.
                             if (slowAmount < enemy.currentSlowMultiplier || enemy.slowDurationTimer <= 0) {
                                 enemy.currentSlowMultiplier = slowAmount; // Применяем более сильное (меньшее) замедление
                                 enemy.slowDurationTimer = effectDuration; // Длительность эффекта из TowerInfo
                             } else if (slowAmount == enemy.currentSlowMultiplier && effectDuration > enemy.slowDurationTimer) {
                                  // Та же сила замедления, но дольше - обновляем длительность
                                  enemy.slowDurationTimer = effectDuration;
                             }
                         }
                     }
                 }
            }
             // --- Логика для Шипов ---
             // Шипы требуют проверки столкновения врагов с позицией башни, а не наоборот.
             // Эта логика должна быть в цикле обновления врагов. (TODO)
        }
    }

    // --- Обновление снарядов ---
    // Удаляем снаряды, которые попали или вылетели за экран
    gGameState.projectiles.erase(
        std::remove_if(gGameState.projectiles.begin(), gGameState.projectiles.end(),
                       [&](Projectile& p){ // Нужна не const ссылка, чтобы менять p.hitEnemiesIds
                           // Проверка вылета за экран (на случай, если летел по последнему направлению)
                           if (p.position.x < -100 || p.position.x > SCREEN_WIDTH + 100 ||
                               p.position.y < -100 || p.position.y > SCREEN_HEIGHT + 100) {
                               return true; // Удалить, если вылетел далеко за экран
                           }

                           // --- Логика для AoE снарядов (Миномет) ---
                           if (p.isAreaDamage) {
                                // Для AoE снарядов, проверяем попадание в область вокруг их текущей позиции
                                // Или проверяем попадание по основной цели, а затем наносим AoE.
                                // Давайте сделаем, что AoE срабатывает при первом попадании в ЛЮБОГО врага.
                                ActiveEnemy* firstHitTarget = nullptr;
                                for(auto& enemy : gGameState.activeEnemies) {
                                     // Ищем живого врага, который еще не был поражен этим снарядом И находится близко
                                    if (enemy.alive && p.hitEnemiesIds.find(enemy.id) == p.hitEnemiesIds.end() &&
                                        distance(p.position, enemy.position) < 15) { // Магическое число 15 - радиус столкновения
                                        firstHitTarget = &enemy;
                                        break; // Нашли первого попавшегося
                                    }
                                }

                                if (firstHitTarget != nullptr) {
                                    // Снаряд попал в первого врага, теперь наносим урон всем в AoE радиусе вокруг *точки попадания*
                                     Vector2 impactPoint = firstHitTarget->position; // Или p.position, если AoE мгновенный в точке снаряда

                                     // Наносим урон всем в радиусе AoE
                                     for(auto& enemy : gGameState.activeEnemies) {
                                          if (enemy.alive && distance(impactPoint, enemy.position) <= p.areaRadius) { // В радиусе AoE от точки попадания
                                              // Наносим урон
                                              enemy.currentHealth -= p.damage; // Урон от снаряда
                                              // SDL_Log("AoE hit enemy %d for %.1f damage. Health: %.1f", enemy.id, p.damage, enemy.currentHealth);

                                              // Применяем замедление от снаряда (если есть)
                                             if (p.slowDuration > 0) {
                                                 if (p.slowAmount < enemy.currentSlowMultiplier || enemy.slowDurationTimer <= 0) {
                                                     enemy.currentSlowMultiplier = p.slowAmount;
                                                     enemy.slowDurationTimer = p.slowDuration;
                                                 } else if (p.slowAmount == enemy.currentSlowMultiplier && p.slowDuration > enemy.slowDurationTimer) {
                                                      enemy.slowDurationTimer = p.slowDuration;
                                                 }
                                             }


                                              // Проверяем смерть врага
                                              if (enemy.currentHealth <= 0 && enemy.alive) { // Проверка alive на всякий случай
                                                  enemy.alive = false;
                                                  gGameState.money += enemy.scaledReward;
                                                  SDL_Log("Enemy (ID %d) killed by AoE Projectile. Money: %d", enemy.id, gGameState.money);
                                              }
                                          }
                                     }
                                     return true; // Удалить AoE снаряд после срабатывания
                                }
                                // Если AoE снаряд не попал ни в одного врага в этом кадре, он летит дальше
                                return false;
                           }

                           // --- Логика для обычных одиночных снарядов (Пушка, Пулемет, Снайпер, Ледышка) ---
                           else { // isProjectile is true, isAreaOfEffect is false, isContinuous is false
                                // Найти основную цель по ID (ищем среди живых врагов)
                                ActiveEnemy* ordinary_target = nullptr;
                                for(auto& enemy : gGameState.activeEnemies) {
                                    if (enemy.id == p.targetEnemyId && enemy.alive) {
                                        ordinary_target = &enemy;
                                        break;
                                    }
                                }

                                // Если основная цель больше не существует или мертва, удаляем снаряд
                                if (ordinary_target == nullptr) {
                                    return true;
                                }

                                // Проверка попадания по основной цели
                                if (distance(p.position, ordinary_target->position) < 15) { // Радиус попадания
                                    // Попадание!
                                    ordinary_target->currentHealth -= p.damage; // Наносим урон
                                    // SDL_Log("Projectile %d hit enemy %d for %.1f damage. Health: %.1f", p.targetEnemyId, ordinary_target->id, p.damage, ordinary_target->currentHealth);

                                    // Применяем замедление от снаряда (если есть)
                                     if (p.slowDuration > 0) {
                                         if (p.slowAmount < ordinary_target->currentSlowMultiplier || ordinary_target->slowDurationTimer <= 0) {
                                             ordinary_target->currentSlowMultiplier = p.slowAmount;
                                             ordinary_target->slowDurationTimer = p.slowDuration;
                                         } else if (p.slowAmount == ordinary_target->currentSlowMultiplier && p.slowDuration > ordinary_target->slowDurationTimer) {
                                              ordinary_target->slowDurationTimer = p.slowDuration;
                                         }
                                     }


                                    // Проверка смерти
                                    if (ordinary_target->currentHealth <= 0 && ordinary_target->alive) {
                                        ordinary_target->alive = false;
                                        gGameState.money += ordinary_target->scaledReward;
                                        SDL_Log("Enemy (ID %d) killed. Money: %d", ordinary_target->id, gGameState.money);
                                    }
                                    return true; // Удалить снаряд после попадания
                                }
                                // Снаряд не попал в этом кадре, оставляем его
                                return false;
                           }
                       }),
        gGameState.projectiles.end()
    );


    // Движение снарядов (после проверки попаданий, чтобы не двигать уже "попавшие" снаряды)
    // Снаряды движутся по прямой, скорость уже определена.
    for (auto& p : gGameState.projectiles) {
         p.position.x += p.velocity.x * p.speed * deltaTime;
         p.position.y += p.velocity.y * p.speed * deltaTime;
    }

    // Обновление таймера наведения UI (остается активным и на паузе, но тут нет паузы)
    // Этот таймер уже обновляется в начале update перед проверкой паузы.
}

// --- Рендеринг ---
void render() {
    // Clear screen with desired background color
    SDL_SetRenderDrawColor(gRenderer, COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
    SDL_RenderClear(gRenderer);

    // Render background texture (if any) - TODO: load this
     if (gTextures.count("background") && gTextures["background"] != nullptr) {
         SDL_RenderCopy(gRenderer, gTextures["background"], NULL, NULL);
     }

    // Render path
     SDL_SetRenderDrawColor(gRenderer, 0xA0, 0xA0, 0xA0, 0xFF); // Gray path
     // Render segments pairwise
     for (int i = 0; i < PATH_POINT_COUNT - 1; ++i) {
          SDL_RenderDrawLine(gRenderer, PATH_POINTS[i].x, PATH_POINTS[i].y, PATH_POINTS[i+1].x, PATH_POINTS[i+1].y);
     }

     // Рисуем точки пути как круги для наглядности (опционально)
     SDL_SetRenderDrawColor(gRenderer, 0x50, 0x50, 0x50, 255);
     for (int i = 0; i < PATH_POINT_COUNT; ++i) {
         drawFilledCircle(gRenderer, {(float)PATH_POINTS[i].x, (float)PATH_POINTS[i].y}, 5, {0x50, 0x50, 0x50, 255});
     }


    // Render placed towers (and their effects like AoE zones)
    for (const auto& tower : gGameState.placedTowers) {
        // Проверка на выход за границы вектора gTowerTypes на всякий случай
        if (tower.typeIndex < 0 || tower.typeIndex >= gTowerTypes.size()) continue;
        const TowerInfo& info = gTowerTypes[tower.typeIndex];

        // Рисуем радиус эффекта для башен с зоной (например, Болото, Огнемет)
        if (info.isAreaOfEffect) { // Проверяем флаг AoE у типа башни
             SDL_Color zoneColor = COLOR_TRANSPARENT_BLUE; // Для замедления (по умолчанию)
             if (info.baseDamage > 0 && info.baseFireRate <= 0) zoneColor = {255, 100, 0, 80}; // Для урона (оранжевый) - Огнемет
             // if (info.name == "Башня Влияния") zoneColor = COLOR_TRANSPARENT_YELLOW; // Для баффа - TowerInfo name check? Or separate flag?

             drawFilledCircle(gRenderer, tower.position, (int)tower.currentAreaOfEffectRadius, zoneColor);
        }
         // Рисуем радиус баффа для Башни Влияния
         if (info.name == "Башня Влияния" && tower.currentRange > 0) { // Башня Влияния использует baseRange для баффа
              drawFilledCircle(gRenderer, tower.position, (int)tower.currentRange, COLOR_TRANSPARENT_YELLOW);
         }


        SDL_Rect towerRect = {(int)tower.position.x - 20, (int)tower.position.y - 20, 40, 40}; // Примерный размер башни

        if (info.texture != nullptr) {
            SDL_RenderCopy(gRenderer, info.texture, NULL, &towerRect);
        } else {
             // Рисуем заглушку, если нет текстуры
             SDL_SetRenderDrawColor(gRenderer, 0, 200, 0, 255); // Green placeholder
             SDL_RenderFillRect(gRenderer, &towerRect);
             SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
             SDL_RenderDrawRect(gRenderer, &towerRect);
        }
         // Отображение уровня башни, если он больше 1
         if (gFont != nullptr && tower.level > 1) {
              std::string levelText = std::to_string(tower.level);
              SDL_Texture* levelTexture = renderText(levelText, COLOR_BLACK, gFontSmall); // Используем меньший шрифт
              if (levelTexture) {
                  int texW = 0, texH = 0;
                  SDL_QueryTexture(levelTexture, NULL, NULL, &texW, &texH);
                  SDL_Rect dstRect = {(int)tower.position.x - texW/2, (int)tower.position.y - texH/2, texW, texH};
                  SDL_RenderCopy(gRenderer, levelTexture, NULL, &dstRect);
                  SDL_DestroyTexture(levelTexture);
              }
         }

         // Рисуем лазерный луч
         if (info.isContinuous && tower.currentTargetEnemyId != -1) {
             // Найти цель по ID
              ActiveEnemy* currentTarget = nullptr;
              for(auto& enemy : gGameState.activeEnemies) {
                   if (enemy.id == tower.currentTargetEnemyId && enemy.alive) {
                       currentTarget = &enemy;
                       break;
                   }
              }
              if (currentTarget != nullptr) {
                   SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255); // Красный лазер
                   // Рисуем толстую линию (примерно)
                   SDL_Point lineStart = {(int)tower.position.x, (int)tower.position.y};
                   SDL_Point lineEnd = {(int)currentTarget->position.x, (int)currentTarget->position.y};
                    // Вычисляем перпендикулярный вектор для толщины
                   Vector2 dir = normalize({(float)(lineEnd.x - lineStart.x), (float)(lineEnd.y - lineStart.y)});
                   Vector2 perpendicular = {-dir.y, dir.x}; // Перпендикуляр
                   float thickness = 2.0f; // Толщина луча (половина)

                   // Рисуем две линии рядом для имитации толщины
                   SDL_RenderDrawLine(gRenderer, (int)(lineStart.x + perpendicular.x * thickness), (int)(lineStart.y + perpendicular.y * thickness),
                                              (int)(lineEnd.x + perpendicular.x * thickness), (int)(lineEnd.y + perpendicular.y * thickness));
                   SDL_RenderDrawLine(gRenderer, (int)(lineStart.x - perpendicular.x * thickness), (int)(lineStart.y - perpendicular.y * thickness),
                                              (int)(lineEnd.x - perpendicular.x * thickness), (int)(lineEnd.y - perpendicular.y * thickness));
                   // Или можно использовать SDL_RenderGeometry, но это сложнее.
              }
         }
    }

    // Render enemies
    for (const auto& enemy : gGameState.activeEnemies) {
        // Проверка на выход за границы вектора gEnemyTypes на всякий случай
         if (enemy.typeIndex < 0 || enemy.typeIndex >= gEnemyTypes.size()) continue;

        const EnemyInfo& info = gEnemyTypes[enemy.typeIndex];
        SDL_Rect enemyRect = {(int)enemy.position.x - 15, (int)enemy.position.y - 15, 30, 30}; // Примерный размер

         if (info.texture != nullptr) {
             SDL_RenderCopy(gRenderer, info.texture, NULL, &enemyRect);
         } else {
             // Рисуем заглушку
             SDL_SetRenderDrawColor(gRenderer, 0, 0, 200, 255); // Blue placeholder
             SDL_RenderFillRect(gRenderer, &enemyRect);
             SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
             SDL_RenderDrawRect(gRenderer, &enemyRect);
         }

        // Draw slow effect indicator
        if (enemy.currentSlowMultiplier < 1.0f && enemy.slowDurationTimer > 0) {
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 150); // Semi-transparent blue
            SDL_Rect slowRect = {(int)enemy.position.x - 10, (int)enemy.position.y - 25, 20, 5}; // Blue bar above health
             SDL_RenderFillRect(gRenderer, &slowRect);
        }


        // Draw health bar
        // Health percentage should be based on the enemy's scaled max health
        float healthPercentage = enemy.currentHealth / enemy.maxScaledHealth;
        if (healthPercentage < 0) healthPercentage = 0; // Just in case health goes below zero
        SDL_Rect healthBarBg = {(int)enemy.position.x - 15, (int)enemy.position.y - 20, 30, 5};
        SDL_Rect healthBarFg = {(int)enemy.position.x - 15, (int)enemy.position.y - 20, (int)(30 * healthPercentage), 5};
        SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255); // Red background
        SDL_RenderFillRect(gRenderer, &healthBarBg);
        SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255); // Green foreground
        SDL_RenderFillRect(gRenderer, &healthBarFg);
    }

    // Render projectiles
    for (const auto& p : gGameState.projectiles) {
        SDL_Rect projRect = {(int)p.position.x - p.srcRect.w/2, (int)p.position.y - p.srcRect.h/2, p.srcRect.w, p.srcRect.h};
         if (p.texture != nullptr) {
              SDL_RenderCopy(gRenderer, p.texture, NULL, &projRect);
         } else {
             // Рисуем заглушку
             SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255); // Yellow placeholder
             SDL_RenderFillRect(gRenderer, &projRect);
         }
    }

    // --- Render UI ---

    // Render tower selection bar background
    SDL_Rect topBarRect = {0, 0, SCREEN_WIDTH, TOWER_SELECTION_BAR_HEIGHT};
    SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 200); // Dark gray, slightly transparent
    SDL_RenderFillRect(gRenderer, &topBarRect);

    // Render tower selection cards
    for (int i = 0; i < gTowerTypes.size(); ++i) {
        const TowerInfo& info = gTowerTypes[i];
        SDL_Rect cardRect = {
            TOWER_CARD_PADDING + i * (TOWER_SLOT_TOTAL_WIDTH), // Используем TOWER_SLOT_TOTAL_WIDTH
            TOWER_CARD_PADDING,
            TOWER_CARD_WIDTH, // Используем TOWER_CARD_WIDTH
            TOWER_CARD_HEIGHT
        };
        SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 255); // Light gray card background
        SDL_RenderFillRect(gRenderer, &cardRect);
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); // Black border
        SDL_RenderDrawRect(gRenderer, &cardRect);

         // Render tower name and cost
         if (gFontSmall != nullptr) { // Используем меньший шрифт для текста на карточках
              SDL_Color textColor = (gGameState.money >= info.cost) ? COLOR_WHITE : COLOR_RED;
              SDL_Texture* nameTexture = renderText(info.name, textColor, gFontSmall);
              SDL_Texture* costTexture = renderText("$" + std::to_string(info.cost), textColor, gFontSmall);

              if (nameTexture) {
                  int texW, texH;
                  SDL_QueryTexture(nameTexture, NULL, NULL, &texW, &texH);
                  SDL_Rect dstRect = {cardRect.x + 3, cardRect.y + 3, std::min(texW, cardRect.w - 6), texH}; // Clamp width, smaller padding
                  SDL_RenderCopy(gRenderer, nameTexture, NULL, &dstRect);
                  SDL_DestroyTexture(nameTexture);
              }
              if (costTexture) {
                  int texW, texH;
                  SDL_QueryTexture(costTexture, NULL, NULL, &texW, &texH);
                  SDL_Rect dstRect = {cardRect.x + 3, cardRect.y + cardRect.h - texH - 3, std::min(texW, cardRect.w - 6), texH}; // Clamp width, smaller padding
                  SDL_RenderCopy(gRenderer, costTexture, NULL, &dstRect);
                  SDL_DestroyTexture(costTexture);
              }
         }

         // Draw tower icon (placeholder) - Centered in the remaining space
         int iconSize = std::min(TOWER_CARD_WIDTH - 2 * TOWER_CARD_PADDING, TOWER_CARD_HEIGHT - (TTF_FontHeight(gFontSmall)*2 + 6)); // Space excluding name+cost
         if (iconSize < 20) iconSize = 20; // Minimum icon size
         SDL_Rect iconRect = {cardRect.x + TOWER_CARD_WIDTH/2 - iconSize/2, cardRect.y + TOWER_CARD_HEIGHT/2 - iconSize/2, iconSize, iconSize}; // Centered
         if (info.texture != nullptr) {
              SDL_RenderCopy(gRenderer, info.texture, NULL, &iconRect);
         } else {
              SDL_SetRenderDrawColor(gRenderer, 0, 200, 0, 255); // Green placeholder
              SDL_RenderFillRect(gRenderer, &iconRect);
         }


        // Highlight selected tower card
        if (gUIState.selectedTowerIndex == i) {
            SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255); // Green highlight
            SDL_RenderDrawRect(gRenderer, &cardRect);
            // Исправлено: создаем временный SDL_Rect для отрисовки толстой рамки
            SDL_Rect thickHighlightRect = {cardRect.x+1, cardRect.y+1, cardRect.w-2, cardRect.h-2};
            SDL_RenderDrawRect(gRenderer, &thickHighlightRect);
        }
    }

    // Render tower hover info window
    if (gUIState.hoveredTowerIndex != -1 && gUIState.towerHoverTimer >= TOWER_HOVER_TIME_THRESHOLD && gUIState.hoveredTowerIndex < gTowerTypes.size()) {
        const TowerInfo& info = gTowerTypes[gUIState.hoveredTowerIndex];
        // Определить позицию окна (под карточкой башни)
        SDL_Rect cardRect = { // Использовать cardRect из рендеринга карточек
            TOWER_CARD_PADDING + gUIState.hoveredTowerIndex * (TOWER_SLOT_TOTAL_WIDTH), // Используем TOWER_SLOT_TOTAL_WIDTH
            TOWER_CARD_PADDING,
            TOWER_CARD_WIDTH, // Используем TOWER_CARD_WIDTH
            TOWER_CARD_HEIGHT
        };
        SDL_Rect infoWindowRect = {cardRect.x, cardRect.y + cardRect.h + 5, 200, 180}; // Увеличен размер окна

        // Проверка, чтобы окно не выходило за правый край экрана
        if (infoWindowRect.x + infoWindowRect.w > SCREEN_WIDTH) {
             infoWindowRect.x = SCREEN_WIDTH - infoWindowRect.w - 5; // Отступ от правого края
        }
         // Проверка, чтобы окно не выходило за нижний край экрана (если бы оно могло появляться внизу)
         // В этом UI окно всегда под верхней панелью, так что проверка нижнего края не так важна
         if (infoWindowRect.y + infoWindowRect.h > SCREEN_HEIGHT) {
             infoWindowRect.y = cardRect.y - infoWindowRect.h - 5; // Попробуем разместить над карточкой, если не влезает снизу (маловероятно тут)
             // Если все равно не влезает, просто прижмем к нижнему краю
             if (infoWindowRect.y < TOWER_SELECTION_BAR_HEIGHT) infoWindowRect.y = SCREEN_HEIGHT - infoWindowRect.h - 5;
         }
         // Проверка, чтобы окно не заходило на верхнюю UI панель
         if (infoWindowRect.y < TOWER_SELECTION_BAR_HEIGHT) {
             infoWindowRect.y = TOWER_SELECTION_BAR_HEIGHT + 5;
         }


        SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 230); // Dark gray background
        SDL_RenderFillRect(gRenderer, &infoWindowRect);
        SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255); // Light gray border
        SDL_RenderDrawRect(gRenderer, &infoWindowRect);

        if (gFontSmall != nullptr) { // Используем меньший шрифт для инфо окна
            int textX = infoWindowRect.x + 5;
            int textY = infoWindowRect.y + 5;
            int lineHeight = TTF_FontHeight(gFontSmall); // Примерная высота строки текста

            // Render Name
            SDL_Texture* nameTex = renderText(info.name, COLOR_WHITE, gFontSmall);
            if(nameTex) {
                int w,h; SDL_QueryTexture(nameTex, NULL, NULL, &w, &h);
                SDL_Rect dst = {textX, textY, std::min(w, infoWindowRect.w - 10), h};
                SDL_RenderCopy(gRenderer, nameTex, NULL, &dst);
                SDL_DestroyTexture(nameTex);
            }
            textY += lineHeight;

            // Render Description (need wrapping or scrolling for long text, simplified here)
            // Try to wrap description manually by inserting newlines if needed
            std::string wrappedDescription = info.description;
            // This is a very basic wrap - needs font metrics for proper wrapping
            // For demo, assume fixed width and split
            int charsPerLineEstimate = (infoWindowRect.w - 10) / 9; // Crude estimate (9 pixels per char)
            if (charsPerLineEstimate > 5) { // Don't wrap if window is too small
                 size_t pos = charsPerLineEstimate;
                 while (pos < wrappedDescription.length()) {
                     // Find a space or break point before or at pos
                     size_t break_pos = wrappedDescription.rfind(' ', pos);
                     if (break_pos == std::string::npos || break_pos < pos - charsPerLineEstimate / 2) {
                         // No space found or too far back, just break at pos
                         break_pos = pos;
                     }
                     // Avoid breaking in the middle of a word at the very start
                     if (break_pos == 0 && wrappedDescription.length() > charsPerLineEstimate) break_pos = charsPerLineEstimate;
                     if (break_pos >= wrappedDescription.length()) break; // Already reached the end

                     wrappedDescription.insert(break_pos, "\n");
                     pos = break_pos + 1 + charsPerLineEstimate; // 1 for the newline
                 }
            }


             size_t start = 0; // Объявлены один раз здесь
             size_t end = 0;
             // Render description lines, leaving space for stats
             while (textY < infoWindowRect.y + infoWindowRect.h - (lineHeight * 4) && (end = wrappedDescription.find('\n', start)) != std::string::npos) { // Оставляем больше места для статов
                 std::string line = wrappedDescription.substr(start, end - start);
                 SDL_Texture* lineTex = renderText(line, COLOR_WHITE, gFontSmall);
                  if(lineTex) {
                     int w,h; SDL_QueryTexture(lineTex, NULL, NULL, &w, &h);
                     SDL_Rect dst = {textX, textY, std::min(w, infoWindowRect.w - 10), h};
                     SDL_RenderCopy(gRenderer, lineTex, NULL, &dst);
                     SDL_DestroyTexture(lineTex);
                  }
                 textY += lineHeight;
                 start = end + 1;
             }
              // Render the last line of description (if any remaining and space permits)
              if (textY < infoWindowRect.y + infoWindowRect.h - (lineHeight * 4) && start < wrappedDescription.length()) {
                  std::string lastLine = wrappedDescription.substr(start);
                  SDL_Texture* lastLineTex = renderText(lastLine, COLOR_WHITE, gFontSmall);
                   if(lastLineTex) {
                      int w,h; SDL_QueryTexture(lastLineTex, NULL, NULL, &w, &h);
                      SDL_Rect dst = {textX, textY, std::min(w, infoWindowRect.w - 10), h};
                      SDL_RenderCopy(gRenderer, lastLineTex, NULL, &dst);
                      SDL_DestroyTexture(lastLineTex);
                   }
                   textY += lineHeight; // Add space for the last line
              }


            // Render Stats (Base stats from TowerInfo)
             std::string stats = "";
             if (info.baseDamage > 0) {
                  stats += (info.isContinuous ? "Урон/сек: " : "Урон: ") + std::to_string((int)info.baseDamage) + "\n";
             }
             if (info.baseRange > 0) {
                  stats += "Дальность: " + std::to_string((int)info.baseRange) + "\n";
             }
             if (info.baseFireRate > 0) { // Только если стреляет снарядами
                 stats += "Скорость: " + std::to_string((int)(info.baseFireRate * 10) / 10.0f) + "/сек\n"; // Округляем до 1 знака
             }
             // Add info about effects
             if (info.slowAmount < 1.0f) {
                  stats += "Замедление: " + std::to_string((int)(100 - info.slowAmount * 100)) + "%\n"; // Показываем % замедления
             }
             if (info.slowDuration > 0 && info.isProjectile) { // Длительность эффекта снаряда
                 stats += "Длит. замед.: " + std::to_string((int)(info.slowDuration*10)/10.0f) + " с\n"; // Округляем
             }
             if (info.isAreaOfEffect) { // Только если AoE
                  stats += "Радиус AoE: " + std::to_string((int)info.areaOfEffectRadius) + "\n";
             }

             // Add upgrade info regardless of type
             if (info.maxLevel > 1) {
                 stats += "Прокачка: $" + std::to_string(info.upgradeCost); // Без новой строки, если это последний текст
             } else {
                 stats += "Не прокачивается";
             }


             start = 0; // Сброс start для нового раздела текста
             // Render stats
             while (textY < infoWindowRect.y + infoWindowRect.h - 5 && (end = stats.find('\n', start)) != std::string::npos) {
                 std::string line = stats.substr(start, end - start);
                 SDL_Texture* lineTex = renderText(line, COLOR_WHITE, gFontSmall);
                  if(lineTex) {
                     int w,h; SDL_QueryTexture(lineTex, NULL, NULL, &w, &h);
                     SDL_Rect dst = {textX, textY, std::min(w, infoWindowRect.w - 10), h};
                     SDL_RenderCopy(gRenderer, lineTex, NULL, &dst);
                     SDL_DestroyTexture(lineTex);
                  }
                 textY += lineHeight;
                 start = end + 1;
             }
              // Render the last line of stats
              if (textY < infoWindowRect.y + infoWindowRect.h - 5 && start < stats.length()) {
                  std::string lastLine = stats.substr(start);
                  SDL_Texture* lastLineTex = renderText(lastLine, COLOR_WHITE, gFontSmall);
                   if(lastLineTex) {
                      int w,h; SDL_QueryTexture(lastLineTex, NULL, NULL, &w, &h);
                      SDL_Rect dst = {textX, textY, std::min(w, infoWindowRect.w - 10), h};
                      SDL_RenderCopy(gRenderer, lastLineTex, NULL, &dst);
                      SDL_DestroyTexture(lastLineTex);
                   }
              }
        }
    }

    // Render placement preview hologram and range
    if (gUIState.selectedTowerIndex != -1 && gUIState.selectedTowerIndex < gTowerTypes.size()) {
        const TowerInfo& info = gTowerTypes[gUIState.selectedTowerIndex];
        SDL_Color rangeColor = gUIState.canPlaceTower ? COLOR_TRANSPARENT_GREEN : COLOR_TRANSPARENT_RED;

        // Draw attack range circle (filled) - only if baseRange > 0 AND it's a projectile tower OR continuous (laser)
        if (info.baseRange > 0 && (info.isProjectile || info.isContinuous)) {
             drawFilledCircle(gRenderer, gUIState.placementPreviewPos, (int)info.baseRange, rangeColor);
             // Draw range circle (outline)
             drawCircle(gRenderer, gUIState.placementPreviewPos, (int)info.baseRange, gUIState.canPlaceTower ? COLOR_GREEN : COLOR_RED);
        }
         // Draw effect radius circle (filled) - only if AreaOfEffectRadius > 0
         if (info.isAreaOfEffect) { // Проверяем флаг AoE у типа башни
              SDL_Color zoneColor = COLOR_TRANSPARENT_BLUE; // Для замедления (по умолчанию)
              if (info.baseDamage > 0) zoneColor = {255, 100, 0, 80}; // Для урона (оранжевый)

              drawFilledCircle(gRenderer, gUIState.placementPreviewPos, (int)info.areaOfEffectRadius, zoneColor);
              drawCircle(gRenderer, gUIState.placementPreviewPos, (int)info.areaOfEffectRadius, COLOR_BLUE);
         }
         // Draw buff range circle - only for Buff tower
          if (info.name == "Башня Влияния" && info.baseRange > 0) { // Башня Влияния использует baseRange для баффа
             drawFilledCircle(gRenderer, gUIState.placementPreviewPos, (int)info.baseRange, COLOR_TRANSPARENT_YELLOW);
             drawCircle(gRenderer, gUIState.placementPreviewPos, (int)info.baseRange, COLOR_YELLOW);
          }


        // Draw tower hologram (texture or placeholder)
        SDL_Rect previewRect = {(int)gUIState.placementPreviewPos.x - 20, (int)gUIState.placementPreviewPos.y - 20, 40, 40};
         if (info.texture != nullptr) {
              // Установить режим смешивания для прозрачности текстуры
              SDL_SetTextureAlphaMod(info.texture, 150); // 150 из 255 = полупрозрачный
              SDL_RenderCopy(gRenderer, info.texture, NULL, &previewRect);
              SDL_SetTextureAlphaMod(info.texture, 255); // Вернуть полную непрозрачность
         } else {
             // Рисуем полупрозрачную заглушку
             SDL_SetRenderDrawColor(gRenderer, 0, 200, 0, 150); // Green semi-transparent
             SDL_RenderFillRect(gRenderer, &previewRect);
             SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 150);
             SDL_RenderDrawRect(gRenderer, &previewRect);
         }

    }

    // Render upgrade window
    if (gUIState.isUpgradeWindowOpen && gUIState.selectedPlacedTowerIndex != -1 && gUIState.selectedPlacedTowerIndex < gGameState.placedTowers.size()) {
        const PlacedTower& tower = gGameState.placedTowers[gUIState.selectedPlacedTowerIndex];
        // Проверка на выход за границы вектора gTowerTypes на всякий случай
        if (tower.typeIndex < 0 || tower.typeIndex >= gTowerTypes.size()) {
             // Close window if selected tower is invalid (shouldn't happen with correct logic)
             gUIState.isUpgradeWindowOpen = false;
             gUIState.selectedPlacedTowerIndex = -1;
             return; // Don't render window
        }
        const TowerInfo& info = gTowerTypes[tower.typeIndex];


        SDL_SetRenderDrawColor(gRenderer, 80, 80, 80, 230); // Darker gray background
        SDL_RenderFillRect(gRenderer, &gUIState.upgradeWindowRect);
        SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255); // Border
        SDL_RenderDrawRect(gRenderer, &gUIState.upgradeWindowRect);

        if (gFont != nullptr) { // Используем основной шрифт для окна прокачки
             int textX = gUIState.upgradeWindowRect.x + 10;
             int textY = gUIState.upgradeWindowRect.y + 10;
             int lineHeight = TTF_FontHeight(gFont); // Примерная высота строки текста

            // Tower Name and Level
            std::string nameLevel = info.name + " (Ур. " + std::to_string(tower.level) + "/" + std::to_string(info.maxLevel) + ")";
            SDL_Texture* nameLevelTex = renderText(nameLevel, COLOR_WHITE, gFont);
            if(nameLevelTex) {
                int w,h; SDL_QueryTexture(nameLevelTex, NULL, NULL, &w, &h);
                SDL_Rect dst = {textX, textY, std::min(w, gUIState.upgradeWindowRect.w - 20), h};
                SDL_RenderCopy(gRenderer, nameLevelTex, NULL, &dst);
                SDL_DestroyTexture(nameLevelTex);
            }
            textY += lineHeight + 5; // Немного больше отступ

            // Current Stats (from PlacedTower)
             std::string currentStats = "";
             if (info.baseDamage > 0) { // Only show damage if tower type has base damage
                  currentStats += (info.isContinuous ? "Урон/сек: " : "Урон: ") + std::to_string((int)tower.currentDamage) + "\n";
             }
              if (info.baseRange > 0) { // Only show range if tower type has base range
                  currentStats += "Дальность: " + std::to_string((int)tower.currentRange) + "\n";
             }
             if (info.baseFireRate > 0) { // Only show fire rate if tower type has base fire rate
                  currentStats += "Скорость: " + std::to_string((int)(tower.currentFireRate * 10) / 10.0f) + "/сек\n"; // Округляем до 1 знака после запятой
             }

             // Current effect stats
             if (info.slowAmount < 1.0f) { // Only show slow if tower type has base slow
                 currentStats += "Замедление: " + std::to_string((int)(100 - tower.currentSlowAmount * 100)) + "%\n";
             }
             if (info.isAreaOfEffect) { // Only show AoE if tower type has AoE
                  currentStats += "Радиус AoE: " + std::to_string((int)tower.currentAreaOfEffectRadius) + "\n";
             }
             // Current buff effect? (Not implemented)

            // Show upgrade effect for next level if not max level
            if (tower.level < info.maxLevel) {
                 currentStats += "\nСлед. ур. (+" + std::to_string(info.upgradeCost) + "$):\n";
                 if (info.damageUpgradeMultiplier != 1.0f && info.baseDamage > 0) { // Use base damage to check if tower type has damage
                      currentStats += "+Урон -> " + std::to_string((int)(tower.currentDamage * info.damageUpgradeMultiplier)) + "\n";
                 }
                 if (info.rangeUpgradeMultiplier != 1.0f && info.baseRange > 0) { // Use base range
                      currentStats += "+Дальность -> " + std::to_string((int)(tower.currentRange * info.rangeUpgradeMultiplier)) + "\n";
                 }
                 if (info.fireRateUpgradeMultiplier != 1.0f && info.baseFireRate > 0) { // Use base fire rate
                      currentStats += "+Скорость -> " + std::to_string((int)((tower.currentFireRate / info.fireRateUpgradeMultiplier) * 10) / 10.0f) + "/сек\n";
                 }
                 // Show effect upgrades if applicable
                 if (info.slowAmount < 1.0f && info.fireRateUpgradeMultiplier > 0) { // Assuming slow effect scales with fire rate multiplier
                      currentStats += "+Замедление -> " + std::to_string((int)(100 - (tower.currentSlowAmount / info.fireRateUpgradeMultiplier) * 100)) + "%\n";
                 }
                 if (info.isAreaOfEffect && info.rangeUpgradeMultiplier != 1.0f) {
                     currentStats += "+Радиус AoE -> " + std::to_string((int)(tower.currentAreaOfEffectRadius * info.rangeUpgradeMultiplier)) + "\n";
                 }
                 // Show buff upgrades if applicable (Not implemented)
            } else {
                 currentStats += "\nМакс Уровень\n";
            }


             size_t start = 0; // Объявлены один раз здесь
             size_t end = 0;
            // Render stats, leaving space for the button prompt
            while (textY < gUIState.upgradeWindowRect.y + gUIState.upgradeWindowRect.h - 25 && (end = currentStats.find('\n', start)) != std::string::npos) {
                std::string line = currentStats.substr(start, end - start);
                SDL_Texture* lineTex = renderText(line, COLOR_WHITE, gFont);
                 if(lineTex) {
                    int w,h; SDL_QueryTexture(lineTex, NULL, NULL, &w, &h);
                    SDL_Rect dst = {textX, textY, std::min(w, gUIState.upgradeWindowRect.w - 20), h};
                    SDL_RenderCopy(gRenderer, lineTex, NULL, &dst);
                    SDL_DestroyTexture(lineTex);
                  }
                 textY += lineHeight;
                 start = end + 1;
            }
              // Render the last line of stats
              if (textY < gUIState.upgradeWindowRect.y + gUIState.upgradeWindowRect.h - 25 && start < currentStats.length()) {
                 std::string lastLine = currentStats.substr(start);
                 SDL_Texture* lastLineTex = renderText(lastLine, COLOR_WHITE, gFont);
                  if(lastLineTex) {
                     int w,h; SDL_QueryTexture(lastLineTex, NULL, NULL, &w, &h);
                     SDL_Rect dst = {textX, textY, std::min(w, gUIState.upgradeWindowRect.w - 20), h};
                     SDL_RenderCopy(gRenderer, lastLineTex, NULL, &dst);
                     SDL_DestroyTexture(lastLineTex);
                  }
              }


             // Render upgrade prompt (Press SPACE)
             if (tower.level < info.maxLevel) {
                  std::string upgradePrompt = "Прокачать (SPACE)";
                  bool canUpgrade = (gGameState.money >= info.upgradeCost);
                  SDL_Color promptColor = canUpgrade ? COLOR_GREEN : COLOR_RED;
                  SDL_Texture* promptTex = renderText(upgradePrompt, promptColor, gFont);
                   if(promptTex) {
                       int w,h; SDL_QueryTexture(promptTex, NULL, NULL, &w, &h);
                       // Position near bottom center of the window
                       SDL_Rect dst = {gUIState.upgradeWindowRect.x + gUIState.upgradeWindowRect.w/2 - w/2, gUIState.upgradeWindowRect.y + gUIState.upgradeWindowRect.h - h - 10, w, h};
                       SDL_RenderCopy(gRenderer, promptTex, NULL, &dst);
                       SDL_DestroyTexture(promptTex);
                   }
             }
        }
         // Highlight selected placed tower
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255); // Yellow highlight
        SDL_Rect towerHighlightRect = {(int)tower.position.x - 25, (int)tower.position.y - 25, 50, 50}; // Больше, чем сама башня
        SDL_RenderDrawRect(gRenderer, &towerHighlightRect);
    }

    // Render game stats (Money, Lives, Wave)
    if (gFont != nullptr) { // Используем основной шрифт для статов
         // Money (Top Left, below tower bar)
         std::string moneyText = "Деньги: " + std::to_string(gGameState.money);
         SDL_Texture* moneyTex = renderText(moneyText, COLOR_YELLOW, gFont);
         if(moneyTex) {
              int w,h; SDL_QueryTexture(moneyTex, NULL, NULL, &w, &h);
              SDL_Rect dst = {10, TOWER_SELECTION_BAR_HEIGHT + 10, w, h}; // Below tower bar
              SDL_RenderCopy(gRenderer, moneyTex, NULL, &dst);
              SDL_DestroyTexture(moneyTex);
         }

         // Lives (Top Left, below money)
         std::string livesText = "Жизни: " + std::to_string(gGameState.lives);
         SDL_Texture* livesTex = renderText(livesText, COLOR_RED, gFont);
          if(livesTex) {
              int w,h; SDL_QueryTexture(livesTex, NULL, NULL, &w, &h);
              SDL_Rect dst = {10, TOWER_SELECTION_BAR_HEIGHT + 10 + TTF_FontHeight(gFont) + 5, w, h}; // Below money + padding
              SDL_RenderCopy(gRenderer, livesTex, NULL, &dst);
              SDL_DestroyTexture(livesTex);
         }

         // Wave info (Bottom right) - Show "Wave: N" for numbered waves, then "Wave: Infinite (N)"
         std::string waveText;
         if (gGameState.currentWave > 0 && gGameState.currentWave <= gWaves.size()) {
             waveText = "Волна: " + std::to_string(gGameState.currentWave) + "/" + std::to_string(gWaves.size());
         } else if (gGameState.currentWave > gWaves.size()) {
             waveText = "Волна: Бесконечная (" + std::to_string(gGameState.currentWave) + ")";
         } else { // wave 0 before start
             waveText = "Волна: -";
         }

         SDL_Texture* waveTex = renderText(waveText, COLOR_WHITE, gFont);
          if(waveTex) {
              int w,h; SDL_QueryTexture(waveTex, NULL, NULL, &w, &h);
              SDL_Rect dst = {SCREEN_WIDTH - w - 10, SCREEN_HEIGHT - h - 10, w, h}; // Bottom right
              SDL_RenderCopy(gRenderer, waveTex, NULL, &dst);
              SDL_DestroyTexture(waveTex);
         }

         // Wave timer / Enemies remaining (Bottom left)
         if (!gGameState.waveInProgress && gGameState.currentWave < gWaves.size() && gGameState.currentWave > 0) {
              // Timer before next defined wave
              std::string timerText = "След. волна через: " + std::to_string((int)std::ceil(gGameState.waveTimer));
              SDL_Texture* timerTex = renderText(timerText, COLOR_WHITE, gFont);
              if(timerTex) {
                  int w,h; SDL_QueryTexture(timerTex, NULL, NULL, &w, &h);
                  SDL_Rect dst = {10, SCREEN_HEIGHT - h - 10, w, h}; // Bottom left
                  SDL_RenderCopy(gRenderer, timerTex, NULL, &dst);
                  SDL_DestroyTexture(timerTex);
              }
         } else if (!gGameState.waveInProgress && gGameState.currentWave >= gWaves.size() && gGameState.currentWave > 0) {
             // Timer before next infinite wave (after last defined wave)
              std::string timerText = "След. волна через: " + std::to_string((int)std::ceil(gGameState.waveTimer));
              SDL_Texture* timerTex = renderText(timerText, COLOR_WHITE, gFont);
              if(timerTex) {
                  int w,h; SDL_QueryTexture(timerTex, NULL, NULL, &w, &h);
                  SDL_Rect dst = {10, SCREEN_HEIGHT - h - 10, w, h}; // Bottom left
                  SDL_RenderCopy(gRenderer, timerTex, NULL, &dst);
                  SDL_DestroyTexture(timerTex);
              }
         }
         else if (!gGameState.waveInProgress && gGameState.currentWave == 0) {
             // Timer before wave 1 starts
             std::string timerText = "Начать игру через: " + std::to_string((int)std::ceil(gGameState.waveTimer));
             SDL_Texture* timerTex = renderText(timerText, COLOR_WHITE, gFont);
              if(timerTex) {
                  int w,h; SDL_QueryTexture(timerTex, NULL, NULL, &w, &h);
                  SDL_Rect dst = {10, SCREEN_HEIGHT - h - 10, w, h}; // Bottom left
                  SDL_RenderCopy(gRenderer, timerTex, NULL, &dst);
                  SDL_DestroyTexture(timerTex);
              }

         }
         else if (gGameState.waveInProgress) {
              // Show enemies remaining when wave is active
              std::string enemiesLeftText = "Врагов на поле: " + std::to_string(gGameState.activeEnemies.size());
              // Can also show enemies left to spawn from the current wave template
              // if (gGameState.currentWave > 0 && !gWaves.empty()) {
              //     int templateIndex = (gGameState.currentWave > gWaves.size()) ? (gWaves.size() - 1) : (gGameState.currentWave - 1);
              //      if (gGameState.enemiesSpawnedInWave < gWaves[templateIndex].spawns.size()) {
              //          enemiesLeftText += " (+ " + std::to_string(gWaves[templateIndex].spawns.size() - gGameState.enemiesSpawnedInWave) + " к спавну)";
              //      }
              // }


              SDL_Texture* enemiesLeftTex = renderText(enemiesLeftText, COLOR_WHITE, gFont);
               if(enemiesLeftTex) {
                   int w,h; SDL_QueryTexture(enemiesLeftTex, NULL, NULL, &w, &h);
                   SDL_Rect dst = {10, SCREEN_HEIGHT - h - 10, w, h}; // Bottom left
                   SDL_RenderCopy(gRenderer, enemiesLeftTex, NULL, &dst);
                   SDL_DestroyTexture(enemiesLeftTex);
               }
         }
    }

    // Render Pause overlay
    if (gGameState.isPaused) {
         SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 150); // Semi-transparent black
         SDL_Rect overlayRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
         SDL_RenderFillRect(gRenderer, &overlayRect);

         if (gFont != nullptr) {
              std::string pauseText = "ПАУЗА";
              SDL_Texture* pauseTex = renderText(pauseText, COLOR_WHITE, gFont); // Используем основной шрифт
               if(pauseTex) {
                   int w,h; SDL_QueryTexture(pauseTex, NULL, NULL, &w, &h);
                   SDL_Rect dst = {SCREEN_WIDTH/2 - w/2, SCREEN_HEIGHT/2 - h/2, w, h};
                   SDL_RenderCopy(gRenderer, pauseTex, NULL, &dst);
                   SDL_DestroyTexture(pauseTex);
               }
         }
    }


    // Present renderer
    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* args[]) {
    // Set C locale to avoid issues with float-to-string conversion (e.g. comma instead of dot)
    // Might need #include <locale>
    // setlocale(LC_NUMERIC, "C");


    if (!init()) {
        SDL_Log("Failed to initialize!");
        return 1;
    }

    loadGameData(); // Load game data and resources
    resetGame(); // Initialize game state

    bool quit = false;
    SDL_Event e;

    // Для расчета deltaTime
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while (!quit) {
        // Calculate deltaTime
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = currentFrameTime - lastFrameTime;
        float deltaTime = delta.count();
        lastFrameTime = currentFrameTime;

        // Prevent large delta time spikes (e.g., when dragging window, debugging)
        if (deltaTime > 0.05f) { // Capped slightly lower (20 FPS min)
            deltaTime = 0.05f;
        }


        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            handleInput(e); // Process input events
        }

        // Обновление игры происходит только если не на паузе
        if (!gGameState.isPaused) {
             update(deltaTime); // Update game state
        } else {
             // Если на паузе, все равно обновляем таймер наведения UI
             if (gUIState.hoveredTowerIndex != -1) {
                gUIState.towerHoverTimer += deltaTime;
            } else {
                gUIState.towerHoverTimer = 0.0f; // Сброс, если нет наведения
            }
        }


        render();         // Render game (рендерим всегда, даже на паузе)

        // Small delay is usually not needed with VSync (SDL_RENDERER_PRESENTVSYNC)
        // If you don't use VSync, you might add SDL_Delay(1) or similar to yield CPU
        // SDL_Delay(1);
    }

    close(); // Clean up SDL resources

    return 0;
}
