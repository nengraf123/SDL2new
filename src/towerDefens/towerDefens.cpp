#include "towerDefens.h"
#include <algorithm>
#include <cmath>
#include <iostream>

TowerDefens::TowerDefens() : lastEnemySpawn(0), enemySpawnInterval(2000), playerHealth(10), playerMoney(100),
    towerCost(50), backButton({650, 650, 120, 60}), healthText(nullptr), moneyText(nullptr),
    enemies(), towers(), projectiles(), enemyPath(), selectedTowerType(-1), previewTower({0, 0, 50, 50}),
    isPlacingTower(false), enemyTexture(nullptr), towerTexture(nullptr), ENEMY_TYPES(10), TOWER_TYPES(10),
    textColor({200, 200, 200, 255}), pathColor({80, 80, 80, 255}), enemyColor({200, 100, 100, 255}),
    towerColor({100, 100, 200, 255}), projectileColor({255, 200, 100, 255}),
    buttonColor({40, 40, 60, 255}), buttonHoverColor({60, 60, 90, 255}),
    borderColor({100, 100, 100, 255}), validPlacementColor({100, 200, 100, 150}),
    invalidPlacementColor({200, 100, 100, 150}), hoveredTower(-1) {
    enemySpeeds[0] = 2.0f; enemySpeeds[1] = 1.5f; enemySpeeds[2] = 0.8f; enemySpeeds[3] = 3.0f;
    enemySpeeds[4] = 1.0f; enemySpeeds[5] = 2.5f; enemySpeeds[6] = 0.5f; enemySpeeds[7] = 1.8f;
    enemySpeeds[8] = 2.2f; enemySpeeds[9] = 1.2f;
    enemyHealths[0] = 2; enemyHealths[1] = 5; enemyHealths[2] = 10; enemyHealths[3] = 1;
    enemyHealths[4] = 7; enemyHealths[5] = 3; enemyHealths[6] = 15; enemyHealths[7] = 4;
    enemyHealths[8] = 6; enemyHealths[9] = 8;
    towerRanges[0] = 100; towerRanges[1] = 120; towerRanges[2] = 80; towerRanges[3] = 150;
    towerRanges[4] = 90; towerRanges[5] = 110; towerRanges[6] = 130; towerRanges[7] = 100;
    towerRanges[8] = 140; towerRanges[9] = 95;
    towerDamages[0] = 1; towerDamages[1] = 2; towerDamages[2] = 1; towerDamages[3] = 3;
    towerDamages[4] = 1; towerDamages[5] = 2; towerDamages[6] = 4; towerDamages[7] = 1;
    towerDamages[8] = 3; towerDamages[9] = 2;
    towerFireRates[0] = 1.0f; towerFireRates[1] = 0.5f; towerFireRates[2] = 2.0f; towerFireRates[3] = 0.8f;
    towerFireRates[4] = 1.5f; towerFireRates[5] = 1.2f; towerFireRates[6] = 0.6f; towerFireRates[7] = 2.5f;
    towerFireRates[8] = 0.9f; towerFireRates[9] = 1.8f;
    towerNames[0] = "Базовая"; towerNames[1] = "Пушка"; towerNames[2] = "Лазер"; towerNames[3] = "Снайпер";
    towerNames[4] = "Медленная"; towerNames[5] = "Ракета"; towerNames[6] = "Тяжёлая"; towerNames[7] = "Миниган";
    towerNames[8] = "Тесла"; towerNames[9] = "Плазма";
}

TowerDefens::~TowerDefens() {
    if (healthText) SDL_DestroyTexture(healthText);
    if (moneyText) SDL_DestroyTexture(moneyText);
    if (enemyTexture) SDL_DestroyTexture(enemyTexture);
    if (towerTexture) SDL_DestroyTexture(towerTexture);
}

void TowerDefens::init() {
    enemyPath = {{0, 100}, {200, 100}, {200, 300}, {400, 300}, {400, 500}, {600, 500}, {600, 700}, {800, 700}};
    for (int i = 0; i < TOWER_TYPES; ++i) {
        towerCards.push_back({10 + i * 60, 10, 50, 50});
    }
    SDL_Surface* enemySurface = IMG_Load("img/123.png");
    if (enemySurface) {
        enemyTexture = SDL_CreateTextureFromSurface(nullptr, enemySurface);
        SDL_FreeSurface(enemySurface);
        std::cerr << "Текстура врага (img/123.png) загружена успешно" << std::endl;
    } else {
        std::cerr << "Ошибка загрузки текстуры врага: " << IMG_GetError() << std::endl;
    }
    SDL_Surface* towerSurface = IMG_Load("img/123.png");
    if (towerSurface) {
        towerTexture = SDL_CreateTextureFromSurface(nullptr, towerSurface);
        SDL_FreeSurface(towerSurface);
        std::cerr << "Текстура башни (img/123.png) загружена успешно" << std::endl;
    } else {
        std::cerr << "Ошибка загрузки текстуры башни: " << IMG_GetError() << std::endl;
    }
}

void TowerDefens::handleEvents(SDL_Event& event, int mx, int my, int& scene) {
    bool mouseOnBack = isMouseOnButton(mx, my, backButton);
    std::vector<bool> mouseOnCard(TOWER_TYPES, false);
    for (int i = 0; i < TOWER_TYPES; ++i) {
        mouseOnCard[i] = isMouseOnButton(mx, my, towerCards[i]);
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        if (mouseOnBack) {
            scene = -1; // Вернуться в главное меню
        }
        for (int i = 0; i < TOWER_TYPES; ++i) {
            if (mouseOnCard[i] && playerMoney >= towerCost) {
                selectedTowerType = i;
                isPlacingTower = true;
                break;
            }
        }
        if (isPlacingTower && isValidPlacement(mx - 25, my - 25, towers)) {
            towers.push_back({mx - 25, my - 25, towerRanges[selectedTowerType], towerDamages[selectedTowerType],
                towerFireRates[selectedTowerType], 0, true, selectedTowerType});
            playerMoney -= towerCost;
            isPlacingTower = false;
            selectedTowerType = -1;
        }
    } else if (event.type == SDL_MOUSEMOTION) {
        if (isPlacingTower) {
            previewTower.x = mx - 25;
            previewTower.y = my - 25;
        }
        hoveredTower = -1;
        for (size_t i = 0; i < towers.size(); ++i) {
            if (towers[i].active && isMouseOnButton(mx, my, {towers[i].x, towers[i].y, 50, 50})) {
                hoveredTower = i;
                break;
            }
        }
    }
}

void TowerDefens::update(SDL_Renderer* renderer, TTF_Font* font) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastEnemySpawn > enemySpawnInterval) {
        int type = rand() % ENEMY_TYPES;
        enemies.push_back({static_cast<float>(enemyPath[0].x), static_cast<float>(enemyPath[0].y),
            enemySpeeds[type], enemyHealths[type], 0, true, type});
        lastEnemySpawn = currentTime;
    }
    for (auto& enemy : enemies) {
        if (!enemy.active) continue;
        if (enemy.pathIndex < enemyPath.size() - 1) {
            float dx = enemyPath[enemy.pathIndex + 1].x - enemy.x;
            float dy = enemyPath[enemy.pathIndex + 1].y - enemy.y;
            float distance = std::sqrt(dx * dx + dy * dy);
            if (distance < enemy.speed) {
                enemy.pathIndex++;
                if (enemy.pathIndex >= enemyPath.size()) {
                    enemy.active = false;
                    playerHealth--;
                    continue;
                }
                enemy.x = enemyPath[enemy.pathIndex].x;
                enemy.y = enemyPath[enemy.pathIndex].y;
            } else {
                float vx = (dx / distance) * enemy.speed;
                float vy = (dy / distance) * enemy.speed;
                enemy.x += vx;
                enemy.y += vy;
            }
        }
    }
    for (auto& tower : towers) {
        if (!tower.active) continue;
        if (currentTime - tower.lastShot > (1000.0f / tower.fireRate)) {
            for (auto& enemy : enemies) {
                if (enemy.active && inRange(tower, enemy.x, enemy.y)) {
                    projectiles.push_back({static_cast<float>(tower.x + 25), static_cast<float>(tower.y + 25),
                        5.0f, tower.damage, &enemy, true});
                    tower.lastShot = currentTime;
                    break;
                }
            }
        }
    }
    for (auto& projectile : projectiles) {
        if (!projectile.active || !projectile.target->active) {
            projectile.active = false;
            continue;
        }
        float dx = projectile.target->x - projectile.x;
        float dy = projectile.target->y - projectile.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        if (distance < projectile.speed) {
            projectile.target->health -= projectile.damage;
            if (projectile.target->health <= 0) {
                projectile.target->active = false;
                playerMoney += 10;
            }
            projectile.active = false;
        } else {
            float vx = (dx / distance) * projectile.speed;
            float vy = (dy / distance) * projectile.speed;
            projectile.x += vx;
            projectile.y += vy;
        }
    }
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) { return !e.active; }), enemies.end());
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& p) { return !p.active; }), projectiles.end());
    if (healthText) SDL_DestroyTexture(healthText);
    healthText = createTextTexture(renderer, font, "Здоровье: " + std::to_string(playerHealth), textColor);
    if (moneyText) SDL_DestroyTexture(moneyText);
    moneyText = createTextTexture(renderer, font, "Деньги: " + std::to_string(playerMoney), textColor);
}

void TowerDefens::render(SDL_Renderer* renderer, TTF_Font* font, int mx, int my) {
    bool mouseOnBack = isMouseOnButton(mx, my, backButton);
    std::vector<bool> mouseOnCard(TOWER_TYPES, false);
    for (int i = 0; i < TOWER_TYPES; ++i) {
        mouseOnCard[i] = isMouseOnButton(mx, my, towerCards[i]);
    }

    SDL_SetRenderDrawColor(renderer, pathColor.r, pathColor.g, pathColor.b, pathColor.a);
    for (size_t i = 0; i < enemyPath.size() - 1; ++i) {
        SDL_RenderDrawLine(renderer, enemyPath[i].x, enemyPath[i].y, enemyPath[i + 1].x, enemyPath[i + 1].y);
    }
    for (const auto& enemy : enemies) {
        if (!enemy.active) continue;
        if (enemyTexture) {
            SDL_Rect enemyRect = {static_cast<int>(enemy.x - 15), static_cast<int>(enemy.y - 15), 30, 30};
            SDL_RenderCopy(renderer, enemyTexture, nullptr, &enemyRect);
        } else {
            SDL_SetRenderDrawColor(renderer, enemyColor.r, enemyColor.g, enemyColor.b, enemyColor.a);
            renderCircleOutline(renderer, static_cast<int>(enemy.x), static_cast<int>(enemy.y), 15);
        }
    }
    for (size_t i = 0; i < towers.size(); ++i) {
        const auto& tower = towers[i];
        if (!tower.active) continue;
        if (towerTexture) {
            SDL_Rect towerRect = {tower.x, tower.y, 50, 50};
            SDL_RenderCopy(renderer, towerTexture, nullptr, &towerRect);
        } else {
            SDL_SetRenderDrawColor(renderer, towerColor.r, towerColor.g, towerColor.b, towerColor.a);
            SDL_Rect towerRect = {tower.x, tower.y, 50, 50};
            SDL_RenderFillRect(renderer, &towerRect);
        }
        if (static_cast<int>(i) == hoveredTower) {
            SDL_SetRenderDrawColor(renderer, towerColor.r, towerColor.g, towerColor.b, 100);
            renderCircleOutline(renderer, tower.x + 25, tower.y + 25, tower.range);
        }
    }
    for (const auto& projectile : projectiles) {
        if (!projectile.active) continue;
        SDL_SetRenderDrawColor(renderer, projectileColor.r, projectileColor.g, projectileColor.b, projectileColor.a);
        renderCircleOutline(renderer, static_cast<int>(projectile.x), static_cast<int>(projectile.y), 5);
    }
    for (int i = 0; i < TOWER_TYPES; ++i) {
        SDL_SetRenderDrawColor(renderer, mouseOnCard[i] ? buttonHoverColor.r : buttonColor.r,
            mouseOnCard[i] ? buttonHoverColor.g : buttonColor.g,
            mouseOnCard[i] ? buttonHoverColor.b : buttonHoverColor.b, 255);
        SDL_Rect scaledCard = {towerCards[i].x - (mouseOnCard[i] ? 5 : 0), towerCards[i].y - (mouseOnCard[i] ? 5 : 0),
            towerCards[i].w + (mouseOnCard[i] ? 10 : 0), towerCards[i].h + (mouseOnCard[i] ? 10 : 0)};
        SDL_RenderFillRect(renderer, &scaledCard);
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_RenderDrawRect(renderer, &scaledCard);
        SDL_Texture* cardText = createTextTexture(renderer, font, towerNames[i], textColor, 40);
        if (cardText) {
            int tw, th;
            SDL_QueryTexture(cardText, nullptr, nullptr, &tw, &th);
            SDL_Rect textRect = {scaledCard.x + (scaledCard.w - tw) / 2, scaledCard.y + (scaledCard.h - th) / 2, tw, th};
            SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, tw, th};
            SDL_SetTextureColorMod(cardText, 50, 50, 50);
            SDL_SetTextureAlphaMod(cardText, 100);
            SDL_RenderCopy(renderer, cardText, nullptr, &shadowRect);
            SDL_SetTextureColorMod(cardText, textColor.r, textColor.g, textColor.b);
            SDL_SetTextureAlphaMod(cardText, 255);
            SDL_RenderCopy(renderer, cardText, nullptr, &textRect);
            SDL_DestroyTexture(cardText);
        }
    }
    if (isPlacingTower) {
        bool valid = isValidPlacement(previewTower.x, previewTower.y, towers);
        SDL_SetRenderDrawColor(renderer, valid ? validPlacementColor.r : invalidPlacementColor.r,
            valid ? validPlacementColor.g : invalidPlacementColor.g,
            valid ? validPlacementColor.b : invalidPlacementColor.b,
            valid ? validPlacementColor.a : invalidPlacementColor.a);
        SDL_RenderFillRect(renderer, &previewTower);
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_RenderDrawRect(renderer, &previewTower);
        SDL_SetRenderDrawColor(renderer, towerColor.r, towerColor.g, towerColor.b, 100);
        renderCircleOutline(renderer, previewTower.x + 25, previewTower.y + 25, towerRanges[selectedTowerType]);
    }
    if (healthText) {
        int tw, th;
        SDL_QueryTexture(healthText, nullptr, nullptr, &tw, &th);
        SDL_Rect textRect = {10, 70, tw, th};
        SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, tw, th};
        SDL_SetTextureColorMod(healthText, 50, 50, 50);
        SDL_SetTextureAlphaMod(healthText, 100);
        SDL_RenderCopy(renderer, healthText, nullptr, &shadowRect);
        SDL_SetTextureColorMod(healthText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(healthText, 255);
        SDL_RenderCopy(renderer, healthText, nullptr, &textRect);
    }
    if (moneyText) {
        int tw, th;
        SDL_QueryTexture(moneyText, nullptr, nullptr, &tw, &th);
        SDL_Rect textRect = {10, 100, tw, th};
        SDL_Rect shadowRect = {textRect.x + 2, textRect.y + 2, tw, th};
        SDL_SetTextureColorMod(moneyText, 50, 50, 50);
        SDL_SetTextureAlphaMod(moneyText, 100);
        SDL_RenderCopy(renderer, moneyText, nullptr, &shadowRect);
        SDL_SetTextureColorMod(moneyText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(moneyText, 255);
        SDL_RenderCopy(renderer, moneyText, nullptr, &textRect);
    }
    SDL_SetRenderDrawColor(renderer, mouseOnBack ? buttonHoverColor.r : buttonColor.r,
        mouseOnBack ? buttonHoverColor.g : buttonColor.g,
        mouseOnBack ? buttonHoverColor.b : buttonHoverColor.b, 255);
    SDL_Rect scaledBackButton = {backButton.x - (mouseOnBack ? 5 : 0), backButton.y - (mouseOnBack ? 5 : 0),
        backButton.w + (mouseOnBack ? 10 : 0), backButton.h + (mouseOnBack ? 10 : 0)};
    SDL_RenderFillRect(renderer, &scaledBackButton);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &scaledBackButton);
    SDL_Texture* backText = createTextTexture(renderer, font, "Назад", textColor, 100);
    if (backText) {
        int tw, th;
        SDL_QueryTexture(backText, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {scaledBackButton.x + (scaledBackButton.w - tw) / 2, scaledBackButton.y + (scaledBackButton.h - th) / 2, tw, th};
        SDL_Rect shadowTr = {tr.x + 2, tr.y + 2, tw, th};
        SDL_SetTextureColorMod(backText, 50, 50, 50);
        SDL_SetTextureAlphaMod(backText, 100);
        SDL_RenderCopy(renderer, backText, nullptr, &shadowTr);
        SDL_SetTextureColorMod(backText, textColor.r, textColor.g, textColor.b);
        SDL_SetTextureAlphaMod(backText, 255);
        SDL_RenderCopy(renderer, backText, nullptr, &tr);
        SDL_DestroyTexture(backText);
    }
}

bool TowerDefens::isMouseOnButton(int mx, int my, const SDL_Rect& button) {
    SDL_Rect cursor = {mx, my, 2, 2};
    return SDL_HasIntersection(&cursor, &button);
}

bool TowerDefens::inRange(Tower& tower, float px, float py) {
    float dx = (tower.x + 25) - px;
    float dy = (tower.y + 25) - py;
    return std::sqrt(dx * dx + dy * dy) <= tower.range;
}

bool TowerDefens::isValidPlacement(int x, int y, const std::vector<Tower>& towers, int towerSize) {
    SDL_Rect newTower = {x, y, towerSize, towerSize};
    for (const auto& tower : towers) {
        if (!tower.active) continue;
        SDL_Rect existingTower = {tower.x, tower.y, towerSize, towerSize};
        if (SDL_HasIntersection(&newTower, &existingTower)) {
            return false;
        }
    }
    for (size_t i = 0; i < enemyPath.size() - 1; ++i) {
        SDL_Rect pathSegment = {std::min(enemyPath[i].x, enemyPath[i + 1].x),
            std::min(enemyPath[i].y, enemyPath[i + 1].y),
            std::abs(enemyPath[i + 1].x - enemyPath[i].x) + 30,
            std::abs(enemyPath[i + 1].y - enemyPath[i].y) + 30};
        if (SDL_HasIntersection(&newTower, &pathSegment)) {
            return false;
        }
    }
    return x >= 0 && y >= 0 && x + towerSize <= 800 && y + towerSize <= 800;
}

void TowerDefens::renderCircleOutline(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    const float PI = 3.1415926535f;
    int prevX = centerX + radius;
    int prevY = centerY;
    for (float angle = 0; angle <= 2 * PI; angle += 0.1f) {
        int x = centerX + static_cast<int>(radius * cos(angle));
        int y = centerY + static_cast<int>(radius * sin(angle));
        SDL_RenderDrawLine(renderer, prevX, prevY, x, y);
        prevX = x;
        prevY = y;
    }
}
